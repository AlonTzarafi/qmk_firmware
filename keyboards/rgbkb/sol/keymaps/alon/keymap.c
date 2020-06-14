#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
    
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    /* _COLEMAK, */
    _FN,
    _MIRROR,
    _ENC_VOLUME,
    _ENC_MOUSE,
    _ENC_PHOTOSHOP,
    _ENC_BLENDER,
    _RGBSTF,
    /* _ADJ */
};

// For Photoshop:
uint8_t opacity = 60;
uint8_t opacity_increment = 10;

// Keycode defines for layers
#define QWERTY   DF(_QWERTY)
/* #define COLEMAK  DF(_COLEMAK) */
#define FN       MO(_FN)
#define MIRROR   MO(_MIRROR)
#define RGBSTF   MO(_RGBSTF)
/* #define ADJ      MO(_ADJ) */

enum custom_keycodes {
  RGBRST = SAFE_RANGE,
  RGB_MENU,
  ENC_VOL,
  ENC_MOUS,
  ENC_PHOTOSHOP,
  ENC_BLENDER,
  ENC_OPACI_1,
  ENC_OPACI_2,
  ENC_OPACI_3,
};

#define FN_ESC   LT(_FN, KC_ESC)
#define FN_CAPS  LT(_FN, KC_CAPS)
#define SPC_CTL  MT(MOD_LCTL, KC_SPC)
#define DEL_CTL  MT(MOD_LCTL, KC_DEL)
/* #define DEL_ENT  ACTION_TAP_DANCE_DOUBLE(KC_DEL, KC_ENT) */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
   * ,------------------------------------------------.  ,------------------------------------------------.
   * | GESC |   1  |   2  |   3  |   4  |   5  |   -  |  |   =  |   6  |   7  |   8  |   9  |   0  | BkSp |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |   [  |  |   ]  |   Y  |   U  |   I  |   O  |   P  |   \  |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |FN(CAPS)| A  |   S  |   D  |   F  |   G  |   (  |  |   )  |   H  |   J  |   K  |   L  |   ;  |   '  |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |Shift |   Z  |   X  |   C  |   V  |   B  |   {  |  |   }  |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * | Ctrl |  Win |  Alt |  RGB | ADJ  | Space| DEL  | | Enter| Space|  FN  | Left | Down | Up   |Right |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------'
   *                                    | Space| DEL  |  | Enter| Space|
   *                                    `-------------'  `-------------'
   */
  /* [_QWERTY] = LAYOUT( \ */
  /*    KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, KC_MINS,  KC_EQL,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC, \ */
  /*    KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_LBRC, KC_RBRC,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSLS, \ */
  /*        FN,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_LPRN, KC_RPRN,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT, \ */
  /*   KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE, KC_RCBR,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT, \ */
  /*   _______, KC_LGUI, KC_LALT,  MIRROR,      FN, KC_MUTE, KC_MUTE, KC_MUTE, SPC_CTL,      FN, KC_MINS,  KC_EQL, KC_RGUI, KC_RCTL, \ */
  /*                                                SPC_CTL,  KC_DEL,  KC_ENT, SPC_CTL \ */
  /* ), */

  /* Colemak
   * ,------------------------------------------------.  ,------------------------------------------------.
   * | GESC |   1  |   2  |   3  |   4  |   5  |   -  |  |   =  |   6  |   7  |   8  |   9  |   0  | BkSp |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   F  |   P  |   B  |   [  |  |   ]  |   J  |   L  |   U  |   Y  |   ;  |   \  |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |FN(CAPS)| A  |   R  |   S  |   T  |   G  |   (  |  |   )  |   K  |   N  |   E  |   I  |   O  |   '  |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |Shift |   Z  |   X  |   C  |   D  |   V  |   {  |  |   }  |   M  |   H  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * | Ctrl |  Win |  Alt |  RGB | ADJ  | Space| DEL  |  | Enter| Space|  FN  | Left | Down | Up   |Right |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------'
   *                                    | Space| DEL  |  | Enter| Space|
   *                                    `-------------'  `-------------'
   */
  /* [_COLEMAK] = LAYOUT( \ */
  /*   KC_GESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, KC_MINS,  KC_EQL,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC, \ */
  /*    KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G, KC_LBRC, KC_RBRC,    KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSLS, \ */
  /*   FN_CAPS,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D, KC_LPRN, KC_RPRN,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT, \ */
  /*   KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_LCBR, KC_RCBR,    KC_K,    KC_M, KC_COMM, KC_DOT,  KC_SLSH,  KC_ENT, \ */
  /*   KC_LCTL, KC_LGUI, KC_LALT, RGB_TOG,     ADJ,  KC_SPC,  KC_DEL,  KC_ENT,  KC_SPC,      FN, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, \ */
  /*                                                 KC_SPC,  KC_DEL,  KC_ENT,  KC_SPC \ */
  /* ), */

  /* FN
   * ,------------------------------------------------.  ,------------------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |  |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | PGDN |  UP  | PGUP |      |      |      |  |      |      | PGDN |  UP  | PGUP | PRINT| HOME |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | LEFT | DOWN | RIGHT|      |      |      |  |      |      | LEFT | DOWN | RIGHT|INSERT| END  |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |RGBMOD|      |      |      |  |      |      | PLAY | NEXT | MUTE | VOL- | VOL+ |
   * `------+------+------+------+------+------+------|  |------+------+------+------+------+------+------'
   *                                    |      |      |  |      |      |
   *                                    `-------------'  `-------------'
   */
  /* [_FN] = LAYOUT( \ */
  /*     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, _______, KC_PSCR,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, \ */
  /*   _______, KC_PGDN,   KC_UP, KC_PGUP, _______, _______, _______, KC_SLCK, _______, KC_PGDN,   KC_UP, KC_PGUP, KC_PSCR, KC_HOME, \ */
  /*   _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, KC_NLCK, _______, KC_LEFT, KC_DOWN, KC_RGHT,  KC_INS,  KC_END, \ */
  /*   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \ */
  /*   _______, _______, _______, RGB_MOD, _______, _______, _______, _______, _______, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, \ */
  /*                                                _______, _______, _______, _______ \ */
  /* ), */
                                                              
  [_QWERTY] = LAYOUT( \
     KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, KC_MINS,  KC_EQL,   KC_6,  KC_7,    KC_8,   KC_9,    KC_0, KC_BSPC, \
     KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_LBRC, KC_RBRC,   KC_Y,  KC_U,    KC_I,   KC_O,    KC_P, KC_BSLS, \
         FN,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_LPRN, KC_RPRN,   KC_H,  KC_J,    KC_K,   KC_L, KC_SCLN, KC_QUOT, \
    KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_MUTE, KC_RCBR,   KC_N,  KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, \
    KC_LCTL, KC_LGUI, KC_LALT,  MIRROR,      FN, KC_MUTE, KC_MUTE, KC_MUTE, SPC_CTL,    FN, KC_MINS, KC_EQL, KC_RGUI, KC_RCTL, \
                                                  KC_SPC, DEL_CTL,  KC_ENT, SPC_CTL \
  ),
  [_FN] = LAYOUT( \
   KC_GRAVE,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, _______, _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_DEL, \
    _______, KC_PGUP,   KC_UP, KC_PGDN,  KC_F11,  KC_F12, _______, _______, _______, KC_PGUP,   KC_UP, KC_PGDN, KC_LBRC, KC_RBRC, \
    KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END , _______, _______, _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END,  KC_END, \
    _______, KC_MPRV, KC_MNXT, KC_MPLY, KC_VOLD, KC_VOLU, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, RGBSTF , _______, _______, _______, _______, _______, _______, KC_VOLD, KC_VOLU, _______, _______, \
                                                  KC_ENT, _______, _______, _______ \
  ),
  
  [_MIRROR] = LAYOUT( \
    KC_BSPC,    KC_0,    KC_9,    KC_8,    KC_7,    KC_6,  KC_EQL, KC_MINS,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC, \
    KC_BSLS,    KC_P,    KC_O,    KC_I,    KC_U,    KC_Y, KC_RBRC, KC_LBRC,    KC_Y,    KC_U,  KC_INS,    KC_O, KC_PSCR, KC_BSLS, \
    KC_QUOT, KC_SCLN,    KC_L,    KC_K,    KC_J,    KC_H, KC_RPRN, KC_LPRN,    KC_H,    KC_J,    KC_K, KC_CAPS, KC_SCLN, KC_QUOT, \
    KC_RSFT, KC_SLSH,  KC_DOT, KC_COMM,    KC_M,    KC_N, _______, KC_LCBR,    KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT, \
    KC_RCTL,  KC_EQL, KC_MINS, _______,  RGBSTF, _______, _______, KC_MUTE,  KC_SPC,      FN, KC_MINS,  KC_EQL, KC_RGUI, KC_RCTL, \
                                                 _______, _______,  KC_ENT,  KC_SPC \
  ),
  
  [_RGBSTF] =  LAYOUT( \
      KC_F1,  KC_F10       ,   KC_F9,   KC_F8,   KC_F7,   KC_F6, _______      , _______    , _______, KC_NO, KC_SLSH, KC_ASTR, KC_MINS, _______, \
    _______, RGB_SAD       , RGB_VAI, RGB_SAI,   RESET, _______, _______      , ENC_BLENDER, _______, KC_7,     KC_8,    KC_9, KC_PLUS, _______, \
    _______, RGB_HUD       , RGB_VAD, RGB_HUI,  RGBRST, _______, _______      , _______    , _______, KC_4,     KC_5,    KC_6, KC_PLUS, _______, \
    _______, RGB_SPD       , XXXXXXX, RGB_SPI,RGB_MENU, _______, ENC_PHOTOSHOP, _______    , _______, KC_1,     KC_2,    KC_3,  KC_ENT, _______, \
    RGB_TOG, KC_APPLICATION, RGB_MOD, _______, _______,ENC_MOUS, ENC_VOL      , ENC_BLENDER, _______, KC_0,     KC_0,  KC_DOT,  KC_ENT, _______, \
                                                 _______, _______      , _______    , _______ \
  ),

  // Using actual numpad keys: it's annoying because of numlock
  /* [_RGBSTF] =  LAYOUT( \ */
  /*     KC_F1,  KC_F10       ,   KC_F9,   KC_F8,   KC_F7,   KC_F6, _______      , _______    , _______, KC_NUMLOCK, KC_PSLS, KC_PAST, KC_PMNS, _______, \ */
  /*   _______, RGB_SAD       , RGB_VAI, RGB_SAI,   RESET, _______, _______      , ENC_BLENDER, _______,      KC_P7,   KC_P8,   KC_P9, KC_PPLS, _______, \ */
  /*   _______, RGB_HUD       , RGB_VAD, RGB_HUI,  RGBRST, _______, _______      , _______    , _______,      KC_P4,   KC_P5,   KC_P6, KC_PPLS, _______, \ */
  /*   _______, RGB_SPD       , XXXXXXX, RGB_SPI,RGB_MENU, _______, ENC_PHOTOSHOP, _______    , _______,      KC_P1,   KC_P2,   KC_P3, KC_PENT, RGB_VAI, \ */
  /*   RGB_TOG, KC_APPLICATION, RGB_MOD, _______, _______,ENC_MOUS, ENC_VOL      , ENC_BLENDER, _______,      KC_P0,   KC_P0, KC_PDOT, KC_PENT, RGB_VAD, \ */
  /*                                                _______, _______      , _______    , _______ \ */
  /* ), */

  /* ADJ
   * ,------------------------------------------------.  ,------------------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |  |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | SAD  | VAI  | SAI  | RESET|      |      |  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------|------|  |------|------+------+------+------+------+------|
   * |      | HUD  | VAD  | HUI  |RGBRST|      |      |  |      |      |QWERTY|COLEMK|      |      |      |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      | SPD  |      | SPI  |      |      |      |  |      |      |      |RGBTOG|  HUI |  SAI | VAI  |
   * |------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
   * |      |      |      |RGBMOD(|      |      |      |  |      |      |     |RGBRMOD| HUD |  SAD | VAD  |
   * `------+------+------+------+------+------+------|  |------+------+------+------+------+------+------'
   *                                    |      |      |  |      |      |
   *                                    `-------------'  `-------------'
   */

  /* [_ADJ] =  LAYOUT( \ */
  /*     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, _______, _______,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12, \ */
  /*   _______, RGB_SAD, RGB_VAI, RGB_SAI,   RESET, _______, _______, _______, _______, _______, _______, _______, _______, _______, \ */
  /*   _______, RGB_HUD, RGB_VAD, RGB_HUI,  RGBRST, _______, _______, _______, _______, _______, _______, _______, _______, _______, \ */
  /*   _______, RGB_SPD, _______, RGB_SPI, _______, _______, _______, _______, _______, RGB_SPI, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \ */
  /*   _______, _______, _______, RGB_MOD, _______, _______, _______, _______, _______, RGB_SPD, RGB_RMOD,RGB_HUD, RGB_SAD, RGB_VAD, \ */
  /*                                                _______, _______, _______, _______ \ */
  /* ), */

  /* --------- Encoder layers ---------- */
  
  [_ENC_VOLUME] =  LAYOUT( \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, KC_MUTE, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, KC_MUTE, KC_MUTE, _______, _______, _______, _______,_______, _______, _______, \
                                                 _______, _______, _______, _______ \
  ),
  [_ENC_MOUSE] =  LAYOUT( \
    _______, _______, _______, _______, _______, _______, KC_ACL2, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, KC_ACL1, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, KC_ACL0, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, KC_BTN3, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, KC_BTN1, KC_BTN2, _______, _______, _______, _______,_______, _______, _______, \
                                                 _______, _______, _______, _______ \
  ),
  [_ENC_PHOTOSHOP] =  LAYOUT( \
    _______, _______, _______, _______, _______, _______, ENC_OPACI_1, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, ENC_OPACI_2, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, ENC_OPACI_3, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, KC_E       , _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, KC_B   , KC_M       , _______, _______, _______, _______,_______, _______, _______, \
                                                 _______, _______    , _______, _______ \
  ),
  [_ENC_BLENDER] =  LAYOUT( \
    _______, _______, _______, _______, _______, _______       , _______     , _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______       , _______     , _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______       , _______     , _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______       , LCTL(KC_I)  , _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, LCTL(KC_GRAVE), LCTL(KC_SPC), _______, _______, _______, _______,_______, _______, _______, \
                                                 _______       , _______     , _______, _______ \
  ),
  
  
};

// For RGBRST Keycode
#if defined(RGB_MATRIX_ENABLE)
void rgb_matrix_increase_flags(void)
{
    switch (rgb_matrix_get_flags()) {
        case LED_FLAG_ALL: {
            rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
            rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER: {
            rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
            rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        case LED_FLAG_UNDERGLOW: {
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_disable_noeeprom();
            }
            break;
        default: {
            rgb_matrix_set_flags(LED_FLAG_ALL);
            rgb_matrix_enable_noeeprom();
            }
            break;
    }
}

void rgb_matrix_decrease_flags(void)
{
    switch (rgb_matrix_get_flags()) {
        case LED_FLAG_ALL: {
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_disable_noeeprom();
            }
            break;
        case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER: {
            rgb_matrix_set_flags(LED_FLAG_ALL);
            rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        case LED_FLAG_UNDERGLOW: {
            rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
            rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        default: {
            rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
            rgb_matrix_enable_noeeprom();
            }
            break;
    }
}
#endif

#ifdef RGB_OLED_MENU
uint8_t rgb_encoder_state = 4;

typedef void (*rgb_matrix_f)(void);

const rgb_matrix_f rgb_matrix_functions[6][2] = {
    { rgb_matrix_increase_hue, rgb_matrix_decrease_hue },
    { rgb_matrix_increase_sat, rgb_matrix_decrease_sat },
    { rgb_matrix_increase_val, rgb_matrix_decrease_val },
    { rgb_matrix_increase_speed, rgb_matrix_decrease_speed },
    { rgb_matrix_step, rgb_matrix_step_reverse },
    { rgb_matrix_increase_flags, rgb_matrix_decrease_flags }
};
#endif

#ifdef ENCODER_ENABLE

static pin_t encoders_pad_a[] = ENCODERS_PAD_A;
#define NUMBER_OF_ENCODERS (sizeof(encoders_pad_a)/sizeof(pin_t))

const uint16_t PROGMEM encoders[][NUMBER_OF_ENCODERS * 2][2]  = {
    [_QWERTY] = ENCODER_LAYOUT( \
        KC_VOLU, KC_VOLD,
        KC_VOLU, KC_VOLD
    ),
    /* [_COLEMAK] = ENCODER_LAYOUT( \ */
    /*     _______, _______, */
    /*     _______, _______ */
    /* ), */
    [_FN] = ENCODER_LAYOUT( \
        _______, _______,
        _______, _______
    ),
    [_RGBSTF] = ENCODER_LAYOUT( \
        _______, _______,
        _______, _______
    )
};

/* void encoder_update_user(uint8_t index, bool clockwise) { */
/*   if (!is_keyboard_master()) */
/*     return; */

/* #ifdef RGB_OLED_MENU */
/*   if (index == RGB_OLED_MENU) { */
/*     (*rgb_matrix_functions[rgb_encoder_state][clockwise])(); */
/*   } else */
/* #endif */
/*   { */
/*     uint8_t layer = biton32(layer_state); */
/*     uint16_t keycode = encoders[layer][index][clockwise]; */
/*     while (keycode == KC_TRANSPARENT && layer > 0) */
/*     { */
/*       layer--; */
/*       if ((layer_state & (1 << layer)) != 0) */
/*           keycode = encoders[layer][index][clockwise]; */
/*     } */
/*     if (keycode != KC_TRANSPARENT) */
/*       tap_code16(keycode); */
/*   } */
/* } */
#endif


#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
  /* if (index == 0) { /\* First encoder *\/ */
  /*   if (clockwise) { */
  /*     tap_code(KC_VOLD); */
  /*   } else { */
  /*     tap_code(KC_VOLU); */
  /*   } */
  /* } else if (index == 1) { /\* Second encoder*\/ */
  /*   if (clockwise) { */
  /*     tap_code(KC_VOLD); */
  /*   } else { */
  /*     tap_code(KC_VOLU); */
  /*   } */
  /* } */

    /* layout: */
    /* 2        |        X */
    /* 1, 0     |    3 , X */

    clockwise = !clockwise;
    
    bool volume_mode = layer_state_is(_ENC_VOLUME);
    if (!layer_state_is(_ENC_MOUSE) && !layer_state_is(_ENC_PHOTOSHOP) && !layer_state_is(_ENC_BLENDER)) {
        /* For keyboard start up */
        /* No other modes: default to volume mode */
        volume_mode = true;
    }

    if (layer_state_is(_FN) && (index == 0 || index == 1)) {
        // FN key forces first 2 knobs to do standard volume and undo/redo
        volume_mode = true;
    }

    // ------------ TODO:
    //enc 3
    // FN is tab froward/backward
    //enc 4
    // FN is next/prev media
    
    if (volume_mode) {
        switch (index) {
        case 0:
            /* Undo redo */
            if (!layer_state_is(_FN)) {
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
            } else {
                if (clockwise) {
                    tap_code(KC_VOLU);
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                    tap_code(KC_VOLD);
                }
            }
            break;
        case 1:
            if (clockwise) {
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                tap_code(KC_Z);
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
            } else {
                register_code(KC_LCTL);
                tap_code(KC_Z);
                unregister_code(KC_LCTL);
            }
            break;
        case 2:
            if (!layer_state_is(_FN)) {
                if (clockwise) {
                    tap_code(KC_WH_D);
                } else {
                    tap_code(KC_WH_U);
                }
            } else {
                if (clockwise) {
                    tap_code(KC_WH_R);
                } else {
                    tap_code(KC_WH_L);
                }
            }
            break;
        case 3:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
        }
    } else if (layer_state_is(_ENC_MOUSE)) {
        switch (index) {
        case 0:
            if (clockwise) {
                tap_code(KC_MS_R);
            } else {
                tap_code(KC_MS_L);
            }
            break;
        case 1:
            if (clockwise) {
                tap_code(KC_MS_D);
            } else {
                tap_code(KC_MS_U);
            }
            break;
        case 2:
            if (!layer_state_is(_FN)) {
                if (clockwise) {
                    tap_code(KC_WH_D);
                } else {
                    tap_code(KC_WH_U);
                }
            } else {
                if (clockwise) {
                    tap_code(KC_WH_R);
                } else {
                    tap_code(KC_WH_L);
                }
            }
            break;
        case 3:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
        }
    } else if (layer_state_is(_ENC_PHOTOSHOP)) {
        // ---------------------- PHOTOSHOP !!!!!!!!!!!!!!
        switch (index) {
        case 0:
            if (clockwise) {
                register_code(KC_LSFT);
                tap_code(KC_RBRC);
                unregister_code(KC_LSFT);
            } else {
                register_code(KC_LSFT);
                tap_code(KC_LBRC);
                unregister_code(KC_LSFT);
            }
            break;
        case 1:
            if (clockwise) {
                tap_code(KC_RBRC);
            } else {
                tap_code(KC_LBRC);
            }
            break;
        case 2:
            if (!layer_state_is(_FN)) {
                if (clockwise) {
                    if (opacity > 100 - opacity_increment) {
                        opacity = 100;
                    } else {
                        opacity += opacity_increment;
                    }
                } else {
                    if (opacity < 0 + opacity_increment) {
                        opacity = 0;
                    } else {
                        opacity -= opacity_increment;
                    }
                }
                
                uint8_t opacity_to_type = opacity;
                if (opacity_to_type == 0) {
                    opacity_to_type = 1;
                }
                
                uint8_t last = opacity_to_type % 10;
                uint8_t first = opacity_to_type / 10 % 10;
                uint8_t digits[2] = {first, last};
                for(int i = 0; i < 2; ++i) {
                    switch (digits[i]) {
                    case 0: tap_code(KC_0); break;
                    case 1: tap_code(KC_1); break;
                    case 2: tap_code(KC_2); break;
                    case 3: tap_code(KC_3); break;
                    case 4: tap_code(KC_4); break;
                    case 5: tap_code(KC_5); break;
                    case 6: tap_code(KC_6); break;
                    case 7: tap_code(KC_7); break;
                    case 8: tap_code(KC_8); break;
                    case 9: tap_code(KC_9); break;
                    }
                }
            } else {
                if (clockwise) {
                    tap_code(KC_DOT);
                } else {
                    tap_code(KC_COMMA);
                }
            }
            break;
        case 3:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
        }
        
    } else if (layer_state_is(_ENC_BLENDER)) {
    }
}
#endif


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t reset_timer;
  
  int fn_action = 0;
  int mirror_action = 0;
  int rgbstf_action = 0;
  int ctl_action = 0;
  
  switch (keycode) {
    case RGBRST:
#if defined(RGBLIGHT_ENABLE)
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
#elif defined(RGB_MATRIX_ENABLE)
        if (record->event.pressed) {
          eeconfig_update_rgb_matrix_default();
        }
#endif
      return false;
    case RESET:
      if (record->event.pressed) {
          reset_timer = timer_read();
      } else {
          if (timer_elapsed(reset_timer) >= 500) {
              reset_keyboard();
          }
      }
      return false;
#if defined(RGB_MATRIX_ENABLE) && defined(KEYBOARD_rgbkb_sol_rev2)
    case RGB_TOG:
      if (record->event.pressed) {
        rgb_matrix_increase_flags();
      }
      return false;
#endif
    case RGB_MENU:
#ifdef RGB_OLED_MENU
      if (record->event.pressed) {
        if (get_mods() & MOD_MASK_SHIFT) {
          rgb_encoder_state = (rgb_encoder_state - 1);
          if (rgb_encoder_state > 5) {
            rgb_encoder_state = 5;
          }
        } else {
          rgb_encoder_state = (rgb_encoder_state + 1) % 6;
        }
      }
#endif
      return false;
  case ENC_VOL:
      if (record->event.pressed) {
          layer_on(_ENC_VOLUME);
          layer_off(_ENC_MOUSE);
          layer_off(_ENC_PHOTOSHOP);
      }
      return false;
  case ENC_MOUS:
      if (record->event.pressed) {
          layer_off(_ENC_VOLUME);
          layer_on(_ENC_MOUSE);
          layer_off(_ENC_PHOTOSHOP);
      }
      return false;
  case ENC_PHOTOSHOP:
      if (record->event.pressed) {
          layer_off(_ENC_VOLUME);
          layer_off(_ENC_MOUSE);
          layer_on(_ENC_PHOTOSHOP);
      }
      return false;
  case ENC_OPACI_1:
      opacity_increment = 5;
      return false;
  case ENC_OPACI_2:
      opacity_increment = 10;
      return false;
  case ENC_OPACI_3:
      opacity_increment = 20;
      return false;
  case FN:
      if (record->event.pressed) { fn_action = 1;} else { fn_action = -1;}
      break;
  case MIRROR:
      if (record->event.pressed) { mirror_action = 1;} else { mirror_action = -1;}
      break;
  case RGBSTF:
      if (record->event.pressed) { rgbstf_action = 1;} else { rgbstf_action = -1;}
      
      break;
  case KC_LCTL:
  case KC_RCTL:
      
  case SPC_CTL:
  case KC_SPC:
      
  case DEL_CTL:
  case KC_DEL:
      
      if (record->event.pressed) { ctl_action = 1;} else { ctl_action = -1;}
      break;
  }

  bool fn_active = layer_state_is(_FN);
  bool mirror_active = layer_state_is(_MIRROR);
  bool rgbstf_active = layer_state_is(_RGBSTF);
  /* bool ctl_active = (keyboard_report->mods & (MOD_BIT(KC_LCTL))); */
  bool ctl_active = (get_mods() & ((MOD_BIT(KC_LCTL)) | (MOD_BIT(KC_RCTL))));
  
  if (fn_action == 1) fn_active = true;
  if (fn_action == -1) fn_active = false;
  if (mirror_action == 1) mirror_active = true;
  if (mirror_action == -1) mirror_active = false;
  if (rgbstf_action == 1) rgbstf_active = true;
  if (rgbstf_action == -1) rgbstf_active = false;
  if (ctl_action == 1) ctl_active = true;
  if (ctl_action == -1) ctl_active = false;
  
  if (ctl_active) {
      rgblight_mode(30);
  } else if (rgbstf_active) {
      rgblight_mode(6);
  } else if (fn_active) {
      rgblight_mode(38);
  } else if (mirror_active) {
      rgblight_mode(13);
  } else {
      rgblight_mode(17);
  }
  
  return true;
}

// OLED Driver Logic
#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    /* if (is_keyboard_master()) */
    /*    return rotation; */
    /* return OLED_ROTATION_270; */
    
    
    /* return OLED_ROTATION_270; */
    /* return OLED_ROTATION_180; */
    /* return OLED_ROTATION_90; */
}

static void render_logo(void) {
  static const char PROGMEM sol_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
  };
  oled_write_P(sol_logo, false);
}

/* static void render_status(void) { */
/*   // Render to mode icon */
/*   static const char PROGMEM sol_icon[] = { */
/*     0x9b,0x9c,0x9d,0x9e,0x9f, */
/*     0xbb,0xbc,0xbd,0xbe,0xbf, */
/*     0xdb,0xdc,0xdd,0xde,0xdf,0 */
/*   }; */
/*   oled_write_P(sol_icon, false); */

/*   // Define layers here */
/*   oled_write_P(PSTR("Layer"), false); */
/*   uint8_t layer = layer_state ? biton(layer_state) : biton32(default_layer_state); */
/*   switch (layer) { */
/*     case _QWERTY: */
/*       oled_write_P(PSTR("BASE "), false); */
/*       break; */
/*     /\* case _COLEMAK: *\/ */
/*     /\*   oled_write_P(PSTR("CLMK "), false); *\/ */
/*     /\*   break; *\/ */
/*     case _FN: */
/*       oled_write_P(PSTR("FN   "), false); */
/*       break; */
/*     case _ADJ: */
/*       oled_write_P(PSTR("ADJ  "), false); */
/*       break; */
/*     default: */
/*       oled_write_P(PSTR("UNDEF"), false); */
/*   } */

/*   // Host Keyboard LED Status */
/*     uint8_t led_state = host_keyboard_leds(); */
/*     oled_write_P(PSTR("-----"), false); */
/*     oled_write_P(IS_LED_ON(led_state, USB_LED_NUM_LOCK) ? PSTR("NUMLK") : PSTR("     "), false); */
/*     oled_write_P(IS_LED_ON(led_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLK") : PSTR("     "), false); */
/*     oled_write_P(IS_LED_ON(led_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLK") : PSTR("     "), false); */

/* #ifdef RGB_OLED_MENU */
/*     static char buffer[31] = { 0 }; */
/*     snprintf(buffer, sizeof(buffer), "h%3d s%3d v%3d s%3d m%3d e%3d ", rgb_matrix_config.hsv.h, rgb_matrix_config.hsv.s, rgb_matrix_config.hsv.v, rgb_matrix_config.speed, rgb_matrix_config.mode, rgb_matrix_get_flags()); */
/*     buffer[4 + rgb_encoder_state * 5] = '<'; */

/*     oled_write_P(PSTR("-----"), false); */
/*     oled_write(buffer, false); */
/* #endif */
/* } */

void oled_task_user(void) {
  /* if (is_keyboard_master()) { */
  /*     render_status(); */
  /* } else { */
  /*     render_logo(); */
  /*     oled_scroll_left(); */
  /* } */
    
    /* render_status(); */
    
    render_logo();
    /* oled_scroll_left(); */
}

#endif
