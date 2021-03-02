#include "rhscrollbar.h"
#include <QFile>

RHScrollBar::RHScrollBar(QWidget *parent): QScrollBar(Qt::Vertical, parent)
{
    this->loadStyleSheet(QStringLiteral(":/res/scrollbar.qss"));
}

void RHScrollBar::hook(QAbstractScrollArea *area)
{
    area->setVerticalScrollBar(new RHScrollBar(area));
}

void RHScrollBar::enterEvent(QEnterEvent*)
{
    this->setCursor(Qt::ArrowCursor);
    this->loadStyleSheet(QStringLiteral(":/res/scrollbar_hover.qss"));
}

void RHScrollBar::leaveEvent(QEvent*)
{
    this->loadStyleSheet(QStringLiteral(":/res/scrollbar.qss"));
}

void RHScrollBar::loadStyleSheet(const QString &filename)
{
    QFile file(filename);
    file.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(file.readAll());
    this->setStyleSheet(styleSheet);
}

