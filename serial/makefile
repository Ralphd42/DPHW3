CC = gcc
CFLAGS =  
LDFLAGS =
OBJFILES = stack.o GetNumbers.o
TARGET = part_1_serial.out
all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
