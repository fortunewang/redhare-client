#include "questiondialog.h"
#include "ui_questiondialog.h"

QuestionDialog::QuestionDialog(QWidget *parent, const QString &text)
    : QDialog(parent), ui(new Ui::QuestionDialog), is_tracking_(false)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    ui->label->setText(text);
}

QuestionDialog::~QuestionDialog()
{
    delete ui;
}

bool QuestionDialog::question(QWidget *parent, const QString &text)
{
    return QuestionDialog(parent, text).exec() == QDialog::Accepted;
}

void QuestionDialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        is_tracking_ = true;
        tracking_offset_ = event->globalPos() - this->pos();
    }
}

void QuestionDialog::mouseReleaseEvent(QMouseEvent*)
{
    if(is_tracking_)
    {
        is_tracking_ = false;
    }
}

void QuestionDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(is_tracking_)
    {
        this->move(event->globalPos() - tracking_offset_);
    }
}

void QuestionDialog::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    QRect rect = this->rect();
    rect.adjust(0, 0, -1, -1);
    p.setBrush(QColor(233,233,233));
    p.setPen(QColor(128,128,128));
    p.drawRect(rect);
}
