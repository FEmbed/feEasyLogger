#
# Component Makefile
#
# port include has high priority than default ones.
COMPONENT_ADD_INCLUDEDIRS += port
COMPONENT_ADD_INCLUDEDIRS += Segger
COMPONENT_ADD_INCLUDEDIRS += EasyLogger/easylogger/inc

COMPONENT_SRCDIRS += port
COMPONENT_SRCDIRS += Segger
COMPONENT_SRCDIRS += EasyLogger/easylogger/src
