# Makefile

# Get a list of all subdirectories
SUBDIRS := $(wildcard */.)

SUBDIRS := $(filter-out output/., $(SUBDIRS))

all: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@


# Clean all subdirectories
clean:
	$(foreach dir,$(SUBDIRS),$(MAKE) -C $(dir) clean;)

.PHONY: all $(SUBDIRS)
