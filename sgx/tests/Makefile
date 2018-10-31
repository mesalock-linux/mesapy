DIRS := $(wildcard */.)
BUILDDIRS = $(DIRS:%=build-%)
TESTDIRS = $(DIRS:%=test-%)
CLEANDIRS = $(DIRS:%=clean-%)

all: $(BUILDDIRS)
$(DIRS): $(BUILDDIRS)
$(BUILDDIRS):
	$(MAKE) -C $(@:build-%=%)

test: $(TESTDIRS)
$(TESTDIRS):
	@cd $(@:test-%=%) && ./app

clean: $(CLEANDIRS)
$(CLEANDIRS):
	$(MAKE) -C $(@:clean-%=%) clean

.PHONY: subdirs $(DIRS)
.PHONY: subdirs $(TESTDIRS)
.PHONY: subdirs $(CLEANDIRS)
.PHONY: all clean test
