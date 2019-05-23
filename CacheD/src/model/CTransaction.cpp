#include "cached/model/CTransaction.h"

#include "l2core/logger/CLog.h"
#include "l2core/utils/dbg/CallStack.h"
#include "l2core/utils/dbg/StackGuard.h"

// L2CacheD 0x0047BDA0
CTransaction::CTransaction()
    : m_success(true)
    , m_items()
{
    guard(L"CTransaction::CTransaction()");
    unguard();
}

// L2CacheD 0x0046E310
CTransaction::~CTransaction()
{
    guard(L"CTransaction::~CTransaction()");

    for (BackupMap::const_iterator it = m_items.begin(); it != m_items.end(); ++it)
    {
        CItem* rollbackItem = it->first;
        CItem* changedItem = it->second;

        if (m_success)
        {
            changedItem->CommitTransation(rollbackItem);
        }
        else
        {
            changedItem->CancelTransation(rollbackItem);
        }

        changedItem->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, false);
        rollbackItem->Release(__FILE__, __LINE__, ORT_FUNCTION_LOCAL, false);
    }

    unguard();
}

// L2CacheD 0x004663F0
void CTransaction::SetRollback()
{
    guard(L"void CTransaction::SetRollback()");
    m_success = false;
    unguard();
}

// L2CacheD 0x0046DCB0
bool CTransaction::ToUpdate(CItemSP itemToUpdate)
{
    guard(L"bool CTransaction::AddItem(CItemSP spItem)");

    if (itemToUpdate->Deleted())
    {
        g_winlog.Add(LOG_ERROR, L"User try change deleted item.");
        CallStack::ReportCallStack();
        unguard();
        return false;
    }

    // checking, that item with such ID does not exist
    for (BackupMap::const_iterator it = m_items.begin(); it != m_items.end(); ++it)
    {
        CItem* changedItem = it->second;
        if ((changedItem->ItemID() != 0) && (changedItem->ItemID() == itemToUpdate->ItemID()))
        {
            unguard();
            return false;
        }
    }

    itemToUpdate->SetTransation();
    CItemSP rollbackItem = itemToUpdate->Copy();
    rollbackItem->SetTrasactMode(TransactType_RollbackChanges);

    itemToUpdate->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
    rollbackItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

    m_items.insert(std::make_pair(rollbackItem.get(), itemToUpdate.get()));

    unguard();
    return true;
}

// L2CacheD 0x0046DF50
bool CTransaction::ToCreate(CItemSP itemToCreate)
{
    guard(L"bool CTransaction::AddItem(CItemSP spItem)");

    itemToCreate->SetTransation();
    CItemSP rollbackItem = itemToCreate->Copy();
    rollbackItem->SetTrasactMode(TransactType_RollbackCreation);

    itemToCreate->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);
    rollbackItem->AddRef(__FILE__, __LINE__, ORT_FUNCTION_LOCAL);

    m_items.insert(std::make_pair(rollbackItem.get(), itemToCreate.get()));

    unguard();
    return true;
}
