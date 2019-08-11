#ifndef PUSH2_LED_OF_WIDGET_H
#define PUSH2_LED_OF_WIDGET_H

#include "FpWidget.h"
#include "Push2Topology.h"

namespace push2
{

inline
fp::Widget getLedOfButton(const fp::Widget& btn)
{
    switch(btn.id)
    {
        case fp::Push2Topology::Button::eBtnAccent: return fp::Widget(fp::Push2Topology::Led::eLedAccent, btn.coord);
        case fp::Push2Topology::Button::eBtnPlay: return fp::Widget(fp::Push2Topology::Led::eLedPlay, btn.coord);
        case fp::Push2Topology::Button::eBtnSel: return fp::Widget(fp::Push2Topology::Led::eLedSel, btn.coord);
        case fp::Push2Topology::Button::eBtnT: return fp::Widget(fp::Push2Topology::Led::eLedT, btn.coord);
        case fp::Push2Topology::Button::eBtnB: return fp::Widget(fp::Push2Topology::Led::eLedB, btn.coord);
        case fp::Push2Topology::Button::eBtnScale: return fp::Widget(fp::Push2Topology::Led::eLedScale, btn.coord);
        case fp::Push2Topology::Button::eBtnDevice: return fp::Widget(fp::Push2Topology::Led::eLedDevice, btn.coord);
        case fp::Push2Topology::Button::eBtnOctaveUp: return fp::Widget(fp::Push2Topology::Led::eLedOctaveUp, btn.coord);
        case fp::Push2Topology::Button::eBtnOctaveDown: return fp::Widget(fp::Push2Topology::Led::eLedOctaveDown, btn.coord);
        default: return fp::Widget(-1, {0,0});
    }
}

inline
fp::Widget getLedOfButton3d(const fp::Widget& btn)
{
    switch(btn.id)
    {
        case fp::Push2Topology::Button3d::eBtnSil: return fp::Widget(fp::Push2Topology::Led::eBtnSilLed, btn.coord);
        default: return fp::Widget(-1, {0,0});
    }
}

} // namespace push2device
#endif