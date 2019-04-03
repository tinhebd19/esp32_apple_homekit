/*
 * Bridge Project For Homekit
 * Author tinhdv19 ---- tinhdv@lumi.biz
 *
 */

#include "app_main.h"
#include "lightbulb.h"
#include "fan.h"
#include "light.h"
#include "home_ethernet.h"
#include "mac_address.h"
#include "temperature.h"
#include "source_acc.h"
#include "cjson_use.h"
#include "tcp_socket_server.h"
#include "tcp_socket_client.h"
#include "add_task.h"

/*
 * @brief The network reset button callback handler.
 * Useful for testing the Wi-Fi re-configuration feature of WAC2
 */
static const char *TAG = "ESP32";

static void reset_network_handler(void* arg)
{
    hap_reset_network();
}
/**
 * @brief The factory reset button callback handler.
 */
static void reset_to_factory_handler(void* arg)
{
    hap_reset_to_factory();
}
/**
 * The Reset button  GPIO initialisation function.
 * Same button will be used for resetting Wi-Fi network as well as for reset to factory based on
 * the time for which the button is pressed.
 */
static void reset_key_init(uint32_t key_gpio_pin)
{
    button_handle_t handle = iot_button_create(key_gpio_pin, BUTTON_ACTIVE_LOW);
    iot_button_add_on_release_cb(handle, RESET_NETWORK_BUTTON_TIMEOUT, reset_network_handler, NULL);
    iot_button_add_on_press_cb(handle, RESET_TO_FACTORY_BUTTON_TIMEOUT, reset_to_factory_handler, NULL);
}

/* Setup Information for the Setup Code: 111-22-333 */
static const hap_setup_info_t setup_info = {
    .salt = {
        0x93, 0x15, 0x1A, 0x47, 0x57, 0x55, 0x3C, 0x21, 0x0B, 0x55, 0x89, 0xB8, 0xC3, 0x99, 0xA0, 0xF3
    },
    .verifier = {
        0x9E, 0x9C, 0xC3, 0x73, 0x9B, 0x04, 0x83, 0xC8, 0x13, 0x7C, 0x5B, 0x5F, 0xAC, 0xC5, 0x63, 0xDF,
        0xF4, 0xF1, 0x0F, 0x39, 0x06, 0x4A, 0x20, 0x2D, 0x53, 0x2A, 0x09, 0x20, 0x3A, 0xA6, 0xBA, 0xE3,
        0x1E, 0x42, 0x4E, 0x58, 0x4E, 0xBB, 0x44, 0x5F, 0x7F, 0xDF, 0xCC, 0x11, 0xD0, 0xF7, 0x8B, 0x35,
        0xE1, 0x16, 0xA9, 0x79, 0x30, 0xBC, 0x37, 0x19, 0x77, 0x36, 0xB1, 0xEC, 0xD4, 0x12, 0x4C, 0xE4,
        0x5D, 0xE3, 0x7E, 0x46, 0xA0, 0x2D, 0x10, 0x07, 0xAB, 0x48, 0x40, 0x36, 0xD5, 0x3F, 0x7F, 0xBE,
        0xA5, 0xAE, 0xD0, 0x25, 0x6B, 0xC4, 0x9E, 0xC8, 0x5F, 0xC9, 0x4E, 0x47, 0x0D, 0xBA, 0xD3, 0x63,
        0x44, 0x20, 0x01, 0x69, 0x97, 0xDD, 0x20, 0x54, 0x7C, 0x59, 0x78, 0x3D, 0x5C, 0x6D, 0xC7, 0x1F,
        0xE6, 0xFD, 0xA0, 0x8E, 0x9B, 0x36, 0x45, 0x1F, 0xC1, 0x4B, 0xB5, 0x26, 0xE1, 0x8E, 0xEB, 0x4C,
        0x05, 0x58, 0xD7, 0xC8, 0x80, 0xA1, 0x43, 0x7F, 0x5F, 0xDB, 0x75, 0x1B, 0x19, 0x57, 0x25, 0xAC,
        0x5D, 0xF5, 0x8D, 0xF6, 0x7B, 0xAA, 0xB7, 0x7D, 0xE0, 0x36, 0xEF, 0xEA, 0xF3, 0x57, 0xAC, 0xFE,
        0x12, 0x87, 0xF9, 0x31, 0x4C, 0xF7, 0x44, 0xBD, 0xB6, 0x26, 0x6C, 0xB4, 0x0D, 0x7C, 0x52, 0x4F,
        0x85, 0x56, 0x91, 0x5D, 0x13, 0xD8, 0xDA, 0x8C, 0x45, 0x3E, 0x73, 0xF2, 0xF9, 0x20, 0x39, 0x24,
        0x8B, 0xFB, 0xEE, 0xFD, 0x77, 0x54, 0x8D, 0x37, 0x22, 0xE8, 0x55, 0xC3, 0xD2, 0xF8, 0xB8, 0x23,
        0xB0, 0xE2, 0x9E, 0x43, 0xAE, 0xB4, 0x37, 0xFA, 0xA7, 0x03, 0xF1, 0x82, 0x68, 0x4C, 0xD4, 0x86,
        0xC6, 0x3E, 0xDE, 0x70, 0x11, 0x03, 0x77, 0x46, 0x59, 0x14, 0x97, 0xC6, 0xAE, 0x52, 0x6F, 0x03,
        0x77, 0x36, 0x40, 0xBC, 0xDE, 0xCD, 0x3D, 0xE0, 0x4F, 0x69, 0x18, 0x0D, 0xCA, 0x85, 0x7E, 0x07,
        0x30, 0xF4, 0xA1, 0xCE, 0x05, 0xB5, 0x4B, 0xE1, 0x1D, 0x43, 0xDF, 0xDB, 0x11, 0x43, 0xDE, 0x21,
        0xAC, 0x8F, 0x03, 0x9E, 0x6E, 0x9F, 0xA8, 0xE5, 0x02, 0x06, 0x1C, 0x63, 0x34, 0x22, 0x1D, 0x39,
        0xE3, 0x3D, 0x12, 0x2E, 0xA2, 0xF3, 0xFC, 0xB5, 0xB4, 0x16, 0x9E, 0x0E, 0x7C, 0x52, 0xC8, 0x7D,
        0x50, 0x3D, 0xDB, 0xF5, 0x83, 0x46, 0x18, 0x92, 0x7F, 0x4D, 0x38, 0xAD, 0x0A, 0x2A, 0xBC, 0x2A,
        0x50, 0x4B, 0xDF, 0x5D, 0xFA, 0x93, 0x41, 0x78, 0xD6, 0x45, 0x54, 0xDB, 0x44, 0x81, 0xF7, 0x5A,
        0x0A, 0xDD, 0x18, 0x4F, 0x27, 0xD7, 0xDD, 0x5E, 0xB7, 0x3E, 0x99, 0xE6, 0xE1, 0x69, 0x35, 0x74,
        0xD6, 0x98, 0x58, 0xB2, 0x13, 0x6F, 0xB7, 0x82, 0x72, 0xBC, 0xA6, 0x8B, 0xA3, 0x36, 0x2A, 0xCE,
        0x65, 0x65, 0x51, 0x08, 0x8A, 0x3D, 0x04, 0x93, 0x8F, 0x01, 0x8A, 0xAB, 0x4B, 0xFC, 0x06, 0xF9
    }
};

/* Mandatory identify routine for the accessory (bridge)
 * In a real accessory, something like LED blink should be implemented
 * got visual identification
 */
static int bridge_identify(hap_acc_t *ha)
{
    ESP_LOGI(TAG, "Bridge identified");
    return HAP_SUCCESS;
}

/*
 * static int accessory_identify(hap_acc_t *ha)
{
    hap_serv_t *hs = hap_acc_get_serv_by_uuid(ha, HAP_SERV_UUID_ACCESSORY_INFORMATION);
    hap_char_t *hc = hap_serv_get_char_by_uuid(hs, HAP_CHAR_UUID_NAME);
    const hap_val_t *val = hap_char_get_val(hc);
    char *name = val->s;

    ESP_LOGI(TAG, "Bridged Accessory %s identified", name);
    return HAP_SUCCESS;
}
 */

/*The main thread for handling the Bridge Accessory */
static void bridge_thread_entry(void *p)
{
    hap_acc_t *accessory;
    //hap_serv_t *service;
    /* Check connect with MFi */
    if(hap_check_mfi_chip() == HAP_SUCCESS){
    	ESP_LOGI(TAG, "MFi authentication co-processor is connected");
    }
    /* Initialize the HAP core */
    hap_init(HAP_TRANSPORT_ETHERNET);

    /* Initialise the mandatory parameters for Accessory which will be added as
     * the mandatory services internally
     */
    char str[20] = {0};
    getNameDevice(str);

    hap_acc_cfg_t cfg = {
        .name = str,
        .manufacturer = "Lumi VietNam",
        .model = "Lumi-Bridge",
        .serial_num = "001122334455",
        .fw_rev = "0.9.0",
        .hw_rev = NULL,
        .pv = "1.1.0",
        .identify_routine = bridge_identify,
        .cid = HAP_CID_BRIDGE,
    };
    /* Create accessory object */
    accessory = hap_acc_create(&cfg);

    /* Add the Accessory to the HomeKit Database */
    hap_add_accessory(accessory);

    /* Set the Setup ID required for QR code based Accessory Setup.
     * Ideally, this should be available in factory_nvs partition. This is
     * just for demonstration purpose
     */
    hap_set_setup_id("ES32");

    /* Provide the Setup Information for HomeKit Pairing.
     * Ideally, this should be available in factory_nvs partition. This is
     * just for demonstration purpose
     */
    /* Use the setup_payload_gen tool to get the QR code for Accessory Setup.
     * The payload below is for a Bridge with setup code 111-22-333 and setup id ES32
     */
    hap_set_setup_info(&setup_info);

   /* Register a common button for reset Wi-Fi network and reset to factory */
	reset_key_init(RESET_GPIO);
	/* Enable WAC2 as per HAP Spec R12 */
	hap_enable_wac2();

/*    while(true)
    {
    	behavior = get_state_behavior(&oldsum_accesory , &sum_accesory);
    	switch(behavior){
    		case(DO_NOTTHING):
    			ESP_LOGI(TAG, "Don't have any behavior accessory ");
    			break;
    		case(ADD_ACC):{
				ESP_LOGI(TAG, "Have some behavior accessory ");
				for (int i = 0; i < sum_accesory; i++) {

					if(i < 5 ){
						add_fan_to_bridge(fan_nomral_full,i);
						ESP_LOGI(TAG, "Add Accessory Fan Succeed");
					}
					else if ((i>=5) && i < 6){

						add_lightbulb_to_bridge(i);
						ESP_LOGI(TAG, "Add Lightbulb Success");
					}
					else{
						add_temperature_to_bridge(i);
						ESP_LOGI(TAG, "Add Temperature Sensor Success");
					}
					ESP_LOGI(TAG, "Use setup payload: \"X-HM://002LETYN1ES32\" for Accessory Setup");
				}
				hap_start();
    			break;
    		}
    		case(REMOVE_ACC):
				ESP_LOGI(TAG, "Remove some behavior accessory ");
    			hap_start();
    			break;
    		case (ERROR_ACC):
    			ESP_LOGI(TAG, "Error add accessory");
    			break;
    		default:
    			ESP_LOGI(TAG, "Error behavior accessory ");
    			break;
    	}


    	vTaskDelay(2000 / portTICK_PERIOD_MS);

    }
*/
	hap_start();
    /* The task ends here. The read/write callbacks will be invoked by the HAP Framework */
    vTaskDelete(NULL);
}

void vApplicationIdleHook( void )
{
/* This hook function does nothing but increment a counter. */
/*
 * When have freetime, do something
 */

}

EventGroupHandle_t xEventGroup_Add_Remove;

void app_main()
{
// Init Accessories Service
#ifdef USE_KIT_ETH
	home_ethernet_init();
#endif

	xEventGroup_Add_Remove = xEventGroupCreate();
	test_cjson();
	lightbulb_init();

/*  Create Tasks  */
//    xTaskCreate(bridge_thread_entry, BRIDGE_TASK_NAME, BRIDGE_TASK_STACKSIZE, NULL, BRIDGE_TASK_PRIORITY, NULL);
//    xTaskCreate(add_remove_accessory , ADD_REMOVE_TASK_NAME, ADD_REMOVE_TASK_STACKSIZE, main_SOURCE_ACC_TASK_BIT, ADD_REMOVE_TASK_PRIORITY, NULL );
//    xTaskCreate(source_acc_task , SOURCE_ACC_TASK_NAME, SOURCE_ACC_TASK_STACKSIZE, main_SOURCE_ACC_TASK_BIT, SOURCE_ACC_TASK_PRIORITY, NULL );

	xTaskCreatePinnedToCore(bridge_thread_entry, BRIDGE_TASK_NAME, BRIDGE_TASK_STACKSIZE, NULL, BRIDGE_TASK_PRIORITY, NULL, 0 );
	xTaskCreatePinnedToCore(add_remove_accessory , ADD_REMOVE_TASK_NAME, ADD_REMOVE_TASK_STACKSIZE, main_SOURCE_ACC_TASK_BIT, ADD_REMOVE_TASK_PRIORITY, NULL , 1 );
	xTaskCreatePinnedToCore(source_acc_task , SOURCE_ACC_TASK_NAME, SOURCE_ACC_TASK_STACKSIZE, main_SOURCE_ACC_TASK_BIT, SOURCE_ACC_TASK_PRIORITY, NULL , 1 );

}

