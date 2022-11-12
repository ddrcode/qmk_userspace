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
- [VI/VIM mode](#VI)
- RGB matrix with no animations - used for [layers/modifiers indications](https://github.com/ddrcode/qmk_userspace/blob/main/features/rgb_matrix.c) only
- One-shot modifiers, One-shot layers (with [customizations](https://github.com/ddrcode/qmk_userspace/blob/main/features/osm.c))

### Future/planned work
- WPM stats (per layout) 
- Host OS recognition

## Installation and usage
1. clone official QMK repository: `git clone https://github.com/qmk/qmk_firmware.git` 
1. Configure QMK according to [official documentation](https://docs.qmk.fm/#/newbs_getting_started) or (my preferred way, Nix users only) by runnix `nix-shell` from `qmk_firmware` folder.
1. `cd qmk_firmware/users`
1. clone this repo to `ddrcode` folder: `git clone git@github.com:ddrcode/qmk_userspace.git ddrcode`
1. You are ready to go, i.e.: `qmk compile users/ddrcode/idobao-id75.json`

### Steps for **Keychron** keyboards:

Official QMK repo at this stage doesn't contain configs for  Keychron Q3 and Q10 keyboards. You must use [Keychron's fork](https://github.com/Keychron/qmk_firmware) instead ([keychron-q3](https://github.com/Keychron/qmk_firmware/tree/keychron-q3) and [playground](https://github.com/Keychron/qmk_firmware/tree/playground) branches respestively).
I'd still recommend to setup QMK with the official repo and then use Keychron fork for sources only. Step-by-step instruction:
1. Follow steps 1 and 2 from the installation guide above
1. Clone Keychron's fork to a folder parallel to `qmk_firmware`, i.e.: `git clone https://github.com/Keychron/qmk_firmware.git qmk_keychron`
1. `cd qmk_keychron/users`
1. clone this repo to `ddrcode` folder: `git clone git@github.com:ddrcode/qmk_userspace.git ddrcode`
1. Switch Keychron fork to a keyboard-specific branch, i.e. for Q3: `git checkout keychron-q3`
1. Compile: `qmk compile users/ddrcode/keychron_q3.json`

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



[#VI]: https://github.com/ddrcode/qmk_userspace/blob/vim/extension_vi.md