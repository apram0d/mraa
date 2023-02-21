/*
 * Author: Ambica Pramod <ambica.pramod@intel.com>
 * Copyright (c) 2023 Intel Corporation.
 *
 * SPDX-License-Identifier: MIT
 */

#include <dirent.h>
#include <mraa/common.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <fcntl.h>

#include "common.h"
#include "x86/intel_nuc_ilk.h"

#define PLATFORM_NAME "Intel NUC Learning Kit"

mraa_board_t*
mraa_intel_nuc_ilk()
{
    int pin_num = 0;

    mraa_board_t* b = (mraa_board_t*) calloc(1, sizeof(mraa_board_t));
    if (b == NULL) {
        return NULL;
    }

    b->platform_name = PLATFORM_NAME;
    b->phy_pin_count = MRAA_INTEL_NUC_ILK_PINCOUNT;
    b->aio_count = 0;
    b->adc_raw = 0;
    b->adc_supported = 0;

    b->pins = (mraa_pininfo_t*) malloc(sizeof(mraa_pininfo_t) * MRAA_INTEL_NUC_ILK_PINCOUNT);
    if (b->pins == NULL) {
        goto error;
    }

    b->adv_func = (mraa_adv_func_t*) calloc(1, sizeof(mraa_adv_func_t));
    if (b->adv_func == NULL) {
        free(b->pins);
        goto error;
    }

    b->chardev_capable = 1;

    // UART-1
    b->uart_dev_count = 1;
    b->def_uart_dev = 0;
    b->uart_dev[0].rx = 10;
    b->uart_dev[0].tx = 8;
    b->uart_dev[0].device_path = "/dev/ttyS4";

    // UART-2
    b->uart_dev_count = 2;
    b->def_uart_dev = 1;
    b->uart_dev[1].rx = 13;
    b->uart_dev[1].tx = 15;
    b->uart_dev[1].device_path = "/dev/ttyS5";

    // BUS DEFINITIONS
    b->i2c_bus_count = 1;
    b->def_i2c_bus = 0;
    b->i2c_bus[b->i2c_bus_count].bus_id = 1;
    b->i2c_bus[b->i2c_bus_count].sda = 3;
    b->i2c_bus[b->i2c_bus_count].scl = 5;

    // BUS DEFINITIONS
    b->i2c_bus_count = 2;
    b->def_i2c_bus = 0;
    b->i2c_bus[b->i2c_bus_count].bus_id = 2;
    b->i2c_bus[b->i2c_bus_count].sda = 18;
    b->i2c_bus[b->i2c_bus_count].scl = 16;

    // BUS DEFINITIONS
    b->i2c_bus_count = 3;
    b->def_i2c_bus = 0;
    b->i2c_bus[b->i2c_bus_count].bus_id = 3;
    b->i2c_bus[b->i2c_bus_count].sda = 22;
    b->i2c_bus[b->i2c_bus_count].scl = 11;

    // BUS DEFINITIONS
    b->i2c_bus_count = 4;
    b->def_i2c_bus = 0;
    b->i2c_bus[b->i2c_bus_count].bus_id = 4;
    b->i2c_bus[b->i2c_bus_count].sda = 27;
    b->i2c_bus[b->i2c_bus_count].scl = 28;

    b->i2c_bus_count = 5;

    // Pin number 0
    strncpy(b->pins[pin_num].name, "INVALID", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 0, 0, 0, 0, 0, 0, 0, 0 };

    // Pin number 1
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "3V3", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 0, 0 };

    // Pin number 2
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "5V", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 0, 0 };

    // Pin number 3
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "I2C1_SDA", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 1, 0, 0 };
    b->pins[pin_num].gpio.pinmap =  864 + 38;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].i2c.pinmap = 0;
    b->pins[pin_num].i2c.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 1;
    b->pins[pin_num].gpio.gpio_line = 38;

    // Pin number 4
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "5V", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 0, 0 };

    // Pin number 5
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "I2C1_SCL", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 1, 0, 0 };
    b->pins[pin_num].gpio.pinmap =  864 + 39;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].i2c.pinmap = 0;
    b->pins[pin_num].i2c.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 1;
    b->pins[pin_num].gpio.gpio_line = 39;

    // Pin number 6
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "GND", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 0, 0 };

    // Pin number 7
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "PMU_BATLOW_N", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 0 };
    b->pins[pin_num].gpio.pinmap = 864 + 30;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 1;
    b->pins[pin_num].gpio.gpio_line = 30;

    // Pin number 8
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "UART1_TX", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 1 };
    b->pins[pin_num].gpio.pinmap = 864 + 63;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].uart.parent_id = 0;
    b->pins[pin_num].uart.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 1;
    b->pins[pin_num].gpio.gpio_line = 63;

    // Pin number 9
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "GND", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 0, 0 };

    // Pin number 10
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "UART1_RX", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 1 };
    b->pins[pin_num].gpio.pinmap = 864 + 62;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].uart.parent_id = 0;
    b->pins[pin_num].uart.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 0;
    b->pins[pin_num].gpio.gpio_line = 62;

    // Pin number 11
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "GPIO17", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 0 };
    b->pins[pin_num].gpio.pinmap = 864 + 75;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 1;
    b->pins[pin_num].gpio.gpio_line = 75;

    // Pin number 12
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "GPIO18", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 0 };
    b->pins[pin_num].gpio.pinmap = 864 + 77;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 1;
    b->pins[pin_num].gpio.gpio_line = 77;

    // Pin number 13
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "UART2_RX", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].gpio.pinmap = 944 + 64;
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 1 };
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].uart.parent_id = 0;
    b->pins[pin_num].uart.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 0;
    b->pins[pin_num].gpio.gpio_line = 64;

    // Pin number 14
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "GND", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 0, 0 };

    // Pin number 15
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "UART2_TX", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 1 };
    b->pins[pin_num].gpio.pinmap =  944 + 65;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].uart.parent_id = 0;
    b->pins[pin_num].uart.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 0;
    b->pins[pin_num].gpio.gpio_line = 65;

    // Pin number 16
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "GPIO23", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 0 };
    b->pins[pin_num].gpio.pinmap = 864 + 78;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 1;
    b->pins[pin_num].gpio.gpio_line = 78;

    // Pin number 17
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "3V3", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 0, 0 };

    // Pin number 18
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "GPIO24", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 0 };
    b->pins[pin_num].gpio.pinmap = 864 + 79;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 1;
    b->pins[pin_num].gpio.gpio_line = 79;

    // Pin number 19
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "SPI_MOSI", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 1, 0, 0, 0 };
    b->pins[pin_num].gpio.pinmap = 864 + 70;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 1;
    b->pins[pin_num].gpio.gpio_line = 70;

    // Pin number 20
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "GND", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 0, 0 };

    // Pin number 21
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "SPI_MISO", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 1, 0, 0, 0 };
    b->pins[pin_num].gpio.pinmap =  864 + 69;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 1;
    b->pins[pin_num].gpio.gpio_line = 69;
    // Pin number 22
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "GPIO25", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 0 };
    b->pins[pin_num].gpio.pinmap = 864 + 71;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 1;
    b->pins[pin_num].gpio.gpio_line = 71;

    // Pin number 23
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "SPI_CLK", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 1, 0, 0, 0 };
    b->pins[pin_num].gpio.pinmap =  864 + 66;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 1;
    b->pins[pin_num].gpio.gpio_line = 66;

    // Pin number 24
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "SPI_CS0", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 1, 0, 0, 0 };
    b->pins[pin_num].gpio.pinmap =  864 + 67;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 1;
    b->pins[pin_num].gpio.gpio_line = 67;

    // Pin number 25
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "GND", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 0, 0 };

    // Pin number 26
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "SPI_CS1", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 1, 0, 0, 0 };
    b->pins[pin_num].gpio.pinmap =  864 + 68;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 1;
    b->pins[pin_num].gpio.gpio_line = 68;

    // Pin number 27
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "I2C2_SDA", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 1, 0, 0 };
    b->pins[pin_num].gpio.pinmap = 864 + 34;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 1;
    b->pins[pin_num].gpio.gpio_line = 34;

    // Pin number 28
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "I2C2_SCL", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 1, 0, 0 };
    b->pins[pin_num].gpio.pinmap =  864 + 34;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 1;
    b->pins[pin_num].gpio.gpio_line = 34;

    // Pin number 29
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "GPIO1", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 0 };
    b->pins[pin_num].gpio.pinmap =  809 + 9;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 3;
    b->pins[pin_num].gpio.gpio_line = 9;

    // Pin number 30
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "GND", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 0, 0 };

    // Pin number 31
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "GPIO6", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 0 };
    b->pins[pin_num].gpio.pinmap =  864 + 76;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 1;
    b->pins[pin_num].gpio.gpio_line = 76;

    // Pin number 32
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "GPIO_PWM0_LS", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 0 };
    b->pins[pin_num].gpio.pinmap =  944 + 43;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 0;
    b->pins[pin_num].gpio.gpio_line = 43;

    // Pin number 33
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "GPIO_PWM0_LS", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 0 };
    b->pins[pin_num].gpio.pinmap =  944 + 42;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 0;
    b->pins[pin_num].gpio.gpio_line = 42;

    // Pin number 34
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "GND", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 0, 0 };

    // Pin number 35
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "GPIO19", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 0 };
    b->pins[pin_num].gpio.pinmap =  809 + 4;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 3;
    b->pins[pin_num].gpio.gpio_line = 4;

    // Pin number 36
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "GPIO16", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 0 };
    b->pins[pin_num].gpio.pinmap =  809 + 7;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 3;
    b->pins[pin_num].gpio.gpio_line = 7;

    // Pin number 37
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "GPIO26", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 0 };
    b->pins[pin_num].gpio.pinmap =  809 + 8;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 3;
    b->pins[pin_num].gpio.gpio_line = 8;

    // Pin number 38
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "GPIO20", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 0 };
    b->pins[pin_num].gpio.pinmap =  864 + 72;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 1;
    b->pins[pin_num].gpio.gpio_line = 72;

    // Pin number 39
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "GND", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 0, 0, 0, 0, 0, 0, 0 };

    // Pin number 40
    pin_num += 1;
    strncpy(b->pins[pin_num].name, "GPIO21", MRAA_PIN_NAME_SIZE);
    b->pins[pin_num].capabilities = (mraa_pincapabilities_t){ 1, 1, 0, 0, 0, 0, 0, 0 };
    b->pins[pin_num].gpio.pinmap =  864 + 73;
    b->pins[pin_num].gpio.mux_total = 0;
    b->pins[pin_num].gpio.gpio_chip = 1;
    b->pins[pin_num].gpio.gpio_line = 73;

    b->gpio_count = 0;
    int i;
    for (i = 0; i < b->phy_pin_count; i++) {
        if (b->pins[i].capabilities.gpio) {
            b->gpio_count++;
        }
    }

    return b;

error:
    syslog(LOG_CRIT, "Intel NUC Learning Kit: Platform failed to initialise");
    free(b);
    return NULL;
}
