#include "Push2Device.h"
#include "UsbMidiIn.h"
#include "UsbMidiOut.h"
#include "Push2Midi1InputCallback.h"
#include "Push2DisplayRenderer.h"
#include "FpIRenderMedium.h"

using namespace push2device;

const std::string Push2Device::PUSH2_USB_MIDI_DEVICE_NAME = "Ableton Push 2:Ableton Push 2 MIDI 1"; 


Push2Device::Push2Device() :
    m_pInputCallback(new Midi1InputCallback( m_encoderLayer, m_buttonLayer, m_button3dLayer, m_touchSurfaceLayer, m_ledColormap ) ),
    m_pDisplayRenderer(new DisplayRenderer()),
    m_pFrameBufRenderer(new fp::FrameBufRendererMedium<DisplayRenderer>(*m_pDisplayRenderer))
{
    midi::PortNotifiers::instance().inputs.registerNewPortCb([this](rtmidiadapt::PortIndex i, const rtmidiadapt::DeviceOnUsbPort& devOnUsbPort){
        if(PUSH2_USB_MIDI_DEVICE_NAME == devOnUsbPort.getDeviceName())
        {
            std::cout << "New input " << i << " : " << devOnUsbPort << std::endl;
            std::unique_ptr<midi::UsbMidiIn> pMidiMedium(new midi::UsbMidiIn);
            if(!pMidiMedium->openPort(i))
            {
                return;
            }
            m_pMidiInput.reset( new midi::Midi1Input(std::move(pMidiMedium)) );
            m_pMidiInput->registerMidiInCbIf(m_pInputCallback.get());
        }
    });
    midi::PortNotifiers::instance().inputs.registerRemovedPortCb([this](const rtmidiadapt::DeviceOnUsbPort& devOnUsbPort){
        if(PUSH2_USB_MIDI_DEVICE_NAME == devOnUsbPort.getDeviceName())
        {
            std::cout << "Removed input " << devOnUsbPort << std::endl;
            m_pMidiInput.reset();
        }
    });
    midi::PortNotifiers::instance().outputs.registerNewPortCb([this](rtmidiadapt::PortIndex i, const rtmidiadapt::DeviceOnUsbPort& devOnUsbPort){
        if(PUSH2_USB_MIDI_DEVICE_NAME == devOnUsbPort.getDeviceName())
        {
            std::cout << "New output " << i << " : " << devOnUsbPort << std::endl;
            std::unique_ptr<midi::UsbMidiOut> pMidiMedium(new midi::UsbMidiOut);
            if(!pMidiMedium->openPort(i))
            {
                return;
            }
            m_pMidiOutput.reset( new midi::Midi1Output(std::move(pMidiMedium)) );

            static const uint8_t SET_AFTERTOUCH_MODE = 0x1E;
            static const uint8_t AFTERTOUCH_MODE_POLYPHONIC = 0x01;
            const std::vector<uint8_t> sysexMsg1 = {0xF0, 0x00, 0x21, 0x1D, 0x01, 0x01, SET_AFTERTOUCH_MODE, AFTERTOUCH_MODE_POLYPHONIC, 0xF7};
            m_pMidiOutput->sysEx(sysexMsg1);

            setGlobalLedGBrightness(127);
            setTouchStripConfiguration();

            for(uint8_t colorIndex = 0; colorIndex <= 127; ++colorIndex)
            {
                static const uint8_t GET_COLORPALETTE_ENTRY = 0x04;
                const std::vector<uint8_t> sysexMsg = {0xF0, 0x00, 0x21, 0x1D, 0x01, 0x01, GET_COLORPALETTE_ENTRY, colorIndex, 0xF7};
                m_pMidiOutput->sysEx(sysexMsg);
            }
        }
    });
    midi::PortNotifiers::instance().outputs.registerRemovedPortCb([this](const rtmidiadapt::DeviceOnUsbPort& devOnUsbPort){
        if(PUSH2_USB_MIDI_DEVICE_NAME == devOnUsbPort.getDeviceName())
        {
            std::cout << "Removed output " << devOnUsbPort << std::endl;
            m_pMidiOutput.reset();
        }
    });
}

Push2Device::~Push2Device()
{
    // makes std::unique_ptr happy 
}

bool Push2Device::init(uint32_t timeoutMs)
{
    return m_pInputCallback->waitUntilSysexAnswersReceived(timeoutMs);
}

fp::IRenderMedium* Push2Device::getRenderMedium(const fp::Widget& w)
{
    return m_pFrameBufRenderer.get();
}

void Push2Device::registerCB(typename fp::Button::CallbackIf& cb, const fp::Widget& w)
{
    m_buttonLayer.registerCB(cb, w);
}

void Push2Device::registerCB(typename fp::Button3d::CallbackIf& cb, const fp::Widget& w)
{
    m_button3dLayer.registerCB(cb, w);
}

void Push2Device::registerCB(typename fp::Encoder::CallbackIf& cb, const fp::Widget& w)
{
    m_encoderLayer.registerCB(cb, w);
}

void Push2Device::registerCB(typename fp::TouchSurface::CallbackIf& cb, const fp::Widget& w)
{
    m_touchSurfaceLayer.registerCB(cb, w);
}

void Push2Device::unRegisterCB(typename fp::Button::CallbackIf& cb, const fp::Widget& w)
{
    m_buttonLayer.unRegisterCB(cb, w);
}

void Push2Device::unRegisterCB(typename fp::Button3d::CallbackIf& cb, const fp::Widget& w)
{
    m_button3dLayer.unRegisterCB(cb, w);
}

void Push2Device::unRegisterCB(typename fp::Encoder::CallbackIf& cb, const fp::Widget& w)
{
    m_encoderLayer.unRegisterCB(cb, w);
}

void Push2Device::unRegisterCB(typename fp::TouchSurface::CallbackIf& cb, const fp::Widget& w)
{
    m_touchSurfaceLayer.unRegisterCB(cb, w);
}

void Push2Device::setLed(const fp::Widget& widget, const fp::Led::ColorRGB& rgb)
{
    if(fp::Push2Topology::Led::eBtnSilLed == widget.id)
    {
       const uint8_t note = 92 - (widget.coord.y * 8) + widget.coord.x;
       m_pMidiOutput->noteOn(0x01, note, rgb2index(rgb));
    }
    else if(fp::Push2Topology::Led::eTouchSurfaceLed == widget.id)
    {
        const auto dimX = fp::Push2Topology::Led::getDim(static_cast<fp::Push2Topology::Led::Id>(widget.id)).x;
        m_pMidiOutput->pitchBend(1, (widget.coord.x * 0x4000 / dimX) - 0x2000);
    }
    else
    {
        uint8_t cc = 0;
        uint8_t colIdx = 0;
        switch(widget.id)
        {
            case fp::Push2Topology::Led::eLedFixedLength:   cc =  90; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedPlay:          cc =  85; colIdx = rgb2index(rgb); break; // color
            case fp::Push2Topology::Led::eLedSession:       cc =  51; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedStopClip:      cc =  29; break; // color
            case fp::Push2Topology::Led::eLedRepeat:        cc =  56; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedSolo:          cc =  61; break; // color
            case fp::Push2Topology::Led::eLedMetronome:     cc =   9; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedDownArrow:     cc =  47; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedConvert:       cc =  35; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedQuantize:      cc = 116; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedUser:          cc =  59; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eTouchSurfaceLed:  return;
            case fp::Push2Topology::Led::eLedUpArrow:       cc =  46; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedAddTrack:      cc =  53; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedAccent:        cc =  57; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedShift:         cc =  49; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedSetup:         cc =  30; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedNote:          cc =  50; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedMix:           cc = 112; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedLeftArrow:     cc =  44; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedDevice:        cc = 110; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedNew:           cc =  87; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eBtnSilLed:        return;          // color
            case fp::Push2Topology::Led::eLedTapTempo:      cc =   3; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedRightArrow:    cc =  45; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedOctaveDown:    cc =  54; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedPageLeft:      cc =  62; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedRecord:        cc =  86; colIdx = rgb2index(rgb); break; // color
            case fp::Push2Topology::Led::eLedUndo:          cc = 119; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedMute:          cc =  60; colIdx = rgb2index(rgb); break; // color
            case fp::Push2Topology::Led::eLedDuplicate:     cc =  88; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedPageRight:     cc =  63; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedOctaveUp:      cc =  55; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedClip:          cc = 113; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedAddDevice:     cc =  52; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedBrowse:        cc = 111; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedScale:         cc =  58; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedDelete:        cc = 118; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedSel:           cc =  43 - widget.coord.x; colIdx = rgb2index(rgb); break; // color
            case fp::Push2Topology::Led::eLedLayout:        cc =  31; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedAutomate:      cc =  89; colIdx = rgb2grey(rgb);  break; // color
            case fp::Push2Topology::Led::eLedT:             cc = 102 + widget.coord.x; colIdx = rgb2index(rgb); break; // color
            case fp::Push2Topology::Led::eLedB:             cc =  20 + widget.coord.x; colIdx = rgb2index(rgb); break; // color
            case fp::Push2Topology::Led::eLedMaster:        cc =  28; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedSelect:        cc =  48; colIdx = rgb2grey(rgb);  break;
            case fp::Push2Topology::Led::eLedDoubleLoop:    cc = 117; colIdx = rgb2grey(rgb);  break;
            default:
                break; 
        }
        m_pMidiOutput->controlParameter(1, cc, static_cast<uint8_t>(colIdx));
    }
}

fp::Button::PressState Push2Device::getButtonState(const fp::Widget& w) const
{
    const auto pValHolder = m_buttonLayer.get(w);
    if(!pValHolder)
    {
        return fp::Button::PressState::Released;
    }
    return pValHolder->pressState.value();
}

uint8_t Push2Device::rgb2grey(const fp::Led::ColorRGB& rgb)
{
    return (rgb.r + rgb.g + rgb.b) / 6;
}

uint8_t Push2Device::rgb2index(const fp::Led::ColorRGB& rgb) const
{
    uint32_t minDistance = -1;
    uint8_t indexAtMin = 0;
    for(uint8_t i = 0; i < LedColorMap::SIZE; ++i)
    {
        auto& data = m_ledColormap.get(i);
        if(!data.isValid)
        {
            continue;
        }
        const uint32_t dist = (data.r - rgb.r)*(data.r - rgb.r) +
                              (data.g - rgb.g)*(data.g - rgb.g) +
                              (data.b - rgb.b)*(data.b - rgb.b);
        if(0 == dist)
        {
            return i;
        }
        if(dist < minDistance)
        {
            minDistance = dist;
            indexAtMin = i;
        }
    }
    return indexAtMin;
}

void Push2Device::setGlobalLedGBrightness(uint8_t level)
{
   if(m_pMidiOutput)
   {
        static const uint8_t SET_GLOBAL_LED_BRIGHTNESS = 0x06;
        if(level > 127) level = 127;
        const std::vector<uint8_t> sysexMsg1 = {0xF0, 0x00, 0x21, 0x1D, 0x01, 0x01, SET_GLOBAL_LED_BRIGHTNESS, level, 0xF7};
        m_pMidiOutput->sysEx(sysexMsg1); 
   } 
}

void Push2Device::setTouchStripConfiguration()
{
   if(m_pMidiOutput)
   {
        static const uint8_t SET_TOUCHSTRIP_CONFIGURATION = 0x17;
        enum Offsets
        {
            eLedsControlledBy = 0,
            eHostSends        = 1,
            eValuesSentAs     = 2,
            eLEDsShow         = 3,
            eBarStartsAt      = 4,
            eDoAutoreturn     = 5,
            eAutoreturnTo     = 6
        };
        enum Options
        {
            oPush2     = 0, oHost     = 1,
            oValues    = 0, oSysex    = 1,
            oPitchBend = 0, oModWheel = 1,
            oBar       = 0, oPoint    = 1,
            oBottom    = 0, oCenter   = 1,
            oNo        = 0, oYes      = 1
        };
        static const uint8_t TOUCHSTRIP_CONFIGURATION = oHost      << eLedsControlledBy |
                                                        oValues    << eHostSends        |
                                                        oPitchBend << eValuesSentAs     |
                                                        oPoint     << eLEDsShow         |
                                                        oBottom    << eBarStartsAt      |
                                                        oNo        << eDoAutoreturn     |
                                                        oBottom    << eAutoreturnTo;

        const std::vector<uint8_t> sysexMsg = {0xF0, 0x00, 0x21, 0x1D, 0x01, 0x01, SET_TOUCHSTRIP_CONFIGURATION, TOUCHSTRIP_CONFIGURATION, 0xF7};
        m_pMidiOutput->sysEx(sysexMsg); 
   } 
}