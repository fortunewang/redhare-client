#ifndef __REDHARE__ROSTERMANAGER__H__
#define __REDHARE__ROSTERMANAGER__H__

#include <QtGlobal>
#include <QObject>
#include <QHash>
#include <QSet>

class RosterEntry;

class RosterManager: public QObject
{
    Q_OBJECT
public:
    RosterEntry* entry(quint64 uid);
    QList<RosterEntry*> entries();
    bool hasGroup(const QString &group);
    QList<QString> groups();
    static RosterManager* instance();
signals:
    void sigEntryAdded(RosterEntry*);
    void sigEntryRemoved(RosterEntry*);
    void sigGroupAdded(const QString&);
    void sigGroupRemoved(const QString&);
public slots:
    void addEntry(RosterEntry *entry);
    void removeEntry(quint64 uid);
    void addGroup(const QString &group);
    void removeGroup(const QString &group);
private:
    QSet<QString> groups_;
    QHash<quint64, RosterEntry*> entries_;
    RosterManager() {}
};

#endif // __REDHARE__ROSTERMANAGER__H__

