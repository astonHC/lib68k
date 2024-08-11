## COPYRIGHT (C) HARRY CLARK 2024
## MOTOROLA 68000 STANDALONE EMULATION LIBRARY

CC 			=		$(PREFIX)gcc
AR			=		$(PREFIX)ar
WARNINGS	=		-std=c90 -Wall -Wextra -Wparentheses -Werror -pedantic
SRC			= 		src
INC			=		inc

68K_FILES	=		$(wildcard $(SRC)/*.c)
68K_OBJS	=		$(68K_FILES:$(SRC)/%.c=$(SRC)/%.o)

TARGET 		=		68k.a

all: $(TARGET)

$(TARGET): $(68K_OBJS)
	$(AR) rcs $@ $^

$(SRC)/%.o: $(SRC)/%.c
	$(CC) $(WARNINGS) -I$(INC) -c $< -o $@

clean:
	rm -f $(SRC)/*.o $(TARGET)

.PHONY: clean
