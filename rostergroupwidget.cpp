#include "rostergroupwidget.h"
#include "rostergroupheaderwidget.h"
#include "rosterentrywidget.h"
#include "rosterentry.h"

RosterGroupWidget::RosterGroupWidget(const QString &title, QWidget *parent)
    : QWidget(parent), is_expanded_(false)
{
    layout_ = new QVBoxLayout(this);
    header_ = new RosterGroupHeaderWidget(title, this);
    layout_->addWidget(header_);

    layout_->setContentsMargins(0,0,0,0);
    layout_->setSpacing(0);
    this->setLayout(layout_);
    this->setPalette(QColor(Qt::white));

    this->setMouseTracking(true);

    QObject::connect(header_, SIGNAL(sigClicked()),
        this, SLOT(onHeaderClicked()));
}

QString RosterGroupWidget::title() const
{
    return header_->title();
}

void RosterGroupWidget::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void RosterGroupWidget::onHeaderClicked()
{
    is_expanded_ = !is_expanded_;
    header_->setExpanded(is_expanded_);
    foreach(RosterEntryWidget *node, nodes_)
    {
        node->setVisible(is_expanded_);
    }
}

void RosterGroupWidget::addEntry(RosterEntry *entry)
{
    RosterEntryWidget *node = new RosterEntryWidget(entry, this);
    node->setVisible(is_expanded_);
    QObject::connect(node, SIGNAL(sigClicked(RosterEntryWidget*)),
        this, SIGNAL(sigEntryClicked(RosterEntryWidget*)));
    nodes_.push_back(node);
    layout_->addWidget(node);
}
