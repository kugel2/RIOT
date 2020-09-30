/*
 * Copyright (C) 2020
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     drivers_as1115
 * 
 * @{
 * @file
 * @author      Florian Winkler <fw@docwinkler.at>
 * 
 * @brief       Default configuration for the AS1115 LED/7-segment driver IC
 */

#ifndef AS1115_PARAMS_H
#define AS1115_PARAMS_H

#include "periph/i2c.h"

#include "as1115_regs.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @name Default device configuration parameters
 * @{
 */
#ifndef AS1115_PARAM_I2C_DEV
/** I2C device is I2C_DEV(0) */
#define AS1115_PARAM_I2C_DEV               I2C_DEV(0)
#endif

#ifndef AS1115_PARAM_I2C_ADDR
/** I2C address of device is (0x0 >> 1) by default and on startup */
#define AS1115_PARAM_I2C_ADDR              (0x0 >> 1)
#endif

#ifndef AS1115_PARAM_SCANLIMIT
/** Controls which digits are displayed 0x0 for only the first digit, 
 *  up to 0x7 for all eight digits.
 */
#define AS1115_PARAM_SCANLIMIT              (0x0)
#endif

#ifndef AS1115_PARAMS
#define AS1115_PARAMS                                           \
    {                                                           \
        .i2c_dev = AS1115_PARAM_I2C_DEV,                        \
        .i2c_addr = AS1115_PARAM_I2C_ADDR,                      \
        .scanlimit = AS1115_PARAM_SCANLIMIT,                    \
    }
#endif /* AS1115_PARAMS */
/**@}*/

/**
 * @brief   Device configurations
 */
static const as1115_params_t as1115_params[] =
{
    AS1115_PARAMS
};

#ifdef __cplusplus
}
#endif

#endif /* AS1115_PARAMS_H */
/** @} */