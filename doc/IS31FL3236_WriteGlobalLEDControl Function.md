### Declaration

```c
void IS31FL3236_WriteGlobalLEDControl(IS31FL3236_HandleTypeDef* handle, uint8_t led_current_setting, uint8_t led_state);
```

### Parameters

- **handle** [`IS31FL3236_HandleTypeDef*`]: The handle instance of the IS31FL3236 chip.
- **led_current_setting** [`uint8_t`]: The new LED current setting of all channels. Use the definitions `IS31FL3236_LED_CURRENT_MAX`, `IS31FL3236_LED_CURRENT_MAX_DIV_2`, `IS31FL3236_LED_CURRENT_MAX_DIV_3`, `IS31FL3236_LED_CURRENT_MAX_DIV_4` to specify the current mode.
- **led_state** [`uint8_t`]: The new LED state of all channels. Use the definitions `IS31FL3236_LED_STATE_OFF` and `IS31FL3236_LED_STATE_ON` to specify the LED mode.

### Description

This function is identical to the `IS31FL3236_WriteLEDControl` function, but insted of changing
the LED current control and state of one channel, it changes these values globally. This function
uses a special harware command (see datasheet), thus it is faster than looping over all channels
and changing the values seperately.

### Example

```c
// Set the basic global LED current mode and state settings. (Turn on all channels to the max. current)
IS31FL3236_WriteGlobalLEDControl(p_hIS31FL3236, IS31FL3236_LED_CURRENT_MAX, IS31FL3236_LED_STATE_ON);
// Send an update command to the chip.
IS31FL3236_Update(p_hIS31FL3236);
```