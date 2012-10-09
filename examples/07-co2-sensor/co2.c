/*
 * Copyright (c) 2011-2012 SmeshLink Technology Corporation.
 * All rights reserved.
 *
 * $Id: co2.c $
 */

/**
 * \file
 *         A custom CO2 sensor using RS232.
 * \author
 *         SmeshLink
 */

#include "co2.h"

#define MAX_DELAY 1000000

static char read_co2_cmd[9] =  {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};

void
co2_init()
{
  rs232_sensor_init(RS232_PORT_0, USART_BAUD_9600, USART_PARITY_NONE | USART_STOP_BITS_1 | USART_DATA_BITS_8);
  rs232_sensor_set_frame_length(9);
}

uint16_t
co2_get()
{
  u32_t counter = MAX_DELAY;
  u16_t co2 = 0;

  rs232_sensor_print(read_co2_cmd);

  while (!rs232_frame.done && counter--) {
  //while (!rs232_frame.done) {

  }

  co2 |= rs232_frame.frame[2];
  co2 = co2 << 8;
  co2 |= rs232_frame.frame[3];

  return co2;
}

int
co2_debug(char* buf)
{
  return rs232_sensor_debug(buf);
}
