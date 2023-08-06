/*
 * dataPacketTx.h
 *
 *  Created on: Jul 28, 2023
 *      Author: Otavio
 */

#ifndef INC_DATAPACKETTX_H_
#define INC_DATAPACKETTX_H_

#include "main.h"
#include <string.h>
#include "crc8.h"

#define MIN_PAYLOAD_TX_DATA_BYTES	0
#define MAX_PAYLOAD_TX_DATA_BYTES	255
#define MIN_PACKET_TX_BYTES			5
#define MAX_PACKET_TX_BYTES			(MIN_PACKET_TX_BYTES + MAX_PAYLOAD_TX_DATA_BYTES)
#define QTY_PAYLOAD_TX_DATA_BYTES	25
#define QTY_PACKET_TX_BYTES			(MIN_PACKET_TX_BYTES + QTY_PAYLOAD_TX_DATA_BYTES)

typedef enum DATA_PACKET_TX_STATUS
{
	INVALID_TX_DATA_PACKET = 0x00,
	VALID_TX_DATA_PACKET
} DataPacketTxStatus;

typedef struct
{
	uint8_t start_1;
	uint8_t start_2;
	uint8_t command;
	uint8_t payloadDataLength;
	uint8_t payloadData[QTY_PAYLOAD_TX_DATA_BYTES];
	uint8_t crc8;
	uint8_t dataPacket[QTY_PACKET_TX_BYTES];
	uint16_t dataPacketLength;
	DataPacketTxStatus dataPacketTxStatus;
} DataPacketTx;

void dataPacketTxInit(DataPacketTx *dataPacketTx, uint8_t start_1, uint8_t start_2);
void dataPacketTxMount(DataPacketTx *dataPacketTx);
void dataPacketTxUartSend(DataPacketTx *dataPacketTx, UART_HandleTypeDef huart);
void dataPacketTxClear(DataPacketTx *dataPacketTx);
void dataPacketTxPayloadDataClear(DataPacketTx *dataPacketTx);
void dataPacketTxSetCommand(DataPacketTx *dataPacketTx, uint8_t command);
uint8_t dataPacketTxGetCommand(DataPacketTx *dataPacketTx);
void dataPacketTxSetPayloadData(DataPacketTx *dataPacketTx, uint8_t *payloadData, uint8_t payloadDataLength);
uint8_t *dataPacketTxGetPayloadData(DataPacketTx *dataPacketTx);
uint8_t dataPacketTxGetPayloadDataLength(DataPacketTx *dataPacketTx);
uint8_t dataPacketTxGetCrc8(DataPacketTx *dataPacketTx);
uint8_t *dataPacketTxGetDataPacket(DataPacketTx *dataPacketTx);
uint8_t dataPacketTxGetDataPacketLength(DataPacketTx *dataPacketTx);
DataPacketTxStatus dataPacketTxGetDataPacketStatus(DataPacketTx *dataPacketTx);

#endif /* INC_DATAPACKETTX_H_ */
