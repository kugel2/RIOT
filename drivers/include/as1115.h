/*
 * Copyright (C) 2020
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    drivers_as1115 AS1115 I2C LED/7-segment driver
 * @ingroup     drivers_display
 * @brief       Device driver for the AS1115 I2C LED/7-segment driver IC
 * 
 * @{
 * @file
 * @brief       Interface definition for the AS1115 LED/7-segment driver IC
 * 
 * @author      Florian Winkler <fw@docwinkler.at>
 */

#ifndef AS1115_H
#define AS1115_H


#ifdef __cplusplus
extern "C"
{
#endif

#include "periph/i2c.h"

#include "as1115_regs.h"

/**
 * @brief    AS1115 device initialisation parameters
 */
typedef struct {
    i2c_t i2c_dev;           /**< I2C device */
    uint16_t i2c_addr;       /**< I2C device address */
    uint8_t scanlimit;       /**< Scanlimit */
} as1115_params_t;

/**
 * @brief    AS1115 device data structure type
 */
typedef struct {
    as1115_params_t params; /**< Device initialisation parameters */
} as1115_t;

/**
 * @brief    AS1115 driver error codes
 */
enum {
    AS1115_OK,
    AS1115_I2C_ERROR,
    AS1115_DIGIT_OUT_OF_RANGE_ERROR,
    AS1115_PARAMETER_OUT_OF_RANGE_ERROR,
};

/**
 * @brief   AS1115 I2C self-addressing settings
 */
enum {
    AS1115_FACTORY_SET_ADDRESS,
    AS1115_USER_SET_ADDRESS,
};

/**
 * @brief   AS1115 shutdown modes
 */
typedef enum {
    AS1115_SHUTDOWN_FEATURE_REG_DEFAULT        = 0x00,
    AS1115_SHUTDOWN_FEATURE_REG_UNCHANGED      = 0x80,
    AS1115_NORMAL_FEATURE_REG_DEFAULT          = 0x01,
    AS1115_NORMAL_FEATURE_REG_UNCHANGED        = 0x81,
} as1115_shutdownmode_t;

/**
 * @brief   Maximum digit number
 *          for the AS1115 0-7
 */
#define AS1115_MAXNUM_DIGIT                     (7)

/**
 * @brief   The maximum brightness of a digit
 */
#define AS1115_MAXIMUM_INTENSITY                (0xF)

/**
 * @brief Initialization.
 *
 * @param[in] dev       Device descriptor of the AS1115
 * @param[in] params    Parameters for device initialization
 *
 * @return  AS1115_OK on success
 * @return  -AS1115_I2C_ERROR if acquiring of I2C bus fails
 */
int as1115_init(as1115_t *dev, const as1115_params_t *params);

/**
 * @brief Turn device on.
 * 
 * @param[in] dev       Device descriptor of the AS1115
 * 
 * @return AS1115_OK on success
 * @return -AS1115_I2C_ERROR if acquiring of I2C bus fails
 */
int as1115_on(as1115_t *dev);

/**
 * @brief Turn device off.
 * 
 * @param[in] dev       Device descriptor of the AS1115
 * 
 * @return AS1115_OK on success
 * @return -AS1115_I2C_ERROR if acquiring of I2C bus fails
 */
int as1115_off(as1115_t *dev);

/**
 * @brief Set the digit data, either raw or direct digit (Hex, CodeB)
 * 
 * @param[in] dev       Device descriptor of the AS1115
 * @param[in] digit     Number of digit to set.
 * @param[in] value     The value to set the digit to. 
 *                      Interpreted as raw segment data or as hex or code B.
 * 
 * @return AS1115_OK on success
 * @return -AS1115_I2C_ERROR if acquiring of I2C bus fails
 * @return -AS1115_DIGIT_OUT_OF_RANGE_ERROR if the digit is out of range
 */
int as1115_set_digit(as1115_t *dev, uint8_t digit, uint8_t value);

/**
 * @brief Enable the decode mode of the digit
 * 
 * @param[in] dev       Device descriptor of the AS1115
 * @param[in] digit     Number of digit to set.
 * @param[in] enable    Enable the decoder for this digit
 *                      0 = enable decoder
 *                      1 = disable decoder
 * 
 * @return AS1115_OK on success
 * @return -AS1115_I2C_ERROR if acquiring of I2C bus fails
 * @return -AS1115_DIGIT_OUT_OF_RANGE_ERROR if the digit is out of range
 */
int as1115_set_decode_mode(as1115_t *dev, uint8_t digit, uint8_t enable);

/**
 * @brief Set the intensity of all digits.
 * 
 * @param[in] dev       Device descriptor of the AS1115
 * @param[in] intensity Brightness 
 *                      0xX0 = miniumum
 *                      0xXF = maximum
 * 
 * @return AS1115_OK on success
 * @return -AS1115_I2C_ERROR if acquiring of I2C bus fails
 * @return -AS1115_PARAMETER_OUT_OF_RANGE_ERROR if the intensity value > 0xF
 */
int as1115_global_intensity(as1115_t *dev, uint8_t intensity);

/**
 * @brief Set the intensity of a individual digit.
 * 
 * @param[in] dev       Device descriptor of the AS1115
 * @param[in] intensity Brightness 
 *                      0xX0 = miniumum
 *                      0xXF = maximum
 * 
 * @return AS1115_OK on success
 * @return -AS1115_I2C_ERROR if acquiring of I2C bus fails
 * @return -AS1115_DIGIT_OUT_OF_RANGE_ERROR if the digit is out of range
 * @return -AS1115_PARAMETER_OUT_OF_RANGE_ERROR if the intensity value > 0xF
 */
int as1115_digit_intensity(as1115_t *dev, uint8_t intensity);

/**
 * @brief Set the digit decoder.
 * 
 * @param[in] dev       Device descriptor of the AS1115
 * @param[in] decoder   Type of decoder:
 *                      0 = BCD decoder
 *                      1 = HEX decoder
 * 
 * @return AS1115_OK on success
 * @return -AS1115_I2C_ERROR if acquiring of I2C bus fails
 * @return -AS1115_UNKNOWN_DECODER if decoder is unknown
 */
int as1115_select_decoder(as1115_t *dev, uint8_t decoder);

/**
 * @brief Run test.
 * 
 * @param[in] dev       Device descriptor of the AS1115
 * @param[in] on        0 = normal operation
 *                      1 = run test
 * 
 * @return  AS1115_OK on success
 * @return  -AS1115_I2C_ERROR if acquiring of I2C bus fails
 */
int as1115_run_test(as1115_t *dev, uint8_t on);

/**
 * @brief Read the keyscan register.
 * 
 * @param[in] dev       Device descriptor of the AS1115
 * 
 * @return  AS1115_OK on success
 * @return  -AS1115_I2C_ERROR if acquiring of I2C bus fails
 */
int as1115_read_keyscanA(as1115_t *dev, uint8_t *data);


#ifdef __cplusplus
}
#endif

#endif /* AS1115_H */
/** @} */
