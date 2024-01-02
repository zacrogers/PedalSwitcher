#pragma once
#include <cstdint>

using std::uint8_t;

class Mux
{
private:
    /* data */
public:
    Mux(uint8_t a, uint8_t b, uint8_t c, uint8_t en);
    ~Mux();
    void set(uint8_t channel);
    void enable(bool enable);
};

Mux::Mux(uint8_t a, uint8_t b, uint8_t c, uint8_t en)
{
}

Mux::~Mux()
{
}

void Mux::set(uint8_t channel){

}

void Mux::enable(bool enable)
{

}