#pragma once

#include <cstdarg>
#include <l2core/utils/cstdint_support.h>

namespace PacketUtils
{

int Assemble(uint8_t* buf, int bufLen, const char* format, ...);                         // L2CacheD 0x00480900, L2NPC 0x0047AAA0
int VAssemble(uint8_t* buf, int bufLen, const char* format, va_list ap);                 // L2LogD 0x00408FA0, L2CacheD 0x0047FD40, L2NPC 0x0047AE30
const unsigned char* Disassemble(const unsigned char* packet, const char* format, ...);  // L2LogD 0x00408DC0, L2CacheD 0x0047FB50
const char* ReadSocketArgs(const char* packet, const char* format, ...);                 // L2CacheD 0x004153A0

}  // namespace PacketUtils
