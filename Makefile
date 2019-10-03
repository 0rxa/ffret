CC="gcc"
DEST="/usr/bin/ffret"
BINARY="ffret"
NAME="main.c"

all:
	$(CC) -o $(BINARY) $(NAME) ffret.c config.c

binary: 
	$(CC) -o $(BINARY) $(NAME) ffret.o config.o

ffret:
	$(CC) -c -o ffret.o ffret.c

config:
	$(CC) -c -o config.o config.c

objs: ffret config

debug:
	$(CC) -g -o $(BINARY) $(NAME) ffret.c config.c

install:
	cp $(BINARY) $(DEST)
	chwon root.root $(DEST)
	chmod 755 $(DEST)

remove:
	rm $(DEST)

clean:
	rm $(BINARY) *o
