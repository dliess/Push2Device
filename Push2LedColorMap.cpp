#include "Push2LedColorMap.h"

using namespace Push2;

LedColorMap::Data LedColorMap::invalidInstance;


LedColorMap::LedColorMap() :
   m_data()
{}

bool LedColorMap::add(uint8_t index, uint8_t r, uint8_t g, uint8_t b, uint8_t w)
{
    if(index >= SIZE)
    {
        return false;
    }
    m_data[index].isValid = true;
    m_data[index].r = r;
    m_data[index].g = g;
    m_data[index].b = b;
    m_data[index].w = w;
    return true;
}

const LedColorMap::Data& LedColorMap::get(uint8_t index) const
{
    if(index >= SIZE)
    {
        return invalidInstance;
    }
    return m_data[index];
}
