/*
 * Copyright (c) 2011-2012 SmeshLink Technology Corporation.
 * All rights reserved.
 *
 * $Id: sht11-sensors-sample.c $
 */

/**
 * \file
 *         This application shows how read data of temperature and humidity
 *         using sht11 sensors interfaces.
 * \author
 *         SmeshLink
 */

#include "contiki.h"

#include "dev/sht11.h"

#include <stdio.h>

/*---------------------------------------------------------------------------*/
PROCESS(sensors_sample_process, "Sensors sample process");
AUTOSTART_PROCESSES(&sensors_sample_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(sensors_sample_process, ev, data)
{
  /* Variables are declared static to ensure their values are kept between kernel calls. */
  static struct etimer timer;

  /* Any process must start with this. */
  PROCESS_BEGIN();

  /* Set the etimer to generate an event in one second. */
  etimer_set(&timer, CLOCK_CONF_SECOND);

  sht11_init();

  while(1) {
    /* Wait for an event. */
    PROCESS_WAIT_EVENT();

    /* Got the timer's event~ */
    if (ev == PROCESS_EVENT_TIMER) {
      /* Read temperature value. */
      unsigned int temp = sht11_temp();
      /* Read humidity value. */
      unsigned int humidity = sht11_humidity();

      printf("temp:%u\nhumidity:%u", temp, humidity);

      /* Reset the etimer so it will generate another event after the exact same time. */
      etimer_reset(&timer);
    }
  } // while (1)

  /* Any process must end with this, even if it is never reached. */
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
