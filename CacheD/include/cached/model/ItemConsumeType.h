#pragma once

enum ItemConsumeType
{
    ConsumeType_Invalid = 0,  // TODO: check usage.. in some cases it's like charge, at least in logs. Long sword is also this Type..
    ConsumeType_Normal = 1,
    ConsumeType_Asset = 2,   // like Crystal C-grade
    ConsumeType_Charge = 3,  // adena
    ConsumeType_Stackable = 4
};
