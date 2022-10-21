# DDRCode QMK Userspace

## Keyboards

This userspace supports the following keyboards:

- Keychron Q3
- Keychron Q10
- Hasu USB-USB Converterr
- Idobao ID75

## Credits 
- [Filterpaper Notes on Userspaces](https://filterpaper.github.io/qmk/userspace.html)
- [Userspace (QMK documentation)](https://docs.qmk.fm/#/feature_userspace)
- [tominabox1 userspace](https://github.com/qmk/qmk_firmware/tree/master/users/tominabox1)
- [drashna userspace](https://github.com/qmk/qmk_firmware/tree/master/users/drashna)

## Future/planned work
- VIM layer (see [here](https://github.com/qmk/qmk_firmware/tree/master/keyboards/ergodox_ez/keymaps/vim) and [here](https://github.com/Zindar/qmk_firmware/tree/master/keyboards/zindar12x5) for inspirations)
- Add more keyboards: Planck and Ergodox

## Firmware size optimization
Two of my boards: Hasu USB_USB converter and Idobao ID75 are equipped with 32kB of RAM only. By following
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
