CC=gcc
CFLAGS=

TARGET=main
SRCS=main.c convert.c unit_tests.c utils.c operations.c test_utils.c floating_number.c

all: $(TARGET)
$(TARGET): $(SRCS:.c=.o)
	$(CC) $(CFLAGS) -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
clean:
	del $(TARGET).exe $(SRCS:.c=.o)
.PHONY: all clean
