#ifndef PUSH_2_DEVICE_H
#define PUSH_2_DEVICE_H

#include "Push2LedColorMap.h"
#include "FpButton.h"
#include "FpButton3d.h"
#include "FpEncoder.h"
#include "FpTouchSurface.h"
#include "FpLed.h"
#include "Push2Topology.h"
#include "FpInputCallbackLayer.h"
#include "FpRenderSwitch.h"
#include "FpLedSceneHandler.h"
#include "Midi1Input.h"
#include "Midi1Output.h"

#include <memory>
#include <string>

namespace fp
{
    class IRenderMedium;
}

namespace push2device
{
    class Midi1InputCallback;
}
namespace push2device
{
    class DisplayRenderer;
}

namespace push2device
{

class Push2Device : public fp::Button::IProvider,
                    public fp::Button3d::IProvider,
                    public fp::Encoder::IProvider,
                    public fp::TouchSurface::IProvider,
                    public fp::Led::ISetter,
                    public fp::LedSceneHandler<Push2Device, fp::Push2Topology::Led, 8>
{
public:
    Push2Device();
    ~Push2Device();  // makes std::unique_ptr happy
    [[nodiscard]] bool init(uint32_t timeoutMs);
    virtual void registerCB(typename fp::Button::CallbackIf& cb, const fp::Widget& w) override;
    virtual void registerCB(typename fp::Button3d::CallbackIf& cb, const fp::Widget& w) override;
    virtual void registerCB(typename fp::Encoder::CallbackIf& cb, const fp::Widget& w) override;
    virtual void registerCB(typename fp::TouchSurface::CallbackIf& cb, const fp::Widget& w) override;

    virtual void unRegisterCB(typename fp::Button::CallbackIf& cb, const fp::Widget& w) override;
    virtual void unRegisterCB(typename fp::Button3d::CallbackIf& cb, const fp::Widget& w) override;
    virtual void unRegisterCB(typename fp::Encoder::CallbackIf& cb, const fp::Widget& w) override;
    virtual void unRegisterCB(typename fp::TouchSurface::CallbackIf& cb, const fp::Widget& w) override;

    // TODO: should be private
    void setLed(const fp::Widget& w, const fp::Led::ColorRGB& colorRGB) override;
    
    fp::Button::PressState getButtonState(const fp::Widget& w) const;
    fp::Encoder::TouchState getEncoderTouchState(const fp::Widget& w) const;
    void setEncoderDivider(const fp::Widget& w, unsigned int divider) noexcept;

    using DisplayTopology = typename fp::Push2Topology::Display;

    using ButtonLayer   = fp::InputCallbackLayer<typename fp::Push2Topology::Button>;
    using Button3dLayer = fp::InputCallbackLayer<typename fp::Push2Topology::Button3d>;
    using EncoderLayer  = fp::InputCallbackLayer<typename fp::Push2Topology::Encoder>;
    using TouchSurfaceLayer = fp::InputCallbackLayer<typename fp::Push2Topology::TouchSurface>;

    fp::IRenderMedium* getRenderMedium(const fp::Widget& w);

    void setGlobalLedGBrightness(uint8_t level);
private:
    std::unique_ptr<midi::Midi1Input<>>  m_pMidiInput;
    std::unique_ptr<midi::Midi1Output> m_pMidiOutput;

    std::unique_ptr<Midi1InputCallback> m_pInputCallback;

    ButtonLayer        m_buttonLayer;
    Button3dLayer      m_button3dLayer;
    EncoderLayer       m_encoderLayer;
    TouchSurfaceLayer  m_touchSurfaceLayer;

    LedColorMap        m_ledColormap;

    std::unique_ptr<DisplayRenderer>                             m_pDisplayRenderer;
    std::unique_ptr<fp::FrameBufRendererMedium<DisplayRenderer>> m_pFrameBufRenderer;

    static const std::string PUSH2_USB_MIDI_DEVICE_LEGACY_NAME;
    static const std::string PUSH2_USB_MIDI_DEVICE_NAME;

    static uint8_t rgb2grey(const fp::Led::ColorRGB& rgb);
    uint8_t rgb2index(const fp::Led::ColorRGB& rgb) const;
    void setTouchStripConfiguration();
};

} // namespace push2device
#endif