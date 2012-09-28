CONTIKI_PROJECT = hello-world
all: $(CONTIKI_PROJECT)

# Consider to move the above line to the platform's Makefile.
UIP_CONF_IPV6 = 1
WITH_UIP6 = 1



# RPL
CFLAGS+= -DUIP_CONF_IPV6_RPL
CONTIKI = ../..
include $(CONTIKI)/Makefile.include