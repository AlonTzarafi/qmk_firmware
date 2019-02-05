#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _NAV 1
#define _MIRROR 2
#define _RGB_KP 3 // RGB control on left side + kep-pad on right side

enum custom_keycodes {
 QWERTY = SAFE_RANGE,
 NAV,
 
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------.             .-----------------------------------------.
   * | GESC |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |   \  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |CAPS(NAV)|A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+------..-----+------+------+------+------+------+------|
   * | Ctrl | GUI  | Alt  |RGBTOG| NAV  |Space |Delete||Enter|Space |  NAV |   -  |   =  | PGUP | PGDN |
   * `------------------------------------------------''-----------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
    KC_ESCAPE, KC_1,    KC_2,    KC_3,         KC_4,     KC_5,                     KC_6,   KC_7,     KC_8,    KC_9,    KC_0,    KC_BSPC, \
    KC_TAB,    KC_Q,    KC_W,    KC_E,         KC_R,     KC_T,                     KC_Y,   KC_U,     KC_I,    KC_O,    KC_P,    KC_BSLS, \
    TT(_NAV),  KC_A,    KC_S,    KC_D,         KC_F,     KC_G,                     KC_H,   KC_J,     KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT,   KC_Z,    KC_X,    KC_C,         KC_V,     KC_B,                     KC_N,   KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
    KC_LCTL,   KC_LGUI, KC_LALT, MO(_MIRROR),  MO(_NAV), KC_SPC, KC_DEL,  KC_ENT,  KC_SPC, MO(_NAV), KC_MINS, KC_EQL,  KC_RGUI, KC_RCTL  \
  ),
  
  /* NAV
   * ,-----------------------------------------.             .-----------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 |  F11 | F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |RGBSAI|RGBVAI|RGBSAD| RESET|  [   |             |   ]  | Pgup |  Up  | Pgdn |Insert| Home |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |RGBHUD|RGBVAD|RGBHUI|      |      |             |      | Left | Down | Right|Delete| End  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |Shift |      |      |      |      |      |             | NKRO |      |      | Pause| Back | Next |
   * |------+------+------+------+------+------+------..-----+------+------+------+------+------+------|
   * | Ctrl | GUI  | Alt  |RGBMOD|      |      |      ||     |      |      |      | Mute | VOLUP| VOLDN|
   * `------------------------------------------------''-----------------------------------------------'
   */
  [_NAV] = LAYOUT( \
    KC_GRAVE, KC_F1,   KC_F2,   KC_F3,       KC_F4,   KC_F5,                    KC_F6,    KC_F7,       KC_F8,   KC_F9,   KC_F10,  _______, \
    _______,  KC_PGUP, KC_UP,   KC_PGDN,     KC_F11,  KC_F12,                   KC_INS,   KC_PGUP,     KC_UP,   KC_PGDN, KC_LBRC, KC_RBRC, \
    KC_HOME,  KC_LEFT, KC_DOWN, KC_RGHT,     KC_END,  _______,                  KC_HOME,  KC_LEFT,     KC_DOWN, KC_RGHT, KC_END,  _______, \
    _______,  KC_MPRV, KC_MNXT, KC_MPLY,     KC_VOLD, KC_VOLU,                  _______,  _______,     _______, _______, _______, _______, \
    _______,  _______, _______, MO(_RGB_KP), _______, KC_ENT, KC_BSPC, _______, _______,  MO(_RGB_KP), KC_VOLD, KC_VOLU, _______, _______  \
  ),
  
  [_MIRROR] = LAYOUT( \
    KC_BSPC,   KC_0,    KC_9,    KC_8,    KC_7,        KC_6,                       XXXXXXX,           XXXXXXX,     XXXXXXX, XXXXXXX, KC_F11,     KC_F12,  \
    KC_BSLS,   KC_P,    KC_O,    KC_I,    KC_U,        KC_Y,                       XXXXXXX,           KC_R,        KC_INS,  XXXXXXX, KC_PSCREEN, XXXXXXX, \
    KC_QUOT,   KC_SCLN, KC_L,    KC_K,    KC_J,        KC_H,                       XXXXXXX,           XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, \
    KC_RSFT,   KC_SLSH, KC_DOT,  KC_COMM, KC_M,        KC_N,                       MAGIC_TOGGLE_NKRO, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX,    KC_RSFT, \
    KC_RCTL,   KC_EQL,  KC_MINS, _______, MO(_RGB_KP), KC_SPC,  KC_ENT,  KC_ENT,   KC_SPACE,          MO(_RGB_KP), XXXXXXX, XXXXXXX, KC_RGUI,    KC_RCTL  \
  ),
  
  [_RGB_KP] = LAYOUT( \
    _______, _______,        _______, _______, _______,   _______,                   XXXXXXX, KC_NUMLOCK, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS, XXXXXXX, \
    _______, RGB_SAI,        RGB_VAI, RGB_SAD, RESET,     _______,                   XXXXXXX, KC_KP_7,    KC_KP_8,     KC_KP_9,        KC_KP_PLUS,  XXXXXXX, \
    _______, RGB_HUD,        RGB_VAD, RGB_HUI, _______,   _______,                   XXXXXXX, KC_KP_4,    KC_KP_5,     KC_KP_6,        KC_KP_PLUS,  XXXXXXX, \
    _______, RGB_TOG,        RGB_MOD, RGB_M_R, _______,   _______,                   XXXXXXX, KC_KP_1,    KC_KP_2,     KC_KP_3,        KC_KP_ENTER, XXXXXXX, \
    _______, KC_APPLICATION, _______, _______, _______,   _______, _______, _______, _______, KC_KP_0,    KC_KP_0,     KC_KP_DOT,      KC_KP_ENTER, XXXXXXX  \
  ),
  
};

/*
#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistant_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    //case COLEMAK:
      //if (record->event.pressed) {
        //#ifdef AUDIO_ENABLE
          //PLAY_NOTE_ARRAY(tone_colemak, false, 0);
        //#endif
        //persistant_default_layer_set(1UL<<_COLEMAK);
      //}
      //return false;
      //break;
  }
  return true;
}

*/
