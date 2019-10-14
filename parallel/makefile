CC = gcc
CFLAGS =  
LDFLAGS = -lpthread
OBJFILES = timing.o stack.o GetNumbers.o  part_1_parallel.o
TARGET = part_1_parallel.out
all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
