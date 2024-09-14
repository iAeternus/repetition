CC=gcc
CFLAGS=

TARGET=main
SRCS=main.c convert.c test_functions.c utils.c operations.c test_utils.c

all: $(TARGET)
$(TARGET): $(SRCS:.c=.o)
	$(CC) $(CFLAGS) -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	del $(TARGET).exe $(SRCS:.c=.o)
.PHONY: all clean
