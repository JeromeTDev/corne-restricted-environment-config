#include QMK_KEYBOARD_H

/* * Corne v4.1 Restricted Environment Keymap
 * - No dynamic storage (Vial/VIA disabled)
 * - Home Row Combos & Shift-Backspace Morph
 */

// --- COMBO DEFINITIONEN ---
const uint16_t PROGMEM combo_esc[] = {KC_J, KC_K, COMBO_END};        // J + K = Escape
const uint16_t PROGMEM combo_leftLP[] = {KC_F, KC_G, COMBO_END};     // F + G = (
const uint16_t PROGMEM combo_rightPT[] = {KC_H, KC_J, COMBO_END};    // H + J = )
const uint16_t PROGMEM combo_leftBT[] = {KC_R, KC_T, COMBO_END};     // R + T = [
const uint16_t PROGMEM combo_rightBT[] = {KC_Y, KC_U, COMBO_END};    // Y + U = ]
const uint16_t PROGMEM combo_leftBR[] = {KC_V, KC_B, COMBO_END};     // V + B = {
const uint16_t PROGMEM combo_rightBR[] = {KC_N, KC_M, COMBO_END};    // N + M = }
//
const uint16_t PROGMEM combo_backslash[] = {KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM combo_pipe[] = {KC_SLSH, KC_RSFT, COMBO_END};      // / + ShiftR = |


const uint16_t PROGMEM combo_tilde[] = {KC_L, KC_SCLN, COMBO_END};    // L + ; = ~
const uint16_t PROGMEM combo_Grave[] = {KC_SCLN, KC_QUOT, COMBO_END};    // ; + ' = ` 

combo_t key_combos[] = {
    COMBO(combo_esc, KC_ESC),
    COMBO(combo_leftLP, KC_LPRN),
    COMBO(combo_rightPT, KC_RPRN),
    COMBO(combo_leftBT, KC_LBRC),
    COMBO(combo_rightBT, KC_RBRC),
    COMBO(combo_leftBR, KC_LCBR),
    COMBO(combo_rightBR, KC_RCBR),
    COMBO(combo_backslash, KC_BSLS),
    COMBO(combo_pipe, KC_PIPE),
    COMBO(combo_tilde, KC_TILDE),
    COMBO(combo_Grave, KC_GRAVE)
};

// --- KEY OVERRIDES (Shift + Backspace = Delete) ---
const key_override_t bspc_del_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t *key_overrides[] = {
    &bspc_del_override,
    NULL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3_ex2(QK_GESC, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_COPY, KC_VOLU, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, LCTL_T(KC_TAB), KC_A, KC_S, KC_D, KC_F, KC_G, KC_PSTE, KC_VOLD, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_LGUI, LT(1,KC_SPC), KC_ENT, KC_ENT, LT(2,KC_SPC), KC_LALT),
    [1] = LAYOUT_split_3x6_3_ex2(KC_TRNS, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_TRNS, KC_TRNS, KC_7, KC_8, KC_9, KC_PSLS, KC_PAST, KC_TRNS, KC_TRNS, KC_CIRC, KC_AMPR, KC_ASTR, KC_PMNS, KC_EQL, KC_TRNS, KC_TRNS, KC_4, KC_5, KC_6, KC_PMNS, KC_PPLS, KC_NO, KC_TRNS, RALT(KC_5), KC_NO, KC_NO, KC_UNDS, KC_PLUS, KC_1, KC_2, KC_3, KC_PDOT, KC_EQL, KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_0, KC_PCMM),
    [2] = LAYOUT_split_3x6_3_ex2(KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_TRNS, KC_TRNS, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F10, RALT(KC_Q), RALT(KC_S), RALT(KC_P), RALT(KC_Y), KC_PSCR, KC_NO, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO, KC_F12, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, MS_LEFT, MS_DOWN, MS_UP, MS_RGHT, MS_BTN1, MS_BTN2, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS)
};




