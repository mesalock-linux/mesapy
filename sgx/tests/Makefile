TESTDIRS := $(wildcard */.)
MAKE ?= make

all: test
test: $(TESTDIRS)

$(TESTDIRS):
	@$(MAKE) -C $@ > /dev/null 2>&1
	@cd $@ && ./test

.PHONY: all $(TESTDIRS)
