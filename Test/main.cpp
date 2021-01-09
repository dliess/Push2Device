#include <iostream>

#include "Push2Device.h"

int main()
{
   try
   {
      push2device::Push2Device push2Device;
      if (!push2Device.init(3000))
      {
         std::cout << "push2Device.init(3000) failed\n";
         return 1;
      }
      push2Device.setLed({fp::Push2Topology::Led::eBtnSilLed, {0, 0}},
                         fp::Led::getRGB(fp::Led::DarkBlue));
      return 0;
   }
   catch (const std::exception& e)
   {
      std::cout << "Exception caught: " << e.what() << "\n";
      return 1;
   }
}