### Declaration

```c
void IS31FL3236_WriteRegister(IS31FL3236_HandleTypeDef* handle, uint8_t register_address, uint8_t value);
```

### Parameters

- **handle** [`IS31FL3236_HandleTypeDef*`]: The handle instance of the IS31FL3236 chip.
- **register_address** [`uint8_t`]: The address of the register on the IS31FL3236 chip to write to. The register addresses can be looked up in the datasheet of the IS31FL3236 or can be retrieved by using the included definitions (see Register Address Definitions).

### Description

This function can be used to manually write to an internal register on the IS31FL3236 chip.

### Register Address Definitions

This library contains a collection of definitions that can be used to retrieve the addresses of the IS31FL3236's internal registers. The following list contains all available register address definitions.

- `IS31FL3236_REGISTER_SHUTDOWN` - Shutdown Register - `0x00`
- `IS31FL3236_REGISTER_PWM` - First PWM value register - `0x01`
- `IS31FL3236_REGISTER_LED_CTRL` - First LED control register - `0x26`
- `IS31FL3236_REGISTER_UPDATE` - Update initiation register - `0x25`
- `IS31FL3236_REGISTER_GLOBAL_CTRL` - Global LED control register - `0x4a`
- `IS31FL3236_REGISTER_RESET` - Reset initiation register - `0x4f`

### Example

```c
// Write 0x00 to the update register - similar to IS31FL3236_Update function.
IS31FL3236_WriteRegister(p_hIS31FL3236, IS31FL3236_REGISTER_UPDATE, 0x00);
```