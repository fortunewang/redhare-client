#ifndef __REDHARE__ACCOUNTMANAGER__H__
#define __REDHARE__ACCOUNTMANAGER__H__

#include <QWidget>

class QSystemTrayIcon;

class AccountManager: private QWidget
{
    Q_OBJECT
public:
    AccountManager();
    void startLogin();
signals:
    void sigTrayDoubleClicked();
    void sigTrayMenuExit();
    void sigTrayMenuActivate();
private:
    QSystemTrayIcon *trayicon_;
private slots:
    void onLoginSucceeded();
    void onTrayActivated(QSystemTrayIcon::ActivationReason reason);
};

#endif // __REDHARE__ACCOUNTMANAGER__H__

