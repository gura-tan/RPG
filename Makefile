TARGET = rpg
CC = gcc

CFLAGS = -I../inc -O0 -g -Wall -fmessage-length=0
CPPFLAGS = -c
LDFLAGS =
LDLIBS =

OBJECTS = \
          rpg.o

$(TARGET): $(OBJECTS)
		$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
		$(RM) $(OBJECTS)
		$(RM) $(TARGET)

.c.o:
		$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $@
