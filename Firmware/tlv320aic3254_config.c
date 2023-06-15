/*
 * tlv320aic3254_config.c
 *
 *  Created on: Jun 15, 2023
 *      Author: Pantelis
 */
#include "tlv320aic3254_config.h"

void tlv320_Init(I2C_HandleTypeDef *hi2c2){

	uint16_t I2C_Reg_Address;
	uint8_t I2C_Data;


	/*Performing hardware Reset*/
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_Delay(100);


	/*Page select 0*/
	I2C_Reg_Address = 0x00;
	I2C_Data = 0x00;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Performing software Reset CHECKED*/
	I2C_Reg_Address = 0x01;
	I2C_Data = 0x01;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	HAL_Delay(100);
	/*I2S 24BIT i2s configured with 16bit extended*/
	I2C_Reg_Address = 0x1B;
	I2C_Data = 0x20;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*External master clock is selected and internal clock generator is off by default*/
	/*For MADC, NADC , AOSR, MDAC, NDAC, DOSR check manual at page 79 */
	/*Configuring NADC and MADC registers - AOSR registers are set to 128 by default CHECKED*/
	//NADC
	I2C_Reg_Address = 0x12;
	I2C_Data = 0x81;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	//MADC
	I2C_Reg_Address = 0x13;
	I2C_Data = 0x82;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	//AOSR
	I2C_Reg_Address = 0x14;
	I2C_Data = 0x80;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	//Sampling Freq = 48Khz, extMCLK = 48Mhz
	/*Configuring NDAC and MDAC registers - DOSR registers are set to 128 by default*/
	//NDAC
	I2C_Reg_Address = 0x0B;
	I2C_Data = 0x81;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	//MDAC
	I2C_Reg_Address = 0x0C;
	I2C_Data = 0x82;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	//DOSR 128
	I2C_Reg_Address = 0x0D;
	I2C_Data = 0x00;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	I2C_Reg_Address = 0x0E;
	I2C_Data = 0x80;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/* ADC PRB_R1, DAC PRB_P1 set by default */

	/*Page select 1 CHECKED*/
	I2C_Reg_Address = 0x00;
	I2C_Data = 0x01;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Power up internal aVDD LDO CHECKED*/
	I2C_Reg_Address = 0x01;
	I2C_Data = 0x00;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Power enable master analog power control */
	I2C_Reg_Address = 0x02;
	I2C_Data = 0x01;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Setting up common mode to 0.9V */
	I2C_Reg_Address = 0x0a;
	I2C_Data = 0x00;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/* Selecting ADC PTM_R4 CHECKED*/
	I2C_Reg_Address = 0x3d;
	I2C_Data = 0x00;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Setting MicPGA startup delay to 3.1ms */
	I2C_Reg_Address = 0x47;
	I2C_Data = 0x32;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Power REF charging time to 40ms */
	I2C_Reg_Address = 0x7b;
	I2C_Data = 0x01;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Routing IN1L to left PGA_Positive with 20k input impedance */
	I2C_Reg_Address = 0x34;
	I2C_Data = 0x80;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Setting up IN1L common mode to the negative terminal */
	I2C_Reg_Address = 0x36;
	I2C_Data = 0x80;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Routing IN1R to right PGA_Positive with 20k input impedance */
	I2C_Reg_Address = 0x37;
	I2C_Data = 0x80;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Setting up IN1R common mode to the negative terminal */
	I2C_Reg_Address = 0x39;
	I2C_Data = 0x80;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Unmute Left MICPGA */
	I2C_Reg_Address = 0x3b;
	I2C_Data = 0x0c;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Unmute Right MICPGA */
	I2C_Reg_Address = 0x3c;
	I2C_Data = 0x0c;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);


	/*Page select 0 */
	I2C_Reg_Address = 0x00;
	I2C_Data = 0x00;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Powering up left and right ADC */
	I2C_Reg_Address = 0x51;
	I2C_Data = 0xc0;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*Unmute Left and Right ADC Digital Volume Control*/
	I2C_Reg_Address = 0x52;
	I2C_Data = 0x00;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);


	/*Page select 1*/
	I2C_Data = 0x01;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, 0x00, 1, &I2C_Data, 1, 100);

	/*LOL Routing*/
	I2C_Reg_Address = 0x0E;
	I2C_Data = 0x08;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*LOR Routing*/
	I2C_Reg_Address = 0x0F;
	I2C_Data = 0x08;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*LOL Driver Gain unmuted*/
	I2C_Reg_Address = 0x12;
	I2C_Data = 0x00;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*LOR Driver Gain unmuted*/
	I2C_Reg_Address = 0x13;
	I2C_Data = 0x00;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);


	/*Page select 0 CHECKED*/
	I2C_Reg_Address = 0x00;
	I2C_Data = 0x00;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);

	/*DAC Channel Setup left - right*/
	I2C_Reg_Address = 0x3F;
	I2C_Data = 0xD4;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);


	/*DAC Channel Setup left - right unmuted*/
	I2C_Reg_Address = 0x40;
	I2C_Data = 0x00;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);


	/*Page select 1*/
	I2C_Data = 0x01;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, 0x00, 1, &I2C_Data, 1, 100);


	/*Powering up left and right DAC*/
	I2C_Data = 0x08;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, 0x0A, 1, &I2C_Data, 1, 100);


	/*Powering up left and right LOL and LOR Drivers*/
	I2C_Reg_Address = 0x09;
	I2C_Data = 0x0c;
	HAL_I2C_Mem_Write(hi2c2, TLV320_I2C_DEVICE_ADDRESS, I2C_Reg_Address, 1, &I2C_Data, 1, 100);
}


