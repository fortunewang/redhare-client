#include "accountmanager.h"
#include "logindialog.h"
#include "mainwidget.h"

#include <QMenu>

AccountManager::AccountManager()
    : trayicon_(new QSystemTrayIcon(QIcon(":/res/redhare.ico"), this))
{
    QObject::connect(trayicon_,
        SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
        this, SLOT(onTrayActivated(QSystemTrayIcon::ActivationReason)));
}

void AccountManager::startLogin()
{
    QMenu *menu = new QMenu(this);
    QAction *action;

    action = menu->addAction(QStringLiteral("打开主面板"));
    QObject::connect(action, SIGNAL(triggered()),
        this, SIGNAL(sigTrayMenuActivate()));

    action = menu->addAction(QStringLiteral("退出"));
    QObject::connect(action, SIGNAL(triggered()),
        this, SIGNAL(sigTrayMenuExit()));

    LoginDialog *login_dialog = new LoginDialog(this);
    login_dialog->setAttribute(Qt::WA_DeleteOnClose);
    login_dialog->setAttribute(Qt::WA_QuitOnClose, false);

    QObject::connect(login_dialog, SIGNAL(destroyed()),
        menu, SLOT(deleteLater()));
    QObject::connect(login_dialog, SIGNAL(accepted()),
        this, SLOT(onLoginSucceeded()));
    QObject::connect(login_dialog, SIGNAL(rejected()), this, SLOT(close()));
    QObject::connect(this, SIGNAL(sigTrayDoubleClicked()),
        login_dialog, SLOT(onTrayDoubleClicked()));
    QObject::connect(this, SIGNAL(sigTrayMenuExit()),
        login_dialog, SLOT(onTrayMenuExit()));
    QObject::connect(this, SIGNAL(sigTrayMenuActivate()),
        login_dialog, SLOT(onTrayMenuActivate()));

    trayicon_->setContextMenu(menu);
    trayicon_->setToolTip(QStringLiteral("redhare"));
    trayicon_->show();
    login_dialog->show();
}

void AccountManager::onLoginSucceeded()
{
    QMenu *menu = new QMenu(this);
    QAction *action;

    action = menu->addAction(QStringLiteral("打开主面板"));
    QObject::connect(action, SIGNAL(triggered()),
        this, SIGNAL(sigTrayMenuActivate()));

    action = menu->addAction(QStringLiteral("退出"));
    QObject::connect(action, SIGNAL(triggered()),
        this, SIGNAL(sigTrayMenuExit()));

    MainWidget *main_widget = new MainWidget(this);
    main_widget->setAttribute(Qt::WA_QuitOnClose);

    QObject::connect(main_widget, SIGNAL(destroyed()),
        menu, SLOT(deleteLater()));
    QObject::connect(this, SIGNAL(sigTrayDoubleClicked()),
        main_widget, SLOT(onTrayDoubleClicked()));
    QObject::connect(this, SIGNAL(sigTrayMenuExit()),
        main_widget, SLOT(onTrayMenuExit()));
    QObject::connect(this, SIGNAL(sigTrayMenuActivate()),
        main_widget, SLOT(onTrayMenuActivate()));

    trayicon_->setContextMenu(menu);
    main_widget->show();
}

void AccountManager::onTrayActivated(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::DoubleClick)
    {
        emit sigTrayDoubleClicked();
    }
}
