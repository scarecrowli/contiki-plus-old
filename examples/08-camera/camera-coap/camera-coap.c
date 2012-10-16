/*
 * Copyright (c) 2011-2012, SmeshLink Technology Ltd.
 * All rights reserved.
 *
 * $Id: camera-coap.c $
 */

/**
 * \file
 *         Restful interface (HTTP or CoAP based) for camera application.
 * \author
 *         SmeshLink
 */

#include "contiki.h"
#include "contiki-net.h"

#include "erbium.h"

#include "dev/leds.h"
#include "dev/adc-sensors.h"
#include "camera.h"

#include <stdio.h>
#include <string.h>

#if WITH_COAP == 3
#include "er-coap-03.h"
#elif WITH_COAP == 7
#include "er-coap-07.h"
#else
#warning "Erbium example without CoAP-specifc functionality"
#endif /* CoAP-specific example */

/*---------------------------------------------------------------------------*/
PROCESS(coap_sample, "Camera CoAP Server");
AUTOSTART_PROCESSES(&coap_sample);
/*---------------------------------------------------------------------------*/
PERIODIC_RESOURCE(voltage, METHOD_GET, "voltage", "title=\"Periodic voltage\";rt=\"Observable\"", 1*CLOCK_SECOND);
void
voltage_handler(void* request, void* response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  char buf[32];
  double voltage = voltage_get();
  sprintf(buf, "%d", (int)(voltage * (double)1000));
  REST.set_header_content_type(response, REST.type.TEXT_PLAIN);
  REST.set_response_payload(response, (uint8_t *)buf, strlen(buf));
}
void
voltage_periodic_handler(resource_t *r)
{
  static uint32_t obs_counter = 0;
  char content[32];

  obs_counter++;

  double voltage = voltage_get();

  /* Build notification. */
  coap_packet_t notification[1]; /* This way the packet can be treated as pointer as usual. */
  coap_init_message(notification, COAP_TYPE_NON, CONTENT_2_05, 0 );
  coap_set_payload(notification, content, snprintf(content, sizeof(content), "%d", (int)(voltage * (double)1000)));

  /* Notify the registered observers with the given message type, observe option, and payload. */
  REST.notify_subscribers(r, obs_counter, notification);
}

RESOURCE(camera, METHOD_GET | METHOD_POST, "camera", "camera");
void
camera_handler(void* request, void* response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  const char *temp;
  uint8_t buff[1024];
  camera_size_t camera_size = CAMERA_SIZE_1;
  u16_t count;
  u32_t size;
  int index = 0, len = 0, tries = 10;

  if (0 == *offset) {
    /* Determine the size of picture. 1 for the smallest and 3 for the largest. */
    if (!REST.get_query_variable(request, "size", &temp)) {
      REST.get_post_variable(request, "size", &temp);
    }
    if (temp) {
      camera_size = camera_parse_size(temp[0]);
    }
    leds_toggle(LEDS_GREEN);
    camera_take_picture(camera_size, preferred_size, &size, &count);
  }

  index = *offset / preferred_size + 1;
  count = camera_get_packet_count();
  len = camera_try_get_packet(index, buff, tries);
  *offset += len;
  if (index >= count) {
    *offset = -1;
  }
  REST.set_header_content_type(response, REST.type.IMAGE_JPEG);
  REST.set_response_payload(response, buff, len);
}

/*---------------------------------------------------------------------------*/
PROCESS_THREAD(coap_sample, ev, data)
{
  PROCESS_BEGIN();

  /* Initialize the REST engine. */
  rest_init_engine();

  /* Activate the application-specific resources. */
  rest_activate_resource(&resource_camera);

  rest_activate_periodic_resource(&periodic_resource_voltage);

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
