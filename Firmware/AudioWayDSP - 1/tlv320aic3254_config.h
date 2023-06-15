/*
 * tlv320aic3254_config.h
 *
 *  Created on: Jun 15, 2023
 *      Author: Patsaoglou P.
 */

#ifndef INC_TLV320AIC3254_CONFIG_H_
#define INC_TLV320AIC3254_CONFIG_H_

#include "stm32f3xx_hal.h"
#define TLV320_I2C_DEVICE_ADDRESS (0x18<<1)

void tlv320_Init(I2C_HandleTypeDef *hi2c2);

#endif /* INC_TLV320AIC3254_CONFIG_H_ */
