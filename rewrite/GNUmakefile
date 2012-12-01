THIS_DIR = $(shell pwd)

all: server.c
	g++ -o server server.c
	g++ -o client client.c
	g++ -o test test.c
clean:
	@echo cleaning: $(THIS_DIR)
	@rm -f server
	@rm -f client
	@rm -f test
