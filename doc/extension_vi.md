# VI Mode Extension

## Overview
This extension enables VI features on keyboard level. 
It doesn't require additional layer, but it works on top of any existing
layer and follows keyboard layout.

## Supported features

### Common features
- Repeat n-times (i.e. `15dd`)
- Repeat last command (`.`)

### Cursor movement
- Cursor navigation (`h j k l`)
- Word jumps (`w e b`)  (`w` is limited, works like `el`)
- Beggining/end of line (`0 $`)
- Beginning/end of file (`gg G`)

### Editing
- Append / insert (`a A i I`)
- Append / prepend lines (`o O`)
- Replace single character (`r`)
- Replace characters until ESC (`R`)
- Merge lines (`J gJ`)
- Undo/redo (`u ctrl+r`)

### Modes
- Visual selection (`v V`)

### File operations
- Save (`:w`)


## Unsupported features

The features listed below can't be supported due to limitations of running VI mode
on keyboard level:

- Move to top of the screen (`H`)
- Move to middle of the screen (`M`)
- Jump through punctations (`E W B`)
- jump to start of the word (`w`) - fallback to `e`
- jump to matching pair (`%`)
- jump to next/prev occurence of character (`f t F T`)
- go to line (`<line>gg` or `:<line>`)
- change cases (`~`, `gu`, `gU`, `g~`)
- undo last changed line (`U`)
- macros (`q*`)
- markers (`m*`)
- indents
- Block selection (`ctrl+v`)

## Enabling VI mode

There is a dedicated key code: `CKC_VI` that toggles VI mode.

Other option is to call of the following functions: `toggle_vi_mode` (`CKC_VI` keycode
calls this function), or `enter_vi_mode`.

To quit VI mode, `exit_vi_mode` function can be called.

## How it works?

VI mode does not require dedicated layer and it works on top of any existing layers. 
When enabled it *hijaks* (almost) all key presses and combines them into
key sequences. Sequences are being then parsed by VI parser and executed when
valid and complete (i.e.: `w`, `5w`, `10dw`, `d10w`)

Key presses that are not *hijaked* by VI mode are layer switchers and media/system keys.

The fact that VI mode is not implemented as a layer is a key feature, as it makes it
to utilise any existing layouts and layers, without extra configuration.
Imagine a 40% keyboard configured with four layers: Qwerty, Colemak, Symbols and Numbers. 
As layer switching happens outside of VI mode, user can easily
switch between layers while typing VI command sequence, i.e. to provide sequences
with numbers (`10dd`) or symbols (`$`).

## Key Remapping

Standard VI keys can be remapped with `vi_key_override(kc_t keycode)` function. 
It's a function which simply returns a keycode based on the input keycode. 
The example below demonstrates how to replace standard `HJKL` navigation keys
with `IJKL` and `H` key for switching to insert mode:

```C
kc_t vi_key_override(kc_t keycode) {
    switch(keycode) {
        case KC_I: return KC_K; // up
        case KC_J: return KC_H; // left
        case KC_K: return KC_J; // down
        case KC_H: return KC_I; // insert
        case S(KC_H): return S(KC_I); // insert at BOL
    }
    return keycode;
}
```