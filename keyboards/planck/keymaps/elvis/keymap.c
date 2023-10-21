/* Copyright 2015-2021 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "features/casemodes.h"

#ifdef AUDIO_ENABLE
#    include "muse.h"
#endif

// Left-hand home row mods
#define HOME_A LCTL_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LGUI_T(KC_D)
#define HOME_F LSFT_T(KC_F)

// Right-hand home row mods
#define HOME_J RSFT_T(KC_J)
#define HOME_K RGUI_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_SCLN RCTL_T(KC_SCLN)

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _SQL,
  _NUM,
  _PLOVER,
  _ADJUST
};

#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define SQL     MO(_SQL)
#define NUM     TG(_NUM)

enum planck_keycodes {

  QWERTY = SAFE_RANGE,
  PLOVER,
  EXT_PLV,
  MC_COPY,
  NAME,    // Elvis Dieguez
  P_EMAIL, // edieguez@ieee.org
  W_EMAIL, // elvis@usymphonie.ai
  W_ADDR,  // 160 NW Gilman Blvd, Suite #225, Issaquah, WA 98027
  FDATE,   // Dates
  GITPULL, // git pull
  GITPUSH, // git push
  GITADD,  // git add 
  GITCOMM, // git commit -m ''
  GITSTAT, // git status
  GITBRCH, // git branch -a
  APTUP,   // apt-get update && apt-get dist-upgrade
  ANGLE,
  BRACK,
  CURLY,
  PARAN,
  SELECT,
  FROM,
  WHERE,
  GRP_BY,
  LFJOIN,
  INJOIN,
  TMPTBL,
  DRPTBL,
  UPDATE,
  SQLSET,
  SQLON,
  SQLAS,
  SQLAND,
  SQLOR,
  CAPSWORD,
  SNAKECASE,
};

/* Define combos  */
enum combo_events {
  BSPC_LSFT_CLEAR,
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM clear_line_combo[] = {KC_BSPC, KC_LSFT, COMBO_END};

combo_t key_combos[] = {
  [BSPC_LSFT_CLEAR] = COMBO_ACTION(clear_line_combo),
};
/* COMBO_ACTION(x) is same as COMBO(x, KC_NO) */

/* Process combos */
void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {

    /* MacOS Version */
    case BSPC_LSFT_CLEAR:
      if (pressed) {
        tap_code16(LCMD(KC_RIGHT));
        tap_code16(LCMD(LSFT(KC_LEFT)));
        tap_code16(KC_BSPC);
      }
      break;
  }
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | _SQL | Ctrl | Alt  | GUI  |_Lower|    Space    |_Raise| Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_BSPC,
    KC_ESC,   HOME_A,  HOME_S,  HOME_D,  HOME_F,  KC_G,    KC_H,    HOME_J,  HOME_K,  HOME_L,  HOME_SCLN, KC_QUOT,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_ENT ,
    SQL,      KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,     KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   -  |   =  |   [  |   ]  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | _NUM | Ctrl | Alt  | GUI  |_Lower|    Space    |_Raise| Home | PgUP | PgDN |  End |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,  KC_ASTR,  KC_LPRN, KC_RPRN, _______,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,  KC_PLUS,  KC_LCBR, KC_RCBR, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MINS,  KC_EQL,   KC_LBRC, KC_RBRC, _______,
    NUM,     _______, _______, _______, _______, _______, _______, _______,  KC_HOME,  KC_PGDN, KC_PGUP, KC_END
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CAPS |      |SNAKE |      |      |APTUP |WEMAIL|PEMAIL|  ADD |COMMIT| PUSH |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  <>  |  {}  |  ()  |  []  |      |WADDR | NAME |STATUS|BRANCH| PULL |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | _NUM | Ctrl | Alt  | GUI  |_Lower|    Space    |_Raise| Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_GRV,   KC_1,    KC_2,      KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    CAPSWORD, XXXXXXX, SNAKECASE, XXXXXXX, XXXXXXX, APTUP,   W_EMAIL, P_EMAIL, GITADD,  GITCOMM, GITPUSH, KC_PIPE,
    _______,  ANGLE,   CURLY,     PARAN,   BRACK,   XXXXXXX, W_ADDR,  NAME,    GITSTAT, GITBRCH, GITPULL, _______,
    _______,  _______, _______,   _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* SQL
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |      |      |      |      |      |      |      |SELECT| FROM |LFJOIN|  ON  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |      |      |      |      |      |      |      |WHERE |GRP BY|INJOIN|  AS  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |      |      |TMPTBL|DRPTBL|UPDATE| AND  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | _SQL | Ctrl | Alt  | GUI  |      |    Space    |      |  ()  |   =  | SET  |  OR  |
 * `-----------------------------------------------------------------------------------'
 */

[_SQL] = LAYOUT_planck_grid(
    KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, SELECT, FROM,   LFJOIN, SQLON,
    KC_DEL,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, WHERE,  GRP_BY, INJOIN, SQLAS,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TMPTBL, DRPTBL, UPDATE, SQLAND,
    _______, _______, _______, _______, XXXXXXX, _______, _______, XXXXXXX, PARAN,  KC_EQL, SQLSET, SQLOR
),

/* NUM
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |      |      |      |      |      |      |  1   |  2   |  3   |  +   | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |      |      |      |      |      |      |  4   |  5   |  6   |  -   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |      |  7   |  8   |  9   |  *   |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |_QWRTY| Ctrl | Alt  | GUI  |      |    Space    |  0   |  .   |  =   |  /   |      |
 * `-----------------------------------------------------------------------------------'
 */

[_NUM] = LAYOUT_planck_grid(
    KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_1, KC_2,   KC_3,   KC_PLUS, KC_BSPC,
    KC_DEL,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_4, KC_5,   KC_6,   KC_MINS, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_7, KC_8,   KC_9,   KC_ASTR, KC_ENT,
    NUM,     _______, _______, _______, XXXXXXX, _______, _______, KC_0, KC_DOT, KC_EQL, KC_SLSH, XXXXXXX
),

/* Plover layer (http://opensteno.org)
 * ,-----------------------------------------------------------------------------------.
 * |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |   #  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   T  |   P  |   H  |   *  |   *  |   F  |   P  |   L  |   T  |   D  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   S  |   K  |   W  |   R  |   *  |   *  |   R  |   B  |   G  |   S  |   Z  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Exit |      |      |   A  |   O  |             |   E  |   U  |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_PLOVER] = LAYOUT_planck_grid(
    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1,    KC_1   ,
    XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
    XXXXXXX, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    EXT_PLV, XXXXXXX, XXXXXXX, KC_C,    KC_V,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX
),


/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Qwerty|      |      |Plover|      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, MU_NEXT, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, _______, PLOVER,  _______,
    _______, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Process case modes
  if (!process_case_modes(keycode, record)) {
      return false;
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case PLOVER:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(plover_song);
        #endif
        layer_off(_RAISE);
        layer_off(_LOWER);
        layer_off(_ADJUST);
        layer_on(_PLOVER);
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
      }
      return false;
      break;
    case EXT_PLV:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(plover_gb_song);
        #endif
        layer_off(_PLOVER);
      }
      return false;
      break;


    /* Capture portion of the screen selected through the mouse (MacOS) */
    case MC_COPY:
      if (record->event.pressed) {
        tap_code16(LCMD(LSFT(KC_4)));
        return false;
      }
      break;

    case NAME:
      if (record->event.pressed) {
          SEND_STRING("Elvis Dieguez");
      } else {
        // When keycode is released
      }
      break;

    case P_EMAIL:
      if (record->event.pressed) {
          SEND_STRING("edieguez@ieee.org");
      } else {
        // When keycode is released
      }
      break;

    case W_EMAIL:
      if (record->event.pressed) {
          SEND_STRING("elvis@symphonie.ai");
      } else {
        // When keycode is released
      }
      break;

    case W_ADDR:
      if (record->event.pressed) {
          SEND_STRING("160 NW Gilman Blvd, Suite #225, Issaquah, WA 98027");
      } else {
        // When keycode is released
      }
      break;

    case FDATE:
      if (record->event.pressed) {
        tap_code16(LALT(LCMD(LSFT(KC_D))));
        return false;
      }
      break;

    case GITADD:
      if (record->event.pressed) {
          SEND_STRING("git add ");
      } else {
        // When keycode is released
      }
      break;

    case GITCOMM:
      if (record->event.pressed) {
          SEND_STRING("git commit -m ''");
          tap_code(KC_LEFT);  // Move cursor between quotes
      } else {
        // When keycode is released
      }
      break;

    case GITPULL:
      if (record->event.pressed) {
          SEND_STRING("git pull\n");
      } else {
        // When keycode is released
      }
      break;

    case GITPUSH:
      if (record->event.pressed) {
          SEND_STRING("git push\n");
      } else {
        // When keycode is released
      }
      break;

    case GITSTAT:
      if (record->event.pressed) {
          SEND_STRING("git status\n");
      } else {
        // When keycode is released
      }
      break;

    case GITBRCH:
      if (record->event.pressed) {
          SEND_STRING("git branch -a\n");
      } else {
        // When keycode is released
      }
      break;

    case APTUP:
      if (record->event.pressed) {
          SEND_STRING("sudo apt-get update && sudo apt-get dist-upgrade\n");
      } else {
        // When keycode is released
      }
      break;

     case ANGLE:
      if (record->event.pressed) {
          SEND_STRING("<>");
          tap_code(KC_LEFT);  // Move cursor between quotes
      } else {
        // When keycode is released
      }
      break;

     case BRACK:
      if (record->event.pressed) {
          SEND_STRING("[]");
          tap_code(KC_LEFT);  // Move cursor between quotes
      } else {
        // When keycode is released
      }
      break;

     case CURLY:
      if (record->event.pressed) {
          SEND_STRING("{}");
          tap_code(KC_LEFT);  // Move cursor between quotes
      } else {
        // When keycode is released
      }
      break;

     case PARAN:
      if (record->event.pressed) {
          SEND_STRING("()");
          tap_code(KC_LEFT);  // Move cursor between quotes
      } else {
        // When keycode is released
      }
      break;

    case CAPSWORD:
      if (record->event.pressed) {
          enable_caps_word();
      }
      return false;

    case SNAKECASE:
      if (record->event.pressed) {
          enable_xcase_with(KC_UNDS);
      }
      return false;
      break;

    case SELECT:
      if (record->event.pressed) {
          SEND_STRING("SELECT ");
      } else {
        // When keycode is released
      }
      break;

    case FROM:
      if (record->event.pressed) {
          SEND_STRING("FROM ");
      } else {
        // When keycode is released
      }
      break;

    case WHERE:
      if (record->event.pressed) {
          SEND_STRING("WHERE ");
      } else {
        // When keycode is released
      }
      break;

    case GRP_BY:
      if (record->event.pressed) {
          SEND_STRING("GROUP BY ");
      } else {
        // When keycode is released
      }
      break;

    case LFJOIN:
      if (record->event.pressed) {
          SEND_STRING("LEFT JOIN ");
      } else {
        // When keycode is released
      }
      break;

    case INJOIN:
      if (record->event.pressed) {
          SEND_STRING("INNER JOIN ");
      } else {
        // When keycode is released
      }
      break;

    case UPDATE:
      if (record->event.pressed) {
          SEND_STRING("UPDATE ");
      } else {
        // When keycode is released
      }
      break;

    case SQLSET:
      if (record->event.pressed) {
          SEND_STRING("SET ");
      } else {
        // When keycode is released
      }
      break;

    case SQLON:
      if (record->event.pressed) {
          SEND_STRING("ON ");
      } else {
        // When keycode is released
      }
      break;

    case SQLAS:
      if (record->event.pressed) {
          SEND_STRING("AS ");
      } else {
        // When keycode is released
      }
      break;

    case SQLAND:
      if (record->event.pressed) {
          SEND_STRING("AND ");
      } else {
        // When keycode is released
      }
      break;

    case SQLOR:
      if (record->event.pressed) {
          SEND_STRING("OR ");
      } else {
        // When keycode is released
      }
      break;

    case TMPTBL:
      if (record->event.pressed) {
          SEND_STRING("CREATE TEMPORARY TABLE IF NOT EXISTS ");
      } else {
        // When keycode is released
      }
      break;

    case DRPTBL:
      if (record->event.pressed) {
          SEND_STRING("DROP TABLE IF EXISTS ");
      } else {
        // When keycode is released
      }
      break;


  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_DOWN);
      #else
        tap_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_UP);
      #else
        tap_code(KC_PGUP);
      #endif
    }
  }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_song); }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
    return true;
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
