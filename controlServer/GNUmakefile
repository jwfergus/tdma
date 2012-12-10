THIS_DIR = $(shell pwd)

all: controlServerMain.c
	@echo making: $(THIS_DIR)
	g++ -O3 -Wall -o controlServerMain -lpthread controlServerMain.c ../lib/comm_functions.c 
clean:
	@echo cleaning: $(THIS_DIR)
	@rm -f controlServerMain
