### Declaration

```c
void IS31FL3236_WriteRGBPWM(IS31FL3236_HandleTypeDef* handle, uint8_t rgb_channel, uint8_t red, uint8_t green, uint8_t blue);
```

### Parameters

- **handle** [`IS31FL3236_HandleTypeDef*`]: The handle instance of the IS31FL3236 chip.
- **rgb_channel** [`uint8_t`]: The RGB channel number (0 - 11) to change the color value of. (The configuration of the RGB channels can be set in the handle struct before initialisation)
- **red** [`uint8_t`]: The red value of the new color (0 - 255).
- **green** [`uint8_t`]: The green value of the new color (0 - 255).
- **blue** [`uint8_t`]: The blue value of the new color (0 - 255).

### Description

This function changes the color of a given RGB LED channel (0 - 11). The function
`IS31FL3236_Update` has to be called afterwards to update the LED
channels to the new value.

### Example

```c
// Set the color of RGB channel 0 to #FF00FF (Violet / Purple)
IS31FL3236_WriteRGBPWM(p_hIS31FL3236, 0, 0xFF, 0x00, 0xFF);
// Send the chip an update command.
IS31FL3236_Update(p_hIS31FL3236);
```