#include "localtest.h"

#ifdef REDHARE_LOCALTEST

#include "rosterentry.h"
#include "rostermanager.h"

void rh_localtest_roster()
{
    RosterManager::instance()->addGroup(QStringLiteral("�ҵĺ���"));
    RosterManager::instance()->addGroup(QStringLiteral("��ѧͬѧ"));

    RosterEntry *entry = new RosterEntry(1);
    entry->setGroup(QStringLiteral("�ҵĺ���"));
    entry->setName(QStringLiteral("����άŵ"));
    entry->setIntro(QStringLiteral("��Ҫ����������ϵ��ˣ���Ӧ�ú͵��汣�ֱ�Ҫ�ľ��롣"));
    entry->setPhoto(QStringLiteral("adobeflashplugin.png"));
    RosterManager::instance()->addEntry(entry);

    entry = new RosterEntry(2);
    entry->setGroup(QStringLiteral("�ҵĺ���"));
    entry->setName(QStringLiteral("�°���"));
    entry->setIntro(QStringLiteral("����֣����ǲ�м������Ϊ�飬ȴ�����Լ����ڲ�ͬ��"));
    entry->setPhoto(QStringLiteral("akregator.png"));
    RosterManager::instance()->addEntry(entry);

    entry = new RosterEntry(3);
    entry->setGroup(QStringLiteral("��ѧͬѧ"));
    entry->setName(QStringLiteral("������"));
    entry->setIntro(QStringLiteral("ʫ�˵�������Ӧ�ý�����Ϊ������ʷ�ļ�¼����Ӧ�ó�Ϊ���������ʤ����֧���Ͷ�����"));
    entry->setPhoto(QStringLiteral("checkgmail.png"));
    RosterManager::instance()->addEntry(entry);

    entry = new RosterEntry(4);
    entry->setGroup(QStringLiteral("��ѧͬѧ"));
    entry->setName(QStringLiteral("����"));
    entry->setIntro(QStringLiteral("���˼�������"));
    entry->setPhoto(QStringLiteral("chromium.png"));
    RosterManager::instance()->addEntry(entry);

    entry = new RosterEntry(5);
    entry->setGroup(QStringLiteral("��ѧͬѧ"));
    entry->setName(QStringLiteral("���"));
    entry->setIntro(QStringLiteral("����֮�⣬��֪ҹɫ֮�"));
    entry->setPhoto(QStringLiteral("facebook.png"));
    RosterManager::instance()->addEntry(entry);

    entry = new RosterEntry(6);
    entry->setGroup(QStringLiteral("��ѧͬѧ"));
    entry->setName(QStringLiteral("���¸��"));
    entry->setIntro(QStringLiteral("���������������ǣ��������޽ӽ�������������������������塣"));
    entry->setPhoto(QStringLiteral("goa-account-twitter.png"));
    RosterManager::instance()->addEntry(entry);

    entry = new RosterEntry(7);
    entry->setGroup(QStringLiteral("��ѧͬѧ"));
    entry->setName(QStringLiteral("������"));
    entry->setIntro(QStringLiteral("���Ƕ��������������������Ȼ�����������ǿա�"));
    entry->setPhoto(QStringLiteral("mozilla-firefox.png"));
    RosterManager::instance()->addEntry(entry);

    entry = new RosterEntry(8);
    entry->setGroup(QStringLiteral("��ѧͬѧ"));
    entry->setName(QStringLiteral("����˹̹"));
    entry->setIntro(QStringLiteral("һ���˵ļ�ֵ��Ӧ����������ʲô������Ӧ������ȡ��ʲô��"));
    entry->setPhoto(QStringLiteral("yahoo.png"));
    RosterManager::instance()->addEntry(entry);

    entry = new RosterEntry(9);
    entry->setGroup(QStringLiteral("��ѧͬѧ"));
    entry->setName(QStringLiteral("ʷ����"));
    entry->setIntro(QStringLiteral("����������ǰ�棬��ʵ��һƬ�տ�������ϣ��ʲôҲû�У���ҪҲû�С�"));
    entry->setPhoto(QStringLiteral("mplayer.png"));
    RosterManager::instance()->addEntry(entry);

    entry = new RosterEntry(10);
    entry->setGroup(QStringLiteral("��ѧͬѧ"));
    entry->setName(QStringLiteral("����"));
    entry->setIntro(QStringLiteral("û������˼�������µķ�ʽ���������Ƕ�ô�Ĺ��ϣ�ֵ������äĿ��ȥ���ӡ�"));
    entry->setPhoto(QStringLiteral("sun-java.png"));
    RosterManager::instance()->addEntry(entry);
}

#endif // REDHARE_LOCALTEST
