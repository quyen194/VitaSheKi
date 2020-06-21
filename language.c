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
#include "config.h"
#include "language.h"

INCLUDE_EXTERN_RESOURCE(english_us_txt);

static char *lang[] = {
  "japanese",
  "english_us",
  "french",
  "spanish",
  "german",
  "italian",
  "dutch",
  "portuguese",
  "russian",
  "korean",
  "chinese_t",
  "chinese_s",
  "finnish",
  "swedish",
  "danish",
  "norwegian",
  "polish",
  "portuguese_br",
  "turkish"
};

char *language_container[LANGUAGE_CONTAINER_SIZE] = {0};

void freeLanguageContainer() {
  int i;
  for (i = 0; i < LANGUAGE_CONTAINER_SIZE; i++) {
    if (language_container[i]) {
      free(language_container[i]);
      language_container[i] = NULL;
    }
  }
}

void loadLanguage(int id) {
  freeLanguageContainer();

  #define LANGUAGE_ENTRY(name) { #name, CONFIG_TYPE_STRING, (void *)&language_container[name] }
  ConfigEntry language_entries[] = {
    // General strings
    LANGUAGE_ENTRY(ERROR),
    LANGUAGE_ENTRY(OK),
    LANGUAGE_ENTRY(YES),
    LANGUAGE_ENTRY(NO),
    LANGUAGE_ENTRY(CANCEL),
    LANGUAGE_ENTRY(ON),
    LANGUAGE_ENTRY(OFF),
    LANGUAGE_ENTRY(FILE_),
    LANGUAGE_ENTRY(FOLDER),

    // Progress strings
    LANGUAGE_ENTRY(MOVING),
    LANGUAGE_ENTRY(COPYING),
    LANGUAGE_ENTRY(DELETING),
    LANGUAGE_ENTRY(EXPORTING),
    LANGUAGE_ENTRY(PREPARING),
    LANGUAGE_ENTRY(INSTALLING),
    LANGUAGE_ENTRY(INSTALLED),
    LANGUAGE_ENTRY(DOWNLOADING),
    LANGUAGE_ENTRY(EXTRACTING),
    LANGUAGE_ENTRY(COMPRESSING),
    LANGUAGE_ENTRY(HASHING),
    LANGUAGE_ENTRY(REFRESHING),
    LANGUAGE_ENTRY(SENDING),
    LANGUAGE_ENTRY(RECEIVING),

    // Audio player strings
    LANGUAGE_ENTRY(TITLE),
    LANGUAGE_ENTRY(ALBUM),
    LANGUAGE_ENTRY(ARTIST),
    LANGUAGE_ENTRY(GENRE),
    LANGUAGE_ENTRY(YEAR),

    // Hex editor strings
    LANGUAGE_ENTRY(OFFSET),
    LANGUAGE_ENTRY(OPEN_HEX_EDITOR),

    // Text editor strings
    LANGUAGE_ENTRY(EDIT_LINE),
    LANGUAGE_ENTRY(ENTER_SEARCH_TERM),

    // Context menu strings
    LANGUAGE_ENTRY(REFRESH_LIVEAREA),
    LANGUAGE_ENTRY(REFRESH_LICENSE_DB),
    LANGUAGE_ENTRY(MOUNT_UMA0),
    LANGUAGE_ENTRY(MOUNT_IMC0),
    LANGUAGE_ENTRY(MOUNT_XMC0),
    LANGUAGE_ENTRY(UMOUNT_UMA0),
    LANGUAGE_ENTRY(UMOUNT_IMC0),
    LANGUAGE_ENTRY(UMOUNT_XMC0),
    LANGUAGE_ENTRY(MOUNT_USB_UX0),
    LANGUAGE_ENTRY(UMOUNT_USB_UX0),
    LANGUAGE_ENTRY(MOUNT_GAMECARD_UX0),
    LANGUAGE_ENTRY(UMOUNT_GAMECARD_UX0),
    LANGUAGE_ENTRY(SORT_BY),
    LANGUAGE_ENTRY(BY_NAME),
    LANGUAGE_ENTRY(BY_SIZE),
    LANGUAGE_ENTRY(BY_DATE),
    LANGUAGE_ENTRY(MARK_ALL),
    LANGUAGE_ENTRY(UNMARK_ALL),
    LANGUAGE_ENTRY(MOVE),
    LANGUAGE_ENTRY(COPY),
    LANGUAGE_ENTRY(PASTE),
    LANGUAGE_ENTRY(DELETE),
    LANGUAGE_ENTRY(RENAME),
    LANGUAGE_ENTRY(NEW),
    LANGUAGE_ENTRY(NEW_FILE),
    LANGUAGE_ENTRY(NEW_FOLDER),
    LANGUAGE_ENTRY(PROPERTIES),
    LANGUAGE_ENTRY(SEND),
    LANGUAGE_ENTRY(RECEIVE),
    LANGUAGE_ENTRY(MORE),
    LANGUAGE_ENTRY(BOOKMARKS),
    LANGUAGE_ENTRY(ADHOC_TRANSFER),
    LANGUAGE_ENTRY(BOOKMARKS_SHOW),
    LANGUAGE_ENTRY(BOOKMARKS_NEW),
    LANGUAGE_ENTRY(RECENT_FILES_SHOW),
    LANGUAGE_ENTRY(COMPRESS),
    LANGUAGE_ENTRY(INSTALL_ALL),
    LANGUAGE_ENTRY(INSTALL_MARKED),
    LANGUAGE_ENTRY(INSTALL_FOLDER),
    LANGUAGE_ENTRY(CALCULATE_SHA1),
    LANGUAGE_ENTRY(OPEN_DECRYPTED),
    LANGUAGE_ENTRY(EXPORT_MEDIA),
    LANGUAGE_ENTRY(CUT),
    LANGUAGE_ENTRY(INSERT_EMPTY_LINE),
    LANGUAGE_ENTRY(SEARCH),

    // File browser properties strings
    LANGUAGE_ENTRY(PROPERTY_NAME),
    LANGUAGE_ENTRY(PROPERTY_TYPE),
    LANGUAGE_ENTRY(PROPERTY_FSELF_MODE),
    LANGUAGE_ENTRY(PROPERTY_SIZE),
    LANGUAGE_ENTRY(PROPERTY_COMPRESSED_SIZE),
    LANGUAGE_ENTRY(PROPERTY_CONTAINS),
    LANGUAGE_ENTRY(PROPERTY_CONTAINS_FILES_FOLDERS),
    LANGUAGE_ENTRY(PROPERTY_CREATION_DATE),
    LANGUAGE_ENTRY(PROPERTY_MODFICATION_DATE),
    LANGUAGE_ENTRY(PROPERTY_TYPE_ARCHIVE),
    LANGUAGE_ENTRY(PROPERTY_TYPE_BMP),
    LANGUAGE_ENTRY(PROPERTY_TYPE_INI),
    LANGUAGE_ENTRY(PROPERTY_TYPE_JPEG),
    LANGUAGE_ENTRY(PROPERTY_TYPE_MP3),
    LANGUAGE_ENTRY(PROPERTY_TYPE_OGG),
    LANGUAGE_ENTRY(PROPERTY_TYPE_PNG),
    LANGUAGE_ENTRY(PROPERTY_TYPE_SFO),
    LANGUAGE_ENTRY(PROPERTY_TYPE_TXT),
    LANGUAGE_ENTRY(PROPERTY_TYPE_VPK),
    LANGUAGE_ENTRY(PROPERTY_TYPE_XML),
    LANGUAGE_ENTRY(PROPERTY_TYPE_FSELF),
    LANGUAGE_ENTRY(PROPERTY_FSELF_MODE_SAFE),
    LANGUAGE_ENTRY(PROPERTY_FSELF_MODE_UNSAFE),
    LANGUAGE_ENTRY(PROPERTY_FSELF_MODE_SCE),

    // File browser strings
    LANGUAGE_ENTRY(REFRESHED),
    LANGUAGE_ENTRY(COPIED_FILE),
    LANGUAGE_ENTRY(COPIED_FOLDER),
    LANGUAGE_ENTRY(COPIED_FILES_FOLDERS),
    LANGUAGE_ENTRY(IMPORTED_LICENSES),

    // Dialog questions
    LANGUAGE_ENTRY(DELETE_FILE_QUESTION),
    LANGUAGE_ENTRY(DELETE_FOLDER_QUESTION),
    LANGUAGE_ENTRY(DELETE_FILES_FOLDERS_QUESTION),
    LANGUAGE_ENTRY(EXPORT_FILE_QUESTION),
    LANGUAGE_ENTRY(EXPORT_FOLDER_QUESTION),
    LANGUAGE_ENTRY(EXPORT_FILES_FOLDERS_QUESTION),
    LANGUAGE_ENTRY(EXPORT_NO_MEDIA),
    LANGUAGE_ENTRY(EXPORT_SONGS_INFO),
    LANGUAGE_ENTRY(EXPORT_VIDEOS_INFO),
    LANGUAGE_ENTRY(EXPORT_PICTURES_INFO),
    LANGUAGE_ENTRY(EXPORT_SONGS_VIDEOS_INFO),
    LANGUAGE_ENTRY(EXPORT_SONGS_PICTURES_INFO),
    LANGUAGE_ENTRY(EXPORT_VIDEOS_PICTURES_INFO),
    LANGUAGE_ENTRY(EXPORT_SONGS_VIDEOS_PICTURES_INFO),
    LANGUAGE_ENTRY(INSTALL_ALL_QUESTION),
    LANGUAGE_ENTRY(INSTALL_MARKED_QUESTION),
    LANGUAGE_ENTRY(INSTALL_FOLDER_QUESTION),
    LANGUAGE_ENTRY(INSTALL_QUESTION),
    LANGUAGE_ENTRY(INSTALL_WARNING),
    LANGUAGE_ENTRY(INSTALL_BRICK_WARNING),
    LANGUAGE_ENTRY(HASH_FILE_QUESTION),
    LANGUAGE_ENTRY(SAVE_MODIFICATIONS),
    LANGUAGE_ENTRY(REFRESH_LIVEAREA_QUESTION),
    LANGUAGE_ENTRY(REFRESH_LICENSE_DB_QUESTION),

    // HENkaku settings strings
    LANGUAGE_ENTRY(HENKAKU_SETTINGS),
    LANGUAGE_ENTRY(HENKAKU_ENABLE_PSN_SPOOFING),
    LANGUAGE_ENTRY(HENKAKU_ENABLE_UNSAFE_HOMEBREW),
    LANGUAGE_ENTRY(HENKAKU_ENABLE_VERSION_SPOOFING),
    LANGUAGE_ENTRY(HENKAKU_SPOOFED_VERSION),
    LANGUAGE_ENTRY(HENKAKU_RESTORE_DEFAULT_SETTINGS),
    LANGUAGE_ENTRY(HENKAKU_RELOAD_CONFIG),
    LANGUAGE_ENTRY(HENKAKU_RESTORE_DEFAULT_MESSAGE),
    LANGUAGE_ENTRY(HENKAKU_RELOAD_CONFIG_MESSAGE),
    LANGUAGE_ENTRY(HENKAKU_UNSAFE_HOMEBREW_MESSAGE),

    // VitaShell settings
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_MAIN),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_LANGUAGE),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_THEME),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_USBDEVICE),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_SELECT_BUTTON),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_NO_AUTO_UPDATE),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_WARNING_MESSAGE),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_DISABLE_SYSTEM_SLEEP),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_INSTALL_TYPE),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_RESTART_SHELL),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_POWER),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_REBOOT),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_POWEROFF),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_STANDBY),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_USB_MEMORY_CARD),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_USB_GAME_CARD),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_USB_SD2VITA),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_USB_PSVSD),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_SELECT_BUTTON_USB),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_SELECT_BUTTON_FTP),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_INSTALL_REPLACE),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_INSTALL_UPDATE),

    // USB strings
    LANGUAGE_ENTRY(USB_CONNECTED),
    LANGUAGE_ENTRY(USB_UX0_MOUNTED),
    LANGUAGE_ENTRY(USB_UX0_UMOUNTED),
    LANGUAGE_ENTRY(GAMECARD_UX0_MOUNTED),
    LANGUAGE_ENTRY(GAMECARD_UX0_UMOUNTED),
    LANGUAGE_ENTRY(USB_NOT_CONNECTED),
    LANGUAGE_ENTRY(USB_CONNECTION_NOT_AVAILABLE),
    LANGUAGE_ENTRY(USB_WAIT_ATTACH),

    // QR strings
    LANGUAGE_ENTRY(QR_SCANNING),
    LANGUAGE_ENTRY(QR_OPEN_WEBSITE),
    LANGUAGE_ENTRY(QR_SHOW_CONTENTS),
    LANGUAGE_ENTRY(QR_CONFIRM_INSTALL),
    LANGUAGE_ENTRY(QR_CONFIRM_DOWNLOAD),
    
    // Adhoc strings
    LANGUAGE_ENTRY(ADHOC_RECEIVE_SEARCHING_PSVITA),
    LANGUAGE_ENTRY(ADHOC_SELECT_PSVITA),
    LANGUAGE_ENTRY(ADHOC_RECEIVE_QUESTION),
    LANGUAGE_ENTRY(ADHOC_CLIENT_DECLINED),
    
    // Others
    LANGUAGE_ENTRY(UMA0_MOUNTED),
    LANGUAGE_ENTRY(IMC0_MOUNTED),
    LANGUAGE_ENTRY(XMC0_MOUNTED),
    LANGUAGE_ENTRY(UMA0_UMOUNTED),
    LANGUAGE_ENTRY(IMC0_UMOUNTED),
    LANGUAGE_ENTRY(XMC0_UMOUNTED),
    LANGUAGE_ENTRY(SAFE_MODE),
    LANGUAGE_ENTRY(UNSAFE_MODE),
    LANGUAGE_ENTRY(PLEASE_WAIT),
    LANGUAGE_ENTRY(MEMORY_CARD_NOT_FOUND),
    LANGUAGE_ENTRY(GAME_CARD_NOT_FOUND),
    LANGUAGE_ENTRY(MICROSD_NOT_FOUND),
    LANGUAGE_ENTRY(NO_SPACE_ERROR),
    LANGUAGE_ENTRY(EXTENDED_PERMISSIONS_REQUIRED),
    LANGUAGE_ENTRY(WIFI_ERROR),
    LANGUAGE_ENTRY(FTP_SERVER),
    LANGUAGE_ENTRY(UPDATE_QUESTION),
    LANGUAGE_ENTRY(UPDATE_OFFLINE_QUESTION),
    LANGUAGE_ENTRY(ARCHIVE_NAME),
    LANGUAGE_ENTRY(COMPRESSION_LEVEL),
    LANGUAGE_ENTRY(ENTER_PASSWORD),
    LANGUAGE_ENTRY(BOOKMARK_CREATED)
  };

  // Load default config file
  readConfigBuffer(&_binary_resources_english_us_txt_start, (int)&_binary_resources_english_us_txt_size,
                   language_entries, sizeof(language_entries) / sizeof(ConfigEntry));

  // Load custom config file
  if (use_custom_config) {
    if (id >= 0 && id < (sizeof(lang) / sizeof(char *))) {
      char path[MAX_PATH_LENGTH];
      snprintf(path, MAX_PATH_LENGTH, "ux0:" VITA_APP_NAME "/language/%s.txt", lang[id]);
      readConfig(path, language_entries, sizeof(language_entries) / sizeof(ConfigEntry));
    }
  }
}
