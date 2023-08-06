/*
 * dataPacketRx.h
 *
 *  Created on: Ago 05, 2023
 *      Author: Otavio
 */

#ifndef INC_DATAPACKETRX_H_
#define INC_DATAPACKETRX_H_

#include "main.h"
#include <string.h>
#include "crc8.h"

#define MIN_PAYLOAD_RX_DATA_BYTES	0
#define MAX_PAYLOAD_RX_DATA_BYTES	255
#define MIN_PACKET_RX_BYTES			5
#define MAX_PACKET_RX_BYTES			(MIN_PACKET_RX_BYTES + MAX_PAYLOAD_RX_DATA_BYTES)
#define QTY_PAYLOAD_RX_DATA_BYTES	25
#define QTY_PACKET_RX_BYTES			(MIN_PACKET_RX_BYTES + QTY_PAYLOAD_RX_DATA_BYTES)

typedef enum DATA_PACKET_RX_STATUS
{
	INVALID_RX_DATA_PACKET = 0x00,
	VALID_RX_DATA_PACKET
} DataPacketRxStatus;

typedef struct
{
	uint8_t start_1;
	uint8_t start_2;
	uint8_t command;
	uint8_t payloadDataLength;
	uint8_t payloadData[QTY_PAYLOAD_RX_DATA_BYTES];
	uint8_t crc8;
	uint8_t dataPacket[QTY_PACKET_RX_BYTES];
	uint16_t dataPacketLength;
	uint16_t currentRxByteIndex;
	uint8_t containsStarterBytes;
	uint16_t starterByteIndex;
	DataPacketRxStatus dataPacketRxStatus;
} DataPacketRx;

void dataPacketRxInit(DataPacketRx *dataPacketRx, uint8_t start_1, uint8_t start_2);
void dataPacketRxAppend(DataPacketRx *dataPacketRx, uint8_t newByte);
void dataPacketRxDecode(DataPacketRx *dataPacketRx);
void dataPacketRxClear(DataPacketRx *dataPacketRx);
void dataPacketRxPayloadDataClear(DataPacketRx *dataPacketRx);
void dataPacketRxSetCommand(DataPacketRx *dataPacketRx, uint8_t command);
uint8_t dataPacketRxGetCommand(DataPacketRx *dataPacketRx);
void dataPacketRxSetPayloadData(DataPacketRx *dataPacketRx, uint8_t *payloadData, uint8_t payloadDataLength);
uint8_t *dataPacketRxGetPayloadData(DataPacketRx *dataPacketRx);
uint8_t dataPacketRxGetPayloadDataLength(DataPacketRx *dataPacketRx);
uint8_t dataPacketRxGetCrc8(DataPacketRx *dataPacketRx);
uint8_t *dataPacketRxGetDataPacket(DataPacketRx *dataPacketRx);
uint8_t dataPacketRxGetDataPacketLength(DataPacketRx *dataPacketRx);
DataPacketRxStatus dataPacketRxGetDataPacketStatus(DataPacketRx *dataPacketRx);

#endif /* INC_DATAPACKETRX_H_ */
