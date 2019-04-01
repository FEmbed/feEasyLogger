#
# Component Makefile
#
# port include has high priority than default ones.
ifdef CONFIG_EASYLOGGER
COMPONENT_ADD_INCLUDEDIRS += port
COMPONENT_ADD_INCLUDEDIRS += EasyLogger/easylogger/inc
COMPONENT_SRCDIRS += port
COMPONENT_SRCDIRS += EasyLogger/easylogger/src

ifdef CONFIG_EASYLOGGER_JLINK_LOG
COMPONENT_ADD_INCLUDEDIRS += Segger
COMPONENT_SRCDIRS += Segger
endif

endif
