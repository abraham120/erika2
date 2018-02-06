# Destination directory
export OUTPUT_DIR = ../Application/$(APP_DEVICE)output

# Configuration OIL file
CONF_OIL = ../Application/$(APP_DEVICE)conf.oil

# Check the environment and use reasonable defaults
ifndef RTDRUID_ECLIPSE_HOME
RTDRUID_ECLIPSE_HOME = C:/Evidence/eclipse
endif
ifneq (ok,$(shell test -d "$(RTDRUID_ECLIPSE_HOME)" && echo ok ))
$(error The variable RTDRUID_ECLIPSE_HOME must point to a valid Eclipse RT-Druid installation)
endif

RTDRUID_OUTPUT = $(addprefix $(OUTPUT_DIR)/, \
 makefile eecfg.h eecfg.c)

.PHONY: all clean cleanall

all: $(RTDRUID_OUTPUT)
	@echo
	@echo Building...
	@echo
	$(MAKE) -C $(OUTPUT_DIR) -w all

clean:
	@echo
	@echo Cleaning...
	@echo
	rm -f -r $(OUTPUT_DIR)

cleanall:
	@echo
	@echo Cleaning completely...
	@echo
	rm -f -r ../Application/*output

# If any target different from `all' or `clean' si given, try to invoke the
# generated makefile. `force' is used to force the invocation of the child
# makefile
%: $(RTDRUID_OUTPUT) force
	$(MAKE) -w -C $(OUTPUT_DIR) $@
# Avoid triggering the catch-all rule
.PHONY: force
force: ;
$(CONF_OIL): ;
$(MAKEFILE_LIST): ;

# Run RT-Druid
$(RTDRUID_OUTPUT): $(CONF_OIL)
	@echo "Running RT-Druid..."
	@ECLIPSE_HOME="$(RTDRUID_ECLIPSE_HOME)" ;\
	export ECLIPSE_HOME ;\
#sh $(RTDRUID_SCRIPT_DIR)/start_ant.sh -buildfile $(RTDRUID_SCRIPT_DIR)/build.xml -Din_conf_file=$< -Dconf_output_dir=$(OUTPUT_DIR) compile
	@sh $(RTDRUID_ECLIPSE_HOME)/evidence/generate_code.sh $(RTDRUID_ECLIPSE_HOME) $< $(OUTPUT_DIR)
