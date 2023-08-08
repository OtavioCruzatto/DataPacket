/*
 * dataPacketTx.c
 *
 *  Created on: Jul 28, 2023
 *      Author: Otavio
 */

#include "dataPacketTx.h"

void dataPacketTxInit(DataPacketTx *dataPacketTx, uint8_t start_1, uint8_t start_2)
{
	dataPacketTx->start_1 = start_1;
	dataPacketTx->start_2 = start_2;
	dataPacketTx->command = 0x00;
	dataPacketTx->payloadDataLength = 0x00;
	memset(dataPacketTx->payloadData, 0x00, QTY_PAYLOAD_TX_DATA_BYTES);
	dataPacketTx->crc8 = 0x00;
	memset(dataPacketTx->dataPacket, 0x00, QTY_PACKET_TX_BYTES);
	dataPacketTx->dataPacketLength = 0x00;
	dataPacketTx->dataPacketTxStatus = INVALID_TX_DATA_PACKET;
}

void dataPacketTxMount(DataPacketTx *dataPacketTx)
{
	dataPacketTx->dataPacket[0] = dataPacketTx->start_1;
	dataPacketTx->dataPacket[1] = dataPacketTx->start_2;
	dataPacketTx->dataPacket[2] = dataPacketTx->command;
	dataPacketTx->dataPacket[3] = dataPacketTx->payloadDataLength;
	memcpy(dataPacketTx->dataPacket + 4, dataPacketTx->payloadData, dataPacketTx->payloadDataLength);
	dataPacketTx->dataPacketLength = dataPacketTx->payloadDataLength + 4 + 1;
	dataPacketTx->crc8 = genCrc(dataPacketTx->dataPacket, dataPacketTx->dataPacketLength - 1);
	dataPacketTx->dataPacket[dataPacketTx->payloadDataLength + 4] = dataPacketTx->crc8;
	dataPacketTx->dataPacketTxStatus = VALID_TX_DATA_PACKET;
}

void dataPacketTxUartSend(DataPacketTx *dataPacketTx, UART_HandleTypeDef huart)
{
	if (dataPacketTx->dataPacketTxStatus == VALID_TX_DATA_PACKET)
	{
		HAL_UART_Transmit(&huart, dataPacketTx->dataPacket, dataPacketTx->dataPacketLength, HAL_MAX_DELAY);
	}
}

void dataPacketTxClear(DataPacketTx *dataPacketTx)
{
	dataPacketTx->dataPacketTxStatus = INVALID_TX_DATA_PACKET;
	dataPacketTx->dataPacketLength = 0;
	dataPacketTx->crc8 = 0x00;
	dataPacketTx->command = 0x00;
	memset(dataPacketTx->dataPacket, 0x00, QTY_PACKET_TX_BYTES);
}

void dataPacketTxPayloadDataClear(DataPacketTx *dataPacketTx)
{
	dataPacketTx->dataPacketTxStatus = INVALID_TX_DATA_PACKET;
	dataPacketTx->dataPacketLength = 0;
	dataPacketTx->crc8 = 0x00;
	dataPacketTx->command = 0x00;
	memset(dataPacketTx->payloadData, 0x00, QTY_PAYLOAD_TX_DATA_BYTES);
}

void dataPacketTxSetCommand(DataPacketTx *dataPacketTx, uint8_t command)
{
	dataPacketTx->dataPacketTxStatus = INVALID_TX_DATA_PACKET;

	if ((command < 0x01) || (command > 0xFE))
	{
		return;
	}

	dataPacketTx->command = command;
}

uint8_t dataPacketTxGetCommand(DataPacketTx *dataPacketTx)
{
	return dataPacketTx->command;
}

void dataPacketTxSetPayloadData(DataPacketTx *dataPacketTx, uint8_t *payloadData, uint8_t payloadDataLength)
{
	dataPacketTx->dataPacketTxStatus = INVALID_TX_DATA_PACKET;
	memcpy(dataPacketTx->payloadData, payloadData, payloadDataLength);
	dataPacketTx->payloadDataLength = payloadDataLength;
}

uint8_t *dataPacketTxGetPayloadData(DataPacketTx *dataPacketTx)
{
	return dataPacketTx->payloadData;
}

uint8_t dataPacketTxGetPayloadDataLength(DataPacketTx *dataPacketTx)
{
	return dataPacketTx->payloadDataLength;
}

uint8_t dataPacketTxGetCrc8(DataPacketTx *dataPacketTx)
{
	return dataPacketTx->crc8;
}

uint8_t *dataPacketTxGetDataPacket(DataPacketTx *dataPacketTx)
{
	return dataPacketTx->dataPacket;
}

uint8_t dataPacketTxGetDataPacketLength(DataPacketTx *dataPacketTx)
{
	return dataPacketTx->dataPacketLength;
}

DataPacketTxStatus dataPacketTxGetDataPacketStatus(DataPacketTx *dataPacketTx)
{
	return dataPacketTx->dataPacketTxStatus;
}
