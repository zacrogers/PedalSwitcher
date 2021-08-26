/* 
    Guitar pedal loop switcher
*/
#include "main.h"


Gpio channel_btns[NUM_CHANNELS] = {
    Gpio(PORTB, PIN3, Gpio::Mode::IN),
    Gpio(PORTB, PIN4, Gpio::Mode::IN),
    Gpio(PORTB, PIN5, Gpio::Mode::IN),
    Gpio(PORTB, PIN6, Gpio::Mode::IN)
};

Gpio patch_mode_btn = Gpio(PORTB, PIN7, Gpio::Mode::IN);
Gpio patch_up_btn   = Gpio(PORTB, PIN7, Gpio::Mode::IN);
Gpio patch_down_btn = Gpio(PORTB, PIN7, Gpio::Mode::IN);

Gpio sr_data        = Gpio(PORTB, PIN0, Gpio::Mode::OUT);
Gpio sr_clock       = Gpio(PORTB, PIN1, Gpio::Mode::OUT);
Gpio sr_latch       = Gpio(PORTB, PIN2, Gpio::Mode::OUT);

ShiftRegister shift_reg(&sr_data, &sr_clock, &sr_latch, 16);

Patch patches[MAX_PATCHES];

uint8_t EEMEM eeprom_patches[MAX_PATCHES];

uint8_t current_patch = 0;
uint8_t prev_patch = 0;

void setup(void)
{
    // load saved patches
    // load_patches_from_eeprom();
    init_patches();

    patches[1] = init_patch(true, false, false, false);
    patches[2] = init_patch(false, true, false, false);
    patches[3] = init_patch(false, false, true, false);
    patches[4] = init_patch(false, false, false, true);
    set_patch(&patches[current_patch]);
}

void loop(void)
{
    // poll_buttons();

    // if(prev_patch != current_patch)
    // {
    //     set_patch(&patches[current_patch]);
    // } 

    for(int i = 0; i < 5; ++i)
    {
        set_patch(&patches[i]);
        delay(2000);
    }
}

Patch init_patch(bool en1, bool en2, bool en3, bool en4)
{
    Patch patch = {0};
    patch.enabled[0] = en1;
    patch.enabled[1] = en2;
    patch.enabled[2] = en3;
    patch.enabled[3] = en4;
    // patch.output[0] = op1;
    // patch.output[1] = op2;
    // patch.output[2] = op3;
    // patch.output[3] = op4;

    return patch;
}


void init_patches(void)
{
    // If there are existing patches load them

    Patch patch = init_patch(false, false, false, false);

    for(uint8_t p = 0; p < MAX_PATCHES; ++p)
    {
        patches[p] = patch;
    }
}


Output find_next_enabled(bool *enabled, uint8_t index)
{
    uint8_t next_enabled = 0;
    Output output = Output::MAIN;

    /* If index is last channel set to main output*/
    if(index < NUM_CHANNELS)
    {
        for(uint8_t i = index; i < NUM_CHANNELS; ++i)
        {
            if(enabled[i])
            {
                next_enabled = i;
            }
        }

        output = (Output)next_enabled;
    }

    return output;
}


void set_patch(Patch *patch)
{
    uint16_t sr_output = 0x00;

    for(uint8_t chan = 0; chan < NUM_CHANNELS; ++chan)
    {
        uint8_t offset = MUX_OFFSET * (chan + 1);
        Output  output = find_next_enabled(patch->enabled, chan);
        uint8_t bitmap = set_mux_channel(patch->enabled[chan], output);

        sr_output |= (bitmap << offset);
    }

    shift_reg.set(sr_output);
}


uint8_t set_mux_channel(bool enable, Output output)
{
    uint8_t out = 0x00;

    if(enable) { out |= 0x01; }
    
    out |= ((uint8_t)output << 0x01);

    return out;
}


void poll_buttons(void)
{
    for(uint8_t chan = 0; chan < NUM_CHANNELS; ++chan)
    {
        if(channel_btns[chan].read())
        {
            patches[current_patch].enabled[chan] = true;
        } 
        else
        {
            patches[current_patch].enabled[chan] = false;
        }
    }

    if(patch_down_btn.read() && (current_patch != 0))
    {   
        prev_patch = current_patch;
        current_patch--;
    }

    if(patch_up_btn.read() && (current_patch != MAX_PATCHES))
    {
        prev_patch = current_patch;
        current_patch++;
    }
}


void save_patch_to_eeprom(uint8_t index)
{
    if(MAX_PATCHES <= index) return;

    uint8_t byte_to_save = 0x00;

    for(uint8_t i = 0; i < NUM_CHANNELS; ++i)
    {
        byte_to_save |= (patches[index].enabled[i] << i);
    }

    eeprom_update_byte(&eeprom_patches[index], byte_to_save);
}


void load_patches_from_eeprom(void)
{
    uint8_t patch_bytes[MAX_PATCHES];

    // Load patch bytes from eeprom
    for(uint8_t i = 0; i < MAX_PATCHES; ++i)
    {
        patch_bytes[i] = eeprom_read_byte(&eeprom_patches[i]);
    }

    // Load patch bytes into patch structs
    for(uint8_t p = 0; p < MAX_PATCHES; ++p)
    {
        Patch patch = init_patch(false, false, false, false);

        for(uint8_t chan = 0; chan < NUM_CHANNELS; ++chan)
        {
            if(patch_bytes[p] & (0x01<<chan))
            {
                patch.enabled[chan] = true;
            }
        }

        patches[p] = patch;
    }
}