#ifndef PUSH2_MIDI1_INPUT_CALLBACK_H
#define PUSH2_MIDI1_INPUT_CALLBACK_H

#include "IMidi1InputCallback.h"
#include "Push2Device.h"

class LedColorMap;

namespace Push2
{

class Midi1InputCallback : public midi::IMidi1InputCallback
{
public:
    Midi1InputCallback(Push2Device::EncoderLayer&      rEncoder,
                       Push2Device::ButtonLayer&       rButton,
                       Push2Device::Button3dLayer&     rButton3d,
                       Push2Device::TouchSurfaceLayer& rTouch,
                       LedColorMap&                    rLedColormap);
    void onNoteOff(double timestamp, const midi::InputMessage<midi::NoteOff>& msg) override;
    void onNoteOn(double timestamp, const midi::InputMessage<midi::NoteOn>& msg) override;
    void onControlChange(double timestamp, const midi::InputMessage<midi::ControlChange>& msg) override;
    void onAfterTouchPoly(double timestamp, const midi::InputMessage<midi::AfterTouchPoly>& msg) override;
    void onPitchBend(double timestamp, const midi::InputMessage<midi::PitchBend>& msg) override;
    void onSystemExclusive(double timestamp, const std::vector<uint8_t>& msg) override;

private:
    Push2Device::EncoderLayer      &m_rEncoder;
    Push2Device::ButtonLayer       &m_rButton;
    Push2Device::Button3dLayer     &m_rButton3d;
    Push2Device::TouchSurfaceLayer &m_rTouch;
    LedColorMap                    &m_rLedColormap;
    void setEncoderByCCVal(const fp::Widget& w, uint8_t ccVal);
    void setButtonByCCVal(const fp::Widget& w, uint8_t ccVal);
    void handleNote(double timestamp, uint8_t noteNumber, uint8_t velocity, bool pressed);
};

} // namespace Push2
#endif