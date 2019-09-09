### Declaration

```c
void IS31FL3236_WriteLEDControl(IS31FL3236_HandleTypeDef* handle, uint8_t channel, uint8_t led_current_setting, uint8_t led_state);
```

### Parameters

- **handle** [`IS31FL3236_HandleTypeDef*`]: The handle instance of the IS31FL3236 chip.
- **channel** [`uint8_t`]: The channel number (0 - 35) to change the PWM value of.
- **led_current_setting** [`uint8_t`]: The new LED current setting of the specified channel. Use the definitions `IS31FL3236_LED_CURRENT_MAX`, `IS31FL3236_LED_CURRENT_MAX_DIV_2`, `IS31FL3236_LED_CURRENT_MAX_DIV_3`, `IS31FL3236_LED_CURRENT_MAX_DIV_4` to specify the current mode of the channel.
- **led_state** [`uint8_t`]: The new LED state of the specified channel. Use the definitions `IS31FL3236_LED_STATE_OFF` and `IS31FL3236_LED_STATE_ON` to specify the LED mode.

### Description

This function sets the LED current mode and state of a specified channel. Further
information about the LED current mode and state can be found in the manufacturer's
datasheet of the IS31FL3236 IC. ([Link to IS31FL3236 Datasheet](http://www.issi.com/WW/pdf/31FL3236.pdf)

### Example

```c
// Set the LED current mode and state.
IS31FL3236_WriteLEDControl(p_hIS31FL3236, 3, IS31FL3236_LED_CURRENT_MAX_DIV_2, IS31FL3236_LED_STATE_ON);
// Send the chip and update command.
IS31FL3236_Update(p_hIS31FL3236);
```