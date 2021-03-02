#include "rostergroupheaderwidget.h"
#include "ui_rostergroupheaderwidget.h"

RosterGroupHeaderWidget::RosterGroupHeaderWidget(const QString &title,
    QWidget *parent)
    : QWidget(parent), ui(new Ui::RosterGroupHeaderWidget)
{
    ui->setupUi(this);
    ui->titleLabel->setText(title);
}

RosterGroupHeaderWidget::~RosterGroupHeaderWidget()
{
    delete ui;
}

QString RosterGroupHeaderWidget::title() const
{
    return ui->titleLabel->text();
}

void RosterGroupHeaderWidget::setExpanded(bool expanded)
{
    if(expanded)
    {
        ui->arrowLabel->setPixmap(QPixmap(QStringLiteral(":/res/arrow_down.png")));
    }
    else
    {
        ui->arrowLabel->setPixmap(QPixmap(QStringLiteral(":/res/arrow_right.png")));
    }
}

void RosterGroupHeaderWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        emit sigClicked();
    }
}

void RosterGroupHeaderWidget::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    QStyleOption opt;
    opt.initFrom(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
