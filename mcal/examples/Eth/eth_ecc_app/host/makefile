UTILS_DIR := ../../utils

all: EthHostEccApp

EthHostEccApp: HostEccApp.c $(UTILS_DIR)/EthUtils.c $(UTILS_DIR)/EthUtils_Host.c
	gcc $^ -I$(UTILS_DIR) -o $@

.PHONY: clean
clean:
	rm -f *.o EthHostEccApp
