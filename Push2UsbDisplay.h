#ifndef PUSH2_USB_DISPLAY_H
#define PUSH2_USB_DISPLAY_H

#include <libusb-1.0/libusb.h>
#include "FpFrameBuffer.h"

namespace push2device
{

class UsbDisplay
{
public:
    UsbDisplay();
    ~UsbDisplay();
    bool init();
    bool sendFrameToDisplay(const FrameBuffer<uint16_t>& frameBuffer);
private:
    libusb_context       *m_pContext;
    libusb_device_handle *m_pDevice;
    static bool handleBulkTransferRet(int ret);
};

} // Push2Device
#endif