### Declaration

```c
void IS31FL3236_WritePWM(IS31FL3236_HandleTypeDef* handle, uint8_t channel, uint8_t pwm_value);
```

### Parameters

- **handle** [`IS31FL3236_HandleTypeDef*`]: The handle instance of the IS31FL3236 chip.
- **channel** [`uint8_t`]: The channel number (0 - 35) to change the PWM value of.
- **pwm_value** [`uint8_t`]: The new PWM-value to write to the given channel.

### Description

This function changes the PWM value of a given LED channel (0 - 35). The function
`IS31FL3236_Update` has to be called afterwards to update the LED
channels to the new value.

### Example

```c
// Set the PWM value of channel (ID) 8 to 200.
IS31FL3236_WritePWM(p_hIS31FL3236, 8, 200);
// Send the chip an update command.
IS31FL3236_Update(p_hIS31FL3236);
```