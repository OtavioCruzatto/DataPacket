/*
 * dataPacket.c
 *
 *  Created on: Jul 28, 2023
 *      Author: Otavio
 */

#include "dataPacket.h"

void dataPacketInit(DataPacket *dataPacket, uint8_t start_1, uint8_t start_2)
{
	dataPacket->start_1 = start_1;
	dataPacket->start_2 = start_2;
	dataPacket->command = 0x00;
	dataPacket->payloadDataLength = 0x00;
	memset(dataPacket->payloadData, 0x00, MAX_PAYLOAD_DATA_BYTES);
	dataPacket->crc8 = 0x00;
	memset(dataPacket->dataPacket, 0x00, MAX_PACKET_BYTES);
	dataPacket->dataPacketLength = 0x00;
	dataPacket->dataPacketStatus = INVALID_DATA_PACKET;
}

void dataPacketMount(DataPacket *dataPacket)
{
	dataPacket->dataPacket[0] = dataPacket->start_1;
	dataPacket->dataPacket[1] = dataPacket->start_2;
	dataPacket->dataPacket[2] = dataPacket->command;
	dataPacket->dataPacket[3] = dataPacket->payloadDataLength;
	memcpy(dataPacket->dataPacket + 4, dataPacket->payloadData, dataPacket->payloadDataLength);
	dataPacket->dataPacketLength = dataPacket->payloadDataLength + 4 + 1;
	dataPacket->crc8 = genCrc(dataPacket->dataPacket, dataPacket->dataPacketLength - 1);
	dataPacket->dataPacket[dataPacket->payloadDataLength + 4] = dataPacket->crc8;
	dataPacket->dataPacketStatus = VALID_DATA_PACKET;
}

void dataPacketUartSend(DataPacket *dataPacket, UART_HandleTypeDef huart)
{
	if (dataPacket->dataPacketStatus == VALID_DATA_PACKET)
	{
		HAL_UART_Transmit(&huart, dataPacket->dataPacket, dataPacket->dataPacketLength, HAL_MAX_DELAY);
	}
}

void dataPacketClear(DataPacket *dataPacket)
{
	dataPacket->dataPacketStatus = INVALID_DATA_PACKET;
	memset(dataPacket->dataPacket, 0x00, MAX_PACKET_BYTES);
}

void dataPacketPayloadDataClear(DataPacket *dataPacket)
{
	dataPacket->dataPacketStatus = INVALID_DATA_PACKET;
	memset(dataPacket->payloadData, 0x00, MAX_PAYLOAD_DATA_BYTES);
}

void dataPacketSetCommand(DataPacket *dataPacket, uint8_t command)
{
	dataPacket->dataPacketStatus = INVALID_DATA_PACKET;

	if ((command < 0x01) || (command > 0xFE))
	{
		return;
	}

	dataPacket->command = command;
}

uint8_t dataPacketGetCommand(DataPacket *dataPacket)
{
	return dataPacket->command;
}

void dataPacketSetPayloadData(DataPacket *dataPacket, uint8_t *payloadData, uint8_t payloadDataLength)
{
	dataPacket->dataPacketStatus = INVALID_DATA_PACKET;
	memcpy(dataPacket->payloadData, payloadData, payloadDataLength);
	dataPacket->payloadDataLength = payloadDataLength;
}

uint8_t *dataPacketGetPayloadData(DataPacket *dataPacket)
{
	return dataPacket->payloadData;
}

uint8_t dataPacketGetPayloadDataLength(DataPacket *dataPacket)
{
	return dataPacket->payloadDataLength;
}

uint8_t dataPacketGetCrc8(DataPacket *dataPacket)
{
	return dataPacket->crc8;
}

uint8_t *dataPacketGetDataPacket(DataPacket *dataPacket)
{
	return dataPacket->dataPacket;
}

uint8_t dataPacketGetDataPacketLength(DataPacket *dataPacket)
{
	return dataPacket->dataPacketLength;
}

DataPacketStatus dataPacketGetDataPacketStatus(DataPacket *dataPacket)
{
	return dataPacket->dataPacketStatus;
}
