# DDRCode QMK Userspace

## Keyboards

This userspace supports the following keyboards:

- [Keychron Q3](https://www.keychron.com/products/keychron-q3-qmk-custom-mechanical-keyboard) (Standard ANSI, tenkeyless)
- [Keychron Q10](https://www.keychron.com/products/keychron-q10-alice-layout-qmk-custom-mechanical-keyboard) (Alice layout)
- [Hasu USB-USB Converterr](https://geekhack.org/index.php?topic=109514.0)
- [Idobao ID75](https://idobao.net/products/idobao-id75-crystal-hot-swap-keyboard-kit) (5x15 ortholinear, 75 keys / 65%)

### Planned
- [Ergodox EZ](https://ergodox-ez.com/) (ortholinear, split layout with thumb cluster)
- [Planck EZ](https://www.zsa.io/planck/) (4x12 ortholinear)

## Main features / ideas
I frequently switch between Colemak (typing) and Qwerty (regular computer use, non text-editing apps).
I prefer to tap rather than hold keys so I intesively use one-shot modifiers and one-shot layers (with custom modifications).
If keyboard layout allows I prefer to use thumbs for modifiers and layer switching, so my layouts are 
optimized for that. Besides that my configuration is rather conservative: I don't use tap dance, chords, magic keys, etc).

- Support for Qwerty and Colemak layouts (with some [unified keyboard shortcuts](https://github.com/ddrcode/qmk_userspace/blob/main/features/key_overrides.c))
- Unified symbols layer across all boards
- Unified navigation layer across all boards
- RGB matrix with no animations - used for [layers/modifiers indications](https://github.com/ddrcode/qmk_userspace/blob/main/features/rgb_matrix.c) only
- One-shot modifiers, One-shot layers (with [customizations](https://github.com/ddrcode/qmk_userspace/blob/main/features/osm.c))

### Future/planned work
- Navigation layer to mimick VIM (see [#1])
- WPM stats (per layout) 
- Host OS recognition

## Credits 
- [Filterpaper Notes on Userspaces](https://filterpaper.github.io/qmk/userspace.html)
- [Userspace (QMK documentation)](https://docs.qmk.fm/#/feature_userspace)
- [tominabox1 userspace](https://github.com/qmk/qmk_firmware/tree/master/users/tominabox1)
- [drashna userspace](https://github.com/qmk/qmk_firmware/tree/master/users/drashna)

## Interesting reads and links
### Firmware size optimization
Two of my boards: Hasu USB_USB converter and Idobao ID75 are equipped with 32kB RAM only. By following
[these steps](https://docs.qmk.fm/#/squeezing_avr?id=squeezing-the-most-out-of-avr)
I was able to reduce the file size by up to 7kB. 

## Copyrights

Copyright 2022 @ddrcode

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.




[#1]: https://github.com/ddrcode/qmk_userspace/issues/1