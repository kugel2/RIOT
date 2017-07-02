/*
 * Copyright (C) 2016 Nicholas Jackson <nicholas.jackson@griffithuni.edu.au>
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @defgroup    boards_cc2650launchpadxl CC2650LAUNCHPADXL
 * @ingroup     boards
 * @brief       Board specific files for the SimpleLink multi-standard CC2650 Launchpad board
 * @{
 *
 * @file
 * @brief       Board specific definitions for the SimpleLink multi-standard CC2650 Launchpad board
 *
 * @author      Nicholas Jackson <nicholas.jackson@griffithuni.edu.au>
 */

#ifndef BOARD_H
#define BOARD_H

#include "periph/gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Xtimer configuration
 * @{
 */
#define XTIMER_WIDTH                 (16)
/** @} */

/**
 * @brief   On-board button configuration
 * @{
 */
#define BUTTON1_DIO         GPIO_PIN(0, 13)
#define BUTTON2_DIO         GPIO_PIN(0, 14)
/** @} */

/**
 * @brief   Macros for controlling the on-board LEDs
 * @{
 */
#define LED0_PIN            GPIO_PIN(0, 10)
#define LED1_PIN            GPIO_PIN(0, 15)

#define LED0_ON             gpio_set(LED0_PIN)
#define LED0_OFF            gpio_clear(LED0_PIN)
#define LED0_TOGGLE         gpio_toggle(LED0_PIN)

#define LED1_ON             gpio_set(LED1_PIN)
#define LED1_OFF            gpio_clear(LED1_PIN)
#define LED1_TOGGLE         gpio_toggle(LED1_PIN)
/** @} */

/**
 * @brief   Initialize board specific hardware, including clock, LEDs, and std-IO
 */
void board_init(void);

#ifdef __cplusplus
}
#endif

#endif //BOARD_H
/** @} */
