CONTIKI_PROJECT = mx-web
all: $(CONTIKI_PROJECT)

APPS = mx-webserver
WEBDIR = ipv6_smeshlink
#HTTPD-CFS = 1

# Use radio driver that communicates with the core MAC layer. Now the default.
#RF230BB=1
# Use static eeprom coffee file system
#COFFEE_FILES=1
# Use full eeprom coffee file system
#COFFEE_FILES=3
# Use static flash coffee file system
#COFFEE_FILES=3
# Use full flash coffee file system
#COFFEE_FILES=4
# Override default coffee file system starting address
#COFFEE_ADDRESS=0xnnnn

#CFLAGS += -DCOFFEE_FILES

UIP_CONF_IPV6 = 1

CONTIKI = ../..
include $(CONTIKI)/Makefile.include