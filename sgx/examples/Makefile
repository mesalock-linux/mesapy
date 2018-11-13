DIRS := $(wildcard */.)
BUILDDIRS = $(DIRS:%=build-%)
RUNDIRS = $(DIRS:%=run-%)
CLEANDIRS = $(DIRS:%=clean-%)

all: build

build: $(BUILDDIRS)
$(DIRS): $(BUILDDIRS)
$(BUILDDIRS):
	$(MAKE) -C $(@:build-%=%)

run: build $(RUNDIRS)
$(RUNDIRS):
	$(MAKE) -C $(@:run-%=%) run

clean: $(CLEANDIRS)
$(CLEANDIRS):
	$(MAKE) -C $(@:clean-%=%) clean

.PHONY: subdirs $(DIRS)
.PHONY: subdirs $(CLEANDIRS)
.PHONY: all clean
