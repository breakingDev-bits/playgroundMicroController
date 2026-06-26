#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "soc/gpio_struct.h"

#define BLINK_GPIO3 14 
#define BLINK_GPIO2 13 
#define BLINK_GPIO 12 

#define GPIO_MASK ((1ULL << BLINK_GPIO3) | (1ULL << BLINK_GPIO2) | (1ULL << BLINK_GPIO))

void app_main(void)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = GPIO_MASK,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
    
    printf("Стартуем разгон пина на максимум...\n");
    portDISABLE_INTERRUPTS();

    uint32_t set_mask = ((1ULL << BLINK_GPIO3) | (1ULL << BLINK_GPIO2));
    uint32_t clear_mask = (1ULL << BLINK_GPIO); 

    label:
        GPIO.out_w1ts = set_mask;   GPIO.out_w1tc = clear_mask;
        GPIO.out_w1tc = set_mask;   GPIO.out_w1ts = clear_mask;

        goto label;

    
}