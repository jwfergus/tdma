THIS_DIR = $(shell pwd)

all: packet_queuing_submodule
	@echo making: $(THIS_DIR)
packet_queuing_submodule: packet_queuing_submodule.cc
	g++ -o packet_queuing_submodule packet_queuing_submodule.cc -lnetfilter_queue

clean:
	@echo cleaning: $(THIS_DIR)
	@rm -f *.pyc *.pyo packet_queuing_submodule
