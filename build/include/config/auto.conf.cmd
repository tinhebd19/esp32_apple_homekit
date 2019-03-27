deps_config := \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/app_trace/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/aws_iot/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/bt/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/components/button/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/driver/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/esp32/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/esp_adc_cal/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/components/homekit/esp_hap_core/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/esp_http_client/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/ethernet/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/components/homekit/extras/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/fatfs/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/freertos/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/heap/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/components/led/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/libsodium/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/log/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/lwip/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/mbedtls/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/nvs_flash/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/openssl/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/pthread/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/spi_flash/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/spiffs/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/tcpip_adapter/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/vfs/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/wear_levelling/Kconfig \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/accessories/bridge/main/Kconfig.projbuild \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/components/homekit/platform/Kconfig.projbuild \
	/home/tinhebd19/esp/Project/esp-homekit-sdk/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)

ifneq "$(IDF_CMAKE)" "n"
include/config/auto.conf: FORCE
endif

$(deps_config): ;
