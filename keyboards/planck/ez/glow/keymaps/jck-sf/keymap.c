// planck/ez/glow:jck-sf

#include QMK_KEYBOARD_H
#include "muse.h"
#include "eeprom.h"
//#include "music.h"
// #include "hebrew.h"
#include "rgblight_list.h"
//#include "kaplan.h"

#define TAPPING_TERM 375

enum custom_keycodes {
    DUMMY = SAFE_RANGE,
    KC_TAP_MOD,
    KC_LSFT_CAPS,
    RGB_SLD,
};

typedef enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    TRIPLE_TAP,
    TRIPLE_HOLD,
    TAP_DANCE_NO_MATCH,
} _t_tap_state;

typedef struct {
    _t_tap_state state;
    _t_tap_state is_press_action;
    _t_tap_state left_brackets;
    _t_tap_state right_brackets;
    _t_tap_state right_shift;
} _t_tap;

enum tapdance_index {
    TD_BRACKETS_LEFT,
    TD_BRACKETS_RIGHT,
    TD_QUOTE_DOUBLEQUOTE,
    TD_SEMICOLON_COLON,
    TD_BSLASH_PIPE,
};

void keyboard_post_init_user(void);

uint8_t cur_dance(qk_tap_dance_state_t *state);

void l_bracket_finished(qk_tap_dance_state_t *state, void *user_data);
void l_bracket_reset(qk_tap_dance_state_t *state, void *user_data);
void r_bracket_finished(qk_tap_dance_state_t *state, void *user_data);
void r_bracket_reset(qk_tap_dance_state_t *state, void *user_data);
void shift_lock_finished(qk_tap_dance_state_t *state, void *user_data);
void shift_lock_reset(qk_tap_dance_state_t *state, void *user_data);

void dq_quote_finished(qk_tap_dance_state_t *state, void *user_data);
void dq_quote_reset(qk_tap_dance_state_t *state, void *user_data);
void semi_colon_finished(qk_tap_dance_state_t *state, void *user_data);
void semi_colon_reset(qk_tap_dance_state_t *state, void *user_data);
void slash_pipe_finished(qk_tap_dance_state_t *state, void *user_data);
void slash_pipe_reset(qk_tap_dance_state_t *state, void *user_data);

qk_tap_dance_action_t tap_dance_actions[] = {
    //Tap once for left bracket, twice for left brace, thrice for left parenthesis
    [TD_BRACKETS_LEFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, l_bracket_finished, l_bracket_reset),
    [TD_BRACKETS_RIGHT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, r_bracket_finished, r_bracket_reset),
    [TD_QUOTE_DOUBLEQUOTE] = ACTION_TAP_DANCE_DOUBLE(KC_QUOTE, KC_DOUBLE_QUOTE),
    [TD_SEMICOLON_COLON] = ACTION_TAP_DANCE_DOUBLE(KC_SCOLON, KC_COLON),
    [TD_BSLASH_PIPE] = ACTION_TAP_DANCE_DOUBLE(KC_BSLASH, KC_PIPE),
};


// keymap ---------------------------------------------------------------------

enum planck_layers {
  _BASE = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _LAYER4,    // mouse
  _LAYER5,    // settings
  _LAYER6,    // NumPad
  _LAYER7,    // Evrite-base
  _LAYER8,    // Evrite-lower
  _LAYER9,    // Evrite-raise
  _LAYER10,   // blank
};

// "ez.h"
// planck_ez_right_led_level(uint8 level)
// planck_ez_left_led_level(uint8 level)
// planck_ez_left_led_off()
// planck_ez_right_led_off()

#define TD_LBRACKET TD(TD_BRACKETS_LEFT)
#define TD_RBRACKET TD(TD_BRACKETS_RIGHT)
//#define SHFT_LOCK TD(TD_LSHIFT_LOCK)

#define KC_TMOD KC_TAP_MOD
#define KC_TMOD_TAP QK_RSFT
#define KC_TMOD_HOLD KC_ENTER
#define KC_TMOD_DTAP KC_ENTER

#define OSM_LSFT OSM(MOD_LSFT)
#define _CAPSLCK KC_LSFT_CAPS

#define MUTE       KC_AUDIO_MUTE
#define VOLUP      KC_AUDIO_VOL_UP
#define VOLDN      KC_AUDIO_VOL_DOWN

#define M_PLAY1    DYN_MACRO_PLAY1
#define M_PLAY2    DYN_MACRO_PLAY2
#define M_REC1     DYN_REC_START1
#define M_REC2     DYN_REC_START2
#define M_RSTOP    DYN_REC_STOP

#define MUTE       KC_AUDIO_MUTE
#define VOLUP      KC_AUDIO_VOL_UP
#define VOLDN      KC_AUDIO_VOL_DOWN

#define RGB_TEST   RGB_MODE_RGBTEST
#define RGB_TLC    TOGGLE_LAYER_COLOR

#define MS_W_UP    KC_MS_WH_UP
#define MS_W_LEFT  KC_MS_WH_LEFT
#define MS_W_RGHT  KC_MS_WH_RIGHT
#define MS_W_DOWN  KC_MS_WH_DOWN
#define MS_BTN1    KC_MS_BTN1
#define MS_BTN2    KC_MS_BTN2

#define MS_UP      KC_MS_UP
#define MS_LEFT    KC_MS_LEFT
#define MS_RIGHT   KC_MS_RIGHT
#define MS_DOWN    KC_MS_DOWN
#define KC_MS_AC0  KC_MS_ACCEL0
#define KC_MS_AC1  KC_MS_ACCEL1
#define KC_MS_AC2  KC_MS_ACCEL2

#define WEBUSB     WEBUSB_PAIR

// #define LOWER MO(_LOWER)
// #define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_planck_grid(
    KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_DEL,
    KC_TAB,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCOLON,TD(TD_QUOTE_DOUBLEQUOTE),
    OSM_LSFT, KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMMA, KC_DOT,   KC_SLASH, KC_TMOD,
    KC_HYPR,  KC_LCTL,  KC_LALT,  KC_LGUI,  LOWER,    KC_SPC,   _______,  RAISE,    KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT
  ),

  [_LOWER] = LAYOUT_planck_grid(
    KC_TILDE, KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     TO(6),
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  TD_LBRACKET,
    _CAPSLCK, _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PLUS,  KC_MINUS, KC_EQUAL, _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  VOLUP,    VOLDN,    MUTE
  ), // MACRO_PLAY1

  [_RAISE] = LAYOUT_planck_grid(
    KC_GRAVE, KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  TO(6),
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PIPE,  TD_RBRACKET,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_UNDS,  KC_BSLASH,_______,
    KC_MEH,   KC_RCTL,  KC_RALT,  KC_RGUI,  _______,  _______,  _______,  _______,  KC_HOME,  KC_PGUP,  KC_PGDN,  KC_END
  ), // MACRO_PLAY2

  [_ADJUST] = LAYOUT_planck_grid(
    RGB_TLC,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   RESET,
    _______,  KC_F11,   KC_F12,   KC_F13,   KC_F14,   KC_F15,   KC_F16,   KC_F17,   KC_F18,   KC_F19,   KC_F20,   _______,
    KC_CAPS,  _______,  _______,  _______,  _______,  TO(4),    TO(5),    _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  TO(1),    TO(7),    _______,  TO(2),    KC_RGUI,  KC_RALT,  KC_RCTRL, KC_MEH
  ),
  [_LAYER4] = LAYOUT_planck_grid(   // mouse
    TO(0),    _______,  _______,  _______,  MS_W_UP,  _______,  MS_BTN1,  MS_UP,    MS_BTN2,  M_REC1,   M_REC2,   M_RSTOP,
    _______,  AU_TOG,   _______,  MS_W_LEFT,_______,  MS_W_RGHT,MS_LEFT,  _______,  MS_RIGHT, _______,  _______,  _______,
    _______,  MU_TOG,   _______,  _______,  MS_W_DOWN,_______,  _______,  MS_DOWN,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
  ),
  [_LAYER5] = LAYOUT_planck_grid(   // rgb settings
    TO(0),    KC_MS_AC2,RGB_HUI,  RGB_VAI,  RGB_SAI,  RGB_TLC,  RGB_SPI,  RGB_MOD,  _______,  _______,  _______,  WEBUSB,
    _______,  KC_MS_AC1,RGB_HUD,  RGB_VAD,  RGB_SAD,  RGB_TOG,  RGB_SPD,  RGB_SLD,  _______,  _______,  _______,  _______,
    _______,  KC_MS_AC0,_______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    RGB_TLC,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RESET
  ),
  [_LAYER6] = LAYOUT_planck_grid(   // NumPad
    TO(0),    TO(7),    TO(8),    TO(9),    TO(10),   _______,  KC_KP_7,  KC_KP_8,  KC_KP_9,  KC_KP_MINUS,_______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  KC_KP_4,  KC_KP_5,  KC_KP_6,  KC_KP_PLUS, _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  KC_KP_1,  KC_KP_2,  KC_KP_3,  KC_KP_ENTER,_______,  _______,
    _______,  _______,  _______,  _______,  _______,  KC_KP_0,  _______,  _______,  KC_KP_0,  KC_KP_DOT,  _______,  _______
  ),
  [_LAYER7] = LAYOUT_planck_grid(   // Evrit-base
    KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_LGUI,  KC_LGUI,  KC_I,     KC_O,     KC_P,     _______,
    KC_TAB,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_COLN,  KC_QUOTE,
    OSM_LSFT, KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_LABK,  KC_RABK,  KC_QUES,  _______,
    _______,  _______,  _______,  _______,  MO(8),    _______,  _______,  MO(9),    _______,  _______,  _______,  _______
  ),
  [_LAYER8] = LAYOUT_planck_grid(   // Evrit-lower
    TO(0),    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
  ),
  [_LAYER9] = LAYOUT_planck_grid(   // Evrit-raise
    TO(0),    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_MEH,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
  ),
  [_LAYER10] = LAYOUT_planck_grid(
    TO(0),    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
  ),
};

extern bool g_suspend_state;
extern rgb_config_t rgb_matrix_config;

// void keyboard_post_init_user(void) {
//   rgb_matrix_enable();
// }
/*
#define HSV_WHITE 0, 0, 255
#define HSV_RED 0, 255, 255
#define HSV_CORAL 11, 176, 255
#define HSV_ORANGE 28, 255, 255
#define HSV_GOLDENROD 30, 218, 218
#define HSV_GOLD 36, 255, 255
#define HSV_YELLOW 43, 255, 255
#define HSV_CHARTREUSE 64, 255, 255
#define HSV_GREEN 85, 255, 255
#define HSV_SPRINGGREEN 106, 255, 255
#define HSV_TURQUOISE 123, 90, 112
#define HSV_TEAL 128, 255, 128
#define HSV_CYAN 128, 255, 255
#define HSV_AZURE 132, 102, 255
#define HSV_BLUE 170, 255, 255
#define HSV_PURPLE 191, 255, 255
#define HSV_MAGENTA 213, 255, 255
#define HSV_PINK 234, 128, 255
*/

//#define dark_blue____ {154,255,255}
//#define light_blue2__ {141,216,201}
//#define light_blue___ {146,224,255}
// #define red__________ {000,255,255}
// #define pale_yellow__ {043,251,250}
// #define pale_orange__ {024,247,244}
// #define pale_pink____ {141,255,233}
// #define tourquoise___ {105,255,255}
// #define light_violet_ {  0,121,255}
// #define light_pink___ {  0,  0,204}
// #define violet_______ {205,255,255}
// #define white________ {255,255,255}

// #define light_green__ { 85,200,200}
// #define blue_________ {170,255,255}
// #define orange_______ { 28,255,255}

// #define evrit________ light_blue2__
// #define evrit_lower__ pale_yellow__
// #define everit_upper_ pale_orange__
// #define base_________ light_green__
// #define lower________ blue_________
// #define upper________ orange_______

#define __base           {83,227,197}
#define __lower          {154,255,255}
#define __upper          {14,255,255}
#define ____________     {0,0,0}
#define __adj_1_____     { HSV_PURPLE }
#define __adj_2_____     {0,121,255}
#define __evrit_____     {161,181,225}
#define __evrit_l___     {43,251,250}
#define __evrit_u___     {24,247,244}
#define __grey______     {0,0,102}
#define __5_________     {215,255,255}
#define __6_________     {205,113,227}
//#define __7_________     {233,218,217}
#define __violet____     {205,255,255}
#define __9_________     {10,225,255}
#define __10________     {22,255,255}
#define __12________     {180,255,233}
#define __13________     {85,203,158}
#define __orchid____     {0xDA,0x70,0xD6}
//#define __15________     {50,153,244}
#define __yellow____     {35,255,255}
#define __royal_blue     {0x41,0x69,0xE1}
//#define __coral_____     {0xFF,0x7F,0x50}
#define __yellow_1__     {43,255,255}
#define __blue______     { HSV_BLUE }

//           ESC             Q               W               E               R               T               Y               U               I               O               P               DEL             TAB             A               S               D               F               G               H               J               K               L               ;               "               LSHIFT          Z               X               C               V               B               N               M               ,               .               ?               RETURN          HYPER           CTRL            ALT             CMD/OS          LOWER           SPACE           RAISE           LEFT            DOWN            UP              RIGHT
const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
     [0] = { __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         __base,         ____________ ,  __base,         __base,         __base,         __base,         __base        },
     [1] = { __lower,        __lower,        __lower,        __lower,        __lower,        __lower,        __lower,        __lower,        __lower,        __lower,        __lower,        __yellow____,   ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  __lower,        __lower,        ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  __lower,        __lower,        __lower,        ____________ ,  __base,         ____________ ,  ____________ ,  ____________ ,  __lower,        ____________ ,  ____________ ,  __violet____,   __violet____,   __violet____,   __violet____  },
     [2] = { __upper,        __upper,        __upper,        __upper,        __upper,        __upper,        __upper,        __upper,        __upper,        __upper,        __upper,        __yellow____,   ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  __upper,        __upper,        ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  __upper,        __upper,        ____________ ,  __base,         ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  __upper,        __yellow____,   __yellow____,   __yellow____,   __yellow____  },
     [3] = { {HSV_RED},      __adj_1_____,   __adj_1_____,   __adj_1_____,   __adj_1_____,   __adj_1_____,   __adj_1_____,   __adj_1_____,   __adj_1_____,   __adj_1_____,   __adj_1_____,   { HSV_RED},     __adj_2_____,   __adj_2_____,   __adj_2_____,   __adj_2_____,   __adj_2_____,   __adj_2_____,   __adj_2_____,   __adj_2_____,   __adj_2_____,   __adj_2_____,   __adj_2_____,   ____________,   ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  {32,176,255},   {32,176,255},   ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  __base,         ____________ ,  ____________ ,  ____________ ,  {0,0,204},      {141,216,201},  {0,0,204},      __base,         __base,         __base,         {83,227,197}  },
     [4] = { __base,         ____________ ,  ____________ ,  ____________ ,  __violet____,   ____________ ,  __violet____,   __violet____,   __violet____,   __lower,        __upper,        {HSV_MAGENTA},  ____________ ,  __violet____,   ____________ ,  __violet____,   { HSV_RED } ,   __violet____,   { HSV_RED },    __violet____,   __violet____,   ____________ ,  ____________ ,  ____________,   ____________ ,  __violet____,   ____________ ,  ____________ ,  __violet____,   ____________ ,  ____________ ,  __violet____,   ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  __violet____ ,  {42,255,255}  },
     [5] = { __base,         __5_________,   __6_________,   __6_________,   __6_________,   __royal_blue,   __6_________,   __10________,   ____________ ,  __12________,   __13________,   __lower,        ____________ ,  __5_________,   __10________,   __10________,   __10________,   __12________,   __12________,   __12________,   ____________ ,  ____________ ,  ____________,   ____________,   ____________ ,  __5_________,   ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  __blue______ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________,   ____________ ,  ____________ ,  ____________ ,  ____________ ,  {HSV_RED}     },
     [6] = { __base,         ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  __yellow____,   __yellow____,   __yellow____,   __orchid____,   ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  __yellow____,   __yellow____,   __yellow____,   __orchid____,   ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  __yellow____,   __yellow____,   __yellow____,   __orchid____,   ____________ ,  __base,         ____________ ,  ____________ ,  ____________ ,  ____________ ,  ____________ ,  __yellow____,   ____________ ,  __yellow____,   __orchid____,   ____________ ,  ____________  },
     [7] = { __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____  },
     [8] = { __base,         __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_____,   __evrit_____,   __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_____,   __evrit_____,   __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_l___,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____  },
     [9] = { __base,         __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_____,   __evrit_____,   __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_____,   __evrit_____,   __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_u___,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____,   __evrit_____  },
    [10] = { __base,         __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   __grey______,   ____________  },
};


/*

//           ESC             Q              W              E              R              T              Y              U              I              O              P             DEL                 TAB            A              S              D              F              G              H              J              K              L              ;               ""                LSHIFT         Z               X             C              V              B              N              M              ,              .              ?              RETURN             HYPER          CTRL           ALT            CMD/OS         LOWER          SPACE          RAISE          LEFT           DOWN           UP             RIGHT
const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {  // base[0] .. lower[1] .. raise[2] .. adjust[3] ...
    [0] =  { base_________, base_________, base_________, base_________, base_________, base_________, base_________, base_________, base_________, base_________, base_________, base_________,     base_________, base_________, base_________, base_________, base_________, base_________, base_________, base_________, base_________, base_________, base_________, base_________,     base_________, base_________, base_________, base_________, base_________, base_________, base_________, base_________, base_________, base_________, base_________, base_________,     base_________, base_________, base_________, base_________, base_________, ______0______, base_________, base_________, base_________, base_________, base_________ },
    [1] =  { lower________, lower________, lower________, lower________, lower________, lower________, lower________, lower________, lower________, lower________, lower________, lower________,     ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______,     ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, lower________, base_________, ______0______,     {215, 91,238}, ______0______, ______0______, ______0______, ______0______, white________, ______0______, violet_______, violet_______, violet_______, violet_______ },
    [2] =  { upper________, upper________, upper________, upper________, upper________, upper________, upper________, upper________, upper________, upper________, upper________, { 10,225,255},     ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______,     ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, upper________, upper________, upper________, ______0______,     {022,255,255}, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, white________, white________, white________, white________ },
    [3] =  { red__________, red__________, red__________, red__________, red__________, red__________, red__________, red__________, red__________, red__________, red__________, red__________,     light_violet_, light_violet_, light_violet_, light_violet_, light_violet_, light_violet_, light_violet_, light_violet_, light_violet_, light_violet_, light_violet_, light_violet_,     ______0______, ______0______, ______0______, ______0______, ______0______, white________, white________, ______0______, ______0______, ______0______, ______0______, ______0______,     light_pink___, light_pink___, light_pink___, light_pink___, light_pink___, evrit________, light_pink___, light_pink___, light_pink___, light_pink___, light_pink___ },

    [4] =  { base_________, ______0______, ______0______, ______0______, { 85,203,158}, ______0______, pale_pink____, dark_blue____, pale_pink____, {215, 91,238}, {022,255,255}, red__________,     white________, violet_______, ______0______, { 85,203,158}, ______0______, { 85,203,158}, dark_blue____, ______0______, dark_blue____, ______0______, ______0______, ______0______,     ______0______, violet_______, ______0______, ______0______, { 85,203,158}, ______0______, ______0______, dark_blue____, ______0______, ______0______, ______0______, ______0______,     ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______ },
    [5] =  { base_________, __5_________,   __6_________,   __6_________,   __6_________,   {022,255,255}, __6_________,   {022,255,255}, ______0______, __12________,   { 85,203,158}, { 85,203,158},     white________, __5_________,   __12________,   __12________,   __12________,   {022,255,255}, __12________,   {022,255,255}, ______0______, ______0______, {132,246,231}, {132,246,231},     ______0______, __5_________,   ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, ______0______,     dark_blue____, ______0______, ______0______, ______0______, ______0______, {43,255,255},  ______0______, ______0______, ______0______, ______0______, {  6,250,248} },
    [6] =  { base_________, evrit________, evrit_lower__, everit_upper_, ______1______, ______0______, { 10,225,255}, { 10,225,255}, { 10,225,255}, ______0______, ______0______, ______0______,     white________, ______0______, ______0______, ______0______, ______0______, ______0______, { 10,225,255}, { 10,225,255}, { 10,225,255}, ______0______, ______0______, ______0______,     ______0______, ______0______, ______0______, ______0______, ______0______, ______0______, { 10,225,255}, { 10,225,255}, { 10,225,255}, ______0______, ______0______, ______0______,     ______0______, ______0______, ______0______, ______0______, ______0______, { 10,225,255}, ______0______, { 10,225,255}, ______0______, ______0______, ______0______ },

    [7] =  { evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________,     evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________,     evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________,     evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________ },
    [8] =  { base_________, evrit_lower__, evrit_lower__, evrit_lower__, evrit_lower__, evrit_lower__, evrit_lower__, evrit_lower__, evrit_lower__, evrit_lower__, evrit_lower__, evrit________,     evrit________, evrit_lower__, evrit_lower__, evrit_lower__, evrit_lower__, evrit_lower__, evrit_lower__, evrit_lower__, evrit_lower__, evrit_lower__, evrit_lower__, evrit________,     evrit________, evrit_lower__, evrit_lower__, evrit_lower__, evrit_lower__, evrit_lower__, evrit_lower__, evrit_lower__, evrit_lower__, evrit_lower__, evrit_lower__, evrit________,     evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________ },
    [9] =  { base_________, everit_upper_, everit_upper_, everit_upper_, everit_upper_, everit_upper_, everit_upper_, everit_upper_, everit_upper_, everit_upper_, everit_upper_, evrit________,     evrit________, everit_upper_, everit_upper_, everit_upper_, everit_upper_, everit_upper_, everit_upper_, everit_upper_, everit_upper_, everit_upper_, everit_upper_, evrit________,     evrit________, everit_upper_, everit_upper_, everit_upper_, everit_upper_, everit_upper_, everit_upper_, everit_upper_, everit_upper_, everit_upper_, everit_upper_, evrit________,     evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________, evrit________ },
    [10] = { ______1______, ______1______, ______1______, ______1______, ______1______, ______1______, ______1______, ______1______, ______1______, ______1______, ______1______, ______1______,     ______1______, ______1______, ______1______, ______1______, ______1______, ______1______, ______1______, ______1______, ______1______, ______1______, ______1______, ______1______,     ______1______, ______1______, ______1______, ______1______, ______1______, ______1______, ______1______, ______1______, ______1______, ______1______, ______1______, ______1______,     ______1______, ______1______, ______1______, ______1______, ______1______, ______1______, ______1______, ______1______, ______1______, ______1______, ______1______ },

}; */

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (g_suspend_state || keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    case  0:   set_layer_color( 0); break;
    case  1:   set_layer_color( 1); break;
    case  2:   set_layer_color( 2); break;
    case  3:   set_layer_color( 3); break;
    case  4:   set_layer_color( 4); break;
    case  5:   set_layer_color( 5); break;
    case  6:   set_layer_color( 6); break;
    case  7:   set_layer_color( 7); break;
    case  8:   set_layer_color( 8); break;
    case  9:   set_layer_color( 9); break;
    case 10:   set_layer_color(10); break;

   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}

//  ----------

uint32_t layer_state_set_user(uint32_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

//#define short_tap (delay(tm_t0, record->event.time) <= TAPPING_TERM)
// void post_process_record_user(uint16_t keycode, keyrecord_t *record) { }

typedef struct {
    bool active;        // true if tap-dance in progress
    uint16_t kc;        // new keycode
    uint32_t timer32;   // milliseconds
} _tap_mod_t;

typedef struct {
    uint16_t key;
    uint16_t tap;
    uint16_t hold;
    uint16_t dtap;
} _tm_actions;

// static _tm_actions tma[] = {
//     [0] = { .key = KC_TMOD, .tap = KC_TMOD_TAP, .hold = KC_TMOD_HOLD, .dtap = KC_TMOD_HOLD },
//     [1] = { .key = KC_CAPS, .tap = KC_LSFT,   .hold = KC_LSFT,    .dtap = KC_CAPSLOCK},
// };

// static uint16_t _tm_actions_cnt = 2;

static bool _caps_lock = false;

void keyboard_post_init_user(void) {
    _caps_lock = false;
    rgb_matrix_enable();

}

uint16_t delay(uint16_t t0, uint16_t t1) {
    return (t1 > t0) ? t1 - t0 : t0 - t1;
}

bool long_tap(uint32_t timer32) {
    return (timer_elapsed32(timer32) > TAPPING_TERM);
}

void process_capslock(void) {
    if (_caps_lock == true) {
        unregister_code16(KC_LSFT);
        _caps_lock = false;
    } else {
        register_code16(KC_LSFT);
        _caps_lock = true;
    }
}

void send_keycode(uint16_t kc) {    // ToDo: move to kaplan.c
    register_code16(kc);
    wait_ms(1);
    unregister_code16(kc);
}

static _tap_mod_t tm = { .active = false, .kc = 0, .timer32 = 0 } ;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (keycode == RGB_SLD && record->event.pressed) {
        rgblight_mode(1);
        return false;
    }
    if (keycode == KC_LSFT_CAPS && record->event.pressed) {
        process_capslock();
        return false;
    }
    if (!tm.active) {
        if (record->event.pressed) {
            if (keycode == KC_TMOD) {            // a new tap-mod has started
                tm.timer32 = timer_read32();
                tm.active = true;
                return false;
            }
        }
    } else {
        if (record->event.pressed) {            // tap-mod is active
            // key-down
           switch (keycode) {
                case KC_TAP_MOD:
                   tm.kc = KC_TMOD_DTAP; break;
                default:
                   tm.kc = (long_tap(tm.timer32) == true) ? KC_TMOD_HOLD : (KC_TMOD_TAP | keycode) ;
           }
            send_keycode(tm.kc);
            tm.active = false;
            return false;
        } else {
            //key-up
           if (keycode == KC_TAP_MOD) {
                if (long_tap(tm.timer32) == true) {
                    tm.kc = KC_TMOD_HOLD;
                    send_keycode(tm.kc);
                    tm.active = false;
                    return false;
               }
            }
        }
    }
    return true;
}

static _t_tap tap_state = {
    .state = 0,
    .is_press_action = true,
    .left_brackets = 0,
    .right_brackets = 0,
    .right_shift = 0
};

_t_tap_state get_tap_dance_state(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        // DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    } else if (state->count == 3) {
        // Assumes no one is trying to type the same letter three times (at least not quickly).
        // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
        // an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
        if (state->interrupted || !state->pressed) return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    } else return TAP_DANCE_NO_MATCH; // Magic number. At some point this method will expand to work for more presses
}

void l_bracket_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = get_tap_dance_state(state);
    switch (tap_state.state) {
        case SINGLE_TAP:  register_code16( KC_LEFT_PAREN); break;
        case SINGLE_HOLD: register_code16( KC_LEFT_PAREN); break;
        case DOUBLE_TAP:  register_code16( KC_LBRACKET); break;
        case DOUBLE_HOLD: register_code16( KC_LBRACKET); break;
        case TRIPLE_TAP:  register_code16( KC_LEFT_CURLY_BRACE); break;
        case TRIPLE_HOLD: register_code16( KC_LEFT_CURLY_BRACE); break;
        default: break;
    }
}

void l_bracket_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case SINGLE_TAP:  unregister_code16( KC_LEFT_PAREN); break;
        case SINGLE_HOLD: unregister_code16( KC_LEFT_PAREN); break;
        case DOUBLE_TAP:  unregister_code16( KC_LBRACKET); break;
        case DOUBLE_HOLD: unregister_code16( KC_LBRACKET); break;
        case TRIPLE_TAP:  unregister_code16( KC_LEFT_CURLY_BRACE); break;
        case TRIPLE_HOLD: unregister_code16( KC_LEFT_CURLY_BRACE); break;
        default: break;
    }
    tap_state.state = 0;
}

void r_bracket_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = get_tap_dance_state(state);
    switch (tap_state.state) {
        case SINGLE_TAP:  register_code16( KC_RIGHT_PAREN); break;
        case SINGLE_HOLD: register_code16( KC_RIGHT_PAREN); break;
        case DOUBLE_TAP:  register_code16( KC_RBRACKET); break;
        case DOUBLE_HOLD: register_code16( KC_RBRACKET); break;
        case TRIPLE_TAP:  register_code16( KC_RIGHT_CURLY_BRACE); break;
        case TRIPLE_HOLD: register_code16( KC_RIGHT_CURLY_BRACE); break;
        default: break;
    }
}

void r_bracket_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case SINGLE_TAP:  unregister_code16( KC_RIGHT_PAREN); break;
        case SINGLE_HOLD: unregister_code16( KC_RIGHT_PAREN); break;
        case DOUBLE_TAP:  unregister_code16( KC_RBRACKET); break;
        case DOUBLE_HOLD: unregister_code16( KC_RBRACKET); break;
        case TRIPLE_TAP:  unregister_code16( KC_RIGHT_CURLY_BRACE); break;
        case TRIPLE_HOLD: unregister_code16( KC_RIGHT_CURLY_BRACE); break;
        default: break;
    }
    tap_state.state = 0;
}

void semi_colon_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = get_tap_dance_state(state);
    switch (tap_state.state) {
        case SINGLE_TAP:  register_code16( KC_SCOLON); break;
        case SINGLE_HOLD: register_code16( KC_SCOLON); break;
        case DOUBLE_TAP:  register_code16( KC_COLON); break;
        case DOUBLE_HOLD: register_code16( KC_COLON); break;
        default: break;
    }
}

void semi_colon_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case SINGLE_TAP:  unregister_code16( KC_SCOLON); break;
        case SINGLE_HOLD: unregister_code16( KC_SCOLON); break;
        case DOUBLE_TAP:  unregister_code16( KC_COLON); break;
        case DOUBLE_HOLD: unregister_code16( KC_COLON); break;
        default: break;
    }
    tap_state.state = 0;
}

void dq_quote_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = get_tap_dance_state(state);
    switch (tap_state.state) {
        case SINGLE_TAP:  register_code16( KC_QUOTE); break;
        case SINGLE_HOLD: register_code16( KC_QUOTE); break;
        case DOUBLE_TAP:  register_code16( KC_DOUBLE_QUOTE); break;
        case DOUBLE_HOLD: register_code16( KC_DOUBLE_QUOTE); break;
        default: break;
    }
}

void dq_quote_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case SINGLE_TAP:  unregister_code16( KC_QUOTE); break;
        case SINGLE_HOLD: unregister_code16( KC_QUOTE); break;
        case DOUBLE_TAP:  unregister_code16( KC_DOUBLE_QUOTE); break;
        case DOUBLE_HOLD: unregister_code16( KC_DOUBLE_QUOTE); break;
        default: break;
    }
    tap_state.state = 0;
}

void slash_pipe_finished(qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = get_tap_dance_state(state);
    switch (tap_state.state) {
        case SINGLE_TAP:  register_code16( KC_SLASH); break;
        case SINGLE_HOLD: register_code16( KC_SLASH); break;
        case DOUBLE_TAP:  register_code16( KC_PIPE); break;
        case DOUBLE_HOLD: register_code16( KC_PIPE); break;
        default: break;
    }
}

void slash_pipe_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case SINGLE_TAP:  unregister_code16( KC_SLASH); break;
        case SINGLE_HOLD: unregister_code16( KC_SLASH); break;
        case DOUBLE_TAP:  unregister_code16( KC_PIPE); break;
        case DOUBLE_HOLD: unregister_code16( KC_PIPE); break;
        default: break;
    }
    tap_state.state = 0;
}




