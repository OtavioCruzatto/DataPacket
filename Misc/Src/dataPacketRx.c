/*
 * dataPacketRx.c
 *
 *  Created on: Ago 05, 2023
 *      Author: Otavio
 */

#include "dataPacketRx.h"

void dataPacketRxInit(DataPacketRx *dataPacketRx, uint8_t start_1, uint8_t start_2)
{
	dataPacketRx->start_1 = start_1;
	dataPacketRx->start_2 = start_2;
	dataPacketRx->command = 0x00;
	dataPacketRx->payloadDataLength = 0x00;
	memset(dataPacketRx->payloadData, 0x00, QTY_PAYLOAD_RX_DATA_BYTES);
	dataPacketRx->crc8 = 0x00;
	memset(dataPacketRx->dataPacket, 0x00, QTY_PACKET_RX_BYTES);
	dataPacketRx->dataPacketLength = 0x00;
	dataPacketRx->currentRxByteIndex = 0;
	dataPacketRx->dataPacketRxStatus = INVALID_RX_DATA_PACKET;
	dataPacketRx->containsStarterBytes = FALSE;
	dataPacketRx->starterByteIndex = 0;
}

void dataPacketRxAppend(DataPacketRx *dataPacketRx, uint8_t newByte)
{
	dataPacketRx->dataPacket[dataPacketRx->currentRxByteIndex] = newByte;
	dataPacketRx->currentRxByteIndex++;
	dataPacketRx->dataPacketLength++;

	if (dataPacketRx->currentRxByteIndex > QTY_PACKET_RX_BYTES)
	{
		dataPacketRxClear(dataPacketRx);
		dataPacketRx->currentRxByteIndex = 0;
		dataPacketRx->dataPacketLength = 0;
	}
}

void dataPacketRxDecode(DataPacketRx *dataPacketRx)
{
	if (dataPacketRx->containsStarterBytes == TRUE)
	{
		dataPacketRxSetCommand(dataPacketRx, dataPacketRx->dataPacket[dataPacketRx->starterByteIndex + 2]);
		dataPacketRx->payloadDataLength = dataPacketRx->dataPacket[dataPacketRx->starterByteIndex + 3];

		if (dataPacketRx->payloadDataLength == 0)
		{
			uint8_t receivedCrc8 = dataPacketRx->dataPacket[dataPacketRx->starterByteIndex + 4];
			dataPacketRx->crc8 = genCrc(dataPacketRx->dataPacket + dataPacketRx->starterByteIndex, 4);

			if (dataPacketRx->crc8 == receivedCrc8)
			{
				dataPacketRx->currentRxByteIndex = 0;
				dataPacketRx->dataPacketRxStatus = VALID_RX_DATA_PACKET;
			}
		}
		else
		{
			uint8_t receivedCrc8 = dataPacketRx->dataPacket[dataPacketRx->starterByteIndex + dataPacketRx->payloadDataLength + 4];
			dataPacketRx->crc8 = genCrc(dataPacketRx->dataPacket + dataPacketRx->starterByteIndex, dataPacketRx->payloadDataLength + 4);

			if (dataPacketRx->crc8 == receivedCrc8)
			{
				dataPacketRxSetPayloadData(dataPacketRx, dataPacketRx->dataPacket + dataPacketRx->starterByteIndex + 4, dataPacketRx->payloadDataLength);
				dataPacketRx->currentRxByteIndex = 0;
				dataPacketRx->dataPacketRxStatus = VALID_RX_DATA_PACKET;
			}
		}
	}
	else
	{
		if (dataPacketRx->dataPacketLength >= MIN_PACKET_RX_BYTES)
		{
			uint16_t index = 0;
			for (index = 0; index < dataPacketRx->dataPacketLength; index++)
			{
				if ((dataPacketRx->dataPacket[index] == dataPacketRx->start_1) && (dataPacketRx->dataPacket[index+1] == dataPacketRx->start_2))
				{
					dataPacketRx->containsStarterBytes = TRUE;
					dataPacketRx->starterByteIndex = index;
					break;
				}
			}

			if (dataPacketRx->containsStarterBytes == FALSE)
			{
				dataPacketRxClear(dataPacketRx);
			}
		}
	}
}

void dataPacketRxClear(DataPacketRx *dataPacketRx)
{
	dataPacketRx->dataPacketRxStatus = INVALID_RX_DATA_PACKET;
	dataPacketRx->containsStarterBytes = FALSE;
	dataPacketRx->currentRxByteIndex = 0;
	dataPacketRx->dataPacketLength = 0;
	dataPacketRx->payloadDataLength = 0;
	dataPacketRx->command = 0x00;
	dataPacketRx->crc8 = 0x00;
	dataPacketRx->starterByteIndex = 0;
	memset(dataPacketRx->payloadData, 0x00, QTY_PAYLOAD_RX_DATA_BYTES);
	memset(dataPacketRx->dataPacket, 0x00, QTY_PACKET_RX_BYTES);
}

void dataPacketRxPayloadDataClear(DataPacketRx *dataPacketRx)
{
	dataPacketRx->dataPacketRxStatus = INVALID_RX_DATA_PACKET;
	dataPacketRx->containsStarterBytes = FALSE;
	dataPacketRx->currentRxByteIndex = 0;
	dataPacketRx->dataPacketLength = 0;
	dataPacketRx->payloadDataLength = 0;
	dataPacketRx->command = 0x00;
	dataPacketRx->crc8 = 0x00;
	memset(dataPacketRx->payloadData, 0x00, QTY_PAYLOAD_RX_DATA_BYTES);
}

void dataPacketRxSetCommand(DataPacketRx *dataPacketRx, uint8_t command)
{
	dataPacketRx->dataPacketRxStatus = INVALID_RX_DATA_PACKET;

	if ((command < 0x01) || (command > 0xFE))
	{
		return;
	}

	dataPacketRx->command = command;
}

uint8_t dataPacketRxGetCommand(DataPacketRx *dataPacketRx)
{
	return dataPacketRx->command;
}

void dataPacketRxSetPayloadData(DataPacketRx *dataPacketRx, uint8_t *payloadData, uint8_t payloadDataLength)
{
	dataPacketRx->dataPacketRxStatus = INVALID_RX_DATA_PACKET;
	memcpy(dataPacketRx->payloadData, payloadData, payloadDataLength);
	dataPacketRx->payloadDataLength = payloadDataLength;
}

uint8_t *dataPacketRxGetPayloadData(DataPacketRx *dataPacketRx)
{
	return dataPacketRx->payloadData;
}

uint8_t dataPacketRxGetPayloadDataLength(DataPacketRx *dataPacketRx)
{
	return dataPacketRx->payloadDataLength;
}

uint8_t dataPacketRxGetCrc8(DataPacketRx *dataPacketRx)
{
	return dataPacketRx->crc8;
}

uint8_t *dataPacketRxGetDataPacket(DataPacketRx *dataPacketRx)
{
	return dataPacketRx->dataPacket;
}

uint8_t dataPacketRxGetDataPacketLength(DataPacketRx *dataPacketRx)
{
	return dataPacketRx->dataPacketLength;
}

DataPacketRxStatus dataPacketRxGetDataPacketStatus(DataPacketRx *dataPacketRx)
{
	return dataPacketRx->dataPacketRxStatus;
}
