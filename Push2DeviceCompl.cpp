#include "Push2DeviceCompl.h"

using namespace Push2;

Push2DeviceCompl::Push2DeviceCompl() :
    Push2Device(m_midiInputs, m_midiOutputs),
    m_midiInputs(m_inProvider),
    m_midiOutputs(m_outProvider)
{
}

bool Push2DeviceCompl::init()
{
    if(!m_inProvider.init())
    {
        return false;
    }
    if(!m_outProvider.init())
    {
        return false;
    }
    return true;
}

void Push2DeviceCompl::updateUsbPortState()
{
    m_midiInputs.update();
    m_midiOutputs.update();
}
