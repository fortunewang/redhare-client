#include "localtest.h"

#ifdef REDHARE_LOCALTEST

#include "rosterentry.h"
#include "rostermanager.h"

void rh_localtest_roster()
{
    RosterManager::instance()->addGroup(QStringLiteral("我的好友"));
    RosterManager::instance()->addGroup(QStringLiteral("大学同学"));

    RosterEntry *entry = new RosterEntry(1);
    entry->setGroup(QStringLiteral("我的好友"));
    entry->setName(QStringLiteral("卡尔维诺"));
    entry->setIntro(QStringLiteral("想要清楚看见地上的人，就应该和地面保持必要的距离。"));
    entry->setPhoto(QStringLiteral("adobeflashplugin.png"));
    RosterManager::instance()->addEntry(entry);

    entry = new RosterEntry(2);
    entry->setGroup(QStringLiteral("我的好友"));
    entry->setName(QStringLiteral("柯艾略"));
    entry->setIntro(QStringLiteral("很奇怪，我们不屑与他人为伍，却害怕自己与众不同。"));
    entry->setPhoto(QStringLiteral("akregator.png"));
    RosterManager::instance()->addEntry(entry);

    entry = new RosterEntry(3);
    entry->setGroup(QStringLiteral("大学同学"));
    entry->setName(QStringLiteral("福克纳"));
    entry->setIntro(QStringLiteral("诗人的声音不应该仅仅成为人类历史的记录，更应该成为人类存在与胜利的支柱和栋梁。"));
    entry->setPhoto(QStringLiteral("checkgmail.png"));
    RosterManager::instance()->addEntry(entry);

    entry = new RosterEntry(4);
    entry->setGroup(QStringLiteral("大学同学"));
    entry->setName(QStringLiteral("略萨"));
    entry->setIntro(QStringLiteral("他人即地狱。"));
    entry->setPhoto(QStringLiteral("chromium.png"));
    RosterManager::instance()->addEntry(entry);

    entry = new RosterEntry(5);
    entry->setGroup(QStringLiteral("大学同学"));
    entry->setName(QStringLiteral("尼采"));
    entry->setIntro(QStringLiteral("白昼之光，岂知夜色之深。"));
    entry->setPhoto(QStringLiteral("facebook.png"));
    RosterManager::instance()->addEntry(entry);

    entry = new RosterEntry(6);
    entry->setGroup(QStringLiteral("大学同学"));
    entry->setName(QStringLiteral("海德格尔"));
    entry->setIntro(QStringLiteral("向死而生的意义是：当你无限接近死亡，才能深切体会生的意义。"));
    entry->setPhoto(QStringLiteral("goa-account-twitter.png"));
    RosterManager::instance()->addEntry(entry);

    entry = new RosterEntry(7);
    entry->setGroup(QStringLiteral("大学同学"));
    entry->setName(QStringLiteral("王尔德"));
    entry->setIntro(QStringLiteral("我们都生活在阴沟里，但其中依然有人在仰望星空。"));
    entry->setPhoto(QStringLiteral("mozilla-firefox.png"));
    RosterManager::instance()->addEntry(entry);

    entry = new RosterEntry(8);
    entry->setGroup(QStringLiteral("大学同学"));
    entry->setName(QStringLiteral("爱因斯坦"));
    entry->setIntro(QStringLiteral("一个人的价值，应当看他贡献什么，而不应当看他取得什么。"));
    entry->setPhoto(QStringLiteral("yahoo.png"));
    RosterManager::instance()->addEntry(entry);

    entry = new RosterEntry(9);
    entry->setGroup(QStringLiteral("大学同学"));
    entry->setName(QStringLiteral("史铁生"));
    entry->setIntro(QStringLiteral("真正的信心前面，其实是一片空旷，除了希望什么也没有，想要也没有。"));
    entry->setPhoto(QStringLiteral("mplayer.png"));
    RosterManager::instance()->addEntry(entry);

    entry = new RosterEntry(10);
    entry->setGroup(QStringLiteral("大学同学"));
    entry->setName(QStringLiteral("梭罗"));
    entry->setIntro(QStringLiteral("没有哪种思考或做事的方式，无论它是多么的古老，值得我们盲目地去跟从。"));
    entry->setPhoto(QStringLiteral("sun-java.png"));
    RosterManager::instance()->addEntry(entry);
}

#endif // REDHARE_LOCALTEST
