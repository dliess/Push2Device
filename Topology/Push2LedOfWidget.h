#ifndef PUSH2_LED_OF_WIDGET_H
#define PUSH2_LED_OF_WIDGET_H

#include "FpWidget.h"
#include "Push2Topology.h"

namespace fp
{

inline
fp::Widget getLedOfButton(const fp::Widget& btn)
{
    switch(btn.id)
    {
        case fp::Push2Topology::Button::eBtnAddTrack: return fp::Widget(fp::Push2Topology::Led::eLedAddTrack, btn.coord);
        case fp::Push2Topology::Button::eBtnAccent: return fp::Widget(fp::Push2Topology::Led::eLedAccent, btn.coord);
        case fp::Push2Topology::Button::eBtnFixedLength: return fp::Widget(fp::Push2Topology::Led::eLedFixedLength, btn.coord);
        case fp::Push2Topology::Button::eBtnAddDevice: return fp::Widget(fp::Push2Topology::Led::eLedAddDevice, btn.coord);
        case fp::Push2Topology::Button::eBtnSession: return fp::Widget(fp::Push2Topology::Led::eLedSession, btn.coord);
        case fp::Push2Topology::Button::eBtnSetup: return fp::Widget(fp::Push2Topology::Led::eLedSetup, btn.coord);
        case fp::Push2Topology::Button::eBtnMute: return fp::Widget(fp::Push2Topology::Led::eLedMute, btn.coord);
        case fp::Push2Topology::Button::eBtnLeftArrow: return fp::Widget(fp::Push2Topology::Led::eLedLeftArrow, btn.coord);
        case fp::Push2Topology::Button::eBtnConvert: return fp::Widget(fp::Push2Topology::Led::eLedConvert, btn.coord);
        case fp::Push2Topology::Button::eBtnStopClip: return fp::Widget(fp::Push2Topology::Led::eLedStopClip, btn.coord);
        case fp::Push2Topology::Button::eBtnBrowse: return fp::Widget(fp::Push2Topology::Led::eLedBrowse, btn.coord);
        case fp::Push2Topology::Button::eBtnRepeat: return fp::Widget(fp::Push2Topology::Led::eLedRepeat, btn.coord);
        case fp::Push2Topology::Button::eBtnSolo: return fp::Widget(fp::Push2Topology::Led::eLedSolo, btn.coord);
        case fp::Push2Topology::Button::eBtnSel: return fp::Widget(fp::Push2Topology::Led::eLedSel, btn.coord);
        case fp::Push2Topology::Button::eBtnShift: return fp::Widget(fp::Push2Topology::Led::eLedShift, btn.coord);
        case fp::Push2Topology::Button::eBtnScale: return fp::Widget(fp::Push2Topology::Led::eLedScale, btn.coord);
        case fp::Push2Topology::Button::eBtnPlay: return fp::Widget(fp::Push2Topology::Led::eLedPlay, btn.coord);
        case fp::Push2Topology::Button::eBtnDelete: return fp::Widget(fp::Push2Topology::Led::eLedDelete, btn.coord);
        case fp::Push2Topology::Button::eBtnNote: return fp::Widget(fp::Push2Topology::Led::eLedNote, btn.coord);
        case fp::Push2Topology::Button::eBtnTapTempo: return fp::Widget(fp::Push2Topology::Led::eLedTapTempo, btn.coord);
        case fp::Push2Topology::Button::eBtnDevice: return fp::Widget(fp::Push2Topology::Led::eLedDevice, btn.coord);
        case fp::Push2Topology::Button::eBtnDownArrow: return fp::Widget(fp::Push2Topology::Led::eLedDownArrow, btn.coord);
        case fp::Push2Topology::Button::eBtnRightArrow: return fp::Widget(fp::Push2Topology::Led::eLedRightArrow, btn.coord);
        case fp::Push2Topology::Button::eBtnOctaveDown: return fp::Widget(fp::Push2Topology::Led::eLedOctaveDown, btn.coord);
        case fp::Push2Topology::Button::eBtnPageLeft: return fp::Widget(fp::Push2Topology::Led::eLedPageLeft, btn.coord);
        case fp::Push2Topology::Button::eBtnMix: return fp::Widget(fp::Push2Topology::Led::eLedMix, btn.coord);
        case fp::Push2Topology::Button::eBtnUndo: return fp::Widget(fp::Push2Topology::Led::eLedUndo, btn.coord);
        case fp::Push2Topology::Button::eBtnLayout: return fp::Widget(fp::Push2Topology::Led::eLedLayout, btn.coord);
        case fp::Push2Topology::Button::eBtnDuplicate: return fp::Widget(fp::Push2Topology::Led::eLedDuplicate, btn.coord);
        case fp::Push2Topology::Button::eBtnNew: return fp::Widget(fp::Push2Topology::Led::eLedNew, btn.coord);
        case fp::Push2Topology::Button::eBtnQuantize: return fp::Widget(fp::Push2Topology::Led::eLedQuantize, btn.coord);
        case fp::Push2Topology::Button::eBtnAutomate: return fp::Widget(fp::Push2Topology::Led::eLedAutomate, btn.coord);
        case fp::Push2Topology::Button::eBtnSelect: return fp::Widget(fp::Push2Topology::Led::eLedSelect, btn.coord);
        case fp::Push2Topology::Button::eBtnPageRight: return fp::Widget(fp::Push2Topology::Led::eLedPageRight, btn.coord);
        case fp::Push2Topology::Button::eBtnMetronome: return fp::Widget(fp::Push2Topology::Led::eLedMetronome, btn.coord);
        case fp::Push2Topology::Button::eBtnUser: return fp::Widget(fp::Push2Topology::Led::eLedUser, btn.coord);
        case fp::Push2Topology::Button::eBtnOctaveUp: return fp::Widget(fp::Push2Topology::Led::eLedOctaveUp, btn.coord);
        case fp::Push2Topology::Button::eBtnT: return fp::Widget(fp::Push2Topology::Led::eLedT, btn.coord);
        case fp::Push2Topology::Button::eBtnUpArrow: return fp::Widget(fp::Push2Topology::Led::eLedUpArrow, btn.coord);
        case fp::Push2Topology::Button::eBtnRecord: return fp::Widget(fp::Push2Topology::Led::eLedRecord, btn.coord);
        case fp::Push2Topology::Button::eBtnB: return fp::Widget(fp::Push2Topology::Led::eLedB, btn.coord);
        case fp::Push2Topology::Button::eBtnMaster: return fp::Widget(fp::Push2Topology::Led::eLedMaster, btn.coord);
        case fp::Push2Topology::Button::eBtnClip: return fp::Widget(fp::Push2Topology::Led::eLedClip, btn.coord);
        case fp::Push2Topology::Button::eBtnDoubleLoop: return fp::Widget(fp::Push2Topology::Led::eLedDoubleLoop, btn.coord);
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

} // namespace fp
#endif