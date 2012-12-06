THIS_DIR = $(shell pwd)

all: mel_daemon.c client.c
	g++ -Wall -o mel_daemon mel_daemon.c comm_functions.c
	g++ -Wall -o client -lpthread client.c comm_functions.c
clean:
	@echo cleaning: $(THIS_DIR)
	@rm -f mel_daemon
	@rm -f client
