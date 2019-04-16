#ifndef PUSH2_LED_COLORMAP_H
#define PUSH2_LED_COLORMAP_H

#include <cstdint>

namespace Push2
{

class LedColorMap
{
public:
    LedColorMap();
    struct Data
    {
        bool isValid = false;
        uint8_t r = 0;
        uint8_t g = 0;
        uint8_t b = 0;
        uint8_t w = 0;
    };
    bool add(uint8_t index, uint8_t r, uint8_t g, uint8_t b, uint8_t w);
    const Data& get(uint8_t index) const;
    static const uint8_t SIZE = 128;
private:
    Data m_data[SIZE];
    static Data invalidInstance;
};

} // namespace Push2
#endif