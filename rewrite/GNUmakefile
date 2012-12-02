THIS_DIR = $(shell pwd)

all: mel_daemon.c client.c
	g++ -o mel_daemon mel_daemon.c
	g++ -o client client.c
	g++ -o test test.c
clean:
	@echo cleaning: $(THIS_DIR)
	@rm -f mel_daemon
	@rm -f client
	@rm -f test
