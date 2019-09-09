### Declaration

```c
void IS31FL3236_SetSoftwareShutdown(IS31FL3236_HandleTypeDef* handle, uint8_t software_shutdown_mode);
```

### Parameters

- **handle** [`IS31FL3236_HandleTypeDef*`]: The handle instance of the IS31FL3236 chip.
- **software_shutdown_mode** [`uint8_t`]: The new software shutdown mode the chip should enter. Use the
definitions `IS31FL3236_SOFTWARE_SHUTDOWN_ENABLED` and `IS31FL3236_SOFTWARE_SHUTDOWN_DISABLED` to specify
the shutdown mode.

### Description

This function sets the IS31FL3236 chip into the given software shutdown mode. For further
information about shutdown modes refer to the datasheet. ([Link to IS31FL3236 Datasheet](http://www.issi.com/WW/pdf/31FL3236.pdf)

### Example

```c
// Set the chip into software enabled mode (disable shutdown mode)
IS31FL3236_SetSoftwareShutdown(p_hIS31FL3236, IS31FL3236_SOFTWARE_SHUTDOWN_DISABLED);
```