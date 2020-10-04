/*
 * Copyright (C) 2020
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     drivers_as1115
 * @{
 * @file
 * @brief       Implementation of the driver for the AS1115 I2C 
 *              LED/7-segment driver
 * 
 * @author      Florian Winkler <fw@docwinkler.at>
 * }
 */

#include "as1115.h"
#include "as1115_regs.h"

#include <string.h>

#define ENABLE_DEBUG        (1)
#include "debug.h"

/**
 * @brief Write data to register.
 * 
 * @param[in] dev      Device descriptor of AS1115
 * @param[in] reg      Register address
 * @param[in] data     Data to write
 * 
 * @return  0 on success
 * @return  -AS1115_I2C_ERROR if I2C bus acquiring failed
 */
static int _write_reg(as1115_t *dev, uint8_t reg, uint8_t data);

/**
 * @brief Read data from register.
 * 
 * @param[in] dev      Device descriptor of AS1115
 * @param[in] reg      Register address
 * @param[out] data    Data read from register address
 * 
 * @return  0 on success
 * @return  -AS1115_I2C_ERROR if I2C bus acquiring failed
 */
static int _read_reg(as1115_t *dev, uint8_t reg, uint8_t* data);

int as1115_init(as1115_t *dev, const as1115_params_t *params)
{
    assert(dev);
    assert(params);

    dev->params = *params;
    
    for (size_t i = 0; i < 4; i++)
    {
        dev->digit_intensity[i] = 0;
    }

    i2c_init(dev->params.i2c_dev);

    int rc = _write_reg(dev, AS1115_REG_SHUTDOWN, AS1115_SHUTDOWN_FEATURE_REG_DEFAULT);

    if (rc != AS1115_OK) {
        DEBUG("[as1115] rc1 = %i, %s\n", rc, strerror(rc));
        perror(NULL);
        return rc;
    }

    rc = _write_reg(dev, AS1115_REG_SCANLIMIT, dev->params.scanlimit);
    if (rc != AS1115_OK) {
        DEBUG("[as1115] rc2 = %i, %s\n", rc, strerror(rc));
        return rc;
    }

    // uint8_t data;
    // rc = _read_reg(dev, AS1115_REG_SHUTDOWN, &data);
    // if (rc != AS1115_OK) {
    //     DEBUG("[as1115] rc2 = %i, %s\n", rc, strerror(rc));
    //     perror(NULL);
    //     return rc;
    // }

    DEBUG("[as1115] init success\n");
    return AS1115_OK;
}

int as1115_on(as1115_t *dev)
{
    int rc = _write_reg(dev, AS1115_REG_SHUTDOWN, AS1115_NORMAL_FEATURE_REG_UNCHANGED);
    if (rc != AS1115_OK) {
        return rc;
    }

    return AS1115_OK;
}

int as1115_off(as1115_t *dev)
{
    int rc = _write_reg(dev, AS1115_REG_SHUTDOWN, AS1115_SHUTDOWN_FEATURE_REG_UNCHANGED);
    if (rc != AS1115_OK) {
        return rc;
    }

    return AS1115_OK;
}

int as1115_run_test(as1115_t *dev, uint8_t on)
{
    int rc;
    uint8_t reg;

    rc = _read_reg(dev, AS1115_REG_TESTMODE, &reg);
    if (rc != AS1115_OK) {
        return rc;
    }

    if (on == 0) {
        reg &= ~(1 << AS1115_BIT_DISPTEST);
    } else {
        reg |= (1 << AS1115_BIT_DISPTEST);
    }
    

    rc = _write_reg(dev, AS1115_REG_TESTMODE, reg);
    if (rc != AS1115_OK) {
        return rc;
    }

    return AS1115_OK;
}

int as1115_set_digit(as1115_t *dev, uint8_t digit, uint8_t value)
{
    assert(dev);

    if (digit > AS1115_MAXNUM_DIGIT) {
        return -AS1115_DIGIT_OUT_OF_RANGE_ERROR;
    }

    int rc = _write_reg(dev, AS1115_REG_DIG0 + digit, value);
    if (rc != 0) {
        return rc;
    }

    return AS1115_OK;
}

int as1115_set_decode_mode(as1115_t *dev, uint8_t digit, uint8_t enable)
{
    assert(dev);
    int rc;
    uint8_t data;

    if (digit > AS1115_MAXNUM_DIGIT) {
        return -AS1115_DIGIT_OUT_OF_RANGE_ERROR;
    }

    rc = _read_reg(dev, AS1115_REG_DECODEMODE, &data);
    if (rc != 0) {
        return rc;
    }
    DEBUG("[as1115] decode reg = %ui\n", data);

    if (enable) {
        data |= (1 << digit);
    } else {
        data &= ~(1 << digit);
    }

    DEBUG("[as1115] decode reg = %ui\n", data);
    rc = _write_reg(dev, AS1115_REG_DECODEMODE, data);
    if (rc != 0) {
        return rc;
    }

    return AS1115_OK;
}

int as1115_global_intensity(as1115_t *dev, uint8_t intensity)
{
    assert(dev);
    int rc;

    if (intensity > AS1115_MAXIMUM_INTENSITY) {
        return -AS1115_PARAMETER_OUT_OF_RANGE_ERROR;
    }

    rc = _write_reg(dev, AS1115_REG_GLOBALINTENSITY, intensity);
    if (rc != 0) {
        return rc;
    }

    return AS1115_OK;
}

int as1115_digit_intensity(as1115_t *dev, uint8_t digit, uint8_t intensity)
{
    assert(dev);
    int rc;
    uint8_t data;
    uint8_t reg;

    if (digit > AS1115_MAXNUM_DIGIT) {
        return -AS1115_DIGIT_OUT_OF_RANGE_ERROR;
    }

    if (intensity > AS1115_MAXIMUM_INTENSITY) {
        return -AS1115_PARAMETER_OUT_OF_RANGE_ERROR;
    }

    reg = AS1115_REG_INTENSITY_DIG01 + (digit / 2);

    data = dev->digit_intensity[digit/2];
    // rc = _read_reg(dev, reg, &data);
    // if (rc != 0) {
    //     return rc;
    // }

    if (digit % 2 == 0) {
        data = data & 0xF0;
    } else {
        intensity = (intensity << 4);
        data = data & 0xF;
    }
    DEBUG("[as1115] change digit %i intensity to %i. reg=%#x, data=%#x\n", digit, intensity, reg, data);
    data = data | intensity;

    dev->digit_intensity[digit/2] = data;

    rc = _write_reg(dev, reg, data);
    if (rc != 0) {
        return rc;
    }

    return AS1115_OK;
}

int as1115_select_decoder(as1115_t *dev, uint8_t decoder)
{
    assert(dev);
    int rc;
    uint8_t data;

    if (decoder > 1) {
        return -AS1115_DIGIT_OUT_OF_RANGE_ERROR;
    }

    rc = _read_reg(dev, AS1115_REG_FEATURE, &data);
    if (rc != 0) {
        return rc;
    }

    if (decoder == 0) {
        data &= ~(1 << AS1115_BIT_DECODE_SEL);
    } else {
        data |= (1 << AS1115_BIT_DECODE_SEL);
    }

    rc = _write_reg(dev, AS1115_REG_FEATURE, data);
    if (rc != 0) {
        return rc;
    }

    return AS1115_OK;
}

int as1115_read_keyscanA(as1115_t *dev, uint8_t *data)
{
    int rc = _read_reg(dev, AS1115_REG_KEYA, data);
    if (rc != 0) {
        return rc;
    }

    return AS1115_OK;
}

int _write_reg(as1115_t *dev, uint8_t reg, uint8_t data)
{
    i2c_t i2c_dev = dev->params.i2c_dev;

    if (i2c_acquire(i2c_dev) != 0) {
        return -AS1115_I2C_ERROR;
    }
    int rc = i2c_write_reg(i2c_dev, dev->params.i2c_addr, reg, data, 0);
    i2c_release(i2c_dev);

    return rc;
}

int _read_reg(as1115_t *dev, uint8_t reg, uint8_t *data)
{
    i2c_t i2c_dev = dev->params.i2c_dev;

    if (i2c_acquire(i2c_dev) != 0) {
        return -AS1115_I2C_ERROR;
    }
    int rc = i2c_read_reg(i2c_dev, dev->params.i2c_addr, reg, data, 0);
    i2c_release(i2c_dev);

    return rc;
}
