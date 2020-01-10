#include <SPI.h>
#include <SD.h>

#define BAUD_RATE 9600

#define NUM_LEDS  8
#deifne NUM_BTNS  8


/* Led indexes */
enum class LedInd
{
    /* Channel state indicators */
    CHAN_1 = 0,
    CHAN_2,
    CHAN_3,
    CHAN_4,   
};

/* Button indexes */
enum class BtnInd
{
    CHAN_1 = 0,
    CHAN_2,
    CHAN_3,
    CHAN_4,
    BANK_UP,
    BANK_DWN,
    MODE
};

enum class States
{
    /* Use this mode when updating the patches on the unit */
    PROGRAMMING = 0, 
    
    /* This is for patch selection mode */
    PATCH,         
    
    /* This mode for enabling/disabling the channels  manually */
    MANUAL
};

typedef enum
{
    uint8_t channels[5];
}Patch;


class ShiftReg16{};

const ShiftReg16 shift_register(data, clk, latch);
const Mux btn_mux = {.sel = {s0, s1, s2}, .out = out};

File   my_file;

States current_state      = States::PROGRAMMING;
Patch  current_patch      = {0};

uint8_t led_state         = 0x00;
uint8_t channel_state     = 0x00;
uint8_t btn_state         = 0x00;

bool    serial_connected  = false;
uint8_t serial_data       = 0;

void setup(void)
{

}


void loop(void)
{
    poll_buttons();
    
    switch(current_state)
    {
        case(States::MANUAL):
            state_manual();
            break;
            
        case(States::PATCH):     
            state_patch();
            break;
            
        case(States::PROGRAMMING):    
            state_programming();
            break;               
    }   
}

/* Global functions */
void change_state(States state)
{
    current_state = state;
}

void poll_buttons(void)
{
    uint8_t mux_state = digitalRead(btn_mux.out);
        
    for(uint8 btn = 0; btn < NUM_BTNS; ++btn)
    {
        btn_state |= mux_state << btn;       
    }
}

void set_shift_register(uint16_t val)
{
    uint16_t state = (led_state << 8) | channel_state;
    /****************************************
        Copy previous shift register code 
    *****************************************/
}

void set_led(LedInd led)
{
    led_state |= (0x01 << (uint8_t)led);
    set_shift_register();
    
}

void clear_led(LedInd led)
{
    led_state &= ~(0x01 << (uint8_t)led);
    set_shift_register();
}

void set_leds(uint8_t leds)
{

}

void set_channels(uint8_t channels)
{

}

void midi_recieve()
{
    
}


/* Programming mode functions */
void state_programming(void)
{    
    if(!serial_connected)
    {
        serial_connect();
    }
    
    if(Serial.available())
    {           
        serial_connected = true;
        serial_data = Serial.read();

        if(serial_data == "SYNC TO")
        {
            sync_from_configurator();
        }     
    }        
}


void sync_from_configurator(void)
{
    Serial.print("CONNECTED");   
    my_file = SD.open("config.txt", FILE_WRITE);

    if(my_file)
    {
        my_file.println(serial_data);     
        my_file.close();
    }
}


void sync_to_configurator(void)
{
    Serial.print("CONNECTED");
}

void serial_connect(void)
{
    Serial.begin(BAUD_RATE);
}

void serial_disconnect(void)
{
    Serial.end();
}


/* Patch mode functions */
void state_patch(void)
{

}


void load_patches(void)
{
    // open sd card
    // 
}


void set_patch(uint8_t patch)
{

}


/* Manual mode functions */
void state_manual(void)
{

}

void enable_channel(uint8_t channel)
{
    set_shift_register();
}

void disable_channel(uint8_t channel)
{
    set_shift_register();
}

