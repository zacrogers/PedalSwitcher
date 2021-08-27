#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <stdlib.h>
#include <avr/eeprom.h>
#include "shift_register.hh"
#include "gpio.hh"

using z_lib::Gpio;

// Total number of patches that can be saved
constexpr uint8_t MAX_PATCHES = 10;

// Total number of pedal loops per board
constexpr uint8_t NUM_CHANNELS = 4;

// 3 channel select pins + enable pin per MUX
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

/* 
    For tracking patch states. 
    Could just be saved as an array or byte but this is slightly clearer.
*/
typedef struct 
{
    bool enabled[NUM_CHANNELS];
}Patch;


/* Constructor for patch struct */
Patch init_patch(bool en1, bool en2, bool en3, bool en4);

/* Init all patches as bypass. Mainly for testing */
void init_patches(void);

/* Save patch struct at index as byte to eeprom */
void save_patch_to_eeprom(uint8_t index);

/* Load all patches from eeprom to array of patch structs */
void load_patches_from_eeprom(void);

/* Set current patch */
void set_patch(Patch *patch);

/* Find the next channel enabled to set mux output routing */
Output find_next_enabled(bool *enabled, uint8_t index); 

/* Returns bitmap to set shift register */
uint8_t set_mux_channel(bool enable, Output output); 

/* Polls the buttons. Funny that. */
void poll_buttons(void);
