#include "rosterwidget.h"
#include "rostergroupwidget.h"
#include "rosterentry.h"
#include "rosterentrywidget.h"
#include "rostermanager.h"

RosterWidget::RosterWidget(QWidget *parent)
    : QWidget(parent), selected_(0)
{
    layout_ = new QVBoxLayout(this);
    layout_->setContentsMargins(0,0,0,0);
    layout_->setSpacing(0);
    layout_->addStretch();
    this->setLayout(layout_);
    this->setPalette(QColor(Qt::white));

    QObject::connect(RosterManager::instance(), SIGNAL(sigGroupAdded(QString)),
        this, SLOT(addGroup(QString)));
    QObject::connect(RosterManager::instance(), SIGNAL(sigEntryAdded(RosterEntry*)),
        this, SLOT(addEntry(RosterEntry*)));
}

void RosterWidget::addGroup(const QString &group)
{
    RosterGroupWidget *node = new RosterGroupWidget(group, this);
    QObject::connect(node, SIGNAL(sigEntryClicked(RosterEntryWidget*)),
        this, SLOT(onEntryClicked(RosterEntryWidget*)));
    QLayoutItem *spacer = layout_->takeAt(layout_->count() - 1);
    nodes_.push_back(node);
    layout_->addWidget(node);
    layout_->addItem(spacer);
}

void RosterWidget::addEntry(RosterEntry *entry)
{
    RosterGroupWidget *node = this->findGroup(entry->group());
    if(node)
    {
        node->addEntry(entry);
    }
}

RosterGroupWidget* RosterWidget::findGroup(const QString &title)
{
    foreach(RosterGroupWidget *node, nodes_)
    {
        if(node->title() == title)
        {
            return node;
        }
    }
    return 0;
}

void RosterWidget::onEntryClicked(RosterEntryWidget *node)
{
    if(node && node != selected_)
    {
        if(selected_)
        {
            selected_->setSelected(false);
        }
        selected_ = node;
        selected_->setSelected(true);
    }

#if 0
    // node = 0 || node == selected_
    if(selected_ && allow_unselected)
    {
        selected_->setSelected(false);
        selected_ = 0;
    }
#endif
}

void RosterWidget::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    QStyleOption opt;
    opt.initFrom(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void RosterWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        QMenu menu;
        menu.addAction(QStringLiteral("刷新"));
        menu.exec(event->globalPosition().toPoint());
    }
}
