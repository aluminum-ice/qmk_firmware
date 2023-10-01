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

// Important changes folded into this keymap on 2023-10-01T18:11:21Z
// https://www.reddit.com/r/qmk/comments/168h56g/missing_definitions/
// https://docs.qmk.fm/#/ChangeLog/20221126?id=keycodes-overhaul-core-changes

#include QMK_KEYBOARD_H
#include "muse.h"
#include "features/casemodes.h"

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

enum preonic_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _PROG
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  BACKLIT,
  MC_COPY,
  P_EMAIL, // edieguez@ieee.org
  W_EMAIL, // elvis@usymphonie.ai
  FDATE,   // Dates
  GITPULL, // git pull
  GITPUSH, // git push
  GITADD,  // git add 
  GITCOMM, // git commit -m ''
  GITSTAT, // git status
  GITBRCH, // git branch -a
  TINIT,   // terraform init
  TAPPLY,  // terraform apply
  TPLAN,   // terraform plan
  TVALID,  // terraform validate
  APTUP,   // apt-get update && apt-get dist-upgrade
  ANGLE,
  BRACK,
  CURLY,
  PARAN,
  CAPSWORD,
  SNAKECASE,
  P_WPM,    // Print my WPM data
};

// // Tap Dance enum
// enum {
//     TD_ESC_CAPS,
// };

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

// // Tap Dance definitions
// qk_tap_dance_action_t tap_dance_actions[] = {
//     // Tap once for Escape, twice for Caps Lock
//     [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
// };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// Change the FN from RGB_TOG to MO(_PROG)
/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |Bspc  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Prog | Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid(
  KC_GRV,            KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      KC_MINS,
  LT(_PROG,KC_TAB),  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_BSPC,
  KC_ESC,            HOME_A,  HOME_S,  HOME_D,  HOME_F,  KC_G,    KC_H,    HOME_J,  HOME_K,  HOME_L,  HOME_SCLN, KC_QUOT,
  KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_ENT,
  MO(_PROG),         KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,     KC_RGHT
),


/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  =   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |P_WPM |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  | COPY |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   [  |   ]  |   \  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Home | PgUP | PgDN |  End |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid(
  _______,  _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, KC_EQL,
  _______,  _______, P_WPM,     _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
  _______,  _______, _______,   _______, _______, _______, _______, _______, _______, _______, MC_COPY, _______,
  _______,  _______, _______,   _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, KC_BSLS, _______,
  _______,  _______, _______,   _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |WEMAIL|   E  |   R  |   T  |   Y  |UPDATE|   I  |   O  |PEMAIL| Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | CAPS |   A  |SNAKE |FDATE |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |  C   |   V  |   B  |   N  |   M  |   [  |   ]  |   \  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid(
  KC_F1,    KC_F2,   KC_F3,     KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  _______,  _______, W_EMAIL,   _______, _______, _______, _______, APTUP,   _______, _______, P_EMAIL, KC_DEL,
  CAPSWORD, _______, SNAKECASE, FDATE,   _______, _______, _______, _______, _______, _______, _______, _______,
  _______,  _______, _______,   _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, KC_BSLS, _______,
  _______,  _______, _______,   _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset| Debug|      |      |      |      |      |      |      |      |Brite |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |Aud cy|Aud on|AudOff|AGnorm|AGswap|      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|MusOff|MidiOn|MidOff|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  CLR |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  _______, QK_BOOT, DB_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG,
  _______, _______, MU_NEXT, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, _______, _______, _______, _______, _______,
  _______, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
  EE_CLR,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Programming
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  | INIT |APPLY |   U  |   I  |   O  |   P  |Bspc  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |  ADD |STATUS|   D  |   F  |   G  | PUSH |   J  |   K  | PULL |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |COMMIT|VALID |BRANCH| PLAN |   M  |  <>  |  []  |  {}  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_PROG] = LAYOUT_preonic_grid(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, PARAN,   _______, _______,
  _______, _______, _______, _______, _______, TINIT,   TAPPLY,  _______, _______, _______, _______, _______,
  _______, GITADD,  GITSTAT, _______, _______, _______, GITPUSH, _______, _______, GITPULL, _______, _______,
  _______, _______, _______, GITCOMM, TVALID,  GITBRCH, TPLAN,   _______, ANGLE,   BRACK,   CURLY,   _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)


};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Process case modes
  if (!process_case_modes(keycode, record)) {
      return false;
  }

  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            #ifdef RGBLIGHT_ENABLE
              rgblight_step();
            #endif
            #ifdef __AVR__
            writePinLow(E6);
            #endif
          } else {
            unregister_code(KC_RSFT);
            #ifdef __AVR__
            writePinHigh(E6);
            #endif
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

        case TINIT:
          if (record->event.pressed) {
              SEND_STRING("terraform init\n");
          } else {
            // When keycode is released
          }
          break;

        case TPLAN:
          if (record->event.pressed) {
              SEND_STRING("terraform plan\n");
          } else {
            // When keycode is released
          }
          break;

        case TVALID:
          if (record->event.pressed) {
              SEND_STRING("terraform validate\n");
          } else {
            // When keycode is released
          }
          break;

        case TAPPLY:
          if (record->event.pressed) {
              SEND_STRING("terraform apply\n");
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

        case P_WPM:
          if (record->event.pressed) {
              char swpm[4];
              sprintf(swpm, "%d", get_current_wpm());
              SEND_STRING(swpm);
          } else {
              // When keycode is released
          }
          break;

      }
    return true;
};

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
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
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
