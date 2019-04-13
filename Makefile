#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

HOMEKIT_PATH ?= $(abspath $(shell pwd)/../..)
IDF_PATH ?= $(HOMEKIT_PATH)/esp-idf


PROJECT_NAME := bridge
EXTRA_COMPONENT_DIRS += $(HOMEKIT_PATH)/components/
EXTRA_COMPONENT_DIRS += $(HOMEKIT_PATH)/components/homekit
EXTRA_COMPONENT_DIRS += /home/tinhebd19/esp/Project/esp-homekit-sdk/inlcude/light
EXTRA_COMPONENT_DIRS += /home/tinhebd19/esp/Project/esp-homekit-sdk/inlcude/fan
EXTRA_COMPONENT_DIRS += /home/tinhebd19/esp/Project/esp-homekit-sdk/inlcude
EXTRA_COMPONENT_DIRS += /home/tinhebd19/esp/Project/esp-homekit-sdk/inlcude/lightbulb
EXTRA_COMPONENT_DIRS += /home/tinhebd19/esp/Project/esp-homekit-sdk/inlcude/ethernet
EXTRA_COMPONENT_DIRS += /home/tinhebd19/esp/Project/esp-homekit-sdk/inlcude/mac_address
EXTRA_COMPONENT_DIRS += /home/tinhebd19/esp/Project/esp-homekit-sdk/inlcude/temperature
EXTRA_COMPONENT_DIRS += /home/tinhebd19/esp/Project/esp-homekit-sdk/inlcude/tcp_socket_server
EXTRA_COMPONENT_DIRS += /home/tinhebd19/esp/Project/esp-homekit-sdk/inlcude/tcp_socket_client
EXTRA_COMPONENT_DIRS += /home/tinhebd19/esp/Project/esp-homekit-sdk/inlcude/add_task
EXTRA_COMPONENT_DIRS += /home/tinhebd19/esp/Project/esp-homekit-sdk/inlcude/clist
EXTRA_COMPONENT_DIRS += /home/tinhebd19/esp/Project/esp-homekit-sdk/inlcude/API_ZWAVE
EXTRA_COMPONENT_DIRS += /home/tinhebd19/esp/Project/esp-homekit-sdk/inlcude/api_service_homekit
EXTRA_COMPONENT_DIRS += /home/tinhebd19/esp/Project/esp-homekit-sdk/inlcude/api_chars_homekit
EXTRA_COMPONENT_DIRS += /home/tinhebd19/esp/Project/esp-homekit-sdk/inlcude/datn_tinhdv

include $(IDF_PATH)/make/project.mk

