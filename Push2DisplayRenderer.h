#ifndef PUSH2_DISPLAY_RENDERER_H
#define PUSH2_DISPLAY_RENDERER_H

#include "FpFrameBuffer.h"
#include "Push2UsbDisplay.h"
#include "FpRenderBase.h"
#include "FpGfxTypes.h"
#include <cstdint>

namespace Push2
{

class DisplayRenderer : public fp::RenderBase
{
public:
    DisplayRenderer();
    ~DisplayRenderer(); // needed so it can be used as a std::unique_ptr
    void drawPixel(const gfx::Coord& coord, const ColorRGB& color) override;
    void streamToSubWindow(const gfx::Rectangle& subWindow,
                           const ColorRGB*       pPixelStream) override;
    void streamFromFramebuf(const gfx::Rectangle&  subWindow,
                            const gfx::Resolution& resolution,
                            const ColorRGB*        pFrameBuf) override;
    fp::gfx::Resolution getResolution() const override;
    void flushFrameBuffer();

private:
    FrameBuffer<uint16_t> m_frameBuf;
    UsbDisplay            m_usbDisplay;
};

} // namespace Push2
#endif