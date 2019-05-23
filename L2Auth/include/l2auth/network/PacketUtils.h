#pragma once

#include <cstdarg>
#include <l2core/utils/cstdint_support.h>

namespace PacketUtils
{

int Assemble(uint8_t* buf, int bufLen, const char* format, ...);
int VAssemble(uint8_t* buf, int bufLen, const char* format, va_list ap);  // L2AuthD 0x0043A690
const unsigned char* Disassemble(const unsigned char* packet, const char* format, ...);

}  // namespace PacketUtils
