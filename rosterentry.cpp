#include "rosterentry.h"

/**
 * @class RosterEntry
 * @brief RosterEntry���ʾһ����ϵ�ˣ���������ϵ�˵�uid�����������ݡ�
 *
 * RosterEntry���ڱ�ʾ�û���һ����ϵ�ˣ���ϵ�˵��������ݣ�uid�������ȣ���������
 * RosterEntry��ʵ���С����޸���ϵ������ʱ��RosterEntry��ʵ����emit��Ӧ���źš�
 * ͨ����˵��RosterEntry��ʵ��Ӧ��ͨ��new��������죬
 * ������RosterManager::instance()->addEntry(entry)��ӵ�������ϵ���С�
**/

/**
 * @fn RosterEntry::RosterEntry(quint64 uid);
 * @brief ����һ���µ���ϵ�ˣ���ָ����uid����������ȡĬ��ֵ��
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
