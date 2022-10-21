#pragma once

/* Layout wrappers */

#define LAYOUT_ansi_87_wrapper(...) LAYOUT_ansi_87(__VA_ARGS__)
#define LAYOUT_ansi_89_wrapper(...) LAYOUT_ansi_89(__VA_ARGS__)


/* Generic/reusable layouts */

#define DDR_FN_ROW              KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12
#define DDR_NUM_ROW             KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0

#define DDR_QWERTY_TOP_ROW      KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P
#define DDR_QWERTY_MID_ROW      KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L
#define DDR_QWERTY_LOW_ROW_L    KC_Z, KC_X, KC_C, KC_V, KC_B
#define DDR_QWERTY_LOW_ROW_R    KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH
#define DDR_QWERTY_LOW_ROW      DDR_QWERTY_LOW_ROW_L, DDR_QWERTY_LOW_ROW_R

#define DDR_COLEMAK_TOP_ROW     KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y
#define DDR_COLEMAK_MID_ROW     KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O
#define DDR_COLEMAK_LOW_ROW_L   KC_Z, KC_X, KC_C, KC_V, KC_B
#define DDR_COLEMAK_LOW_ROW_R   KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH
#define DDR_COLEMAK_LOW_ROW     DDR_COLEMAK_LOW_ROW_L, DDR_COLEMAK_LOW_ROW_R

#define DDR_SYMBOLS_TOP_ROW_L   S(KC_3),  S(KC_7),  S(KC_LBRC), S(KC_RBRC), S(KC_2)
#define DDR_SYMBOLS_TOP_ROW_R   KC_PEQL,  KC_P7,  KC_P8, KC_P9, KC_PAST
#define DDR_SYMBOLS_MID_ROW_L   S(KC_4),  S(KC_1),  S(KC_9),    S(KC_0),    S(KC_MINS)
#define DDR_SYMBOLS_MID_ROW_R   KC_PPLS,  KC_P4,  KC_P5, KC_P6, KC_PMNS
#define DDR_SYMBOLS_LOW_ROW_L   S(KC_6),  S(KC_BSLS), KC_LBRC,  KC_RBRC, KC_TILD
#define DDR_SYMBOLS_LOW_ROW_R   KC_PERC,  KC_P1,  KC_P2, KC_P3, KC_BSLS
#define DDR_SYMBOLS_TOP_ROW     DDR_SYMBOLS_TOP_ROW_L, DDR_SYMBOLS_TOP_ROW_R
#define DDR_SYMBOLS_MID_ROW     DDR_SYMBOLS_MID_ROW_L, DDR_SYMBOLS_MID_ROW_R
#define DDR_SYMBOLS_LOW_ROW     DDR_SYMBOLS_LOW_ROW_L, DDR_SYMBOLS_LOW_ROW_R


/* Custom keycodes */

#define DDR_KEY(idx)   (4096+idx)

#define CKC_SEC1    DDR_KEY(0)
#define CKC_SEC2    DDR_KEY(1)
#define CKC_SEC3    DDR_KEY(2)
#define CKC_BL      DDR_KEY(3)
#define CKC_WPM     DDR_KEY(4)
#define CKC_LL      DDR_KEY(5)


/***************************************************************************************************************************************************************************************
    Keychron Q3
    @see https://github.com/Keychron/qmk_firmware/tree/keychron-q3/keyboards/keychron/q3
 ***************************************************************************************************************************************************************************************/

#define DDR_Q3_QWERTY           KC_ESC,   DDR_FN_ROW,                                                     QK_BOOT,   KC_NO,    RGB_MOD, \
                                KC_GRV,   DDR_NUM_ROW,         KC_MINS,  KC_EQL,  KC_BSPC,                KC_INS,  KC_HOME,  KC_PGUP, \
                                KC_TAB,   DDR_QWERTY_TOP_ROW,  KC_LBRC,  KC_RBRC, KC_BSLS,                KC_DEL,  KC_END,   KC_PGDN, \
                                KC_BSPC,  DDR_QWERTY_MID_ROW,  KC_SCLN,  KC_QUOT, KC_ENT, \
                                KC_LSFT,  DDR_QWERTY_LOW_ROW,  KC_RSFT,                                            KC_UP, \
                                KC_LCTL,  KC_LCMD,  KC_LOPT, KC_SPC, KC_ROPT, OSL(3),KC_RCMD, KC_RCTL,    KC_LEFT, KC_DOWN,  KC_RGHT

#define DDR_Q3_COLEMAK          KC_ESC,   DDR_FN_ROW,                                                     KC_NO,   KC_NO,    RGB_MOD, \
                                KC_GRV,   DDR_NUM_ROW,         KC_MINS,  KC_EQL,  KC_BSPC,                KC_INS,  KC_HOME,  KC_PGUP, \
                                KC_TAB,   DDR_COLEMAK_TOP_ROW, KC_SCLN,  S(KC_SCLN), KC_RBRC, OSL(3),     KC_DEL,  KC_END,   KC_PGDN, \
                                KC_BSPC,  DDR_COLEMAK_MID_ROW, KC_QUOT, KC_ENT, \
                                KC_LSFT,  DDR_COLEMAK_LOW_ROW, KC_RSFT,                                            KC_UP, \
                                OSM(MOD_LCTL),OSM(MOD_LWIN),OSM(MOD_LALT), KC_SPC, OSM(MOD_RALT), OSL(3), OSM(MOD_RWIN),OSM(MOD_RCTL), KC_LEFT, KC_DOWN,  KC_RGHT

#define DDR_Q3_EMPTY \
        _______,            _______,  _______,    _______,    _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______, \
        _______,  _______,  _______,  _______,    _______,    _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______, \
        _______,  _______,  _______,  _______,    _______,    _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______, \
        _______,  _______,  _______,  _______,    _______,    _______,   _______,  _______,  _______,  _______,  _______,  _______,              _______,                               \
        _______,            _______,  _______,    _______,    _______,   _______,  _______,  _______,  _______,  _______,  _______,              _______,            _______,           \
        _______,  _______,  _______,                                     _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______

#define DDR_Q3_SYMBOLS \
        _______,            CKC_WPM,  CKC_BL,     CKC_SEC1,   _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,    QK_BOOT,  _______,  _______,  _______, \
        _______,  _______,  _______,  _______,    _______,    _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______, \
        _______,  S(KC_3),  S(KC_7),  S(KC_LBRC), S(KC_RBRC), S(KC_2),   KC_PEQL,  _______,  KC_UP,    _______,  KC_PAST,  _______,  _______,    _______,  _______,  _______,  _______, \
        KC_DEL,   S(KC_4),  S(KC_1),  S(KC_9),    S(KC_0),    S(KC_MINS),KC_PPLS,  KC_LEFT,  KC_DOWN,  KC_RIGHT, KC_PMNS,  KC_GRV,               _______,                               \
        _______,            S(KC_6),  S(KC_BSLS), KC_LBRC,    KC_RBRC,   S(KC_GRV),S(KC_5),  _______,  _______,  KC_BSLS,  _______,              _______,            _______,           \
        _______,  _______,  _______,                                     _______,                                _______,  _______,  _______,    _______,  _______,  _______,  _______


/***************************************************************************************************************************************************************************************
    Keychron Q10
    @see https://github.com/Keychron/qmk_firmware/tree/playground/keyboards/keychron/q10
 ***************************************************************************************************************************************************************************************/

#define DDR_Q10_QWERTY \
        KC_MUTE,  KC_ESC,             DDR_FN_ROW,                                                                                                    KC_HOME,            KC_END,  \
        DF(1),    KC_GRV,             DDR_NUM_ROW,                                                                               KC_MINS,  KC_EQL,   KC_BSPC,            KC_DEL,  \
        CKC_LL,   KC_TAB,             DDR_QWERTY_TOP_ROW,                                                                        KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGUP, \
        _______,  KC_BSPC,            DDR_QWERTY_MID_ROW,                                                              KC_SCLN,  KC_QUOT,            KC_ENT,             KC_PGDN, \
        _______,  KC_LSFT,            DDR_QWERTY_LOW_ROW_L,                             KC_B,      DDR_QWERTY_LOW_ROW_R,                             KC_RSFT,  KC_UP,             \
        _______,  KC_LCTL,  KC_LCMD,            KC_LOPT,  KC_SPC,   MO(3),                     KC_SPC,            KC_ROPT,                           KC_LEFT,  KC_DOWN,  KC_RGHT

#define DDR_Q10_COLEMAK \
        KC_MUTE,  KC_ESC,             DDR_FN_ROW,                                                                                                    KC_HOME,            KC_END,  \
        DF(0),    KC_GRV,             DDR_NUM_ROW,                                                                               KC_MINS,  KC_EQL,   KC_BSPC,            KC_DEL,  \
        CKC_LL,   KC_TAB,             DDR_COLEMAK_TOP_ROW,                                                             KC_SCLN,  S(KC_SCLN),KC_RBRC, TO(4),              KC_PGUP, \
        _______,  KC_BSPC,            DDR_COLEMAK_MID_ROW,                                                                       KC_QUOT,            KC_ENT,             KC_PGDN, \
        _______,  OSM(MOD_LSFT),      DDR_COLEMAK_LOW_ROW_L,                            KC_ESC,    DDR_COLEMAK_LOW_ROW_R,                            OSM(MOD_RSFT),KC_UP,         \
        _______,  OSM(MOD_LCTL),  OSM(MOD_LGUI), OSM(MOD_LALT), LT(4,KC_SPC),  OSL(3),        OSM(MOD_RSFT),        OSM(MOD_RALT),                   KC_LEFT,  KC_DOWN,  KC_RGHT

#define DDR_Q10_DEFAULT \
        KC_MUTE,  KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,             KC_DEL,  \
        DF(0),    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP, \
        _______,  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN, \
        _______,  KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME, \
        _______,  KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,             \
        _______,  KC_LCTL,  KC_LCMD,            KC_LALT,  KC_SPC,   KC_NO,                     KC_SPC,             KC_RALT,                          KC_LEFT,  KC_DOWN,  KC_RGHT

#define DDR_Q10_SYMBOLS \
        _______,  _______,  _______,  _______,  CKC_SEC1, _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  QK_BOOT,  _______,            _______, \
        DF(2),    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______, \
        _______,  _______,                                              DDR_SYMBOLS_TOP_ROW,                                     _______,  _______,  _______,            _______, \
        _______,  _______,                                              DDR_SYMBOLS_MID_ROW,                                     _______,            _______,            _______, \
        _______,  _______,            DDR_SYMBOLS_LOW_ROW_L,                             _______,            DDR_SYMBOLS_LOW_ROW_R,                  _______,  _______,           \
        _______,  _______,  _______,            _______,  _______,  _______,                       _______,            KC_P0,                        _______,  _______,  _______

#define DDR_Q10_NAV \
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______, \
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______, \
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  KC_UP,    _______,  _______,  _______,  _______,  _______,            _______, \
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   TG(4),    KC_LEFT,  KC_DOWN,  KC_RIGHT, _______,  _______,            _______,            _______, \
        _______,            _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,           \
        _______,  _______,  _______,            _______,  _______,  _______,                       _______,            _______,                      _______,  _______,  _______
