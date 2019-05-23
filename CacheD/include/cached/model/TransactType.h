#pragma once

enum TransactType
{
    TransactType_Invalid = 0,
    TransactType_RollbackChanges = 1,
    TransactType_RollbackCreation = 2
};
