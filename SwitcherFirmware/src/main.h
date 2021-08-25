#pragma once

#include <Arduino.h>
#include <EEPROM.h>
#include <stdint.h>
#include <stdlib.h>
// #include <string.h>
// #include <vector.h>
// #include "mux.hh"
#include "shift_register.hh"
#include "gpio.hh"

using z_lib::Gpio;

constexpr uint8_t MAX_PATCHES = 10;
constexpr uint8_t NUM_CHANNELS = 4;
// 4 control pins per mux. 
constexpr int MUX_OFFSET = 4;

enum class Output
{
    SEND1,
    SEND2,
    SEND3,
    SEND4,
    MAIN,
    N_OUTPUTS
};

enum class Input
{
    REC1,
    REC2,
    REC3,
    REC4,
    MAIN,
    N_INPUTS
};

typedef struct 
{
    bool enable;
    Output output;
}Mux;


typedef struct 
{
    // std::string name;
    bool enabled[5];
    Output output[5];
}Patch;

Patch init_patch(
    bool en1, 
    bool en2, 
    bool en3, 
    bool en4, 
    Output op1, 
    Output op2, 
    Output op3, 
    Output op4);

void init_patches(void);
void add_patch(uint8_t index);
void save_patch(uint8_t index);
void set_patch(Patch *patch);
void bypass(void);

uint8_t set_mux_channel(bool enable, Output output); /* returns bitmap to set shift register */

void poll_buttons(void);
