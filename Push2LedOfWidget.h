#ifndef PUSH2_LED_OF_WIDGET_H
#define PUSH2_LED_OF_WIDGET_H

#include "FpWidget.h"
#include "Push2Topology.h"

namespace Push2
{

inline
fp::Widget getLedOfButton(const fp::Widget& btn)
{
    switch(btn.id)
    {
        case fp::Push2Topology::Button::eBtnAccent: return Widget(fp::Push2Topology::Led::eLedAccent, btn.coord);
        case fp::Push2Topology::Button::eBtnPlay: return Widget(fp::Push2Topology::Led::eLedPlay, btn.coord);
        case fp::Push2Topology::Button::eBtnSel: return Widget(fp::Push2Topology::Led::eLedSel, btn.coord);
        case fp::Push2Topology::Button::eBtnT: return Widget(fp::Push2Topology::Led::eLedT, btn.coord);
        case fp::Push2Topology::Button::eBtnB: return Widget(fp::Push2Topology::Led::eLedB, btn.coord);
        default: return Widget(-1, {0,0});
    }
}

inline
fp::Widget getLedOfButton3d(const fp::Widget& btn)
{
    switch(btn.id)
    {
        case fp::Push2Topology::Button3d::eBtnSil: return Widget(fp::Push2Topology::Led::eBtnSilLed, btn.coord);
        default: return Widget(-1, {0,0});
    }
}

} // namespace Push2
#endif