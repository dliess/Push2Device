#ifndef PUSH2_DEVICE_COMPL_H
#define PUSH2_DEVICE_COMPL_H

#include "Push2Device.h"
#include "UsbMidiInputPortListProvider.h"
#include "UsbMidiOutputPortListProvider.h"
#include "UsbMidiPortNotifier.h"


namespace Push2
{


class Push2DeviceCompl : public Push2Device
{
public:
    Push2DeviceCompl();
    bool init();
    void updateUsbPortState();
private:
    midi::InputPortListProvider                      m_inProvider;
    midi::OutputPortListProvider                     m_outProvider;
    midi::PortNotifier<midi::InputPortListProvider>  m_midiInputs;
    midi::PortNotifier<midi::OutputPortListProvider> m_midiOutputs;
};

} // namespace Push2
#endif