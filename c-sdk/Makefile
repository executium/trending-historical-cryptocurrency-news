CC=gcc
IDIR =./include
CFLAGS=-I$(IDIR)
ODIR=.
LDIR =../lib

LIBS=-lcurl -ljson-c -lcrypto


DEPS = class.h config.h script.h hmac.h base64.h


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

script: config.o class.o script.o base64.o hmac.o
	$(CC) -o script script.o config.o base64.o class.o  hmac.o $(LIBS)


clean:
		rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
