#include "Push2UsbDisplay.h"
#include "FinalAction.h"
#include <iostream>

// ----- Time measuring -----
#include "CyclicDataOutputterThread.h"
#include "Histogram.h"
#include "Measurer.h"
#include "OutputterDestinationsZmq.h"
using TenthMs = std::chrono::duration<int, std::ratio<1, 10000>>;
using DataHolderTenthMs = TimeMeasure::Histogram<TenthMs>;

template <unsigned int Id>
using MeasurerTenthMs = TimeMeasure::Measurer<Id, DataHolderTenthMs>;

TimeMeasure::CyclicDataOutputterThread<DataHolderTenthMs,
                                       TimeMeasure::Destination::Zmq>
    outThreadZmq({
        &MeasurerTenthMs<0>::instance().dataHolder()
    });
// --------------------------


using namespace push2device;

UsbDisplay::UsbDisplay() :
    m_pContext(nullptr),
    m_pDevice(nullptr)
{}

UsbDisplay::~UsbDisplay()
{
    if(m_pDevice)
    {
        libusb_release_interface(m_pDevice, 0);
        libusb_close(m_pDevice);
        m_pDevice = nullptr;
    }
    if(m_pContext)
    {
        libusb_exit(m_pContext);
        m_pContext = nullptr;
    }
}

bool UsbDisplay::init()
{
    int ret = libusb_init(&m_pContext); 
    if(0 != ret)
    {
        std::cerr << "libusb_init failed, ret: " << ret << std::endl;
        return false;
    }
    auto cleanupContext = finally([this](){
        libusb_exit(m_pContext);
        m_pContext = nullptr;
    });
    // to make this work as non-root:
    // create in /etc/udev/rules.d/60-push2.rules
    // with content: SUBSYSTEM=="usb", ATTR{idProduct}=="1967", ATTR{idVendor}=="2982", MODE="0666"
    m_pDevice = libusb_open_device_with_vid_pid(m_pContext, 0x2982, 0x1967);
    if (!m_pDevice)
    {
        std::cerr << "libusb_open_device_with_vid_pid() failed" << std::endl;
        return false;
    }
    auto cleanupDevice = finally([this](){
        libusb_release_interface(m_pDevice, 0);
        libusb_close(m_pDevice);
        m_pDevice = nullptr;
    });
    switch(libusb_claim_interface(m_pDevice, 0))
    {
        case 0:
        {
            // Success
            break;
        }
        case LIBUSB_ERROR_NOT_FOUND:
        {
            std::cerr << "libusb_init failed : the requested interface does not exist" << std::endl;
            return false;
        }
        case LIBUSB_ERROR_BUSY:
        {
            std::cerr << "libusb_init failed : a program or driver has claimed the interface" << std::endl;
            return false;
        }
        case LIBUSB_ERROR_NO_DEVICE:
        {
            std::cerr << "libusb_init failed : the device has been disconnected " << std::endl;
            return false;
        }
        default:
        {
            std::cerr << "libusb_init failed" << std::endl;
            return false;
        }
    }
    cleanupContext.disable();
    cleanupDevice.disable();
    
    MeasurerTenthMs<0>::instance().dataHolder().setHistogramRange(1000);
    outThreadZmq.destination().bind("tcp://*:12342");
    outThreadZmq.startThread(500);

    return true;
}

// TODO: remove this assertion later
#include <cassert>
bool UsbDisplay::sendFrameToDisplay(const FrameBuffer<uint16_t>& frameBuffer)
{
    MeasurerTenthMs<0>::Guard guard;
    static uint8_t header[] = { 0xEF, 0xCD, 0xAB, 0x89, 0x00, 0x00, 0x00, 0x00,
                                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    int transferred = 0;

    // Transfer header which indicates start of image transfer
    int ret = 0;
    ret = libusb_bulk_transfer(m_pDevice,
                               0x01 | LIBUSB_ENDPOINT_OUT,
                               header,
                               sizeof(header),
                               &transferred,
                               3000);
    if(!handleBulkTransferRet(ret))
    {
        return false;
    }

    // TODO: remove this assertion later
    assert(20 * 16384 == frameBuffer.size());

    // Transfer image
    ret = libusb_bulk_transfer(m_pDevice,
                               0x01 | LIBUSB_ENDPOINT_OUT, 
                               const_cast<uint8_t*>(frameBuffer.getRawBuffer()),
                               frameBuffer.size(), // 20 * 16384, 
                               &transferred,
                               3000);
    if(!handleBulkTransferRet(ret))
    {
        return false;
    }
    return true;
}

bool UsbDisplay::handleBulkTransferRet(int ret)
{
    switch(ret)
    {
        case 0:
        {
            return true;
        }
        case LIBUSB_ERROR_TIMEOUT:
        {
            std::cerr << "handleBulkTransferRet error: transfer timed out" << std::endl;
            return false;
        }
        case LIBUSB_ERROR_PIPE:
        {
            std::cerr << "handleBulkTransferRet error: the control request was not supported" << std::endl;
            return false;
        }
        case LIBUSB_ERROR_OVERFLOW:
        {
            std::cerr << "handleBulkTransferRet error: the device offered more data" << std::endl;
            return false;
        }
        case LIBUSB_ERROR_NO_DEVICE:
        {
            std::cerr << "handleBulkTransferRet error: the device has been disconnected" << std::endl;
            return false;
        }
        default:
        {
            std::cerr << "handleBulkTransferRet error" << std::endl;
            return false;
        }
    }
}
