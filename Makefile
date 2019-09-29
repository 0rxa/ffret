CC="gcc"
DEST="/usr/bin/ffret"
BINARY="ffret"
NAME="main.c"
FFRET_OBJ="ffret"

ffret:
	$(CC) -o $(BINARY) $(NAME) ffret.c

install:
	cp $(BINARY) $(DEST)
	chwon root.root $(DEST)
	chmod 755 $(DEST)

remove:
	rm $(DEST)

clean:
	rm $(BINARY)
