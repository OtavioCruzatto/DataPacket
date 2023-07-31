/*
 * crc8.c
 *
 *  Created on: 6 de out de 2021
 *      Author: Otavio
 */

#include "crc8.h"

static uint8_t calcCrc8(uint8_t crc3, uint8_t b);

/**
  * Calcula o crc8 entre o range passado como parametro.
  */
uint8_t genCrc(uint8_t buffer[], uint16_t qtd_de_bytes_no_pacote)
{
    uint8_t crc = 0;
    uint8_t i = 0;

    for (i = 0; i < qtd_de_bytes_no_pacote; i++)
    {
      crc = calcCrc8(crc, buffer[i]);
    }

  return crc;
}

/**
  * Funcao que calcula o CRC8
  */
static uint8_t calcCrc8(uint8_t crc3, uint8_t b)
{
    uint8_t pos = 0;
    pos = (((crc3 & 0xff) ^ b) & 0xff);

    return ((crc3) >> 8) ^ table[pos];
}
