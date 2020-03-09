/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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
*/

#pragma once

// place overrides here

#define OLED_TIMEOUT 0
#define MK_3_SPEED
#define MOUSEKEY_DELAY 200
#define MOUSEKEY_INTERVAL 35
/* Defaults: */
/* #define MK_C_OFFSET_0 1   */
/* #define MK_C_OFFSET_1 4 */
/* #define MK_C_OFFSET_2 32 */
/* Mine: */
#define MK_C_OFFSET_0 4
#define MK_C_OFFSET_1 32
#define MK_C_OFFSET_2 64


#ifdef TAPPING_TERM
#undef TAPPING_TERM
#endif
// Fast typing attempts:
#define TAPPING_TERM 164
#define PREVENT_STUCK_MODIFIERS
#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD
#define TAPPING_FORCE_HOLD

