INCLUDES += -I$(APPDIR)

APPLICATION = nrfdongle_ep_test

BOARD ?= nrf52840dongle

RIOTBASE ?= $(CURDIR)/../..

EXTERNAL_MODULE_DIRS += $(CURDIR)/..

USEMODULE += doriot_dca
USEMODULE += posix_inet
USEMODULE += core_idle_thread
USEMODULE += xtimer
USEMODULE += gnrc_udp
USEMODULE += gnrc_netdev_default
USEMODULE += auto_init_gnrc_netif
USEMODULE += cord_ep

USEMODULE += gnrc_ipv6_router_default
USEMODULE += gnrc_rpl
USEMODULE += auto_init_gnrc_rpl

CFLAGS += -DVFS_DIR_BUFFER_SIZE=16 -DVFS_FILE_BUFFER_SIZE=16
CFLAGS += -DVFS_NAME_MAX=31
CFLAGS += -DDEBUG_ASSERT_VERBOSE

DEVELHELP ?= 1

QUIET ?= 1

include $(RIOTBASE)/Makefile.include
