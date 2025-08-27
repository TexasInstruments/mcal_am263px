################################################################################
# Eth Host Application Configurations (Edit Below)
################################################################################

# Enable/Disable Build of Host Application for Virtual Mac Test
export ETH_VIRTUAL_MAC_MODE ?= FALSE

# Enable/Disable Update Physical Address Filter API Test Cases
export ETH_UPDATE_PHYS_ADDR_FILTER ?= TRUE

# Enable/Disable Traffic Shaping Support Test Cases
export ETH_TRAFFIC_SHAPING_API ?= FALSE

# Enable/Disable Zero Copy Support Test Cases
export ETH_ZERO_COPY_SUPPORT ?= FALSE

# Enable/Disable Checksum Offload Test Cases
export ETH_CHECKSUM_OFFLOAD_SUPPORT ?= FALSE
################################################################################
# Eth Host Application Configurations Ends
################################################################################
UTILS_DIR := ../../utils

HOST_APP_TARGETS = EthHostTestApp

STD_CFLAGS = -DSTD_OFF=0x00 -DSTD_ON=0x01
ifeq ($(ETH_UPDATE_PHYS_ADDR_FILTER),TRUE)
    TST_CFLAGS = -DETH_UPDATE_PHYS_ADDR_FILTER_API=STD_ON
else
    TST_CFLAGS = -DETH_UPDATE_PHYS_ADDR_FILTER_API=STD_OFF
endif

ifeq ($(ETH_TRAFFIC_SHAPING_API),TRUE)
    TST_CFLAGS += -DETH_TRAFFIC_SHAPING_API=STD_ON
else
    TST_CFLAGS += -DETH_TRAFFIC_SHAPING_API=STD_OFF
endif

ifeq ($(ETH_CHECKSUM_OFFLOAD_SUPPORT),TRUE)
    TST_CFLAGS += -DETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_TCP=STD_ON
    TST_CFLAGS += -DETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_UDP=STD_ON
else
    TST_CFLAGS += -DETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_TCP=STD_OFF
    TST_CFLAGS += -DETH_CTRL_ENABLE_OFFLOAD_CHECKSUM_UDP=STD_OFF
endif

HOST_CFLAGS = $(STD_CFLAGS) $(TST_CFLAGS)
VIRT_CFLAGS = $(STD_CFLAGS) $(TST_CFLAGS)

all: $(HOST_APP_TARGETS)

EthHostTestApp: HostTestApp.c $(UTILS_DIR)/EthUtils.c  $(UTILS_DIR)/EthUtils_Host.c
	gcc $^ -I$(UTILS_DIR) $(HOST_CFLAGS) -o $@

.PHONY: clean
clean:
	rm -f *.o EthHostTestApp
