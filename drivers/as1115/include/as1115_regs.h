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
 * @brief       Register definitions for the AS1115 I2C LED/7-segment driver IC

 * @author      Florian Winkler <fw@docwinkler.at>
 */

#ifndef AS1115_REGS_H
#define AS1115_REGS_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Register definitions */

/**
 * @brief Digit 0-7 registers
 */
#define AS1115_REG_DIG0                 (0x01)
#define AS1115_REG_DIG1                 (0x02)
#define AS1115_REG_DIG2                 (0x03)
#define AS1115_REG_DIG3                 (0x04)
#define AS1115_REG_DIG4                 (0x05)
#define AS1115_REG_DIG5                 (0x06)
#define AS1115_REG_DIG6                 (0x07)
#define AS1115_REG_DIG7                 (0x08)

/**
 * @brief Decode-mode register
 */
#define AS1115_REG_DECODEMODE           (0x09)

/**
 * @brief Global intensity register
 */
#define AS1115_REG_GLOBALINTENSITY      (0x0A)

/**
 * @brief Scan limit register
 */
#define AS1115_REG_SCANLIMIT            (0x0B)

/**
 * @brief AS1115 Shutdown register
 */
#define AS1115_REG_SHUTDOWN             (0x0C)

/**
 * @brief Feature register
 */
#define AS1115_REG_FEATURE              (0x0E)

/**
 * @brief AS1115 testmode register
 */
#define AS1115_REG_TESTMODE             (0x0F)

/**
 * @brief Digit intensity registers
 */
#define AS1115_REG_INTENSITY_DIG01      (0x10)
#define AS1115_REG_INTENSITY_DIG23      (0x11)
#define AS1115_REG_INTENSITY_DIG45      (0x12)
#define AS1115_REG_INTENSITY_DIG67      (0x13)

/**
 * @brief Diagnostic Digit 0-7 registers
 */
#define AS1115_REG_DIAGNOSTIC_DIG0      (0x14)
#define AS1115_REG_DIAGNOSTIC_DIG1      (0x15)
#define AS1115_REG_DIAGNOSTIC_DIG2      (0x16)
#define AS1115_REG_DIAGNOSTIC_DIG3      (0x17)
#define AS1115_REG_DIAGNOSTIC_DIG4      (0x18)
#define AS1115_REG_DIAGNOSTIC_DIG5      (0x19)
#define AS1115_REG_DIAGNOSTIC_DIG6      (0x1A)
#define AS1115_REG_DIAGNOSTIC_DIG7      (0x1B)

/**
 * @brief AS1115 keyscan register A
 */
#define AS1115_REG_KEYA                 (0x1C)

/**
 * @brief AS1115 keyscan register B
 */
#define AS1115_REG_KEYB                 (0x1D)

/**
 * @brief I2C Self-Adressing register
 */
#define AS1115_REG_SELFADRESSING        (0x2D)


/* Bits in the feature register */

/**
 * @brief   External clock active.
 *          0 = internal clock
 *          1 = CLK pin as system clock input
 */
#define AS1115_BIT_CLK_EN               (0)

/**
 * @brief   Resets all control registers except feature register.
 *          Digit registers keep their data.
 *          0 = normal operation
 *          1 = reset registers
 */
#define AS1115_BIT_REG_RESET            (1)

/**
 * @brief   Select the digit decoder type
 *          0 = BCD decoder
 *          1 = HEX decoder
 */
#define AS1115_BIT_DECODE_SEL           (2)

/**
 * @brief   Enable blinking.
 *          0 = enable blinking
 *          1 = disable blinking
 */
#define AS1115_BIT_BLINK_EN             (4)

/**
 * @brief   Set blinking frequency.
 *          0 = blink period is 1 second
 *          1 = blink period is 2 seconds
 */
#define AS1115_BIT_BLINK_FREQ_SEL       (5)

/**
 * @brief   Sychronize blinking to rising edge of LD/CS pin
 */
#define AS1115_BIT_SYNC                 (6)

/**
 * @brief   Blinking start phase
 *          0 = blinking starts with display off
 *          1 = blinking starts with display on
 */
#define AS1115_BIT_BLINK_START          (7)

/* Bits in testmode register */

/**
 * @brief   Optical display test.
 *          0 = normal operation
 *          1 = run display test
 */
#define AS1115_BIT_DISPTEST             (0)

/* Bits in the decode mode register */

/**
 * @brief   Bits in the decode mode register
 *          0 = no decode
 *          1 = decode BCD/HEX (according to feature register)
 */
#define AS1115_BIT_DECODEMODE_DIG0      (0)
#define AS1115_BIT_DECODEMODE_DIG1      (1)
#define AS1115_BIT_DECODEMODE_DIG2      (2)
#define AS1115_BIT_DECODEMODE_DIG3      (3)
#define AS1115_BIT_DECODEMODE_DIG4      (4)
#define AS1115_BIT_DECODEMODE_DIG5      (5)
#define AS1115_BIT_DECODEMODE_DIG6      (6)
#define AS1115_BIT_DECODEMODE_DIG7      (7)

#ifdef __cplusplus
}
#endif

#endif /* AS1115_REGS_H */
/** @} */