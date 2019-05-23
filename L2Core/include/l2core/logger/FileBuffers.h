#pragma once

enum FileBuffers
{
    FileBuffers_System = 0x0,
    FileBuffers_In = 0x1,
    FileBuffers_Out = 0x2,
    FileBuffers_Db = 0x3,
    FileBuffers_Audit = 0x4,
    FileBuffers_Error = 0x5,
    FileBuffers_Chat = 0x6,
    FileBuffers_ChatOut = 0x7,
    FileBuffers_BuffersCount = 0x8,
};
