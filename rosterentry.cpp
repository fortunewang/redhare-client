#include "rosterentry.h"

/**
 * @class RosterEntry
 * @brief RosterEntry类表示一个联系人，保存有联系人的uid、姓名等数据。
 *
 * RosterEntry用于表示用户的一个联系人，联系人的所有数据（uid、姓名等）都保存在
 * RosterEntry的实例中。在修改联系人数据时，RosterEntry的实例会emit响应的信号。
 * 通常来说，RosterEntry的实例应当通过new运算符构造，
 * 并调用RosterManager::instance()->addEntry(entry)添加到所有联系人中。
**/

/**
 * @fn RosterEntry::RosterEntry(quint64 uid);
 * @brief 构造一个新的联系人，并指定其uid。其他数据取默认值。
**/

void RosterEntry::setName(const QString &name)
{
    name_ = name;
    emit sigNameChanged(name);
}

void RosterEntry::setIntro(const QString &intro)
{
    intro_ = intro;
    emit sigIntroChanged(intro);
}

void RosterEntry::setGroup(const QString &group)
{
    group_ = group;
    emit sigGroupChanged(group);
}

void RosterEntry::setPhoto(const QString &filename)
{
    photo_ = filename;
    emit sigPhotoChanged(filename);
}
