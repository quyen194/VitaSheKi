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
#include "browser.h"
#include "init.h"
#include "file.h"
#include "package_installer.h"
#include "utils.h"
#include "qr.h"
#include "rif.h"

#include "audio/vita_audio.h"

INCLUDE_EXTERN_RESOURCE(english_us_txt);

INCLUDE_EXTERN_RESOURCE(theme_txt);

INCLUDE_EXTERN_RESOURCE(default_colors_txt);
INCLUDE_EXTERN_RESOURCE(default_archive_icon_png);
INCLUDE_EXTERN_RESOURCE(default_audio_icon_png);
INCLUDE_EXTERN_RESOURCE(default_battery_bar_charge_png);
INCLUDE_EXTERN_RESOURCE(default_battery_bar_green_png);
INCLUDE_EXTERN_RESOURCE(default_battery_bar_red_png);
INCLUDE_EXTERN_RESOURCE(default_battery_png);
INCLUDE_EXTERN_RESOURCE(default_cover_png);
INCLUDE_EXTERN_RESOURCE(default_fastforward_png);
INCLUDE_EXTERN_RESOURCE(default_fastrewind_png);
INCLUDE_EXTERN_RESOURCE(default_file_icon_png);
INCLUDE_EXTERN_RESOURCE(default_folder_icon_png);
INCLUDE_EXTERN_RESOURCE(default_ftp_png);
INCLUDE_EXTERN_RESOURCE(default_image_icon_png);
INCLUDE_EXTERN_RESOURCE(default_pause_png);
INCLUDE_EXTERN_RESOURCE(default_play_png);
INCLUDE_EXTERN_RESOURCE(default_sfo_icon_png);
INCLUDE_EXTERN_RESOURCE(default_text_icon_png);
INCLUDE_EXTERN_RESOURCE(default_file_symlink_icon_png);
INCLUDE_EXTERN_RESOURCE(default_folder_symlink_icon_png);

INCLUDE_EXTERN_RESOURCE(electron_colors_txt);
INCLUDE_EXTERN_RESOURCE(electron_archive_icon_png);
INCLUDE_EXTERN_RESOURCE(electron_audio_icon_png);
INCLUDE_EXTERN_RESOURCE(electron_battery_bar_charge_png);
INCLUDE_EXTERN_RESOURCE(electron_battery_bar_green_png);
INCLUDE_EXTERN_RESOURCE(electron_battery_bar_red_png);
INCLUDE_EXTERN_RESOURCE(electron_battery_png);
INCLUDE_EXTERN_RESOURCE(electron_bg_audioplayer_png);
INCLUDE_EXTERN_RESOURCE(electron_bg_browser_png);
INCLUDE_EXTERN_RESOURCE(electron_bg_hexeditor_png);
INCLUDE_EXTERN_RESOURCE(electron_bg_photoviewer_png);
INCLUDE_EXTERN_RESOURCE(electron_bg_texteditor_png);
INCLUDE_EXTERN_RESOURCE(electron_context_png);
INCLUDE_EXTERN_RESOURCE(electron_context_more_png);
INCLUDE_EXTERN_RESOURCE(electron_cover_png);
INCLUDE_EXTERN_RESOURCE(electron_dialog_png);
INCLUDE_EXTERN_RESOURCE(electron_fastforward_png);
INCLUDE_EXTERN_RESOURCE(electron_fastrewind_png);
INCLUDE_EXTERN_RESOURCE(electron_file_icon_png);
INCLUDE_EXTERN_RESOURCE(electron_folder_icon_png);
INCLUDE_EXTERN_RESOURCE(electron_ftp_png);
INCLUDE_EXTERN_RESOURCE(electron_image_icon_png);
INCLUDE_EXTERN_RESOURCE(electron_pause_png);
INCLUDE_EXTERN_RESOURCE(electron_play_png);
INCLUDE_EXTERN_RESOURCE(electron_sfo_icon_png);
INCLUDE_EXTERN_RESOURCE(electron_text_icon_png);
INCLUDE_EXTERN_RESOURCE(electron_settings_png);
// QuyenNC add start
INCLUDE_EXTERN_RESOURCE(sounds_install_complete_ogg);

INCLUDE_EXTERN_RESOURCE(Akatsuki_colors_txt);
INCLUDE_EXTERN_RESOURCE(Akatsuki_archive_icon_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_audio_icon_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_battery_bar_charge_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_battery_bar_green_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_battery_bar_red_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_battery_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_bg_audioplayer_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_bg_browser_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_bg_hexeditor_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_bg_photoviewer_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_bg_texteditor_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_context_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_context_more_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_cover_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_dialog_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_fastforward_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_fastrewind_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_file_icon_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_folder_icon_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_ftp_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_image_icon_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_pause_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_play_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_sfo_icon_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_text_icon_png);
INCLUDE_EXTERN_RESOURCE(Akatsuki_settings_png);

INCLUDE_EXTERN_RESOURCE(HatsuneMiku_colors_txt);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_archive_icon_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_audio_icon_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_battery_bar_charge_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_battery_bar_green_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_battery_bar_red_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_battery_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_bg_audioplayer_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_bg_browser_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_bg_hexeditor_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_bg_photoviewer_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_bg_texteditor_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_context_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_context_more_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_cover_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_dialog_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_fastforward_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_fastrewind_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_file_icon_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_folder_icon_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_ftp_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_image_icon_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_pause_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_play_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_sfo_icon_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_text_icon_png);
INCLUDE_EXTERN_RESOURCE(HatsuneMiku_settings_png);

INCLUDE_EXTERN_RESOURCE(NeonRift_colors_txt);
INCLUDE_EXTERN_RESOURCE(NeonRift_archive_icon_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_audio_icon_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_battery_bar_charge_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_battery_bar_green_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_battery_bar_red_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_battery_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_bg_audioplayer_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_bg_browser_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_bg_hexeditor_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_bg_photoviewer_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_bg_texteditor_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_context_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_context_more_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_cover_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_dialog_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_fastforward_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_fastrewind_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_file_icon_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_folder_icon_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_ftp_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_image_icon_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_pause_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_play_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_sfo_icon_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_text_icon_png);
INCLUDE_EXTERN_RESOURCE(NeonRift_settings_png);
// QuyenNC add end

INCLUDE_EXTERN_RESOURCE(umass_skprx);

extern unsigned char _binary_build_modules_kernel_kernel_skprx_start;
extern unsigned char _binary_build_modules_kernel_kernel_skprx_size;
extern unsigned char _binary_build_modules_user_user_suprx_start;
extern unsigned char _binary_build_modules_user_user_suprx_size;
extern unsigned char _binary_build_modules_patch_patch_skprx_start;
extern unsigned char _binary_build_modules_patch_patch_skprx_size;
extern unsigned char _binary_build_modules_usbdevice_usbdevice_skprx_start;
extern unsigned char _binary_build_modules_usbdevice_usbdevice_skprx_size;

#define DEFAULT_FILE(path, name, replace) { path, (void *)&_binary_resources_##name##_start, (int)&_binary_resources_##name##_size, replace }

static DefaultFile default_files[] = {
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/language/english_us.txt", english_us_txt, 0),

  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/theme.txt", theme_txt, 0),

  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Default/colors.txt", default_colors_txt, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Default/archive_icon.png", default_archive_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Default/audio_icon.png", default_audio_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Default/battery.png", default_battery_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Default/battery_bar_charge.png", default_battery_bar_charge_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Default/battery_bar_green.png", default_battery_bar_green_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Default/battery_bar_red.png", default_battery_bar_red_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Default/cover.png", default_cover_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Default/fastforward.png", default_fastforward_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Default/fastrewind.png", default_fastrewind_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Default/file_icon.png", default_file_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Default/file_symlink_icon.png",default_file_symlink_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Default/folder_icon.png", default_folder_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Default/folder_symlink_icon.png",default_folder_symlink_icon_png,  1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Default/ftp.png", default_ftp_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Default/image_icon.png", default_image_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Default/pause.png", default_pause_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Default/play.png", default_play_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Default/sfo_icon.png", default_sfo_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Default/text_icon.png", default_text_icon_png, 1),

  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/colors.txt", electron_colors_txt, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/archive_icon.png", electron_archive_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/audio_icon.png", electron_audio_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/battery.png", electron_battery_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/battery_bar_charge.png", electron_battery_bar_charge_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/battery_bar_green.png", electron_battery_bar_green_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/battery_bar_red.png", electron_battery_bar_red_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/bg_audioplayer.png", electron_bg_audioplayer_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/bg_browser.png", electron_bg_browser_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/bg_hexeditor.png", electron_bg_hexeditor_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/bg_photoviewer.png", electron_bg_photoviewer_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/bg_texteditor.png", electron_bg_texteditor_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/context.png", electron_context_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/context_more.png", electron_context_more_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/cover.png", electron_cover_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/dialog.png", electron_dialog_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/fastforward.png", electron_fastforward_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/fastrewind.png", electron_fastrewind_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/file_icon.png", electron_file_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/folder_icon.png", electron_folder_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/ftp.png", electron_ftp_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/image_icon.png", electron_image_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/pause.png", electron_pause_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/play.png", electron_play_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/sfo_icon.png", electron_sfo_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/text_icon.png", electron_text_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Electron/settings.png", electron_settings_png, 1),

  // QuyenNC add start
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/colors.txt", Akatsuki_colors_txt, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/archive_icon.png", Akatsuki_archive_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/audio_icon.png", Akatsuki_audio_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/battery.png", Akatsuki_battery_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/battery_bar_charge.png", Akatsuki_battery_bar_charge_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/battery_bar_green.png", Akatsuki_battery_bar_green_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/battery_bar_red.png", Akatsuki_battery_bar_red_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/bg_audioplayer.png", Akatsuki_bg_audioplayer_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/bg_browser.png", Akatsuki_bg_browser_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/bg_hexeditor.png", Akatsuki_bg_hexeditor_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/bg_photoviewer.png", Akatsuki_bg_photoviewer_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/bg_texteditor.png", Akatsuki_bg_texteditor_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/context.png", Akatsuki_context_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/context_more.png", Akatsuki_context_more_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/cover.png", Akatsuki_cover_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/dialog.png", Akatsuki_dialog_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/fastforward.png", Akatsuki_fastforward_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/fastrewind.png", Akatsuki_fastrewind_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/file_icon.png", Akatsuki_file_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/folder_icon.png", Akatsuki_folder_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/ftp.png", Akatsuki_ftp_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/image_icon.png", Akatsuki_image_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/pause.png", Akatsuki_pause_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/play.png", Akatsuki_play_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/sfo_icon.png", Akatsuki_sfo_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/text_icon.png", Akatsuki_text_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/Akatsuki/settings.png", Akatsuki_settings_png, 1),

  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/colors.txt", HatsuneMiku_colors_txt, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/archive_icon.png", HatsuneMiku_archive_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/audio_icon.png", HatsuneMiku_audio_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/battery.png", HatsuneMiku_battery_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/battery_bar_charge.png", HatsuneMiku_battery_bar_charge_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/battery_bar_green.png", HatsuneMiku_battery_bar_green_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/battery_bar_red.png", HatsuneMiku_battery_bar_red_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/bg_audioplayer.png", HatsuneMiku_bg_audioplayer_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/bg_browser.png", HatsuneMiku_bg_browser_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/bg_hexeditor.png", HatsuneMiku_bg_hexeditor_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/bg_photoviewer.png", HatsuneMiku_bg_photoviewer_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/bg_texteditor.png", HatsuneMiku_bg_texteditor_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/context.png", HatsuneMiku_context_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/context_more.png", HatsuneMiku_context_more_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/cover.png", HatsuneMiku_cover_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/dialog.png", HatsuneMiku_dialog_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/fastforward.png", HatsuneMiku_fastforward_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/fastrewind.png", HatsuneMiku_fastrewind_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/file_icon.png", HatsuneMiku_file_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/folder_icon.png", HatsuneMiku_folder_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/ftp.png", HatsuneMiku_ftp_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/image_icon.png", HatsuneMiku_image_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/pause.png", HatsuneMiku_pause_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/play.png", HatsuneMiku_play_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/sfo_icon.png", HatsuneMiku_sfo_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/text_icon.png", HatsuneMiku_text_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/HatsuneMiku/settings.png", HatsuneMiku_settings_png, 1),

  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/colors.txt", NeonRift_colors_txt, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/archive_icon.png", NeonRift_archive_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/audio_icon.png", NeonRift_audio_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/battery.png", NeonRift_battery_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/battery_bar_charge.png", NeonRift_battery_bar_charge_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/battery_bar_green.png", NeonRift_battery_bar_green_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/battery_bar_red.png", NeonRift_battery_bar_red_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/bg_audioplayer.png", NeonRift_bg_audioplayer_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/bg_browser.png", NeonRift_bg_browser_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/bg_hexeditor.png", NeonRift_bg_hexeditor_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/bg_photoviewer.png", NeonRift_bg_photoviewer_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/bg_texteditor.png", NeonRift_bg_texteditor_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/context.png", NeonRift_context_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/context_more.png", NeonRift_context_more_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/cover.png", NeonRift_cover_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/dialog.png", NeonRift_dialog_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/fastforward.png", NeonRift_fastforward_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/fastrewind.png", NeonRift_fastrewind_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/file_icon.png", NeonRift_file_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/folder_icon.png", NeonRift_folder_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/ftp.png", NeonRift_ftp_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/image_icon.png", NeonRift_image_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/pause.png", NeonRift_pause_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/play.png", NeonRift_play_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/sfo_icon.png", NeonRift_sfo_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/text_icon.png", NeonRift_text_icon_png, 1),
  DEFAULT_FILE("ux0:" VITA_APP_NAME "/theme/NeonRift/settings.png", NeonRift_settings_png, 1),

  DEFAULT_FILE("ux0:" VITA_APP_NAME "/sounds/install_complete.ogg", sounds_install_complete_ogg, 1),
  // QuyenNC add end

  DEFAULT_FILE("ux0:" VITA_APP_NAME "/module/umass.skprx", umass_skprx, 1),
  
  { "ux0:" VITA_APP_NAME "/module/kernel.skprx",    (void *)&_binary_build_modules_kernel_kernel_skprx_start,
                                               (int)&_binary_build_modules_kernel_kernel_skprx_size, 1 },
  { "ux0:" VITA_APP_NAME "/module/user.suprx",      (void *)&_binary_build_modules_user_user_suprx_start,
                                               (int)&_binary_build_modules_user_user_suprx_size, 1 },
  { "ux0:" VITA_APP_NAME "/module/patch.skprx",     (void *)&_binary_build_modules_patch_patch_skprx_start,
                                               (int)&_binary_build_modules_patch_patch_skprx_size, 1 },
  { "ux0:" VITA_APP_NAME "/module/usbdevice.skprx", (void *)&_binary_build_modules_usbdevice_usbdevice_skprx_start,
                                               (int)&_binary_build_modules_usbdevice_usbdevice_skprx_size, 1 },
};

char vitashell_titleid[12];

int is_safe_mode = 0;

SceUID patch_modid = -1, kernel_modid = -1, user_modid = -1;

// System params
int language = 0, enter_button = 0, date_format = 0, time_format = 0;

int isSafeMode() {
  return is_safe_mode;
}

static void initSceAppUtil() {
  // Init SceAppUtil
  SceAppUtilInitParam init_param;
  SceAppUtilBootParam boot_param;
  memset(&init_param, 0, sizeof(SceAppUtilInitParam));
  memset(&boot_param, 0, sizeof(SceAppUtilBootParam));
  sceAppUtilInit(&init_param, &boot_param);

  // Mount
  sceAppUtilMusicMount();
  sceAppUtilPhotoMount();

  // System params
  sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_LANG, &language);
  sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_ENTER_BUTTON, &enter_button);
  sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_DATE_FORMAT, &date_format);
  sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_TIME_FORMAT, &time_format);

  // Set common dialog config
  SceCommonDialogConfigParam config;
  sceCommonDialogConfigParamInit(&config);
  sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_LANG, (int *)&config.language);
  sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_ENTER_BUTTON, (int *)&config.enterButtonAssign);
  sceCommonDialogSetConfigParam(&config);
}

static void finishSceAppUtil() {
  // Unmount
  sceAppUtilPhotoUmount();
  sceAppUtilMusicUmount();

  // Shutdown AppUtil
  sceAppUtilShutdown();
}

static int isKoreanChar(unsigned int c) {
  unsigned short ch = c;

  // Hangul compatibility jamo block
  if (0x3130 <= ch && ch <= 0x318F) {
    return 1;
  }

  // Hangul syllables block
  if (0xAC00 <= ch && ch <= 0xD7AF) {
    return 1;
  }

  // Korean won sign
  if (ch == 0xFFE6) {
    return 1;
  }

  return 0;
}

static int isLatinChar(unsigned int c) {
  unsigned short ch = c;

  // Basic latin block + latin-1 supplement block
  if (ch <= 0x00FF) {
    return 1;
  }

  // Cyrillic block
  if (0x0400 <= ch && ch <= 0x04FF) {
    return 1;
  }

  return 0;
}

vita2d_pgf *loadSystemFonts() {
  vita2d_system_pgf_config configs[] = {
    { SCE_FONT_LANGUAGE_KOREAN, isKoreanChar },
    { SCE_FONT_LANGUAGE_LATIN, isLatinChar },
    { SCE_FONT_LANGUAGE_DEFAULT, NULL },
  };

  return vita2d_load_system_pgf(3, configs);
}

static void initVita2dLib() {
  vita2d_init();
}

static void finishVita2dLib() {
  vita2d_free_pgf(font);
  vita2d_fini();

  font = NULL;
}

static int initSQLite() {
  return sqlite_init();
}

static int finishSQLite() {
  return sqlite_exit();
}

#define NET_MEMORY_SIZE (4 * 1024 * 1024)

static char *net_memory = NULL;

static void initNet() {
  net_memory = malloc(NET_MEMORY_SIZE);

  SceNetInitParam param;
  param.memory = net_memory;
  param.size = NET_MEMORY_SIZE;
  param.flags = 0;

  sceNetInit(&param);
  sceNetCtlInit();

  sceSslInit(300 * 1024);
  sceHttpInit(40 * 1024);

  sceHttpsDisableOption(SCE_HTTPS_FLAG_SERVER_VERIFY);

  sceNetAdhocInit();

  SceNetAdhocctlAdhocId adhocId;
  memset(&adhocId, 0, sizeof(SceNetAdhocctlAdhocId));
  adhocId.type = SCE_NET_ADHOCCTL_ADHOCTYPE_RESERVED;
  memcpy(&adhocId.data[0], VITASHELL_TITLEID, SCE_NET_ADHOCCTL_ADHOCID_LEN);
  sceNetAdhocctlInit(&adhocId);
}

static void finishNet() {
  sceNetAdhocctlTerm();
  sceNetAdhocTerm();
  sceSslTerm();
  sceHttpTerm();
  sceNetCtlTerm();
  sceNetTerm();
  free(net_memory);
}

void installDefaultFiles() {
  // Make VitaSheKi folders
  sceIoMkdir("ux0:" VITA_APP_NAME "", 0777);
  sceIoMkdir("ux0:" VITA_APP_NAME "/internal", 0777);
  sceIoMkdir("ux0:" VITA_APP_NAME "/language", 0777);
  sceIoMkdir("ux0:" VITA_APP_NAME "/module", 0777);
  sceIoMkdir("ux0:" VITA_APP_NAME "/theme", 0777);
  sceIoMkdir("ux0:" VITA_APP_NAME "/theme/Default", 0777);
  sceIoMkdir("ux0:" VITA_APP_NAME "/theme/Electron", 0777);
  // QuyenNC add start
  sceIoMkdir("ux0:" VITA_APP_NAME "/theme/Akatsuki", 0777);
  sceIoMkdir("ux0:" VITA_APP_NAME "/theme/HatsuneMiku", 0777);
  sceIoMkdir("ux0:" VITA_APP_NAME "/theme/NeonRift", 0777);
  sceIoMkdir("ux0:" VITA_APP_NAME "/sounds", 0777);
  // QuyenNC add end

  // Write default files if they don't exist
  int i;
  for (i = 0; i < (sizeof(default_files) / sizeof(DefaultFile)); i++) {
    SceIoStat stat;
    memset(&stat, 0, sizeof(stat));
    if (sceIoGetstat(default_files[i].path, &stat) < 0 || (default_files[i].replace && (int)stat.st_size != default_files[i].size))
      WriteFile(default_files[i].path, default_files[i].buffer, default_files[i].size);
  }  
}

void initVitaShell() {
  // Set CPU to 444mhz
  scePowerSetArmClockFrequency(444);

  // Init SceShellUtil events
  sceShellUtilInitEvents(0);

  // Prevent automatic CMA connection
  sceShellUtilLock(SCE_SHELL_UTIL_LOCK_TYPE_USB_CONNECTION);

  // Get titleid
  memset(vitashell_titleid, 0, sizeof(vitashell_titleid));
  sceAppMgrAppParamGetString(sceKernelGetProcessId(), 12, vitashell_titleid, sizeof(vitashell_titleid));

  // Allow writing to ux0:app/VITASHEKI
  sceAppMgrUmount("app0:");
  sceAppMgrUmount("savedata0:");

  // Is safe mode
  if (sceIoDevctl("ux0:", 0x3001, NULL, 0, NULL, 0) == 0x80010030)
    is_safe_mode = 1;

  // Set sampling mode
  sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);

  // Load modules
  sceSysmoduleLoadModule(SCE_SYSMODULE_VIDEO_EXPORT);
  sceSysmoduleLoadModule(SCE_SYSMODULE_PGF);
  sceSysmoduleLoadModule(SCE_SYSMODULE_MUSIC_EXPORT);
  sceSysmoduleLoadModule(SCE_SYSMODULE_PHOTO_EXPORT);
  sceSysmoduleLoadModule(SCE_SYSMODULE_NET);
  sceSysmoduleLoadModule(SCE_SYSMODULE_HTTPS);
  sceSysmoduleLoadModule(SCE_SYSMODULE_PSPNET_ADHOC);
  sceSysmoduleLoadModule(SCE_SYSMODULE_SQLITE);

  // Init
  vitaAudioInit(0x40);
  initVita2dLib();
  initSceAppUtil();
  initNet();
  initQR();
  initSQLite();

  // Init power tick thread
  initPowerTickThread();

  // Delete VitaShell updater if available
  if (checkAppExist("VSKIUPDER")) {
    deleteApp("VSKIUPDER");
  }

  // Install default files
  installDefaultFiles();

  // Load modules
  int search_unk[2];
  SceUID search_modid;
  search_modid = _vshKernelSearchModuleByName("VitaSheKiPatch", search_unk);
  if(search_modid < 0) {
    patch_modid = taiLoadKernelModule("ux0:" VITA_APP_NAME "/module/patch.skprx", 0, NULL);
    if (patch_modid >= 0) {
      int res = taiStartKernelModule(patch_modid, 0, NULL, 0, NULL, NULL);
      if (res < 0)
        taiStopUnloadKernelModule(patch_modid, 0, NULL, 0, NULL, NULL);
    }
  }
  search_modid = _vshKernelSearchModuleByName("VitaSheKiKernel2", search_unk);
  if(search_modid < 0) {
    kernel_modid = taiLoadKernelModule("ux0:" VITA_APP_NAME "/module/kernel.skprx", 0, NULL);
    if (kernel_modid >= 0) {
      int res = taiStartKernelModule(kernel_modid, 0, NULL, 0, NULL, NULL);
      if (res < 0)
        taiStopUnloadKernelModule(kernel_modid, 0, NULL, 0, NULL, NULL);
    }
  }
  user_modid = sceKernelLoadStartModule("ux0:" VITA_APP_NAME "/module/user.suprx", 0, NULL, 0, NULL, NULL);

  // clear up recent folder frequently
  SceIoStat stat;
  SceDateTime now;
  sceRtcGetCurrentClock(&now, 0);
  int res = sceIoGetstat(VITASHELL_RECENT_PATH, &stat);
  if (res >= 0) {
    if (now.year * 365 + now.day - stat.st_ctime.year * 365 - stat.st_ctime.day
        >= VITASHELL_RECENT_PATH_DELETE_INTERVAL_DAYS) {
      removePath(VITASHELL_RECENT_PATH, 0);
    }
  }

  if (!checkFolderExist(VITASHELL_BOOKMARKS_PATH)) {
    sceIoMkdir(VITASHELL_BOOKMARKS_PATH, 0777);
  }
  if (!checkFolderExist(VITASHELL_RECENT_PATH)) {
    sceIoMkdir(VITASHELL_RECENT_PATH, 0777);
  }
  time_last_recent_files = 0;
  time_last_bookmarks = 0;
}

void finishVitaShell() {
  // Finish
  finishSQLite();
  finishNet();
  finishSceAppUtil();
  finishVita2dLib();
  finishQR();
  vitaAudioShutdown();
  
  // Unload modules
  sceSysmoduleUnloadModule(SCE_SYSMODULE_SQLITE);
  sceSysmoduleUnloadModule(SCE_SYSMODULE_PSPNET_ADHOC);
  sceSysmoduleUnloadModule(SCE_SYSMODULE_HTTPS);
  sceSysmoduleUnloadModule(SCE_SYSMODULE_NET);
  sceSysmoduleUnloadModule(SCE_SYSMODULE_PHOTO_EXPORT);
  sceSysmoduleUnloadModule(SCE_SYSMODULE_MUSIC_EXPORT);
  sceSysmoduleUnloadModule(SCE_SYSMODULE_PGF);
  sceSysmoduleUnloadModule(SCE_SYSMODULE_VIDEO_EXPORT);
}
