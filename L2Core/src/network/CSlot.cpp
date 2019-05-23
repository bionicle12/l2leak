#include "l2core/network/CSlot.h"

CSlot::CSlot()
    : m_lock()
{
    m_data.packet = NULL;
}

CSlot::~CSlot()
{
}
