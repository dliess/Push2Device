#include "Push2Midi1InputCallback.h"
#include "Push2LedColorMap.h"
#include <iostream>
#include <chrono>

using namespace push2device;

Midi1InputCallback::Midi1InputCallback(Push2Device::EncoderLayer&      rEncoder,
                                       Push2Device::ButtonLayer&       rButton,
                                       Push2Device::Button3dLayer&     rButton3d,
                                       Push2Device::TouchSurfaceLayer& rTouch,
                                       LedColorMap&                    rLedColormap) :
    m_rEncoder(rEncoder),
    m_rButton(rButton),
    m_rButton3d(rButton3d),
    m_rTouch(rTouch),
    m_rLedColormap(rLedColormap)
{}


void Midi1InputCallback::onNoteOff(double timestamp, const midi::Message<midi::NoteOff>& msg)
{
    handleNote(timestamp, msg.noteNumber(), msg.velocity(), false);
}

void Midi1InputCallback::onNoteOn(double timestamp, const midi::Message<midi::NoteOn>& msg)
{
    handleNote(timestamp, msg.noteNumber(), msg.velocity(), true);
}

void Midi1InputCallback::onControlChange(double timestamp, const midi::Message<midi::ControlChange>& msg)
{
    switch(msg.controllerNumber())
    {
        case 3:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnTapTempo);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 9:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnMetronome);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 14:
        {
            const fp::Widget widget(fp::Push2Topology::Encoder::eEncoderTempo);
            setEncoderByCCVal(widget, msg.controllerValue());
            break;
        }
        case 15:
        {
            const fp::Widget widget(fp::Push2Topology::Encoder::eEncoderMetronome);
            setEncoderByCCVal(widget, msg.controllerValue());
            break;
        }
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        {
            const uint8_t idx = msg.controllerNumber() - 20;
            const fp::Widget widget(fp::Push2Topology::Button::eBtnB, idx);
            setButtonByCCVal(widget, msg.controllerValue());
            break;
        }
        case 28:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnMaster);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 29:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnStopClip);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 30:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnSetup);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 31:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnLayout);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 35:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnConvert);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 36:
        case 37:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
        case 43:
        {
            const uint8_t idx = 43 - msg.controllerNumber();
            const fp::Widget widget(fp::Push2Topology::Button::eBtnSel, idx);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 44:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnLeftArrow);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 45:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnRightArrow);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 46:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnUpArrow);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 47:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnDownArrow);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 48:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnSelect);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 49:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnShift);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 50:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnNote);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 51:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnSession);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 52:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnAddDevice);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 53:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnAddTrack);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 54:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnOctaveDown);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 55:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnOctaveUp);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 56:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnRepeat);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 57:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnAccent);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 58:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnScale);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 59:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnUser);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 60:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnMute);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 61:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnSolo);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 62:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnPageLeft);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 63:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnPageRight);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 71:
        case 72:
        case 73:
        case 74:
        case 75:
        case 76:
        case 77:
        case 78:
        {
            const uint8_t idx = msg.controllerNumber() - 71;
            const fp::Widget widget(fp::Push2Topology::Encoder::eEncoder, idx);
            setEncoderByCCVal(widget, msg.controllerValue());
            break;
        }
        case 79:
        {
            const fp::Widget widget(fp::Push2Topology::Encoder::eEncoderMain, 0);
            setEncoderByCCVal(widget, msg.controllerValue());
            break;
        }
        case 85:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnPlay);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 86:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnRecord);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 87:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnNew);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 88:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnDuplicate);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 89:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnAutomate);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 90:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnFixedLength);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 102:
        case 103:
        case 104:
        case 105:
        case 106:
        case 107:
        case 108:
        case 109:
        {
            const uint8_t idx = msg.controllerNumber() - 102;
            const fp::Widget widget(fp::Push2Topology::Button::eBtnT, idx);
            setButtonByCCVal(widget, msg.controllerValue());
            break;
        }
        case 110:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnDevice);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 111:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnBrowse);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 112:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnMix);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 113:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnClip);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 116:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnQuantize);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 117:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnDoubleLoop);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 118:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnDelete);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        case 119:
        {
            const fp::Widget widget(fp::Push2Topology::Button::eBtnUndo);
            setButtonByCCVal(widget, msg.controllerValue());            
            break;
        }
        default:
        {
            break;
        }
    }
}

void Midi1InputCallback::onAfterTouchPoly(double timestamp, const midi::Message<midi::AfterTouchPoly>& msg)
{
    static const uint8_t BtnMatrixStartMidiNoteNmbr = 36;
    static const uint8_t BtnMatrixEndMidiNoteNmbr = 99;
    if(BtnMatrixStartMidiNoteNmbr <= msg.noteNumber() &&
       msg.noteNumber() <= BtnMatrixEndMidiNoteNmbr)
    {
        const uint8_t linearIndex = msg.noteNumber() - BtnMatrixStartMidiNoteNmbr;
        const uint8_t x = linearIndex % 8;
        const uint8_t y = 7 - (linearIndex / 8);
        const fp::Widget w(fp::Push2Topology::Button3d::eBtnSil, {x, y});
        auto pValueHandler = m_rButton3d.get(w);
        if(pValueHandler)
        {
            pValueHandler->pressure.set( msg.pressure() );
        }
        m_rButton3d.checkValuesAndInvokeCallbacks(w);
    }
}

void Midi1InputCallback::onPitchBend(double timestamp, const midi::Message<midi::PitchBend>& msg)
{
    const auto id = fp::Push2Topology::TouchSurface::eTouchStrip;
    const fp::Widget w(id);
    const auto resolutionX = fp::Push2Topology::TouchSurface::getResolution(id).x;
    auto pValueHandler = m_rTouch.get(w);
    if(pValueHandler)
    {
        pValueHandler->pos.set({  static_cast<int>((msg.value() + 0x2000) * resolutionX / 0x4000) , 0});
    }
    m_rTouch.checkValuesAndInvokeCallbacks(w);
}
/*
#include <iomanip>
*/
void Midi1InputCallback::onSystemExclusive(double timestamp, const std::vector<uint8_t>& msg)
{
    
    // Debug print
    /*
    std::cout << "Incoming Sysex: ";
    for(auto& entry : msg)
    {
        std::cout << std::hex <<  std::setfill('0') << std::setw(2) << static_cast<int>(entry) << " ";
    }
    std::cout << std::endl;
    */
    static const uint8_t SYSEX_CMD_INDEX = 6;
    static const uint8_t SYSEX_CMD__GET_COLOR_PALETTE = 0x04;
    if((SYSEX_CMD_INDEX + 1) > msg.size())
    {
        std::cerr << "invalid sysex msg received from Push2 " << msg.size() << std::endl;
        return;
    }
    switch(msg[SYSEX_CMD_INDEX])
    {
        case SYSEX_CMD__GET_COLOR_PALETTE:
        {
            const uint8_t COLORMAP_INDEX = SYSEX_CMD_INDEX + 1;
            const uint8_t COLORMAP_RED_LSB = SYSEX_CMD_INDEX + 2;
            const uint8_t COLORMAP_RED_MSB = SYSEX_CMD_INDEX + 3;
            const uint8_t COLORMAP_GREEN_LSB = SYSEX_CMD_INDEX + 4;
            const uint8_t COLORMAP_GREEN_MSB = SYSEX_CMD_INDEX + 5;
            const uint8_t COLORMAP_BLUE_LSB = SYSEX_CMD_INDEX + 6;
            const uint8_t COLORMAP_BLUE_MSB = SYSEX_CMD_INDEX + 7;
            const uint8_t COLORMAP_WHITE_LSB = SYSEX_CMD_INDEX + 8;
            const uint8_t COLORMAP_WHITE_MSB = SYSEX_CMD_INDEX + 9;
            if((COLORMAP_WHITE_MSB + 1) > msg.size())
            {
                std::cerr << "invalid sysex msg received from Push2 " << msg.size() << std::endl;
                return;
            }
            if(COLORMAP_WHITE_MSB)
            m_rLedColormap.add(msg[COLORMAP_INDEX],
                               (msg[COLORMAP_RED_LSB] & 0x7f)   + ( (msg[COLORMAP_RED_MSB] & 0x01) << 7),
                               (msg[COLORMAP_GREEN_LSB] & 0x7f) + ( (msg[COLORMAP_GREEN_MSB]& 0x01) << 7),
                               (msg[COLORMAP_BLUE_LSB] & 0x7f)  + ( (msg[COLORMAP_BLUE_MSB]& 0x01) << 7),
                               (msg[COLORMAP_WHITE_LSB] & 0x7f) + ( (msg[COLORMAP_WHITE_MSB]& 0x01) << 7));
            if(0x7f == msg[COLORMAP_INDEX])
            {
                std::unique_lock<std::mutex> lock(m_mutex);
                m_hasReceivedSysexAnswers = true;
                m_condVar.notify_all();
            }
            break;
        }
    }
}


void Midi1InputCallback::setEncoderByCCVal(const fp::Widget& w, uint8_t ccVal)
{
    auto pIncrHolder = m_rEncoder.get(w);
    if(pIncrHolder)
    {
        const int8_t shiftedVal = ccVal << 1;
        pIncrHolder->increments.set(shiftedVal >> 1);
    }
    m_rEncoder.checkValuesAndInvokeCallbacks(w);
}

void Midi1InputCallback::setButtonByCCVal(const fp::Widget& w, uint8_t ccVal)
{
    auto pValueHandler = m_rButton.get(w);
    if(pValueHandler)
    {
        pValueHandler->pressState.set((ccVal == 127) ? fp::Button::Pressed : fp::Button::Released);
    }
    m_rButton.checkValuesAndInvokeCallbacks(w);
}

void Midi1InputCallback::handleNote(double timestamp, uint8_t noteNumber, uint8_t velocity, bool pressed)
{
    static const uint8_t EncoderStartMidiNoteNmbr = 0;
    static const uint8_t EncoderEndMidiNoteNmbr = 10;
    static const uint8_t TouchStripTouchedMidiNoteNmbr = 12;
    static const uint8_t BtnMatrixStartMidiNoteNmbr = 36;
    static const uint8_t BtnMatrixEndMidiNoteNmbr = 99;

    if(EncoderStartMidiNoteNmbr <= noteNumber && 
       noteNumber <= EncoderEndMidiNoteNmbr)
    {
        fp::Widget w(fp::Push2Topology::Encoder::eEncoder, noteNumber);
        switch(noteNumber)
        {
            case 8:
            {
                w = fp::Widget(fp::Push2Topology::Encoder::eEncoderMain);
                break;
            }
            case 9:
            {
                w = fp::Widget(fp::Push2Topology::Encoder::eEncoderMetronome);
                break;
            }
            case 10:
            {
                w = fp::Widget(fp::Push2Topology::Encoder::eEncoderTempo);
                break;
            }
            default:
            {
                break;
            }
        }
        auto pValueHandler = m_rEncoder.get(w);
        if(pValueHandler)
        {
            pValueHandler->touchState.set(velocity != 0 ? fp::Encoder::Touched : fp::Encoder::Released);
        }
        m_rEncoder.checkValuesAndInvokeCallbacks(w);
    }
    else if(TouchStripTouchedMidiNoteNmbr == noteNumber)
    {
        const fp::Widget w(fp::Push2Topology::TouchSurface::eTouchStrip);
        auto pValueHandler = m_rTouch.get(w);
        if(pValueHandler)
        {
            pValueHandler->touchState.set(velocity != 0 ? fp::TouchSurface::Touched : fp::TouchSurface::Released);
        }
        m_rTouch.checkValuesAndInvokeCallbacks(w);
    }
    else if(BtnMatrixStartMidiNoteNmbr <= noteNumber &&
       noteNumber <= BtnMatrixEndMidiNoteNmbr)
    {
        const uint8_t linearIndex = noteNumber - BtnMatrixStartMidiNoteNmbr;
        const uint8_t x = linearIndex % 8;
        const uint8_t y = 7 - (linearIndex / 8);
        const fp::Widget w(fp::Push2Topology::Button3d::eBtnSil, {x, y});
        auto pValueHandler = m_rButton3d.get(w);
        if(pValueHandler)
        {
            pValueHandler->pressState.set( pressed ? fp::Button3d::Pressed : fp::Button3d::Released );
            pValueHandler->velocity = velocity;
        }
        m_rButton3d.checkValuesAndInvokeCallbacks(w);
    }
}

bool Midi1InputCallback::waitUntilSysexAnswersReceived(uint32_t timeoutMs)
{
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_condVar.wait_for(lock, std::chrono::milliseconds(timeoutMs),
                                [this](){return m_hasReceivedSysexAnswers;});
} 
