/*
 * Copyright (c) 2011-2012 SmeshLink Technology Corporation.
 * All rights reserved.
 *
 * $Id: co2-sensor.c $
 */

/**
 * \file
 *         This application demonstrates a custom CO2 sensor.
 * \author
 *         SmeshLink
 */

#include "contiki.h"
#include "contiki-net.h"

#include "co2.h"

#include <stdio.h>

/*---------------------------------------------------------------------------*/
PROCESS(co2_process, "CO2 process");
AUTOSTART_PROCESSES(&co2_process);
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(co2_process, ev, data)
{
  static struct etimer timer;

  PROCESS_BEGIN();

  etimer_set(&timer, CLOCK_CONF_SECOND);

  co2_init();

  while(1) {
    /* Wait for an event. */
    PROCESS_WAIT_EVENT();

    /* Got the timer's event~ */
    if (ev == PROCESS_EVENT_TIMER) {
      /* Read co2 value. */
      uint16_t co2 = co2_get();

      printf("co2:%u\n", co2);

      /* Reset the etimer so it will generate another event after the exact same time. */
      etimer_reset(&timer);
    }
  } // while (1)

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
