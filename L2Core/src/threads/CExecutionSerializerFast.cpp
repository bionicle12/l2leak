#include "l2core/threads/CExecutionSerializerFast.h"

#include <stdio.h>

// L2NPC inlined in CIOSocket c.tor
CExecutionSerializerFast::CExecutionSerializerFast()
    : m_consumeIndex(0)
    , m_writeIndex(0)
    , m_size(0)
    , m_threadIndex(-1)
    , field_24(0)
{
    ::memset(m_parameters, 0, sizeof(m_parameters));
    ::memset(m_executors, 0, sizeof(m_executors));
}
