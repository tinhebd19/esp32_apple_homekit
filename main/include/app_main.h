/*
 * app_main.h
 *
 *  Created on: Mar 21, 2019
 *      Author: tinhebd19 --- tinhdv@lumi.biz
 */

#ifndef _APP_MAIN_H_
#define _APP_MAIN_H_

#include <stdbool.h>
#include <stdio.h>
#include <string.h>


#include "hap.h"
#include "hap_fw_upgrade.h"
//#include "hap_cloud_servs.h"
#include <hap_apple_servs.h>
#include <hap_apple_chars.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/timers.h>
#include <freertos/event_groups.h>

#include <esp_log.h>
#include "esp_system.h"
#include "driver/gpio.h"
#include <iot_button.h>
#include <esp_system.h>

#include "cJSON.h"

#include "esp_err.h"
#include "esp_event_loop.h"
#include "esp_event.h"
#include "esp_attr.h"
#include "esp_log.h"
#include "esp_eth.h"

#include "rom/ets_sys.h"
#include "rom/gpio.h"

#include "soc/dport_reg.h"
#include "soc/io_mux_reg.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/gpio_reg.h"
#include "soc/gpio_sig_map.h"

#include "tcpip_adapter.h"
#include "nvs_flash.h"

#include "soc/emac_ex_reg.h"
#include "driver/periph_ctrl.h"


#define USE_DEVKIT      1
//#define USE_KIT_ETH     1

//#define CONFIG_PHY_ADDRESS 1
//#define CONFIG_PHY_CLOCK_MODE 0

#define BRIDGE_TASK_PRIORITY  6
#define BRIDGE_TASK_STACKSIZE 4 * 1024
#define BRIDGE_TASK_NAME      "hap_bridge"

#define NUM_BRIDGED_ACCESSORIES 11

#define main_BRIDGE_TASK_BIT (1 << 0UL)            // Event bit 0, Set by Bridge Task
#define main_ADD_REMOVE_TASK_BIT (1 << 1UL)			// Event bit 1, Set by Add Remove Task
#define main_SOURCE_ACC_TASK_BIT  (1 << 3UL)

/* Reset network credentials if button is pressed for more than 3 seconds and then released */
#define RESET_NETWORK_BUTTON_TIMEOUT        3

/* Reset to factory if button is pressed and held for more than 10 seconds */
#define RESET_TO_FACTORY_BUTTON_TIMEOUT     10

#ifdef USE_DEVKIT
/* The button "Boot" will be used as the Reeset button for the example */
#define RESET_GPIO  GPIO_NUM_0
#endif

#ifdef USE_KIT_ETH
/* The button "Boot" will be used as the Reset button for the example */
#define RESET_GPIO  GPIO_NUM_5
#endif

extern uint8_t sum_accesory;
extern  uint8_t oldsum_accesory;
extern EventGroupHandle_t xEventGroup_Add_Remove;

typedef enum{
	DO_NOTTHING = 1,
	ADD_ACC,
	REMOVE_ACC,
	ERROR_ACC
} state_behavior_t;


#endif /* _APP_MAIN_H_ */
