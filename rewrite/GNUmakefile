THIS_DIR = $(shell pwd)

all: mel_daemon.c client.c
	g++ -O3 -Wall -o mel_daemon mel_daemon.c comm_functions.c -lnfnetlink -lnetfilter_queue
	g++ -O3 -Wall -o client -lpthread client.c comm_functions.c
	g++ -Wall -o test test.c -lnfnetlink -lnetfilter_queue
clean:
	@echo cleaning: $(THIS_DIR)
	@rm -f mel_daemon
	@rm -f client
	@rm -f test
