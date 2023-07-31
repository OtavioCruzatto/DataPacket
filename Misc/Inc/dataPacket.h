/*
 * dataPacket.h
 *
 *  Created on: Jul 28, 2023
 *      Author: Otavio
 */

#ifndef INC_DATAPACKET_H_
#define INC_DATAPACKET_H_

#include "main.h"
#include <string.h>
#include "crc8.h"

#define MIN_PAYLOAD_DATA_BYTES	0
#define MAX_PAYLOAD_DATA_BYTES	255
#define MIN_PACKET_BYTES		5
#define MAX_PACKET_BYTES		260

typedef enum DATA_PACKET_STATUS
{
	INVALID_DATA_PACKET = 0x00,
	VALID_DATA_PACKET
} DataPacketStatus;

typedef struct
{
	uint8_t start_1;
	uint8_t start_2;
	uint8_t command;
	uint8_t payloadDataLength;
	uint8_t payloadData[MAX_PAYLOAD_DATA_BYTES];
	uint8_t crc8;
	uint8_t dataPacket[MAX_PACKET_BYTES];
	uint16_t dataPacketLength;
	DataPacketStatus dataPacketStatus;
} DataPacket;

void dataPacketInit(DataPacket *dataPacket, uint8_t start_1, uint8_t start_2);
void dataPacketMount(DataPacket *dataPacket);
void dataPacketUartSend(DataPacket *dataPacket, UART_HandleTypeDef huart);
void dataPacketClear(DataPacket *dataPacket);
void dataPacketPayloadDataClear(DataPacket *dataPacket);
void dataPacketSetCommand(DataPacket *dataPacket, uint8_t command);
uint8_t dataPacketGetCommand(DataPacket *dataPacket);
void dataPacketSetPayloadData(DataPacket *dataPacket, uint8_t *payloadData, uint8_t payloadDataLength);
uint8_t *dataPacketGetPayloadData(DataPacket *dataPacket);
uint8_t dataPacketGetPayloadDataLength(DataPacket *dataPacket);
uint8_t dataPacketGetCrc8(DataPacket *dataPacket);
uint8_t *dataPacketGetDataPacket(DataPacket *dataPacket);
uint8_t dataPacketGetDataPacketLength(DataPacket *dataPacket);
DataPacketStatus dataPacketGetDataPacketStatus(DataPacket *dataPacket);

#endif /* INC_DATAPACKET_H_ */
