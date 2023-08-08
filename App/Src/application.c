/*
 * application.c
 *
 *  Created on: Aug 7, 2023
 *      Author: Otavio
 */

#include "application.h"

void applicationInit(Application *application, GPIO_TypeDef* ledPort, uint16_t ledPin)
{
	application->ledPort = ledPort;
	application->ledPin = ledPin;
	application->blinkDelay = 0;
	application->blinkStatus = FALSE;
	application->command = 0;
	application->decodeCommandStatus = FALSE;
}

void applicationDecodeCommand(Application *application)
{
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

		default:
		  application->blinkDelay = 0;
		  application->blinkStatus = FALSE;
		  break;
	}
}

void applicationExecuteCommand(Application *application)
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


