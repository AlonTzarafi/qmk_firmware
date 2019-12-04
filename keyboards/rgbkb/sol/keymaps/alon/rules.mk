# Default keymap does not have any overridden options from the rev1 / rev2 rules.mk files.
# Example:
#     if you wanted to disable EXTRAKEY_ENABLE, you would copy the line from the rev1/rules.mk file
#     and paste it in to this file, changing the yes to no. Like so:
# EXTRAKEY_ENABLE         = no       # Audio control and System control(+450)
#
# To keep things clean and tidy, as well as make upgrades easier, only place overrides from the defaults in this file.


# Keycode Options
# NKRO_ENABLE             = yes        # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work

# RGB Options
RGB_MATRIX_KEYPRESSES   = yes        # Enable reactive per-key effects.
RGB_MATRIX_FRAMEBUFFER_EFFECTS = yes # Enable frame buffer effects like the typing heatmap.

RGBLIGHT_FULL_POWER     = no        # Allow maximum RGB brightness for RGBLIGHT or RGB_MATRIX. Otherwise, limited to a safe level for a normal USB-A port
FULLHAND_ENABLE         = yes        # Enables the additional 24 Full Hand LEDs
IOS_DEVICE_ENABLE       = no        # Limit max brightness to connect to IOS device (iPad,iPhone)

# Misc
OLED_DRIVER_ENABLE      = no       # Enable the OLED Driver
EXTRA_ENCODERS_ENABLE   = yes       # Enables 3 encoders per side (up from 1, not compatible with OLED_DRIVER_ENABLE)
SWAP_HANDS_ENABLE       = no        # Enable one-hand typing
LINK_TIME_OPTIMIZATION_ENABLE = yes # Enable Link Time Optimizations greatly reducing firmware size by disabling the old Macros and Functions features

# Special RGB Matrix, OLED, & Encoder Control Menu!
RGB_OLED_MENU           = no        # Enabled by setting this to the encoder index (0-5) you wish to use to control the menu.
                                    # Use the RGB_MENU keycode in the keymap for the encoder to advance the menu to the next option.

#----------SOL2 SETTINGS ENDS HERE

# MORE OLED SETTINGS:
OLED_TIMEOUT            = 0

#MORE GENERAL SETTINGS:
DYNAMIC_MACRO_ENABLE = yes

# Do not edit past here
include keyboards/$(KEYBOARD)/post_rules.mk
