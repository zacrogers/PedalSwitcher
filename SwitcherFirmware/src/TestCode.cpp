#include "main.h"


int mux_channels[3] = {0,0,0};

Gpio sr_data = Gpio(PORTB, PIN0, Gpio::Mode::OUT);
Gpio sr_clock = Gpio(PORTB, PIN1, Gpio::Mode::OUT);
Gpio sr_latch = Gpio(PORTB, PIN2, Gpio::Mode::OUT);

ShiftRegister shift_reg(&sr_data, &sr_clock, &sr_latch, 16);

Gpio channel_btns[4] = {
    Gpio(PORTB, PIN3, Gpio::Mode::OUT),
    Gpio(PORTB, PIN4, Gpio::Mode::OUT),
    Gpio(PORTB, PIN5, Gpio::Mode::OUT),
    Gpio(PORTB, PIN6, Gpio::Mode::OUT)
};

Gpio patch_up_btn = Gpio(PORTB, PIN7, Gpio::Mode::IN);
Gpio patch_down_btn = Gpio(PORTB, PIN7, Gpio::Mode::IN);

Patch patches[MAX_PATCHES];

uint8_t current_patch = 0;

void setup(void)
{

    // set_patch(bypass_patch);
}

void loop(void)
{

    for(int i = 0; i < MAX_PATCHES; i++)
    {

    }
 
}

Patch init_patch(
    bool en1, 
    bool en2, 
    bool en3, 
    bool en4, 
    Output op1, 
    Output op2, 
    Output op3, 
    Output op4)
{
    Patch patch = {0};
    patch.enabled[0] = en1;
    patch.enabled[1] = en2;
    patch.enabled[2] = en3;
    patch.enabled[3] = en4;
    patch.output[0] = op1;
    patch.output[1] = op2;
    patch.output[2] = op3;
    patch.output[3] = op4;

    return patch;
}

void init_patches(void)
{
    // If there are existing patches load them

    Patch patch = init_patch(
        true,
        false,
        false,
        false,
        Output::MAIN,
        Output::MAIN,
        Output::MAIN,
        Output::MAIN
    );

    for(uint8_t i = 0; i < MAX_PATCHES; i++)
    {
        patches[i] = patch;
    }
}

void set_patch(Patch *patch)
{
    uint16_t output = 0x00;

    for(uint8_t i = 0; i < 5; i++)
    {
        uint8_t offset = MUX_OFFSET * (i + 1);
        output |= (set_mux_channel(patch->enabled[i], patch->output[i]) << offset);
    }

    shift_reg.set(output);
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
    for(uint8_t i = 0; i < NUM_CHANNELS; i++)
    {
        if(channel_btns[i].read())
        {
            patches[current_patch].enabled[i] = true;
        } 
        else
        {
            patches[current_patch].enabled[i] = false;
        }
    }

    if(patch_down_btn.read() && (current_patch != 0))
    {   
        current_patch--;
    }

    if(patch_up_btn.read() && (current_patch != MAX_PATCHES))
    {
        current_patch++;
    }
}

void bypass(void)
{
    uint16_t output = 0x00;
    output |= set_mux_channel(true, Output::MAIN);
    output |= (set_mux_channel(false, Output::MAIN) << MUX_OFFSET);
    output |= (set_mux_channel(false, Output::MAIN) << (MUX_OFFSET*2));
    // shift_reg.set(output);
}