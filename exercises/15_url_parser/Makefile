CC = gcc
CPPFLAGS ?=
CPPFLAGS += -MMD -MP
CFLAGS = -Wall -Wextra -O2 -std=c11
LDFLAGS =
LDLIBS =

TARGET = 15_url_parser
SRC = 15_url_parser.c
OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)

.PHONY: all clean run rebuild debug

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

run: all
	@./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ) $(DEP)

rebuild: clean all

debug: CFLAGS += -g -O0
debug: clean all

-include $(DEP)