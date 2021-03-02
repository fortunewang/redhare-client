#include "rostermanager.h"
#include "rosterentry.h"

/**
 * @class RosterManager
 * @brief RosterManager类用于管理所有的联系人。
 *
 * RosterManager是单例类。其唯一实例通过静态函数RosterManager::instance()获得。
 * RosterManager以uid为索引，管理用户所有的联系人。
**/

RosterManager* RosterManager::instance()
{
    static RosterManager manager;
    return &manager;
}

void RosterManager::addEntry(RosterEntry *entry)
{
    this->removeEntry(entry->uid());
    entry->setParent(this);
    entries_.insert(entry->uid(), entry);
    emit sigEntryAdded(entry);
}

void RosterManager::removeEntry(quint64 uid)
{
    RosterEntry *entry = entries_.take(uid);
    if(entry != nullptr)
    {
        emit sigEntryRemoved(entry);
        entry->deleteLater();
    }
}

RosterEntry* RosterManager::entry(quint64 uid)
{
    return entries_.value(uid);
}

QList<RosterEntry*> RosterManager::entries()
{
    return entries_.values();
}

void RosterManager::addGroup(const QString &group)
{
    if(!groups_.contains(group))
    {
        groups_.insert(group);
        emit sigGroupAdded(group);
    }
}

void RosterManager::removeGroup(const QString &group)
{
    if(groups_.remove(group))
    {
        emit sigGroupRemoved(group);
    }
}

bool RosterManager::hasGroup(const QString &group)
{
    return groups_.contains(group);
}

QList<QString> RosterManager::groups()
{
    return groups_.values();
}
