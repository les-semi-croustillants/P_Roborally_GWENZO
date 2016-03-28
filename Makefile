CC      = gcc -w

SOURCES = board.c
HEADERS = $(SOURCES:.c=.h)
OBJECTS = $(SOURCES:.c=.o)

GTK_SOURCES = board_display.c
GTK_HEADERS = $(GTK_SOURCES:.c=.h)
GTK_OBJECTS = $(GTK_SOURCES:.c=.o)

ALL_OBJECTS = $(OBJECTS) $(GTK_OBJECTS)
ALL_HEADERS = $(HEADERS) $(GTK_HEADERS)

CFLAGS  += -g -Wall -std=c99 -pedantic
LDFLAGS +=

GTK_CFLAGS  = $(CFLAGS) $(shell pkg-config --cflags gtk+-3.0 librsvg-2.0)
GTK_LDFLAGS = $(LDFLAGS) $(shell pkg-config --libs gtk+-3.0 librsvg-2.0)

all : example showboard editor

$(OBJECTS) : %.o : %.c
	$(CC) -c $(CFLAGS) $? -o $@

$(GTK_OBJECTS) : %.o : %.c
	$(CC) -c $(GTK_CFLAGS) $? -o $@

########## example ##########

EXAMPLE_SOURCES = example.c graph.c dijkstra.c heap.c array.c wobowall_e.c
EXAMPLE_OBJECTS = $(EXAMPLE_SOURCES:.c=.o)

example : $(EXAMPLE_OBJECTS) $(OBJECTS) $(HEADERS)
	$(CC) $^ -o $@ $(LDFLAGS)
	
$(EXAMPLE_OBJECTS): %.o : %.c
	$(CC) -c $(CFLAGS) $? -o $@

########## showboard ##########

SHOWBOARD_SOURCES = showboard.c
SHOWBOARD_OBJECTS = $(SHOWBOARD_SOURCES:.c=.o)

showboard : $(SHOWBOARD_OBJECTS) $(ALL_OBJECTS) $(ALL_HEADERS)
	$(CC) $^ -o $@ $(GTK_LDFLAGS)

$(SHOWBOARD_OBJECTS): %.o : %.c
	$(CC) -c $(GTK_CFLAGS) $? -o $@

########## editor ##########

EDITOR_SOURCES = editor.c
EDITOR_OBJECTS = $(EDITOR_SOURCES:.c=.o)

editor : $(EDITOR_OBJECTS) $(ALL_OBJECTS) $(ALL_HEADERS)
	$(CC) $^ -o $@ $(GTK_LDFLAGS)

$(EDITOR_OBJECTS): %.o : %.c
	$(CC) -c $(GTK_CFLAGS) $? -o $@

########## cleanup ##########

clean:
	@rm -f example showboard editor $(ALL_OBJECTS) $(EXAMPLE_OBJECTS) $(SHOWBOARD_OBJECTS) $(EDITOR_OBJECTS)
