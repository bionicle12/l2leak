#pragma once

enum ItemChangeScope
{
    ItemChangeScope_Unknown = -1,
    ItemChangeScope_Added = 1,
    ItemChangeScope_Increased = 2,
    ItemChangeScope_Decreased = 3,
    ItemChangeScope_Deleted = 4,
    ItemChangeScope_Fee = 5
};
