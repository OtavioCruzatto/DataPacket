/*
 * application.c
 *
 *  Created on: Aug 7, 2023
 *      Author: Otavio
 */

#include "application.h"

void applicationInit(Application *application, GPIO_TypeDef* ledPort, uint16_t ledPin, TIM_HandleTypeDef *pwmTimer, uint8_t pwmChannel)
{
	application->ledPort = ledPort;
	application->ledPin = ledPin;
	application->blinkDelay = DELAY_100_MILISECONDS;
	application->blinkStatus = TRUE;
	application->command = 0;
	application->decodeCommandStatus = FALSE;
	application->dataLenght = 0;
	application->dutyCycle = 0;
	application->updateDutyCycle = FALSE;
	application->pwmTimer = pwmTimer;
	application->pwmChannel = pwmChannel;
	memset(application->data, 0x00, QTY_DATA_BYTES);
}

void applicationDecodeCommand(Application *application)
{
	uint16_t decodedDutyCycle = 0;

	switch (application->command)
	{
		case CMD_TEMPORIZATION_1:
			application->blinkDelay = DELAY_100_MILISECONDS;
			application->blinkStatus = TRUE;
			break;

		case CMD_TEMPORIZATION_2:
			application->blinkDelay = DELAY_250_MILISECONDS;
			application->blinkStatus = TRUE;
			break;

		case CMD_TEMPORIZATION_3:
			application->blinkDelay = DELAY_500_MILISECONDS;
			application->blinkStatus = TRUE;
			break;

		case CMD_SET_DUTY_CYCLE:
			decodedDutyCycle = ((uint16_t) application->data[0] << 8) + ((uint16_t) application->data[1]);
			if (decodedDutyCycle > MAX_DUTY_CYCLE)
			{
				decodedDutyCycle = MAX_DUTY_CYCLE;
			}
			application->dutyCycle = decodedDutyCycle;
			application->updateDutyCycle = TRUE;
			break;

		default:
			application->blinkDelay = DELAY_100_MILISECONDS;
			application->blinkStatus = TRUE;

			application->dutyCycle = 2250;
			application->updateDutyCycle = TRUE;
			break;
	}
}

void applicationExecuteBlinkLed(Application *application)
{
	if (application->blinkStatus == TRUE)
	{
	  HAL_GPIO_TogglePin(application->ledPort, application->ledPin);
	}
	else
	{
	  HAL_GPIO_WritePin(application->ledPort, application->ledPin, GPIO_PIN_RESET);
	}
}

void applicationUpdateDutyCycle(Application *application)
{
	__HAL_TIM_SET_COMPARE(application->pwmTimer, application->pwmChannel, application->dutyCycle);
}

uint32_t applicationGetBlinkDelay(Application *application)
{
	return application->blinkDelay;
}

void applicationSetCommand(Application *application, uint8_t command)
{
	application->command = command;
}

void applicationSetDecodeStatus(Application *application, Bool status)
{
	application->decodeCommandStatus = status;
}

Bool applicationGetDecodeStatus(Application *application)
{
	return application->decodeCommandStatus;
}

void applicationSetData(Application *application, uint8_t *data, uint8_t dataLength)
{
	if (dataLength <= QTY_DATA_BYTES)
	{
		application->dataLenght = dataLength;
		memcpy(application->data, data, dataLength);
	}
}

void applicationSetUpdateDutyCycle(Application *application, Bool status)
{
	application->updateDutyCycle = status;
}

Bool applicationGetUpdateDutyCycle(Application *application)
{
	return application->updateDutyCycle;
}


