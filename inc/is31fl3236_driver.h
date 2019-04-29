/*----------------------------------------------------------------
 * FILENAME :		is31fl3236_driver.h
 * PROJECT :		IS31FL3236_STM32_Driver
 * AUTHOR :			Johannes Berndorfer
 * BREIF :			Hardware abstraction layer for the IS31FL3236
 * 					IC on STM32 (ARM) hardware.
 *
 * Copyright (c) 2019 Johannes Berndorfer. All rights reserved.
 * ---------------------------------------------------------------
 * DATE CREATED :	28.04.2019
 * VERSION :		1.0
 * ---------------------------------------------------------------
 * DESCRIPTION :
 * 		Header file of the IS31FL3236_STM32_Driver library. This
 * 		file shall be included for use of the IS31FL3236 library
 * 		for the STM32.
 *
 * 		For more info and documentation of this library please
 * 		refer to the GitHub wiki at:
 * 			https://github.com/berndoJ/IS31FL3236_STM32_HAL_Driver/wiki
 *
 *--------------------------------------------------------------*/

#ifndef _IS31FL3236_DRIVER_H_
#define _IS31FL3236_DRIVER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stm32f1xx_hal.h> // Include ST's HAL library for the STM32. The correct library for the platform has to be chosen.

#define IS31FL3236_I2C_AD_TO_GND				0x00
#define IS31FL3236_I2C_AD_TO_SCL				0x02
#define IS31FL3236_I2C_AD_TO_SDA				0x04
#define IS31FL3236_I2C_AD_TO_VCC				0x06
#define IS31FL3236_GET_I2C_ADDR(AD_conn)		(0x78 | AD_conn) // Retrieves the I2C address of the IS31FL3236 chip by specifying the connection of the AD pin.

#define IS31FL3236_MAX_CHANNELS					36 // The IS31FL3236 chip has 36 controllable PWM channels.
#define IS31FL3236_MAX_RGB_CHANNELS				(IS31FL3236_MAX_CHANNELS / 3) // Maximum amount of RGB channels for RGB channel mode.

#define IS31FL3236_REGISTER_SHUTDOWN			0x00 // Shutdown register: The LSBit of this register determine-s if the chip is in shutdown. Write 0x00 for shutdown, 0x01 for normal operation.
#define IS31FL3236_REGISTER_PWM					0x01 // Add the PWM channel index (range from 0 to 35) to IS31FL3236_REGISTER_PWM to address different channels; Write pwm value for channel in this register.
#define IS31FL3236_REGISTER_LED_CTRL			0x26 // LED control register: LED control state (on or off) and maximum current setting. Refer to datasheet for detailed information.
#define IS31FL3236_REGISTER_UPDATE				0x25 // Update register: Write 0x00 to this register to update PWM and LED control values.
#define IS31FL3236_REGISTER_GLOBAL_CTRL			0x4a // Global control register: The LSBit of this register sets all led states: 0 on, 1 off.
#define IS31FL3236_REGISTER_RESET				0x4f // Reset register: Write 0x00 to reset all registers of the chip.

#define IS31FL3236_LED_CURRENT_MAX				0x00 // LED current is set to maximum current specified by external resistor. (refer to datasheet) [RESET DEFAULT]
#define IS31FL3236_LED_CURRENT_MAX_DIV_2		0x02 // LED current is set to maximum current specified by external resistor divided by 2. (refer to datasheet)
#define IS31FL3236_LED_CURRENT_MAX_DIV_3		0x04 // LED current is set to maximum current specified by external resistor divided by 3. (refer to datasheet)
#define IS31FL3236_LED_CURRENT_MAX_DIV_4		0x06 // LED current is set to maximum current specified by external resistor divided by 4. (refer to datasheet)

#define IS31FL3236_LED_STATE_OFF				0x00 // LED is off. [RESET DEFAULT]
#define IS31FL3236_LED_STATE_ON					0x01 // LED is controlled by PWM registers.

#define IS31FL3236_SOFTWARE_SHUTDOWN_ENABLED	0x00 // Chip software shutdown mode enabled. [RESET DEFAULT]
#define IS31FL3236_SOFTWARE_SHUTDOWN_DISABLED	0x01 // Chip software shutdown mode disabled.

#define IS31FL3236_RGB_CONFIG_RED				0x00 // RGB mode color red.
#define IS31FL3236_RGB_CONFIG_GREEN				0x01 // RGB mode color green.
#define IS31FL3236_RGB_CONFIG_BLUE				0x02 // RGB mode color blue.

#define IS31FL3236_CHIP_DISABLED				GPIO_PIN_RESET // Chip disabled state.
#define IS31FL3236_CHIP_ENABLED					GPIO_PIN_SET // Chip enabled state.

// Initialisation struct typedef.
typedef struct
{
	I2C_HandleTypeDef* I2C_Bus;
	uint8_t I2C_Device_Address;
	uint32_t I2C_Transmit_Timeout_Milliseconds;
	GPIO_TypeDef* Chip_Enable_Signal_Port;
	uint16_t Chip_Enable_Signal_Pin;
	uint8_t RGB_Mode_Color_1;
	uint8_t RGB_Mode_Color_2;
	uint8_t RGB_Mode_Color_3;
} IS31FL3236_InitTypeDef;

// Handle struct typedef.
typedef struct
{
	IS31FL3236_InitTypeDef Init;
} IS31FL3236_HandleTypeDef;

void IS31FL3236_Init(IS31FL3236_HandleTypeDef* handle);
void IS31FL3236_SetChipEnable(IS31FL3236_HandleTypeDef* handle, uint8_t enable_state);
void IS31FL3236_WriteRegister(IS31FL3236_HandleTypeDef* handle, uint8_t register_address, uint8_t value);
void IS31FL3236_Reset(IS31FL3236_HandleTypeDef* handle);
void IS31FL3236_Update(IS31FL3236_HandleTypeDef* handle);

void IS31FL3236_WriteLEDControl(IS31FL3236_HandleTypeDef* handle, uint8_t channel, uint8_t led_current_setting, uint8_t led_state);
void IS31FL3236_WriteGlobalLEDControl(IS31FL3236_HandleTypeDef* handle, uint8_t led_current_setting, uint8_t led_state);
void IS31FL3236_WritePWM(IS31FL3236_HandleTypeDef* handle, uint8_t channel, uint8_t pwm_value);
void IS31FL3236_WriteRGBPWM(IS31FL3236_HandleTypeDef* handle, uint8_t rgb_channel, uint8_t red, uint8_t green, uint8_t blue);
void IS31FL3236_SetSoftwareShutdown(IS31FL3236_HandleTypeDef* handle, uint8_t software_shutdown_mode);

#ifdef __cplusplus
}
#endif

#endif /* _IS31FL3236_DRIVER_H_ */
