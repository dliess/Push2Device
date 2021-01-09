#include <chrono> // std::chrono::seconds
#include <iostream>
#include <thread> // std::this_thread::sleep_for

#include "Push2Device.h"

struct TouchStripCB : public fp::TouchSurface::CallbackIf
{
   void onTouchStateChanged(fp::TouchSurface::TouchState touchState,
                            const fp::Widget& w) override
   {
      std::cout << "onTouchStateChanged: " << touchState << "\n";
   }
   void onPositionEvents(const fp::TouchSurface::PressData& data,
                         const fp::Widget& w) override
   {
      std::cout << "onPositionEvents: pos" << data.pos.x << " pressure: " << data.pressure << "\n";
   }
};

int main()
{
   try // TODO: what functions need this?
   {
      if (!midi::PortNotifiers::instance().init()) // TODO
      {
         return -1;
      }
      push2device::Push2Device push2Device;
      midi::PortNotifiers::instance().update();

      if (!push2Device.init(3000))
      {
         std::cout << "push2Device.init(3000) failed\n";
         return 1;
      }
      push2Device.reserveLed(
         nullptr,
         {fp::Push2Topology::Led::eBtnSilLed, {fp::IdxAll, fp::IdxAll}},
         fp::Led::getRGB(fp::Led::Red));

      TouchStripCB touchStripCB;
      push2Device.registerCB(touchStripCB,
                             fp::Push2Topology::TouchSurface::eTouchStrip);

      std::this_thread::sleep_for(std::chrono::milliseconds(500));

      for (uint8_t x = 0; x < fp::Push2Topology::Led::getDim(
                                 fp::Push2Topology::Led::eTouchSurfaceLed)
                                 .x;
           ++x)
      {
         push2Device.setLed({fp::Push2Topology::Led::eTouchSurfaceLed, {x, 0}},
                            fp::Led::getRGB(fp::Led::White));
         push2Device.setLed(
            {fp::Push2Topology::Led::eBtnSilLed,
             {static_cast<uint8_t>(x % 8), static_cast<uint8_t>(x / 8)}},
            fp::Led::getRGB(fp::Led::DarkBlue));

         std::this_thread::sleep_for(std::chrono::milliseconds(500));
      }
      return 0;
   }
   catch (const std::exception& e)
   {
      std::cout << "Exception caught: " << e.what() << "\n";
      return 1;
   }
}