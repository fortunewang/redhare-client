#include "rostermanager.h"
#include "rosterentry.h"

/**
 * @class RosterManager
 * @brief RosterManager�����ڹ������е���ϵ�ˡ�
 *
 * RosterManager�ǵ����ࡣ��Ψһʵ��ͨ����̬����RosterManager::instance()��á�
 * RosterManager��uidΪ�����������û����е���ϵ�ˡ�
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
    QHash<quint64,RosterEntry*>::iterator it = entries_.find(uid);
    if(it != entries_.end())
    {
        RosterEntry *entry = it.value();
        entries_.erase(it);
        emit sigEntryRemoved(entry);
        entry->deleteLater();
    }
}

RosterEntry* RosterManager::entry(quint64 uid)
{
    QHash<quint64,RosterEntry*>::iterator it = entries_.find(uid);
    if(it != entries_.end())
    {
        return it.value();
    }
    return 0;
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