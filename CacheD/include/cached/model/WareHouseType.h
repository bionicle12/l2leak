#pragma once

enum WareHouseType
{
    WareHouseType_Uninitialized = -1,
    WareHouseType_Inventory = 0,
    WareHouseType_CharWarehouse = 1,  // warehouse/freight, depending on ident
    WareHouseType_Pledge = 2,
    WareHouseType_Castle = 3,
    WareHouseType_Manor = 4,
    WareHouseType_Pet = 5,
    WareHouseType_Mail = 6,  // Glory Days

    // Some storage for items, seized/unseized via admin API. Not available from gameplay
    WareHouseType_Seized_CharWarehouse = 1001,
    WareHouseType_Seized_Pledge = 1002,
    WareHouseType_Seized_Castle = 1003,
    WareHouseType_Seized_Pet = 1005,
    WareHouseType_Last
};
