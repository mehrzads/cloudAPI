###############################################################################
#
# Cloud API Makefile
#
###############################################################################

PROJECTS := $(shell find examples -name Makefile)
%.ph_build : 
	+@$(MAKE) -C $(dir $*) $(MAKECMDGOALS)

%.ph_clean : 
	+@$(MAKE) -C $(dir $*) clean 

all:  $(addsuffix .ph_build,$(PROJECTS))
	@echo "Finished building all"

tidy:
	@find * | egrep "#" | xargs rm -f
	@find * | egrep "\~" | xargs rm -f

clean:  tidy $(addsuffix .ph_clean,$(PROJECTS)) 
	@echo "Finished cleaning"

