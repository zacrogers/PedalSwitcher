#pragma once

#include <stdint.h>
#include "gpio.hh"
// using std::uint8_t;
using z_lib::Gpio;

template<int N_BITS>
class ShiftRegister
{
    private:
        Gpio *_data; 
        Gpio *_clock; 
        Gpio *_latch;
        uint16_t _prev_state = 0x00;
    public:
        ShiftRegister(Gpio *data, Gpio *clock, Gpio *latchs);
        int num_bits(){return N_BITS;}
        void set(uint16_t val);
};

template<int N_BITS>
ShiftRegister<N_BITS>::ShiftRegister(Gpio *data, Gpio *clock, Gpio *latch) 
                                : _data{data}, _clock{clock}, _latch{latch}
{
}

template<int N_BITS>
void ShiftRegister<N_BITS>::set(uint16_t val)
{
    /* If state doesn't change don't bother setting */
    if(_prev_state == val) return;

    /* Set register output*/
    _latch->clear();

    for(int bit = 0; bit < N_BITS; ++bit)
    {
        _clock->clear();
        
        if((0x01 << val) & (0x01 << bit))
        {
            _data->set();
        }                                          
        else                   
        {
            _data->clear();
        }
        _clock->set();
    } 
    
    _latch->set();

    _prev_state = val;
}