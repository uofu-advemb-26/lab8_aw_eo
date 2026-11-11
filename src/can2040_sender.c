#include <can2040.h>
#include <hardware/regs/intctrl.h>
#include <stdio.h>
#include <pico/stdlib.h>

#include "FreeRTOS.h"
#include "task.h"

#include "pico/multicore.h"
#include "pico/cyw43_arch.h"


#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

#define DELAY_MS 1000

static struct can2040 cbus;

static void can2040_cb(struct can2040 *cd, uint32_t notify, struct can2040_msg *msg)
{
    // Put your code here....
}

static void PIOx_IRQHandler(void)
{
    can2040_pio_irq_handler(&cbus);
}

void canbus_setup(void)
{
    uint32_t pio_num = 1;
    uint32_t sys_clock = 125000000, bitrate = 500000;
    uint32_t gpio_rx = 4, gpio_tx = 5;

    // Setup canbus
    can2040_setup(&cbus, pio_num);
    can2040_callback_config(&cbus, can2040_cb);

    // Enable irqs
    irq_set_exclusive_handler(PIO1_IRQ_0, PIOx_IRQHandler);
    irq_set_priority(PIO1_IRQ_0, PICO_DEFAULT_IRQ_PRIORITY - 1);
    irq_set_enabled(PIO1_IRQ_0, 1);

    // Start canbus
    can2040_start(&cbus, sys_clock, bitrate, gpio_rx, gpio_tx);
}

static void sender_task(__unused void *p)
{
    bool on = false;
    uint8_t count = 0;

    for (;;) {
        struct can2040_msg msg = { .id = 0x123, .dlc = 1 };
        vTaskDelay(500);
        msg.data[0] = count++;
        int rc = can2040_transmit(&cbus, &msg);
        printf("tx %u rc=%d\n", msg.data[0], rc);
    }
}


int main(void)
{
    stdio_init_all();
    canbus_setup();
    repeating_timer_t timer;
    const char *rtos_name;
    rtos_name = "FreeRTOS";    

    xTaskCreate(sender_task, "sender", 1024, NULL, tskIDLE_PRIORITY + 1UL, NULL);
    vTaskStartScheduler();
    return 0;
}