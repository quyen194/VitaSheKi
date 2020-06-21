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
#include "init.h"
#include "theme.h"
#include "language.h"
#include "settings.h"
#include "message_dialog.h"
#include "ime_dialog.h"
#include "utils.h"

static void restartShell();
static void rebootDevice();
static void shutdownDevice();
static void suspendDevice();

static int changed = 0;
static int theme = 0;

static char spoofed_version[6];

static SettingsMenuEntry *settings_menu_entries = NULL;
static int n_settings_entries = 0;

static char *usbdevice_options[4] = {0};
static char *select_button_options[2] = {0};
// QuyenNC add start
static char *package_install_options[2] = {0};
// QuyenNC add end

static char **theme_options = NULL;
static int theme_count = 0;
static char *theme_name = NULL;

static ConfigEntry settings_entries[] = {
  { "USBDEVICE",          CONFIG_TYPE_DECIMAL, (int *)&vitashell_config.usbdevice },
  { "SELECT_BUTTON",      CONFIG_TYPE_DECIMAL, (int *)&vitashell_config.select_button },
  { "DISABLE_AUTOUPDATE", CONFIG_TYPE_BOOLEAN, (int *)&vitashell_config.disable_autoupdate },
  { "DISABLE_WARNING",    CONFIG_TYPE_BOOLEAN, (int *)&vitashell_config.disable_warning },
  // QuyenNC add start
  { "PACKAGE_INSTALL_TYPE", CONFIG_TYPE_DECIMAL, (int *)&vitashell_config.package_install_type },
  { "SYSTEM_STANDBY_TIMESEC", CONFIG_TYPE_DECIMAL, (int *)&vitashell_config.system_standby_timesec },
  // QuyenNC add end
};

static ConfigEntry theme_entries[] = {
  { "THEME_NAME", CONFIG_TYPE_STRING, (void *)&theme_name },
};

SettingsMenuOption main_settings[] = {
  // { VITASHELL_SETTINGS_LANGUAGE,     SETTINGS_OPTION_TYPE_BOOLEAN, NULL, NULL, 0, NULL, 0, &language },
  { VITASHELL_SETTINGS_THEME,           SETTINGS_OPTION_TYPE_OPTIONS, NULL, NULL, 0, NULL, 0, NULL },
  
  { VITASHELL_SETTINGS_USBDEVICE,       SETTINGS_OPTION_TYPE_OPTIONS, NULL, NULL, 0,
    usbdevice_options, sizeof(usbdevice_options) / sizeof(char **), &vitashell_config.usbdevice },
  { VITASHELL_SETTINGS_SELECT_BUTTON,   SETTINGS_OPTION_TYPE_OPTIONS, NULL, NULL, 0,
    select_button_options, sizeof(select_button_options) / sizeof(char **), &vitashell_config.select_button },
  { VITASHELL_SETTINGS_NO_AUTO_UPDATE,  SETTINGS_OPTION_TYPE_BOOLEAN, NULL, NULL, 0, NULL, 0, &vitashell_config.disable_autoupdate },
  { VITASHELL_SETTINGS_WARNING_MESSAGE, SETTINGS_OPTION_TYPE_BOOLEAN, NULL, NULL, 0, NULL, 0, &vitashell_config.disable_warning },
  // QuyenNC add start
  { VITASHELL_SETTINGS_DISABLE_SYSTEM_SLEEP, SETTINGS_OPTION_TYPE_BOOLEAN, NULL, NULL, 0, NULL, 0, &vitashell_config.disable_system_sleep },
  { VITASHELL_SETTINGS_INSTALL_TYPE,   SETTINGS_OPTION_TYPE_OPTIONS, NULL, NULL, 0,
    package_install_options, sizeof(package_install_options) / sizeof(char *), &vitashell_config.package_install_type },
  // QuyenNC add end

  { VITASHELL_SETTINGS_RESTART_SHELL,   SETTINGS_OPTION_TYPE_CALLBACK, (void *)restartShell, NULL, 0, NULL, 0, NULL },
};

SettingsMenuOption power_settings[] = {
  { VITASHELL_SETTINGS_REBOOT,    SETTINGS_OPTION_TYPE_CALLBACK, (void *)rebootDevice, NULL, 0, NULL, 0, NULL },
  { VITASHELL_SETTINGS_POWEROFF,  SETTINGS_OPTION_TYPE_CALLBACK, (void *)shutdownDevice, NULL, 0, NULL, 0, NULL },
  { VITASHELL_SETTINGS_STANDBY,   SETTINGS_OPTION_TYPE_CALLBACK, (void *)suspendDevice, NULL, 0, NULL, 0, NULL },
};

SettingsMenuEntry vitashell_settings_menu_entries[] = {
  { VITASHELL_SETTINGS_MAIN,  main_settings,  sizeof(main_settings) / sizeof(SettingsMenuOption) },
  { VITASHELL_SETTINGS_POWER, power_settings, sizeof(power_settings) / sizeof(SettingsMenuOption) },
};

static SettingsMenu settings_menu;

void loadSettingsConfig() {
  // Load settings config file
  memset(&vitashell_config, 0, sizeof(VitaShellConfig));
  readConfig("ux0:" VITA_APP_NAME "/settings.txt", settings_entries, sizeof(settings_entries) / sizeof(ConfigEntry));
}

void saveSettingsConfig() {
  // Save settings config file
  writeConfig("ux0:" VITA_APP_NAME "/settings.txt", settings_entries, sizeof(settings_entries) / sizeof(ConfigEntry));

  if (sceKernelGetModel() == SCE_KERNEL_MODEL_VITATV) {
    vitashell_config.select_button = SELECT_BUTTON_MODE_FTP;
  }
}

static void restartShell() {
  closeSettingsMenu();
  sceAppMgrLoadExec("app0:eboot.bin", NULL, NULL);
}

static void rebootDevice() {
  closeSettingsMenu();
  scePowerRequestColdReset();
}

static void shutdownDevice() {
  closeSettingsMenu();
  scePowerRequestStandby();
}

static void suspendDevice() {
  closeSettingsMenu();
  scePowerRequestSuspend();
}

void initSettingsMenu() {
  int i, j;

  memset(&settings_menu, 0, sizeof(SettingsMenu));
  settings_menu.status = SETTINGS_MENU_CLOSED;

  n_settings_entries = sizeof(vitashell_settings_menu_entries) / sizeof(SettingsMenuEntry);
  settings_menu_entries = vitashell_settings_menu_entries;

  usbdevice_options[0] = language_container[VITASHELL_SETTINGS_USB_MEMORY_CARD];
  usbdevice_options[1] = language_container[VITASHELL_SETTINGS_USB_GAME_CARD];
  usbdevice_options[2] = language_container[VITASHELL_SETTINGS_USB_SD2VITA];
  usbdevice_options[3] = language_container[VITASHELL_SETTINGS_USB_PSVSD];

  select_button_options[0] = language_container[VITASHELL_SETTINGS_SELECT_BUTTON_USB];
  select_button_options[1] = language_container[VITASHELL_SETTINGS_SELECT_BUTTON_FTP];

  // QuyenNC add start
  package_install_options[0] = language_container[VITASHELL_SETTINGS_INSTALL_REPLACE];
  package_install_options[1] = language_container[VITASHELL_SETTINGS_INSTALL_UPDATE];
  // QuyenNC add end

  theme_options = malloc(MAX_THEMES * sizeof(char *));
  
  for (i = 0; i < MAX_THEMES; i++)
    theme_options[i] = malloc(MAX_THEME_LENGTH);
}

void openSettingsMenu() {
  settings_menu.status = SETTINGS_MENU_OPENING;
  settings_menu.entry_sel = 0;
  settings_menu.option_sel = 0;

  // Get current theme
  if (theme_name)
    free(theme_name);

  // read config from file
  readConfig("ux0:" VITA_APP_NAME "/theme/theme.txt", theme_entries, sizeof(theme_entries) / sizeof(ConfigEntry));

  // QuyenNC add start
  // read config from registry
  int system_standby_timesec = 0;
  sceRegMgrGetKeyInt("/CONFIG/POWER_SAVING/", "suspend_interval", &system_standby_timesec);
  vitashell_config.disable_system_sleep = (system_standby_timesec) ? 0 : 1;
  vitashell_config.disable_system_sleep_compare = vitashell_config.disable_system_sleep;
  if (system_standby_timesec) {
    // save old setting
    vitashell_config.system_standby_timesec = system_standby_timesec;
  }
  // QuyenNC add start

  // Get theme index in main tab
  int theme_index = -1;

  int i;
  for (i = 0; i < (sizeof(main_settings) / sizeof(SettingsMenuOption)); i++) {
    if (main_settings[i].name == VITASHELL_SETTINGS_THEME) {
      theme_index = i;
      break;
    }
  }

  // Find all themes
  if (theme_index >= 0) {
    SceUID dfd = sceIoDopen("ux0:" VITA_APP_NAME "/theme");
    if (dfd >= 0) {
      theme_count = 0;
      theme = 0;

      int res = 0;

      do {
        SceIoDirent dir;
        memset(&dir, 0, sizeof(SceIoDirent));

        res = sceIoDread(dfd, &dir);
        if (res > 0) {
          if (SCE_S_ISDIR(dir.d_stat.st_mode)) {
            if (theme_name && strcasecmp(dir.d_name, theme_name) == 0)
              theme = theme_count;
            
            strncpy(theme_options[theme_count], dir.d_name, MAX_THEME_LENGTH);
            theme_count++;
          }
        }
      } while (res > 0 && theme_count < MAX_THEMES);
      
      sceIoDclose(dfd);
      
      main_settings[theme_index].options = theme_options;
      main_settings[theme_index].n_options = theme_count;
      main_settings[theme_index].value = &theme;
    }
  }

  changed = 0;
}

void closeSettingsMenu() {
  settings_menu.status = SETTINGS_MENU_CLOSING;

  // Save settings
  if (changed) {
    // QuyenNC add start
    if (vitashell_config.disable_system_sleep != vitashell_config.disable_system_sleep_compare) {
      if (vitashell_config.disable_system_sleep) {
        // write to registry
        sceRegMgrSetKeyInt("/CONFIG/POWER_SAVING/", "suspend_interval", 0);
      } else {
        sceRegMgrSetKeyInt("/CONFIG/POWER_SAVING/", "suspend_interval", vitashell_config.system_standby_timesec);
      }
    }
    // QuyenNC add end

    saveSettingsConfig();
      
    // Save theme config file
    theme_entries[0].value = &theme_options[theme];
    writeConfig("ux0:" VITA_APP_NAME "/theme/theme.txt", theme_entries, sizeof(theme_entries) / sizeof(ConfigEntry));
    theme_entries[0].value = (void *)&theme_name;
  }
}

int getSettingsMenuStatus() {
  return settings_menu.status;
}

void drawSettingsMenu() {
  if (settings_menu.status == SETTINGS_MENU_CLOSED)
    return;

  // Closing settings menu
  if (settings_menu.status == SETTINGS_MENU_CLOSING) {
    if (settings_menu.cur_pos > 0.0f) {
      settings_menu.cur_pos -= easeOut(0.0f, settings_menu.cur_pos, 0.25f, 0.01f);
    } else {
      settings_menu.status = SETTINGS_MENU_CLOSED;
    }
  }

  // Opening settings menu
  if (settings_menu.status == SETTINGS_MENU_OPENING) {
    if (settings_menu.cur_pos < SCREEN_HEIGHT) {
      settings_menu.cur_pos += easeOut(settings_menu.cur_pos, SCREEN_HEIGHT, 0.25f, 0.01f);
    } else {
      settings_menu.status = SETTINGS_MENU_OPENED;
    }
  }

  // Draw settings menu
  vita2d_draw_texture(settings_image, 0.0f, SCREEN_HEIGHT - settings_menu.cur_pos);

  float y = SCREEN_HEIGHT - settings_menu.cur_pos + START_Y;

  int i;
  for (i = 0; i < n_settings_entries; i++) {
    // QuyenNC mod start
    // Title
    if (settings_menu_entries[i].name) {
      float x = pgf_text_width(language_container[settings_menu_entries[i].name]);
      pgf_draw_text(ALIGN_CENTER(SCREEN_WIDTH, x), y, SETTINGS_MENU_TITLE_COLOR, language_container[settings_menu_entries[i].name]);
    }
    // QuyenNC mod end

    y += FONT_Y_SPACE;

    SettingsMenuOption *options = settings_menu_entries[i].options;

    // QuyenNC mod start
    int max_show_option = (settings_menu_entries[i].n_options < MAX_SHOW_OPTION) ? settings_menu_entries[i].n_options : MAX_SHOW_OPTION;

    int j = 0;
    if (i == settings_menu.entry_sel) {
      j = settings_menu.begin_sel;
    } else if (i < settings_menu.entry_sel) {
      j = settings_menu_entries[i].n_options - max_show_option;
    }
    int max_j = j + max_show_option;
    if (max_j > settings_menu_entries[i].n_options) {
      max_j = settings_menu_entries[i].n_options;
    }
    // QuyenNC mod end
    for (; j < max_j; j++) {
      // Focus
      if (settings_menu.entry_sel == i && settings_menu.option_sel == j)
        vita2d_draw_rectangle(SHELL_MARGIN_X, y + 3.0f, MARK_WIDTH, FONT_Y_SPACE, SETTINGS_MENU_FOCUS_COLOR);

      if (options[j].type == SETTINGS_OPTION_TYPE_CALLBACK) {
        // Item
        float x = pgf_text_width(language_container[options[j].name]);
        pgf_draw_text(ALIGN_CENTER(SCREEN_WIDTH, x), y, SETTINGS_MENU_ITEM_COLOR, language_container[options[j].name]);
      // QuyenNC add start
      } else if (options[j].type == SETTINGS_OPTION_TYPE_NONE) {
        // draw nothing
      // QuyenNC add end
      } else {
        // Item
        float x = pgf_text_width(language_container[options[j].name]);
        pgf_draw_text(ALIGN_RIGHT(SCREEN_HALF_WIDTH - 10.0f, x), y, SETTINGS_MENU_ITEM_COLOR, language_container[options[j].name]);

        // Option
        switch (options[j].type) {
          case SETTINGS_OPTION_TYPE_BOOLEAN:
            pgf_draw_text(SCREEN_HALF_WIDTH + 10.0f, y, SETTINGS_MENU_OPTION_COLOR,
                          (options[j].value && *(options[j].value)) ? language_container[ON] : language_container[OFF]);
            break;

          case SETTINGS_OPTION_TYPE_STRING:
            pgf_draw_text(SCREEN_HALF_WIDTH + 10.0f, y, SETTINGS_MENU_OPTION_COLOR, options[j].string);
            break;

          case SETTINGS_OPTION_TYPE_OPTIONS:
          {
            int value = 0;
            if (options[j].value)
              value = *(options[j].value);
            pgf_draw_text(SCREEN_HALF_WIDTH + 10.0f, y, SETTINGS_MENU_OPTION_COLOR, options[j].options ? options[j].options[value] : "");
            break;
          }
        }
      }

      y += FONT_Y_SPACE;
    }

    y += FONT_Y_SPACE;
  }
}

static int agreement = SETTINGS_AGREEMENT_NONE;

void settingsAgree() {
  agreement = SETTINGS_AGREEMENT_AGREE;
}

void settingsDisagree() {
  agreement = SETTINGS_AGREEMENT_DISAGREE;
}

void settingsMenuCtrl() {
  SettingsMenuOption *option = &settings_menu_entries[settings_menu.entry_sel].options[settings_menu.option_sel];

  // Agreement
  if (agreement != SETTINGS_AGREEMENT_NONE) {
    agreement = SETTINGS_AGREEMENT_NONE;
  }

  // Change options
  if (pressed_pad[PAD_ENTER] || pressed_pad[PAD_LEFT] || pressed_pad[PAD_RIGHT]) {
    changed = 1;

    switch (option->type) {
      case SETTINGS_OPTION_TYPE_BOOLEAN:
        if (option->value)
          *(option->value) = !*(option->value);
        break;
      
      case SETTINGS_OPTION_TYPE_STRING:
        initImeDialog(language_container[option->name], option->string, option->size_string, SCE_IME_TYPE_EXTENDED_NUMBER, 0, 0);
        setDialogStep(DIALOG_STEP_SETTINGS_STRING);
        break;
        
      case SETTINGS_OPTION_TYPE_CALLBACK:
        if (option->callback)
          option->callback(&option);
        break;
        
      case SETTINGS_OPTION_TYPE_OPTIONS:
      {
        if (option->value) {
          if (pressed_pad[PAD_LEFT]) {
            if (*(option->value) > 0)
              (*(option->value))--;
            else
              *(option->value) = option->n_options - 1;
          } else if (pressed_pad[PAD_ENTER] || pressed_pad[PAD_RIGHT]) {
            if (*(option->value) < option->n_options - 1)
              (*(option->value))++;
            else
              *(option->value) = 0;
          }
        }
        
        break;
      }

    // QuyenNC add start
    default:
      changed = 0;
      break;
    // QuyenNC add end
    }
  }

  // QuyenNC add start
  // init move
  int e_index = settings_menu.entry_sel;
  int o_index = settings_menu.option_sel;
  int b_index = settings_menu.begin_sel;
  // QuyenNC add end

  // QuyenNC mod start
  // Move
  if (hold_pad[PAD_UP] || hold2_pad[PAD_LEFT_ANALOG_UP]) {
    for (;;) {
      // option one step backward
      o_index--;
      // if option is out of current category
      if (o_index < 0) {
        // incase: not the first category
        if (e_index > 0) {
          e_index--;
          o_index = settings_menu_entries[e_index].n_options;  // next loop will correct position with -1
          if (settings_menu_entries[e_index].n_options > MAX_SHOW_OPTION) {
            b_index = settings_menu_entries[e_index].n_options - MAX_SHOW_OPTION;
          } else {
            b_index = 0;
          }
          continue;
        }
        // incase: the first category => can't move backward
        e_index = settings_menu.entry_sel;
        o_index = settings_menu.option_sel;
        b_index = settings_menu.begin_sel;
        break;
      }
      // need move b_index?
      if (settings_menu_entries[e_index].n_options > MAX_SHOW_OPTION) {
        if ((b_index > 0) &&
            ((o_index - b_index) < (MAX_SHOW_OPTION / 2))) {
          b_index--;
        }
      }
      // check for valid position
      if (settings_menu_entries[e_index].options[o_index].name != 0) {
        break;
      }
    }

  } else if (hold_pad[PAD_DOWN] || hold2_pad[PAD_LEFT_ANALOG_DOWN]) {
    for (;;) {
      // option one step forward
      o_index++;
      // if option is out of current category
      if (o_index > settings_menu_entries[e_index].n_options - 1) {
        // incase: not the last category
        if (e_index < n_settings_entries - 1) {
          e_index++;
          o_index = -1;  // next loop will correct position with +1
          b_index = 0;
          continue;
        }
        // incase: the last category => can't move forward
        e_index = settings_menu.entry_sel;
        o_index = settings_menu.option_sel;
        b_index = settings_menu.begin_sel;
        break;
      }
      // need move b_index?
      if (settings_menu_entries[e_index].n_options > MAX_SHOW_OPTION) {
        if (((b_index + MAX_SHOW_OPTION) < settings_menu_entries[e_index].n_options) &&
            ((o_index - b_index) > (MAX_SHOW_OPTION / 2))) {
          b_index++;
        }
      }
      // check for valid position
      if (settings_menu_entries[e_index].options[o_index].name != 0) {
        break;
      }
    }
  }
  // QuyenNC mod end

  // QuyenNC add start
  // apply move
  settings_menu.entry_sel = e_index;
  settings_menu.option_sel = o_index;
  settings_menu.begin_sel = b_index;
  // QuyenNC add end

  // Close
  if (pressed_pad[PAD_START] || pressed_pad[PAD_CANCEL]) {
    closeSettingsMenu();
  }
}
