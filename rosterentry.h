#ifndef __REDHARE__ROSTERENTRY__H__
#define __REDHARE__ROSTERENTRY__H__

#include <QtGlobal>
#include <QObject>

class RosterEntry: public QObject
{
    Q_OBJECT
public:
    RosterEntry(quint64 uid): uid_(uid) {}
    quint64 uid() const { return uid_; }
    QString name() const { return name_; }
    QString intro() const { return intro_; }
    QString group() const { return group_; }
    QString photo() const { return photo_; }
public slots:
    void setName(const QString &name);
    void setIntro(const QString &intro);
    void setGroup(const QString &group);
    void setPhoto(const QString &filename);
signals:
    void sigNameChanged(const QString &name);
    void sigIntroChanged(const QString &intro);
    void sigGroupChanged(const QString &group);
    void sigPhotoChanged(const QString &filename);
private:
    const quint64 uid_;
    QString name_;
    QString intro_;
    QString group_;
    QString photo_;
};

#endif // __REDHARE__ROSTERENTRY__H__

