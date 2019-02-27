CFLAGS = -I ../include -I ../private
CFLAGS += -std=c99 -pedantic -Wall -W -Werror

.PHONY: all
all: test
.DEFAULT_GOAL: all

include ../common.mk

test: merge-sort

merge-sort: merge-sort.c
	$(VECHO) "  CC\$@.c\n"
	$(Q)$(CC) -o $@ $(CFLAGS) $@.c
