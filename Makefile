CC = gcc
CFLAGS = -Wall -O2
BUILD_DIR = build
SRC_DIR = src
COMMON_DIR = $(SRC_DIR)/common

INCLUDES = -I$(COMMON_DIR)
COMMON_SRCS = $(COMMON_DIR)/utils.c

all: setup dragon-fetch sys-fetch

setup:
	mkdir -p $(BUILD_DIR)

dragon-fetch: $(SRC_DIR)/dragon_fetch.c $(COMMON_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $(BUILD_DIR)/$@

sys-fetch: $(SRC_DIR)/sys_fetch.c $(COMMON_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $(BUILD_DIR)/$@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all setup clean
