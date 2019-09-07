## Initialisation of a new Device Handle

In order to support multiple IS31FL3236 devices on the same STM32 microcontroller,
this library uses seperately initialised handles to refer to a specific IS31FL3236
chip. All necessary hardware information, such as the I2C bus, SDN pin, etc., has
to be provided in order for the initialisation to be complete.

The initialisation of a new IS31FL3236 is shown by the following piece of example
code.

```c
// Handle pointer for possible global access:
IS31FL3236_HandleTypeDef* ptr_h_led_drvr_foo;
```

```c
IS31FL3236_HandleTypeDef h_led_drvr_foo;
h_led_drvr_foo.I2C_Bus = hi2c1;
h_led_drvr_foo.I2C_Device_Address = IS31FL3236_GET_I2C_ADDR(IS31FL3236_I2C_AD_TO_GND);
h_led_drvr_foo.I2C_Transmit_Timeout_Milliseconds = 10; // 10ms is default.
h_led_drvr_foo.Chip_Enable_Signal_Port = GPIOA;
h_led_drvr_foo.Chip_Enable_Signal_Pin = GPIO_PIN_10;

// Optional [
h_led_drvr_foo.RGB_Mode_Color_1 = IS31FL3236_RGB_CONFIG_RED;
h_led_drvr_foo.RGB_Mode_Color_2 = IS31FL3236_RGB_CONFIG_GREEN;
h_led_drvr_foo.RGB_Mode_Color_3 = IS31FL3236_RGB_CONFIG_BLUE;
// ]

// Store the pointer to the handle in a (global) variable for future access in other functions.
ptr_h_led_drvr_foo = &h_led_drvr_foo;

// Init the handle.
IS31FL3236_Init(ptr_h_led_drvr_foo);
```

Note that `IS31FL3236_Init` has to be called with a handle before the
handle gets used by any other function.

The `IS31FL3236_Init` performes a device reset, disables the software
device shutdown and enables the IS31FL3236 chip via the enable/SDB signal.

After the initialisation the driver is operational and can be used.

## Update Cycles of the IS31FL3236

In order to allow instant switching from one configuration to another, the
IS31FL3236 chip latches the recieved data only when an update command is sent
to the device via the I2C bus.

By calling `IS31FL3236_Update` the device latches all recieved data
to the led control circuitry.

## Reset, Software Shutdown and Chip Enable

By calling `IS31FL3236_Reset` the device gets reset. What a reset
command does can be read in the device datasheet of the IS31Fl3236.

The `IS31FL3236_SetSoftwareShutdown` sets the software shutdown mode
of the deivce.

`IS31FL3236_SetChipEnable` controlls the hardware chip enable (SDB)
signal of the chip.