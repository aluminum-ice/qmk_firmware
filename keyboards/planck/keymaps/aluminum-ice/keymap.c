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
#define SPACEFN LT(_SQL, KC_SPC)

enum planck_keycodes {

  QWERTY = SAFE_RANGE,
  PLOVER,
  EXT_PLV,
  MC_COPY,
  FDATE,   // Dates
  GITCLN,  // git clone
  GITCHK,  // git checkout
  GITPULL, // git pull
  GITPUSH, // git push
  GITADD,  // git add 
  GITCOMM, // git commit -m ''
  GITSTAT, // git status
  GITBRCH, // git branch -a
  APTUP,   // apt-get update && apt-get dist-upgrade
  ANGLE,
  BRACK,
  TICK,
  CURLY,
  PARAN,
  SELECT,
  FROM,
  SQLWHR,
  GRP_BY,
  ORD_BY,
  LFJOIN,
  INJOIN,
  TMPTBL,
  DRPTBL,
  UPDATE,
  SQLSET,
  SQLON,
  SQLIN,
  SQLAS,
  SQLAND,
  SQLOR,
  SQLCASE,
  SQLWHEN,
  SQLTHEN,
  SQLELSE,
  SQLEND,
  SQLTUP,
  SQLTLR,
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
 * | Ctrl |  Alt | GUI  | _SQL |_Lower|   SpaceFN   |_Raise| Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,      KC_BSPC,
    KC_ESC,   HOME_A,  HOME_S,  HOME_D,  HOME_F,  KC_G,    KC_H,    HOME_J,  HOME_K,  HOME_L,  HOME_SCLN, KC_QUOT,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_ENT ,
    KC_LCTL,  KC_LALT, KC_LGUI, SQL,     LOWER,   SPACEFN, SPACEFN, RAISE,   KC_LEFT, KC_DOWN, KC_UP,     KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |   -  |   =  |   [  |   ]  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | _NUM | Ctrl |  Alt | GUI  |_Lower|   SpaceFN   |_Raise| Home | PgUP | PgDN |  End |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,  KC_ASTR,  KC_LPRN, KC_RPRN, _______,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,  KC_PLUS,  KC_LCBR, KC_RCBR, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_MINS,  KC_EQL,   KC_LBRC, KC_RBRC, _______,
    NUM,     KC_LCTL, KC_LALT, KC_LGUI, _______, _______, _______, _______,  KC_HOME,  KC_PGDN, KC_PGUP, KC_END
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | CAPS |      |SNAKE |      |      |APTUP |      | CLONE|  ADD |COMMIT| PUSH |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|  <>  |  {}  |  ()  |  []  |      |      |CHKOUT|STATUS|BRANCH| PULL |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | _NUM | Ctrl |  Alt | GUI  |_Lower|   SpaceFN   |_Raise| Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_GRV,   KC_1,    KC_2,      KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    CAPSWORD, XXXXXXX, SNAKECASE, XXXXXXX, XXXXXXX, APTUP,   XXXXXXX, GITCLN,  GITADD,  GITCOMM, GITPUSH, KC_PIPE,
    _______,  ANGLE,   CURLY,     PARAN,   BRACK,   TICK,    XXXXXXX, GITCHK,  GITSTAT, GITBRCH, GITPULL, _______,
    NUM,      KC_LCTL, KC_LALT,   KC_LGUI, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY
),

/* SQL
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |TMPTBL|DRPTBL|UPDATE| CASE | WHEN | THEN |      |SELECT| FROM |LFJOIN|  ON  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  AS  |      |      | ELSE | END  |      |      |WHERE |GRP BY|INJOIN|  IN  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|      |      |      | TUP  | TDN  |      |      |      |ORD BY|      | AND  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | _SQL |      |    SPACEFN  |      |  ()  |   =  | SET  |  OR  |
 * `-----------------------------------------------------------------------------------'
 */

[_SQL] = LAYOUT_planck_grid(
    KC_TAB,  TMPTBL,  DRPTBL,  UPDATE,  SQLCASE, SQLWHEN, SQLTHEN, XXXXXXX, SELECT,  FROM,   LFJOIN,  SQLON,
    KC_DEL,  SQLAS,   XXXXXXX, XXXXXXX, SQLELSE, SQLEND,  XXXXXXX, XXXXXXX, SQLWHR,  GRP_BY, INJOIN,  SQLIN,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, SQLTUP,  SQLTLR,  XXXXXXX, XXXXXXX, XXXXXXX, ORD_BY, XXXXXXX, SQLAND,
    XXXXXXX, XXXXXXX, XXXXXXX, _______, XXXXXXX, _______, _______, XXXXXXX, PARAN,   KC_EQL, SQLSET,  SQLOR
),

/* NUM
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |      |      |      |      |      |      |  1   |  2   |  3   |  +   | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |      |      |      |      |      |      |  4   |  5   |  6   |  -   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|  <>  |  {}  |  ()  |  []  |      |      |  7   |  8   |  9   |  *   |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |_QWRTY| Ctrl | Alt  | GUI  |      |   SpaceFN   |  0   |  .   |  =   |  /   |      |
 * `-----------------------------------------------------------------------------------'
 */

[_NUM] = LAYOUT_planck_grid(
    KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_1, KC_2,   KC_3,   KC_PLUS, KC_BSPC,
    KC_DEL,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_4, KC_5,   KC_6,   KC_MINS, XXXXXXX,
    _______, ANGLE,   CURLY,   PARAN,   BRACK,   XXXXXXX, XXXXXXX, KC_7, KC_8,   KC_9,   KC_ASTR, KC_ENT,
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
 * | CLR  |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, QK_BOOT, DB_TOGG, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_DEL ,
    _______, _______, MU_NEXT, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, _______, PLOVER,  _______,
    _______, AU_PREV, AU_NEXT, MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  _______, _______, _______, _______, _______,
    EE_CLR,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {

    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

    switch (get_highest_layer(state)) {
    case _RAISE:
        rgblight_setrgb (RGB_RED);
        break;
    case _LOWER:
        rgblight_setrgb (RGB_BLUE);
        break;
    case _SQL:
        rgblight_setrgb (RGB_YELLOW);
        break;
    case _NUM:
        rgblight_setrgb (RGB_GREEN);
        break;
    case _PLOVER:
        rgblight_setrgb (0x00,  0xFF, 0x00);
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




// // Light LEDs 6 to 9 and 12 to 15 red when caps lock is active. Hard to ignore!
// const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {6, 4, HSV_RED},       // Light 4 LEDs, starting with LED 6
//     {12, 4, HSV_RED}       // Light 4 LEDs, starting with LED 12
// );
// // Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
// const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {9, 2, HSV_CYAN}
// );
// // Light LEDs 11 & 12 in purple when keyboard layer 2 is active
// const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {11, 2, HSV_PURPLE}
// );
// // Light LEDs 13 & 14 in green when keyboard layer 3 is active
// const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {13, 2, HSV_GREEN}
// );

// // Now define the array of layers. Later layers take precedence
// const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
//     my_capslock_layer,
//     my_layer1_layer,    // Overrides caps lock layer
//     my_layer2_layer,    // Overrides other layers
//     my_layer3_layer     // Overrides other layers
// );

// void keyboard_post_init_user(void) {
//     // Enable the LED layers
//     rgblight_layers = my_rgb_layers;
// }

// bool led_update_user(led_t led_state) {
//     rgblight_set_layer_state(0, led_state.caps_lock);
//     return true;
// }

// layer_state_t default_layer_state_set_user(layer_state_t state) {
//     rgblight_set_layer_state(1, layer_state_cmp(state, _RAISE));
//     return state;
// }

// layer_state_t layer_state_set_user(layer_state_t state) {
//     rgblight_set_layer_state(2, layer_state_cmp(state, _FN));
//     rgblight_set_layer_state(3, layer_state_cmp(state, _LOWER));
//     return state;
// }


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
        eeconfig_read_keymap(&keymap_config);
        keymap_config.nkro = 1;
        eeconfig_update_keymap(&keymap_config);
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

    case FDATE:
      if (record->event.pressed) {
        tap_code16(LALT(LCMD(LSFT(KC_D))));
        return false;
      }
      break;

    case GITCLN:
      if (record->event.pressed) {
          SEND_STRING("git clone ");
      } else {
        // When keycode is released
      }
      break;

    case GITCHK:
      if (record->event.pressed) {
          SEND_STRING("git checkout ");
      } else {
        // When keycode is released
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

     case TICK:
      if (record->event.pressed) {
          SEND_STRING("``");
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

    case SQLWHR:
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

    case ORD_BY:
      if (record->event.pressed) {
          SEND_STRING("ORDER BY ");
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

    case SQLIN:
      if (record->event.pressed) {
          SEND_STRING("IN ");
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

    case SQLCASE:
      if (record->event.pressed) {
          SEND_STRING("CASE ");
          tap_code(KC_ENT);  // Move cursor to next line
          tap_code(KC_TAB);  // Tab cursor
          SEND_STRING("WHEN ");
      } else {
        // When keycode is released
      }
      break;

    case SQLWHEN:
      if (record->event.pressed) {
          SEND_STRING("WHEN ");
      } else {
        // When keycode is released
      }
      break;

    case SQLTHEN:
      if (record->event.pressed) {
          SEND_STRING("THEN ");
      } else {
        // When keycode is released
      }
      break;

    case SQLELSE:
      if (record->event.pressed) {
          SEND_STRING("ELSE ");
      } else {
        // When keycode is released
      }
      break;

    case SQLEND:
      if (record->event.pressed) {
          SEND_STRING("END AS ");
      } else {
        // When keycode is released
      }
      break;

    case SQLTUP:
      if (record->event.pressed) {
          SEND_STRING("TRIM(UPPER())");
          tap_code(KC_LEFT);  // Move cursor between quotes
          tap_code(KC_LEFT);  // Move cursor between quotes
      } else {
        // When keycode is released
      }
      break;

    case SQLTLR:
      if (record->event.pressed) {
          SEND_STRING("TRIM(LOWER())");
          tap_code(KC_LEFT);  // Move cursor between quotes
          tap_code(KC_LEFT);  // Move cursor between quotes
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
