SRCDIR=src
INCDIR=include
RESCDIR=resource
DIRSDL=/usr
INCLUDE=-I$(INCDIR)
CFLAGS=-c -g -O2 -I$(DIRSDL)/include/SDL -I$(DIRSDL)/include -I$(DIRSDL)/local/include -I$(DIRSDL)/local/include/SDL -I$(DIRSDL)/local/lib $(INCLUDE)
LFLAGS=-L$(DIRSDL)/lib    -lSDL_phelma  -L$(DIRSDL)/local/lib  -lSDL_draw  -lSDL_sound -lm -lSDL_ttf

all:lecture

lecture:$(SRCDIR)/fonction.o $(SRCDIR)/visuel.o $(SRCDIR)/lecture.o $(SRCDIR)/liste.o $(SRCDIR)/dico.o $(SRCDIR)/file.o $(SRCDIR)/main.o
	gcc -o $@  $^  -lm -g  $(LFLAGS)
	rm -f *.o

fonction.o : fonction.c fonction.h
	gcc $(CFLAGS) fonction.c -lm
	

