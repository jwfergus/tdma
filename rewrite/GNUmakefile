THIS_DIR = $(shell pwd)

all: server.c
	gcc -o server server.c
	gcc -o client client.c

clean:
	@echo cleaning: $(THIS_DIR)
	@rm -f server
	@rm -f client
