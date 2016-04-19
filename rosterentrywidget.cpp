#include "rosterentrywidget.h"
#include "ui_rosterentrywidget.h"
#include "rosterentry.h"
#include "photo_processing.h"
#include "rhconfig.h"
#include "chatwidget.h"

RosterEntryWidget::RosterEntryWidget(RosterEntry *entry, QWidget *parent)
    : QWidget(parent), ui(new Ui::RosterEntryWidget), info_(entry)
{
    ui->setupUi(this);
    ui->nameLabel->setText(entry->name());
    ui->introLabel->setText(entry->intro());
    this->setSelected(false);

    QImage photo;
    if(!entry->photo().isEmpty() && photo.load(RHConfig::asPhotoPath(entry->photo())))
    {
        photo_processing::scale(photo, 35, 35);
        photo_processing::round(photo);
        ui->photoLabel->setPixmap(QPixmap::fromImage(photo));
    }
}

RosterEntryWidget::~RosterEntryWidget()
{
    delete ui;
}

void RosterEntryWidget::setSelected(bool selected)
{
    if(selected)
    {
        this->setStyleSheet("\
            RosterEntryWidget {background-color: rgb(255,200,200);}\
            RosterEntryWidget:hover {background-color: rgb(255,200,200);}");
    }
    else
    {
        this->setStyleSheet("\
            RosterEntryWidget {background: transparent;}\
            RosterEntryWidget:hover {background-color: rgb(200,255,200);}");
    }
}

void RosterEntryWidget::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void RosterEntryWidget::mousePressEvent(QMouseEvent *event)
{
    emit sigClicked(this);
    if(event->button() == Qt::RightButton)
    {
        QMenu menu(this);
        menu.addAction(QStringLiteral("删除"));
        menu.addAction(QStringLiteral("移至黑名单"));
        menu.addAction(QStringLiteral("查看资料"));
        menu.addAction(QStringLiteral("修改备注"));
        menu.exec(event->globalPos());
    }
}

void RosterEntryWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        ChatWidget::open(info_);
    }
}
