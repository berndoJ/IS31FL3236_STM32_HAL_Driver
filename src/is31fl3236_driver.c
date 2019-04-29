/*----------------------------------------------------------------
 * FILENAME :		is31fl3236_driver.c
 * PROJECT :		IS31FL3236_STM32_Driver
 * AUTHOR :			Johannes Berndorfer
 * BREIF :			Hardware abstraction layer for the IS31FL3236
 * 					IC on STM32 (ARM) hardware. (Source code)
 *
 * Copyright (c) 2019 Johannes Berndorfer. All rights reserved.
 * ---------------------------------------------------------------
 * DATE CREATED :	28.04.2019
 * VERSION :		1.0
 * ---------------------------------------------------------------
 * DESCRIPTION :
 * 		This file contains the source code of the IS31FL3236
 * 		library for the STM32 platform.
 *
 *--------------------------------------------------------------*/

#include <is31fl3236_driver.h>

static uint8_t __IS31FL3236_Select_Color(uint8_t color_selector, uint8_t r, uint8_t g, uint8_t b);

/*
 * Initialises the given handle.
 */
void IS31FL3236_Init(IS31FL3236_HandleTypeDef* handle)
{
	IS31FL3236_Reset(handle);
	IS31FL3236_SetSoftwareShutdown(handle, IS31FL3236_SOFTWARE_SHUTDOWN_DISABLED);
	IS31FL3236_SetChipEnable(handle, IS31FL3236_CHIP_ENABLED);
}

/*
 * Changes the chip enable state of the specified chip.
 */
void IS31FL3236_SetChipEnable(IS31FL3236_HandleTypeDef* handle, uint8_t enable_state)
{
	HAL_GPIO_WritePin(handle->Init.Chip_Enable_Signal_Port, handle->Init.Chip_Enable_Signal_Pin, enable_state);
}

/*
 * Writes a given value to a given register.
 */
void IS31FL3236_WriteRegister(IS31FL3236_HandleTypeDef* handle, uint8_t register_address, uint8_t value)
{
	uint8_t buf[2];
	buf[0] = register_address;
	buf[1] = value;
	HAL_I2C_Master_Transmit(handle->Init.I2C_Bus, handle->Init.I2C_Device_Address, buf, 2, handle->Init.I2C_Transmit_Timeout_Milliseconds);
}

/*
 * Resets the specified chip. (Through I2C)
 */
void IS31FL3236_Reset(IS31FL3236_HandleTypeDef* handle)
{
	IS31FL3236_WriteRegister(handle, IS31FL3236_REGISTER_RESET, 0x00);
}

/*
 * Latches the written PWM and led control values in the chip to the led control circuit.
 */
void IS31FL3236_Update(IS31FL3236_HandleTypeDef* handle)
{
	IS31FL3236_WriteRegister(handle, IS31FL3236_REGISTER_UPDATE, 0x00);
}

/*
 * Sets the LED control for the specified chip / channel.
 */
void IS31FL3236_WriteLEDControl(IS31FL3236_HandleTypeDef* handle, uint8_t channel, uint8_t led_current_setting, uint8_t led_state)
{
	if (channel < IS31FL3236_MAX_CHANNELS)
		IS31FL3236_WriteRegister(handle, IS31FL3236_REGISTER_LED_CTRL + channel, (led_current_setting | led_state));
}

/*
 * Writes an led control word to all channels of a specified chip.
 */
void IS31FL3236_WriteGlobalLEDControl(IS31FL3236_HandleTypeDef* handle, uint8_t led_current_setting, uint8_t led_state)
{
	for (uint8_t i = 0; i < IS31FL3236_MAX_CHANNELS; i++)
	{
		IS31FL3236_WriteLEDControl(handle, i, led_current_setting, led_state);
	}
}

/*
 * Writes the given PWM value (0 - 255) to the specified chip / channel.
 */
void IS31FL3236_WritePWM(IS31FL3236_HandleTypeDef* handle, uint8_t channel, uint8_t pwm_value)
{
	if (channel < IS31FL3236_MAX_CHANNELS)
		IS31FL3236_WriteRegister(handle, IS31FL3236_REGISTER_PWM + channel, pwm_value);
}

/*
 * Writes a given color (r, g, b) to a specified rgb channel of the specified chip. The periodic order the individual leds
 * are connected can be set in the Init attribute of the handle struct. (RGB_Mode_Color_x)
 */
void IS31FL3236_WriteRGBPWM(IS31FL3236_HandleTypeDef* handle, uint8_t rgb_channel, uint8_t red, uint8_t green, uint8_t blue)
{
	if (rgb_channel < IS31FL3236_MAX_RGB_CHANNELS)
	{
		IS31FL3236_WritePWM(handle, rgb_channel * 3, __IS31FL3236_Select_Color(handle->Init.RGB_Mode_Color_1, red, green, blue));
		IS31FL3236_WritePWM(handle, (rgb_channel * 3) + 1, __IS31FL3236_Select_Color(handle->Init.RGB_Mode_Color_2, red, green, blue));
		IS31FL3236_WritePWM(handle, (rgb_channel * 3) + 2, __IS31FL3236_Select_Color(handle->Init.RGB_Mode_Color_3, red, green, blue));
	}
}

/*
 * Sets the software shutdown mode of the specified chip.
 */
void IS31FL3236_SetSoftwareShutdown(IS31FL3236_HandleTypeDef* handle, uint8_t software_shutdown_mode)
{
	IS31FL3236_WriteRegister(handle, IS31FL3236_REGISTER_SHUTDOWN, software_shutdown_mode);
}




/*
 * Selects red, green or blue value by the given color selector.
 */
static uint8_t __IS31FL3236_Select_Color(uint8_t color_selector, uint8_t r, uint8_t g, uint8_t b)
{
	switch (color_selector)
	{
	case IS31FL3236_RGB_CONFIG_RED:
		return r;
	case IS31FL3236_RGB_CONFIG_GREEN:
		return g;
	case IS31FL3236_RGB_CONFIG_BLUE:
		return b;
	default:
		return 0;
	}
}
