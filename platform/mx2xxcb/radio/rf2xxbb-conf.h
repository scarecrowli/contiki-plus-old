/*
 * Copyright (c) 2012, SmeshLink Technology Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * @(#)$$
 */

/**
 * \file
 *         Configuration of rf2xxbb.
 *
 * \author
 *         SmeshLink
 */


#ifndef RF2XXBB_CONF_H_
#define RF2XXBB_CONF_H_

#if RF212BB
#define RF212_MAX_TX_POWER  0xe4 //8db
#define RF212_MIN_TX_POWER  0x0A //-11db
#define RF2XXBB 1
#define RF2XX_TXPOWER  RF212_MAX_TX_POWER
#define RF2XX_MAX_TX_POWER RF212_MAX_TX_POWER
#define RF2xxBB_CHANNEL_802_15_4 0
#define RF2xxBB_CHANNEL_LOWER_BOUND 0
#define RF2xxBB_CHANNEL_UPPER_BOUND 3
#define RF2xxBB_TXPOWER_LOWER_BOUND 0
#define RF2xxBB_TXPOWER_UPPER_BOUND 0xff

#define rf2xx_driver rf212_driver
#define rf2xx_is_ready_to_send() rf212_is_ready_to_send()
#define rf2xx_set_promiscuous_mode(value) rf212_set_promiscuous_mode(value)

#define rf2xx_calibrate rf212_calibrate
#define RF2xx_receive_on RF212_receive_on
#define rf2xx_listen_channel rf212_listen_channel
#define rf2xx_get_channel rf212_get_channel
#define rf2xx_set_channel rf212_set_channel
#define rf2xx_get_txpower rf212_get_txpower
#define rf2xx_set_txpower rf212_set_txpower
#define rf2xx_warm_reset rf212_warm_reset
#define rf2xx_start_sneeze rf212_start_sneeze
#define rf2xx_rssi rf212_rssi
#define rf2xx_set_pan_addr rf212_set_pan_addr

#if WITH_UIP6
#define RF212_CONF_AUTOACK              1
#else
#define RF212_CONF_AUTOACK              1
#endif

#define RF2XX_CHANNEL 0

#define RF212_CONF_TIMESTAMPS 0
#define RF212_CONF_SYMBOL_LOOP_COUNT 500

#elif RF230BB

#define RF2XXBB 1
#define RF230_MAX_TX_POWER 0
#define RF230_MIN_TX_POWER 0x0f
#define RF2XX_TXPOWER  RF230_MAX_TX_POWER
#define RF2XX_MAX_TX_POWER RF230_MAX_TX_POWER
#define RF2xxBB_CHANNEL_802_15_4 26
#define RF2xxBB_CHANNEL_LOWER_BOUND 11
#define RF2xxBB_CHANNEL_UPPER_BOUND 26
#define RF2xxBB_TXPOWER_LOWER_BOUND 0
#define RF2xxBB_TXPOWER_UPPER_BOUND 15

#define rf2xx_driver rf230_driver
#define rf2xx_is_ready_to_send() rf230_is_ready_to_send()
#define rf2xx_set_promiscuous_mode(value) rf230_set_promiscuous_mode(value)

#define rf2xx_calibrate rf230_calibrate
#define RF2xx_receive_on RF230_receive_on
#define rf2xx_listen_channel rf230_listen_channel
#define rf2xx_get_channel rf230_get_channel
#define rf2xx_set_channel rf230_set_channel
#define rf2xx_get_txpower rf230_get_txpower
#define rf2xx_set_txpower rf230_set_txpower
#define rf2xx_warm_reset rf230_warm_reset
#define rf2xx_start_sneeze rf230_start_sneeze
#define rf2xx_rssi rf230_rssi
#define rf2xx_set_pan_addr rf230_set_pan_addr

#if WITH_UIP6
#define RF230_CONF_AUTOACK              1
#else
#define RF230_CONF_AUTOACK              1
#endif

#define RF2XX_CHANNEL 26

#define RF230_CONF_TIMESTAMPS 0
#define RF230_CONF_SYMBOL_LOOP_COUNT 500

#else

#endif  /* RF212BB */

  /* Network setup */
#if RF212BB

#if 1              /* No radio cycling */

#define RF212_CONF_AUTOACK        1
/* Request 802.15.4 ACK on all packets sent by sicslowpan.c (else autoretry) */
/* Broadcasts will be duplicated by the retry count, since no one will ACK them! */
#define RF212_CONF_AUTORETRIES    2
/* CCA theshold energy -91 to -61 dBm (default -77). Set this smaller than the expected minimum rssi to avoid packet collisions */
/* The Jackdaw menu 'm' command is helpful for determining the smallest ever received rssi */
#define RF212_CONF_CCA_THRES    -85
/* Number of CSMA attempts 0-7. 802.15.4 2003 standard max is 5. */
#define RF212_CONF_CSMARETRIES    5
/* Allow sneeze command from jackdaw menu. Useful for testing CCA on other radios */
/* During sneezing, any access to an RF230 register will hang the MCU and cause a watchdog reset */
/* The host interface, jackdaw menu and rf230_send routines are temporarily disabled to prevent this */
/* But some calls from an internal uip stack might get through, e.g. from CCA or low power protocols, */
/* as temporarily disabling all the possible accesses would add considerable complication to the radio driver! */
#define RF212_CONF_SNEEZER        1

#elif 1  /* Contiki-mac radio cycling */

#define RF212_CONF_AUTORETRIES    1
#define RF212_CONF_AUTOACK        1
#define RF212_CONF_CSMARETRIES    0

#elif 1             /* cx-mac radio cycling */

#define RF212_CONF_AUTOACK        1
#define RF212_CONF_AUTORETRIES    1

#endif

#define RF2XX_CONF_AUTOACK RF212_CONF_AUTOACK
#define RF2XX_CONF_AUTORETRIES RF212_CONF_AUTORETRIES
#define RF2XX_CONF_CCA_THRES RF212_CONF_CCA_THRES
#define RF2XX_CONF_CSMARETRIES RF212_CONF_CSMARETRIES
#define RF2XX_CONF_SNEEZER RF212_CONF_SNEEZER

/* Define MAX_*X_POWER to reduce tx power and ignore weak rx packets for testing a miniature multihop network.
 * Leave undefined for full power and sensitivity.
 * tx=0 (3dbm, default) to 15 (-17.2dbm)
 * RF230_CONF_AUTOACK sets the extended mode using the energy-detect register with rx=0 (-91dBm) to 84 (-7dBm)
 *   else the rssi register is used having range 0 (91dBm) to 28 (-10dBm)
 *   For simplicity RF230_MIN_RX_POWER is based on the energy-detect value and divided by 3 when autoack is not set.
 * On the RF230 a reduced rx power threshold will not prevent autoack if enabled and requested.
 * These numbers applied to both Raven and Jackdaw give a maximum communication distance of about 15 cm
 * and a 10 meter range to a full-sensitivity RF230 sniffer.
#define RF230_MAX_TX_POWER 15
#define RF230_MIN_RX_POWER 30
#define RF2XX_MAX_TX_POWER RF230_MAX_TX_POWER
#define RF2XX_MIN_RX_POWER RF230_MIN_RX_POWER
 */

#elif RF230BB

#if 1              /* No radio cycling */

#define RF230_CONF_AUTOACK        1
/* Request 802.15.4 ACK on all packets sent by sicslowpan.c (else autoretry) */
/* Broadcasts will be duplicated by the retry count, since no one will ACK them! */
#define RF230_CONF_AUTORETRIES    3
/* CCA theshold energy -91 to -61 dBm (default -77). Set this smaller than the expected minimum rssi to avoid packet collisions */
/* The Jackdaw menu 'm' command is helpful for determining the smallest ever received rssi */
#define RF230_CONF_CCA_THRES    -85
/* Number of CSMA attempts 0-7. 802.15.4 2003 standard max is 5. */
#define RF230_CONF_CSMARETRIES    5
/* Allow sneeze command from jackdaw menu. Useful for testing CCA on other radios */
/* During sneezing, any access to an RF230 register will hang the MCU and cause a watchdog reset */
/* The host interface, jackdaw menu and rf230_send routines are temporarily disabled to prevent this */
/* But some calls from an internal uip stack might get through, e.g. from CCA or low power protocols, */
/* as temporarily disabling all the possible accesses would add considerable complication to the radio driver! */
#define RF230_CONF_SNEEZER        1

#elif 1  /* Contiki-mac radio cycling */

#define RF230_CONF_AUTORETRIES    1
#define RF230_CONF_AUTOACK        1
#define RF230_CONF_CSMARETRIES    1

#elif 1             /* cx-mac radio cycling */

#define RF230_CONF_AUTOACK        1
#define RF230_CONF_AUTORETRIES    1

#endif

#define RF2XX_CONF_AUTOACK RF230_CONF_AUTOACK
#define RF2XX_CONF_AUTORETRIES RF230_CONF_AUTORETRIES
#define RF2XX_CONF_CCA_THRES RF230_CONF_CCA_THRES
#define RF2XX_CONF_CSMARETRIES RF230_CONF_CSMARETRIES
#define RF2XX_CONF_SNEEZER RF230_CONF_SNEEZER

#endif /* RF212BB */

#endif /* RF2XXBB_CONF_H_ */
