#include "Push2DisplayRenderer.h"
#include "Push2Topology.h"
#include <cstdlib> //exit
#include <iostream>

using namespace push2device;

DisplayRenderer::DisplayRenderer() :
    m_frameBuf({1024, 160})
{
    if(!m_usbDisplay.init())
    {
        std::cerr << "m_usbDisplay.init() failed, exiting ..." << std::endl;
        exit(-1);
    }
}

DisplayRenderer::~DisplayRenderer()
{
}

void DisplayRenderer::drawPixel(const gfx::Coord& coord, const ColorRGB& color)
{
    m_frameBuf.at(coord.x, coord.y) = color.toUint16_BRG565(coord.x, coord.y);
}

void DisplayRenderer::streamToSubWindow(const gfx::Rectangle& subWindow,
                                        const ColorRGB*       pPixelStream)
{
    for(gfx::Pixel subY = 0; subY < subWindow.height(); ++subY)
    {
        for(gfx::Pixel subX = 0; subX < subWindow.width(); ++subX)
        {
            const gfx::Pixel x = subWindow.upperLeft.x + subX;
            const gfx::Pixel y = subWindow.upperLeft.y + subY;
            const auto streamIndex = subX + (subY * subWindow.width());
            m_frameBuf.at(x, y) = pPixelStream[streamIndex].toUint16_BRG565(x, y);
        }
    }
}

void DisplayRenderer::streamFromFramebuf(const gfx::Rectangle&  subWindow,
                                         const gfx::Resolution& resolution,
                                         const ColorRGB*        pFrameBuf)
{
    for(gfx::Pixel subY = 0; subY < subWindow.height(); ++subY)
    {
        for(gfx::Pixel subX = 0; subX < subWindow.width(); ++subX)
        {
            const gfx::Pixel x = subWindow.upperLeft.x + subX;
            const gfx::Pixel y = subWindow.upperLeft.y + subY;
            const auto streamIndex = x + (y * resolution.x);
            m_frameBuf.at(x, y) = pFrameBuf[streamIndex].toUint16_BRG565(x, y);
        }
    }
}

fp::gfx::Resolution DisplayRenderer::getResolution() const
{
    return fp::Push2Topology::Display::getResolution(fp::Push2Topology::Display::Id::eDisplay);
}

void DisplayRenderer::flushFrameBuffer()
{
    m_usbDisplay.sendFrameToDisplay(m_frameBuf);
}
