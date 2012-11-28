DIRS	= command_server demonstration node rewrite
MAIN_DIR = $(shell pwd)
MAKEFLAGS= --no-print-directory

all: 
	@for dir in $(DIRS); do (cd $$dir; $(MAKE); cd .. ); done


clean:
	@echo cleaning: $(MAIN_DIR)
	@rm -f *.pyc *.pyo
	@for dir in $(DIRS); do (cd $$dir; $(MAKE) clean; cd .. ); done
