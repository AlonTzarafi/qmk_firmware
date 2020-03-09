// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(my_cool_effect)
RGB_MATRIX_EFFECT(my_cool_effect2)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// e.g: A simple effect, self-contained within a single method
static bool my_cool_effect(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  for (uint8_t i = led_min; i < led_max; i++) {
    /* rgb_matrix_set_color(i, 0xff, 0xff, 0x00); */
      rgb_matrix_set_color(i, 0x0B, 0x00, 0x00);
  }
  return led_max < DRIVER_LED_TOTAL;
}

// e.g: A more complex effect, relying on external methods and state, with
// dedicated init and run methods
static uint8_t some_global_state;
static uint8_t some_global_state2;
static uint8_t val;
static void my_cool_effect2_complex_init(effect_params_t* params) {
  some_global_state = 1;
  some_global_state2 = 0;
  val = 0;
}
static bool my_cool_effect2_complex_run(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
  int v = rgb_matrix_config.hsv.v / 30;
  for (uint8_t i = led_min; i < led_max; i++) {
    /* rgb_matrix_set_color(i, 0xff, some_global_state++, 0xff); */
    /* rgb_matrix_set_color(i, 0x00, 0x08, 0x00); */
      /* if (i == 69+24 or 38) { */
      if (i == 87) {
          /* rgb_matrix_set_color(i, 2*val, val, 80-val); */
          some_global_state += 73;
          val = some_global_state/10;
          rgb_matrix_set_color(i, v*3*val, v*(20+val), v*(111-2*val));
      } else if (i == 86) {
          val = some_global_state/34;
          rgb_matrix_set_color(i, v*2*val, v*val, v*(40-val));
      } else if (i > 77 && i < 95) {
          some_global_state2 += rand();
          if (some_global_state2 % 283 == 0) {
              val = some_global_state/34;
              rgb_matrix_set_color(i, v*2*val, v*val, v*(77-val));
          } else {
              rgb_matrix_set_color(i, v*0x00, v*0x00, v*0x07);
          }
      } else {
          rgb_matrix_set_color(i, v*0x00, v*0x00, v*0x07);
      }
  }

  return led_max < DRIVER_LED_TOTAL;
}
static bool my_cool_effect2(effect_params_t* params) {
  if (params->init) my_cool_effect2_complex_init(params);
  return my_cool_effect2_complex_run(params);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// Local Variables:
// mode: c
// End:
