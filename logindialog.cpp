#include "logindialog.h"
#include "ui_logindialog.h"
#include "accountmanager.h"

#include <QMouseEvent>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::LoginDialog), is_tracking_(false)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::ToolTip |
        Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

/******************************************************************************
 * overrides
******************************************************************************/

void LoginDialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        is_tracking_ = true;
        tracking_offset_ = event->globalPos() - this->pos();
    }
}

void LoginDialog::mouseReleaseEvent(QMouseEvent*)
{
    if(is_tracking_)
    {
        is_tracking_ = false;
    }
}

void LoginDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(is_tracking_)
    {
        this->move(event->globalPos() - tracking_offset_);
    }
}

void LoginDialog::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    QRect rect = this->rect();
    rect.adjust(0, 0, -1, -1);
    p.setBrush(QColor(233,233,233));
    p.setPen(QColor(128,128,128));
    p.drawRect(rect);
}

/******************************************************************************
 * slots
******************************************************************************/

void LoginDialog::onTrayDoubleClicked()
{
    this->showNormal();
    this->activateWindow();
}

void LoginDialog::onTrayMenuActivate()
{
    this->showNormal();
    this->activateWindow();
}

void LoginDialog::onTrayMenuExit()
{
    this->reject();
}

void LoginDialog::on_closeButton_clicked()
{
    this->reject();
}

void LoginDialog::on_minimizeButton_clicked()
{
    this->showMinimized();
}

void LoginDialog::on_loginButton_clicked()
{
    this->accept();
}

void LoginDialog::on_signupButton_clicked() {}

void LoginDialog::on_automaticBox_toggled(bool checked)
{
    if(checked)
    {
        ui->rememberBox->setChecked(true);
    }
}

void LoginDialog::on_rememberBox_toggled(bool checked)
{
    if(!checked)
    {
        ui->automaticBox->setChecked(false);
    }
}
