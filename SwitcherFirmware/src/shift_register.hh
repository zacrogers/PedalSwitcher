#pragma once

#include <stdint.h>

#include "gpio.hh"
// using std::uint8_t;
using z_lib::Gpio;

class ShiftRegister
{
private:
    Gpio *_data; 
    Gpio *_clock; 
    Gpio *_latch;
    uint8_t _n_bits;
    uint16_t _prev_state = 0x00;
public:
    ShiftRegister(Gpio *data, Gpio *clock, Gpio *latch, uint8_t n_bits);
    ~ShiftRegister();
    uint8_t num_bits(){return _n_bits;}
    void set(uint16_t val);
};

ShiftRegister::ShiftRegister(Gpio *data, Gpio *clock, Gpio *latch, uint8_t n_bits) 
                                : _data{data}, _clock{clock}, _latch{latch}, _n_bits{n_bits}
{
}

ShiftRegister::~ShiftRegister()
{
}


void ShiftRegister::set(uint16_t val)
{
    if(_prev_state == val) return;

    /* Set register output*/
    _latch->clear();

    for(int led = 0; led < _n_bits; led++)
    {
        _clock->clear();
        
        if((0x01 << val) & (0x01 << led))
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