CONTIKI_PROJECT = camera-udp
all: $(CONTIKI_PROJECT)

# IPv6
UIP_CONF_IPV6 = 1
# RPL
UIP_CONF_RPL = 0
# Address type: set to 0 for using ds2401, 1 for EUI64_ADDRESS defined in params.c.
#UIP_CONF_EUI64 = 0

APPS += camera-interface

CONTIKI = ../../..
include $(CONTIKI)/Makefile.include
