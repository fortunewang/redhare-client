#ifndef __REDHARE__LOGINDIALOG__H__
#define __REDHARE__LOGINDIALOG__H__

#include <QDialog>

class QMouseEvent;
class AccountManager;

namespace Ui {
class LoginDialog;
}

class LoginDialog: public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

public slots:
    void onTrayDoubleClicked();
    void onTrayMenuActivate();
    void onTrayMenuExit();

protected:
    virtual void mousePressEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    virtual void mouseMoveEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    virtual void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;

private:
    Ui::LoginDialog *ui;
    bool is_tracking_;
    QPoint tracking_offset_;

private slots:
    void on_closeButton_clicked();
    void on_minimizeButton_clicked();
    void on_loginButton_clicked();
    void on_signupButton_clicked();
    void on_automaticBox_toggled(bool checked);
    void on_rememberBox_toggled(bool checked);
};

#endif // __REDHARE__LOGINDIALOG__H__
