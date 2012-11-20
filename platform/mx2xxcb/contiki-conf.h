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
 *         Configuration for SmeshLink MX2XXCC.
 *
 * \author
 *         Simon Barner <barner@in.tum.de>
 *         David Kopf <dak664@embarqmail.com>
 *         SmeshLink
 */

#ifndef __CONTIKI_CONF_H__
#define __CONTIKI_CONF_H__

#define HAVE_STDINT_H
#include "avrdef.h"

#include "platform-conf.h"

/* The 1284p can use TIMER2 with the external 32768Hz crystal to keep time. Else TIMER0 is used. */
/* The sleep timer in raven-lcd.c also uses the crystal and adds a TIMER2 interrupt routine if not already define by clock.c */
#define AVR_CONF_USE32KCRYSTAL 1

#if RF2XXBB
#else
#define PACKETBUF_CONF_HDR_SIZE    0         //RF230 combined driver/mac handles headers internally
#endif /*RF2XXBB */

#if WITH_UIP6
#define NETSTACK_CONF_NETWORK sicslowpan_driver
#else /* !WITH_UIP6 */
#define RIMEADDR_CONF_SIZE    2
#define NETSTACK_CONF_NETWORK rime_driver
#endif /* WITH_UIP6 */

/* 10 bytes per stateful address context - see sicslowpan.c */
/* Default is 1 context with prefix aaaa::/64 */
/* These must agree with all the other nodes or there will be a failure to communicate! */
#define SICSLOWPAN_CONF_MAX_ADDR_CONTEXTS 1
#define SICSLOWPAN_CONF_ADDR_CONTEXT_0 {addr_contexts[0].prefix[0]=0xaa;addr_contexts[0].prefix[1]=0xaa;}
#define SICSLOWPAN_CONF_ADDR_CONTEXT_1 {addr_contexts[1].prefix[0]=0xbb;addr_contexts[1].prefix[1]=0xbb;}
#define SICSLOWPAN_CONF_ADDR_CONTEXT_2 {addr_contexts[2].prefix[0]=0x20;addr_contexts[2].prefix[1]=0x01;addr_contexts[2].prefix[2]=0x49;addr_contexts[2].prefix[3]=0x78,addr_contexts[2].prefix[4]=0x1d;addr_contexts[2].prefix[5]=0xb1;}

/* 211 bytes per queue buffer */
#define QUEUEBUF_CONF_NUM         8

/* 54 bytes per queue ref buffer */
#define QUEUEBUF_CONF_REF_NUM     2

/* Take the default TCP maximum segment size for efficiency and simpler wireshark captures */
/* Use this to prevent 6LowPAN fragmentation (whether or not fragmentation is enabled) */
//#define UIP_CONF_TCP_MSS      48

/* 25 bytes per UDP connection */
#define UIP_CONF_UDP_CONNS      10

#define UIP_CONF_UDP_CHECKSUMS   1
#define UIP_CONF_TCP_SPLIT       1
#define UIP_CONF_DHCP_LIGHT      1

#if 1 /* No radio cycling */

#define NETSTACK_CONF_MAC         nullmac_driver
#define NETSTACK_CONF_RDC         sicslowmac_driver
#define NETSTACK_CONF_FRAMER      framer_802154
#define NETSTACK_CONF_RADIO       rf2xx_driver
#define CHANNEL_802_15_4          RF2xxBB_CHANNEL_802_15_4
#define RADIO_CONF_CALIBRATE_INTERVAL 256
#define SICSLOWPAN_CONF_ACK_ALL   0
/* Allow 6lowpan fragments (needed for large TCP maximum segment size) */
#define SICSLOWPAN_CONF_FRAG      1
/* Most browsers reissue GETs after 3 seconds which stops fragment reassembly so a longer MAXAGE does no good */
#define SICSLOWPAN_CONF_MAXAGE    3
/* How long to wait before terminating an idle TCP connection. Smaller to allow faster sleep. Default is 120 seconds */
#define UIP_CONF_WAIT_TIMEOUT     5
/* 211 bytes per queue buffer */
#define QUEUEBUF_CONF_NUM         8
/* 54 bytes per queue ref buffer */
#define QUEUEBUF_CONF_REF_NUM     2
/* Allocate remaining RAM as desired */
/* 30 bytes per TCP connection */
/* 6LoWPAN does not do well with concurrent TCP streams, as new browser GETs collide with packets coming */
/* from previous GETs, causing decreased throughput, retransmissions, and timeouts. Increase to study this. */
/* ACKs to other ports become interleaved with computation-intensive GETs, so ACKs are particularly missed. */
/* Increasing the number of packet receive buffers in RAM helps to keep ACKs from being lost */
#define UIP_CONF_MAX_CONNECTIONS  4
/* 2 bytes per TCP listening port */
#define UIP_CONF_MAX_LISTENPORTS  4
/* 25 bytes per UDP connection */
#define UIP_CONF_UDP_CONNS       10
/* See uip-ds6.h */
#define UIP_CONF_DS6_NBR_NBU      20
#define UIP_CONF_DS6_DEFRT_NBU    2
#define UIP_CONF_DS6_PREFIX_NBU   3
#define UIP_CONF_DS6_ROUTE_NBU    20
#define UIP_CONF_DS6_ADDR_NBU     3
#define UIP_CONF_DS6_MADDR_NBU    0
#define UIP_CONF_DS6_AADDR_NBU    0

#elif 1  /* Contiki-mac radio cycling */

#define NETSTACK_CONF_MAC         csma_driver
#define NETSTACK_CONF_RDC         contikimac_driver
/* Default is two CCA separated by 500 usec */
#define NETSTACK_CONF_RDC_CHANNEL_CHECK_RATE   8
/* Wireshark won't decode with the header, but padded packets will fail ipv6 checksum */
#define CONTIKIMAC_CONF_WITH_CONTIKIMAC_HEADER 0
/* So without the header this needed for RPL mesh to form */
#define CONTIKIMAC_CONF_SHORTEST_PACKET_SIZE   43-18  //multicast RPL DIS length
/* Not tested much yet */
#define WITH_PHASE_OPTIMIZATION                0
#define CONTIKIMAC_CONF_COMPOWER               1
#define RIMESTATS_CONF_ON                      1
#define NETSTACK_CONF_FRAMER      framer_802154
#define NETSTACK_CONF_RADIO       rf2xx_driver
#define CHANNEL_802_15_4          RF2xxBB_CHANNEL_802_15_4
/* The radio needs to interrupt during an rtimer interrupt */
#define RTIMER_CONF_NESTED_INTERRUPTS 1
#define SICSLOWPAN_CONF_FRAG      1
#define SICSLOWPAN_CONF_MAXAGE    3
/* 211 bytes per queue buffer. Contikimac burst mode needs 15 for a 1280 byte MTU */
#define QUEUEBUF_CONF_NUM         15
/* 54 bytes per queue ref buffer */
#define QUEUEBUF_CONF_REF_NUM     2
/* Allocate remaining RAM. Not much left due to queuebuf increase  */
#define UIP_CONF_MAX_CONNECTIONS  2
#define UIP_CONF_MAX_LISTENPORTS  2
#define UIP_CONF_UDP_CONNS        4
#define UIP_CONF_DS6_NBR_NBU     10
#define UIP_CONF_DS6_DEFRT_NBU    2
#define UIP_CONF_DS6_PREFIX_NBU   2
#define UIP_CONF_DS6_ROUTE_NBU    4
#define UIP_CONF_DS6_ADDR_NBU     3
#define UIP_CONF_DS6_MADDR_NBU    0
#define UIP_CONF_DS6_AADDR_NBU    0

#elif 1  /* cx-mac radio cycling */
/* RF230 does clear-channel assessment in extended mode (autoretries>0) */
#if RF2XX_CONF_AUTORETRIES
#define NETSTACK_CONF_MAC         nullmac_driver
#else
#define NETSTACK_CONF_MAC         csma_driver
#endif
#define NETSTACK_CONF_RDC         cxmac_driver
#define NETSTACK_CONF_FRAMER      framer_802154
#define NETSTACK_CONF_RADIO       rf2xx_driver
#define CHANNEL_802_15_4          RF2xxBB_CHANNEL_802_15_4
#define SICSLOWPAN_CONF_FRAG      1
#define SICSLOWPAN_CONF_MAXAGE    3
#define CXMAC_CONF_ANNOUNCEMENTS  0
#define NETSTACK_CONF_RDC_CHANNEL_CHECK_RATE 8
/* 211 bytes per queue buffer. Burst mode will need 15 for a 1280 byte MTU */
#define QUEUEBUF_CONF_NUM         15
/* 54 bytes per queue ref buffer */
#define QUEUEBUF_CONF_REF_NUM     2
/* Allocate remaining RAM. Not much left due to queuebuf increase  */
#define UIP_CONF_MAX_CONNECTIONS  2
#define UIP_CONF_MAX_LISTENPORTS  4
#define UIP_CONF_UDP_CONNS        5
#define UIP_CONF_DS6_NBR_NBU      4
#define UIP_CONF_DS6_DEFRT_NBU    2
#define UIP_CONF_DS6_PREFIX_NBU   3
#define UIP_CONF_DS6_ROUTE_NBU    4
#define UIP_CONF_DS6_ADDR_NBU     3
#define UIP_CONF_DS6_MADDR_NBU    0
#define UIP_CONF_DS6_AADDR_NBU    0
//Below gives 10% duty cycle, undef for default 5%
//#define CXMAC_CONF_ON_TIME (RTIMER_ARCH_SECOND / 80)
//Below gives 50% duty cycle
//#define CXMAC_CONF_ON_TIME (RTIMER_ARCH_SECOND / 16)

#else
#error Network configuration not specified!
#endif

#ifndef RF_CHANNEL
#define RF_CHANNEL              RF2XX_CHANNEL
#endif /* RF_CHANNEL */

#define CONTIKIMAC_CONF_BROADCAST_RATE_LIMIT 0

#ifndef IEEE802154_CONF_PANID
#define IEEE802154_CONF_PANID       0xABCD
#endif

#define AODV_COMPLIANCE
#define AODV_NUM_RT_ENTRIES 32

#define WITH_ASCII 1

#define PROCESS_CONF_NUMEVENTS 8
#define PROCESS_CONF_STATS 1

#if WITH_UIP6

#define RIMEADDR_CONF_SIZE              8

#define UIP_CONF_LL_802154              1
#define UIP_CONF_LLH_LEN                0

#ifndef UIP_CONF_IPV6_RPL
#warning "UIP_CONF_IPV6_RPL is undefined, enabled by default"
#define UIP_CONF_IPV6_RPL               1
#endif /*UIP_CONF_IPV6_RPL */

/* See uip-ds6.h */
#define UIP_CONF_DS6_NBR_NBU            20
#define UIP_CONF_DS6_DEFRT_NBU          2
#define UIP_CONF_DS6_PREFIX_NBU         3
#define UIP_CONF_DS6_ROUTE_NBU          20
#define UIP_CONF_DS6_ADDR_NBU           3
#define UIP_CONF_DS6_MADDR_NBU          0
#define UIP_CONF_DS6_AADDR_NBU          0

#define RPL_CONF_MAX_PARENTS            4
#define NEIGHBOR_CONF_MAX_NEIGHBORS     8

#define UIP_CONF_IPV6_QUEUE_PKT         1
#define UIP_CONF_IPV6_CHECKS            1
#define UIP_CONF_IPV6_REASSEMBLY        0
#define UIP_CONF_NETIF_MAX_ADDRESSES    3
#define UIP_CONF_IP_FORWARD             0
#define UIP_CONF_BUFFER_SIZE            240
#define UIP_CONF_FWCACHE_SIZE           0

#define UIP_CONF_ICMP6                  1
#define UIP_CONF_UDP                    1

#ifndef UIP_CONF_TCP
#define UIP_CONF_TCP                    1
#endif /*UIP_CONF_TCP */

#define SICSLOWPAN_CONF_COMPRESSION_IPV6        0
#define SICSLOWPAN_CONF_COMPRESSION_HC1         1
#define SICSLOWPAN_CONF_COMPRESSION_HC01        2
#define SICSLOWPAN_CONF_COMPRESSION             SICSLOWPAN_COMPRESSION_HC06
#ifndef SICSLOWPAN_CONF_FRAG
#define SICSLOWPAN_CONF_FRAG                    1
#define SICSLOWPAN_CONF_MAXAGE                  8
#endif /* SICSLOWPAN_CONF_FRAG */
#define SICSLOWPAN_CONF_CONVENTIONAL_MAC        1
#else   /* !WITH_UIP6 */
#define UIP_CONF_IP_FORWARD      1
#define UIP_CONF_BUFFER_SIZE     128
#endif /* WITH_UIP6 */

/* Logging adds 200 bytes to program size */
#define LOG_CONF_ENABLED         1

#define CCIF
#define CLIF

/* ************************************************************************** */
//#pragma mark RPL Settings
/* ************************************************************************** */
#if UIP_CONF_IPV6_RPL

#define UIP_CONF_ROUTER                 1
#define UIP_CONF_ND6_SEND_RA            0
#define UIP_CONF_ND6_REACHABLE_TIME     600000
#define UIP_CONF_ND6_RETRANS_TIMER      10000
#define UIP_CONF_ND6_MAX_PREFIXES       3
#define UIP_CONF_ND6_MAX_NEIGHBORS      4
#define UIP_CONF_ND6_MAX_DEFROUTERS     2

#define UIP_CONF_ICMP_DEST_UNREACH 1
/* For slow slip connections, to prevent buffer overruns */
//#define UIP_CONF_RECEIVE_WINDOW 300
#undef UIP_CONF_FWCACHE_SIZE
#define UIP_CONF_FWCACHE_SIZE    30
#define UIP_CONF_BROADCAST       1
//#define UIP_ARCH_IPCHKSUM        1
#define UIP_CONF_UDP             1
#define UIP_CONF_UDP_CHECKSUMS   1
#define UIP_CONF_PINGADDRCONF    0
#define UIP_CONF_LOGGING         0

#undef UIP_CONF_TCP_SPLIT
#define UIP_CONF_TCP_SPLIT       0

#endif /* RPL */

typedef unsigned short uip_stats_t;
typedef unsigned long off_t;

#ifdef PROJECT_CONF_H
#include PROJECT_CONF_H
#endif /* PROJECT_CONF_H */

#endif /* __CONTIKI_CONF_H__ */
