THIS_DIR = $(shell pwd)

all: mel_daemon.c
	@echo making: $(THIS_DIR)
	g++ -O3 -Wall -o mel_daemon mel_daemon.c ../lib/comm_functions.c -lnfnetlink -lnetfilter_queue
clean:
	@echo cleaning: $(THIS_DIR)
	@rm -f mel_daemon
