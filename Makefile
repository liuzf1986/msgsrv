CC=g++
LD=g++
CFLAGS=-c -O3 -std=c++11
LDFLAGS=-Wl,--no-as-needed -lpthread

OBJS=test.o TimeUtil.o
TARGET=test

$(TARGET):$(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) $<

%.o : %.cpp
	$(CC) $(CFLAGS) $<

.PHONY:clean
clean:
	rm -f $(TARGET) $(OBJS)
