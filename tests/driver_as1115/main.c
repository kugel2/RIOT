/*
 * Copyright (C) 2020
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     tests
 * 
 * @{
 * @file
 * @brief       Test application for the AS1115 I2C LED/7-segment driver
 * 
 * @author      Florian Winkler <fw@docwinkler.at>
 * @}
 */

#include <stdio.h>
#include <stdlib.h>

#include "xtimer.h"
#include "shell.h"

#define AS1115_PARAM_SCANLIMIT (0x06)

#include "as1115.h"
#include "as1115_params.h"

as1115_t as1115_dev;

int test_disp(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    if (argc != 2) {
        puts("usage: test_disp <state (0-1)>");

        puts("  state 0: normal operation");
        puts("  state 1: run display test");
    }
    else {
        uint8_t value = atoi(argv[1]);
        printf("%ui", value);
        as1115_run_test(&as1115_dev, value);
    }
    return 0;
}

int keyscan(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    uint8_t data;


    int rc = as1115_read_keyscanA(&as1115_dev, &data);
    if (rc != AS1115_OK) {
        puts("Read Keys failed!");
        return rc;
    }

    printf("%x\n", data);
    return 0;
}

int power_on(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    int rc = as1115_on(&as1115_dev);
    if (rc != AS1115_OK) {
        puts("Power on failed!");
        return rc;
    }

    return 0;
}

int power_off(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    int rc = as1115_off(&as1115_dev);
    if (rc != AS1115_OK) {
        puts("Power off failed!");
        return rc;
    }

    return 0;
}

int set_digit(int argc, char **argv) 
{
    if (argc != 3) {
        puts("usage: set_digit <digit no (0-7)> <value>");
    } else {
        uint8_t digit = atoi(argv[1]);
        uint8_t value = strtol(argv[2], NULL, 16);

        int rc = as1115_set_digit(&as1115_dev, digit, value);
        if (rc != AS1115_OK) {
            printf("Setting digit failed! rc=%i\n", rc);
            return rc;
        }
    }
    return 0;
}

int set_digit_enable_decode(int argc, char **argv)
{
    if (argc != 3) {
        puts("usage: set_digit_enable_decode <digit no (0-7)> <mode (0-1)>");
    } else {
        uint8_t digit = atoi(argv[1]);
        uint8_t enable = atoi(argv[2]);

        if (enable > 1) {
            puts("<mode> only 0-1");
            return 0;
        }

        int rc = as1115_set_decode_mode(&as1115_dev, digit, enable);
        if (rc != AS1115_OK) {
            printf("Set decode on digit %i failed! rc=%i\n", digit, rc);
            return rc;
        }
    }
    return 0;
}

int global_intensity(int argc, char **argv)
{
    if (argc != 2) {
        puts("usage: global_intensity <intensity (0x0-0xf)>");
    } else {
        uint8_t intensity = strtol(argv[1], NULL, 16);

        int rc = as1115_global_intensity(&as1115_dev, intensity);
        if (rc != AS1115_OK) {
            puts("Set global intensity failed!");
            return -1;
        }
    }
    return 0;
}

static const shell_command_t shell_commands[] = {
    { "power_on", "Turn the device on.", power_on },
    { "power_off", "Turn the device off.", power_off },
    { "set_digit", "Set the digit value.", set_digit },
    { "enable_decode", "Enables/disables the decoder of the digit.", set_digit_enable_decode },
    { "global_intensity", "Set the global display intensity", global_intensity },
    { "test_disp", "Optical display test.", test_disp },
    { "keyscan", "Read the keyscan register.", keyscan },
    { NULL, NULL, NULL }
};

int main(void)
{

    if (as1115_init(&as1115_dev, &as1115_params[0]) != AS1115_OK) {
        puts("Initialization failed!");
        return 1;
    }

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
