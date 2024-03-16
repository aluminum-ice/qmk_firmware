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

enum chameleon_layers {
  _QWERTY = 0,
  _LOWER  = 1,
  _RAISE  = 2,
  _ADJUST = 3,
  // _SQL,
  _NUM    = 4
};

#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define SQL     MO(_SQL)
#define NUM     TG(_NUM)

enum chameleon_keycodes {
  QWERTY = SAFE_RANGE,
  BACKLIT,
  MC_COPY,
  FDATE,   // Dates
  ANGLE,
  BRACK,
  CURLY,
  PARAN,
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

// Change the FN from RGB_TOG to MO(_PROG)
/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |  Alt | GUI  | _SQL |_Lower|    Space    |_Raise| Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_5x12(
  KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,      KC_MINS,
  KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_BSPC,
  KC_ESC,   HOME_A,  HOME_S,  HOME_D,  HOME_F,  KC_G,    KC_H,    HOME_J,  HOME_K,  HOME_L,  HOME_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_ENT,
  KC_LCTL,  KC_LALT, KC_LGUI, XXXXXXX, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,     KC_RGHT
),


/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  =   |
 * |-----------------------------------------------------------------------------------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   -  |   =  |   [  |   ]  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | _NUM | Ctrl |  Alt | GUI  |_Lower|    Space    |_Raise| Home | PgUP | PgDN |  End |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_5x12(
    _______,  _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, KC_EQL,
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,  KC_ASTR,  KC_LPRN, KC_RPRN,  _______,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,  KC_PLUS,  KC_LCBR, KC_RCBR,  KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MINS,  KC_EQL,   KC_LBRC, KC_RBRC,  _______,
    NUM,     KC_LCTL, KC_LALT, KC_LGUI, _______, _______, _______, _______,  KC_HOME,  KC_PGDN, KC_PGUP,  KC_END
),


/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |-----------------------------------------------------------------------------------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CAPS |      |SNAKE |      |      |APTUP |WEMAIL|PEMAIL|  ADD |COMMIT| PUSH |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  <>  |  {}  |  ()  |  []  |      |WADDR | NAME |STATUS|BRANCH| PULL |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | _NUM | Ctrl |  Alt | GUI  |_Lower|    Space    |_Raise| Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_5x12(
    KC_F1,    KC_F2,   KC_F3,     KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_GRV,   KC_1,    KC_2,      KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    CAPSWORD, XXXXXXX, SNAKECASE, XXXXXXX, XXXXXXX, _______, _______, _______, _______, _______, _______, KC_PIPE,
    _______,  ANGLE,   CURLY,     PARAN,   BRACK,   XXXXXXX, _______, _______, _______, _______, _______, _______,
    NUM,      KC_LCTL, KC_LALT,   KC_LGUI, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),


/* SQL
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  -   |
 * |-----------------------------------------------------------------------------------|
 * | Tab  |      |      |      |      |      |      |      |SELECT| FROM |LFJOIN|  ON  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |      |      |      |      |      |      |      |WHERE |GRP BY|INJOIN|  AS  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |      |      |TMPTBL|DRPTBL|UPDATE| AND  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | _SQL |      |    Space    |      |  ()  |   =  | SET  |  OR  |
 * `-----------------------------------------------------------------------------------'
 */

// [_SQL] = LAYOUT_ortho_5x12(
//     KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,  KC_0,   KC_MINS,
//     KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, SELECT, FROM,   LFJOIN, SQLON,
//     KC_DEL,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, WHERE,  GRP_BY, INJOIN, SQLAS,
//     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TMPTBL, DRPTBL, UPDATE, SQLAND,
//     XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, _______, _______, XXXXXXX, PARAN,  KC_EQL, SQLSET, SQLOR
// ),

/* NUM
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |-----------------------------------------------------------------------------------|
 * | Tab  |      |      |      |      |      |      |  1   |  2   |  3   |  +   | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |      |      |      |      |      |      |  4   |  5   |  6   |  -   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|      |      |      |      |      |      |  7   |  8   |  9   |  *   |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |_QWRTY| Ctrl | Alt  | GUI  |      |    Space    |  0   |  .   |  =   |  /   |      |
 * `-----------------------------------------------------------------------------------'
 */

[_NUM] = LAYOUT_ortho_5x12(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_1,    KC_2,    KC_3,    KC_PLUS, KC_BSPC,
    KC_DEL,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_4,    KC_5,    KC_6,    KC_MINS, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_7,    KC_8,    KC_9,    KC_ASTR, KC_ENT,
    NUM,     _______, _______, _______, XXXXXXX, _______, _______, KC_0,    KC_DOT,  KC_EQL,  KC_SLSH, XXXXXXX
),


/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |Qwerty|      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CLR  |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_ortho_5x12(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, _______, _______, _______, _______, _______, QWERTY,  _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    EE_CLR,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};


layer_state_t layer_state_set_user(layer_state_t state) {

    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

    switch (get_highest_layer(state)) {
    case _RAISE:
        rgblight_setrgb (RGB_RED);
        break;
    case _LOWER:
        rgblight_setrgb (RGB_BLUE);
        break;
    // case _SQL:
    //     rgblight_setrgb (RGB_YELLOW);
    //     break;
    case _NUM:
        rgblight_setrgb (RGB_GREEN);
        break;
    case _ADJUST:
        rgblight_setrgb (RGB_PURPLE);
        break;
    default: //  for any other layers, or the default layer
        rgblight_setrgb (RGB_CYAN);
        break;
    }

  return state;
}


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
    // case LOWER:
    //   if (record->event.pressed) {
    //     layer_on(_LOWER);
    //     update_tri_layer(_LOWER, _RAISE, _ADJUST);
    //   } else {
    //     layer_off(_LOWER);
    //     update_tri_layer(_LOWER, _RAISE, _ADJUST);
    //   }
    //   return false;
    //   break;
    // case RAISE:
    //   if (record->event.pressed) {
    //     layer_on(_RAISE);
    //     update_tri_layer(_LOWER, _RAISE, _ADJUST);
    //   } else {
    //     layer_off(_RAISE);
    //     update_tri_layer(_LOWER, _RAISE, _ADJUST);
    //   }
    //   return false;
    //   break;
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

    case FDATE:
      if (record->event.pressed) {
        tap_code16(LALT(LCMD(LSFT(KC_D))));
        return false;
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

  }
  return true;
};
