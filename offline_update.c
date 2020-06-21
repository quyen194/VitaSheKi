/*
  VitaShell
  Copyright (C) 2015-2018, TheFloW

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "main.h"
#include "io_process.h"
#include "package_installer.h"
#include "archive.h"
#include "file.h"
#include "message_dialog.h"
#include "language.h"
#include "utils.h"
#include "sfo.h"
#include "offline_update.h"

char offlineUpdatePackagePath[MAX_PATH_LENGTH];

int getFileNameLowCase(const char * src, char * des) {
  char srcLow[MAX_PATH_LENGTH];

  // clone
  strcpy(srcLow, src);

  for (;;) {
    char * sub = strstr(srcLow, "\\");
    if (!sub) sub = strstr(srcLow, "/");
    if (!sub) break;
    strcpy(srcLow, &sub[1]);
  }

  for (int i = 0; srcLow[i]; i++) {
    srcLow[i] = tolower(srcLow[i]);
  }

  strcpy(des, srcLow);
  return strlen(des);
}

int isVitaSheKiPackage(const char *file) {
  char path[MAX_PATH_LENGTH];

  if (!getFileNameLowCase(file, path)) {
    // initMessageDialog(SCE_MSG_DIALOG_BUTTON_TYPE_OK, "Failed!!! getFileNameLowCase.");
    // setDialogStep(DIALOG_STEP_ERROR);
    return 0;
  }

  if (!strcasestr(path, "vitasheki")) {
    // initMessageDialog(SCE_MSG_DIALOG_BUTTON_TYPE_OK, "package not vitasheki: %s", path);
    // setDialogStep(DIALOG_STEP_ERROR);
    return 0;
  }

  // Recursively clean up pkg directory
  removePath(PACKAGE_DIR, NULL);

  // Get src paths info
  uint64_t size = 0;
  getPathInfo(file, &size, NULL, NULL, NULL);

  // Check memory card free space
  if (checkMemoryCardFreeSpace(PACKAGE_DIR, size)) {
    return 0;
  }

  // Open archive
  archiveClearPassword();
  int res = archiveOpen(file);
  if (res < 0) {
    return 0;
  }

  // Src path
  char src_path[MAX_PATH_LENGTH];
  strcpy(src_path, file);
  addEndSlash(src_path);

  // Extract process
  res = extractArchivePath(src_path, PACKAGE_DIR "/", NULL);
  if (res < 0) {
    return 0;
  }

  // Close archive
  res = archiveClose();
  if (res < 0) {
    return 0;
  }

  // Make head.bin
  res = makeHeadBin();
  if (res < 0) {
    return 0;
  }

  // Read param.sfo
  void *sfo_buffer = NULL;
  int sfo_size = allocateReadFile(PACKAGE_DIR "/sce_sys/param.sfo", &sfo_buffer);
  if (sfo_size < 0) {
    // initMessageDialog(SCE_MSG_DIALOG_BUTTON_TYPE_OK, "Read param.sfo failed");
    // setDialogStep(DIALOG_STEP_ERROR);
    return 0;
  }

  // Get titleid
  char titleid[12];
  getSfoString(sfo_buffer, "TITLE_ID", titleid, sizeof(titleid));

  // Recursively clean up pkg directory
  removePath(PACKAGE_DIR, NULL);

  // Check update's conditions
  if (strcmp(titleid, VITASHELL_TITLEID)) {
    // initMessageDialog(SCE_MSG_DIALOG_BUTTON_TYPE_OK, "package not vitasheki: %s", titleid);
    // setDialogStep(DIALOG_STEP_ERROR);
    return 0;
  }

  return 1;
}

int updateOfflineVerify(const char *file) {
  // check is VitaSheki installer
  if (!isVitaSheKiPackage(file)) {
    return 0;
  }

  strcpy(offlineUpdatePackagePath, file);

  // Update question
  initMessageDialog(SCE_MSG_DIALOG_BUTTON_TYPE_YESNO, language_container[UPDATE_OFFLINE_QUESTION]);
  setDialogStep(DIALOG_STEP_UPDATE_OFFLINE_QUESTION);

  return 1;
}

int updateOffline(SceSize args, void *argp) {
  initMessageDialog(MESSAGE_DIALOG_PROGRESS_BAR, language_container[PREPARING]);
  setDialogStep(DIALOG_STEP_INSTALLING);

  // Set progress to 0%
  sceMsgDialogProgressBarSetValue(SCE_MSG_DIALOG_PROGRESSBAR_TARGET_BAR_DEFAULT, 0);
  sceKernelDelayThread(DIALOG_WAIT); // Needed to see the percentage

  // Get src paths info
  uint64_t size = 0;
  getPathInfo(offlineUpdatePackagePath, &size, NULL, NULL, NULL);

  // Update thread
  SceUID thid = createStartUpdateThread(size, 1);

  // Copying process
  uint64_t value = 0;

  FileProcessParam param;
  param.value = &value;
  param.max = size;
  param.SetProgress = SetProgress;
  param.cancelHandler = cancelHandler;

  int res = copyFile(offlineUpdatePackagePath, VITASHELL_UPDATE_FILE, &param);
  if (res <= 0) {
    closeWaitDialog();
    if (res < 0) {
      errorDialog(res);
    }
    return 0;
  }

  // Set progress to 100%
  sceMsgDialogProgressBarSetValue(SCE_MSG_DIALOG_PROGRESSBAR_TARGET_BAR_DEFAULT, 100);
  sceKernelDelayThread(COUNTUP_WAIT);

  if (thid >= 0) {
    sceKernelWaitThreadEnd(thid, NULL, NULL);
  }

  closeWaitDialog();
  initMessageDialog(MESSAGE_DIALOG_PROGRESS_BAR, language_container[INSTALLING]);
  setDialogStep(DIALOG_STEP_EXTRACTING);

  thid = sceKernelCreateThread("update_extract_thread", (SceKernelThreadEntry)update_extract_thread, 0x40, 0x100000, 0, 0, NULL);
  if (thid >= 0)
    sceKernelStartThread(thid, 0, NULL);

  return sceKernelExitDeleteThread(0);
}
