#include "scrotdialog.h"

ScreenShotDialog::ScreenShotDialog(QWidget *parent) :
    QDialog(parent),
    is_catching_(false),
    is_tracking_(false)
{
    QDialog::setMouseTracking(true);
    background_ = QApplication::primaryScreen()->grabWindow(QApplication::desktop()->winId());
    darker_background_ = background_;
    QPainter(&darker_background_).fillRect(
        QRect(QPoint(0,0), background_.size()),
        QBrush(QColor(0,0,0,150)));
}

void ScreenShotDialog::showEvent(QShowEvent *)
{
    showFullScreen();
    setCursor(Qt::CrossCursor);
}

void ScreenShotDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, darker_background_);
    painter.drawPixmap(rect_, background_, rect_);
}

void ScreenShotDialog::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        if(!rect_.isEmpty())
        {
            rect_.setCoords(0,0,-1,-1);
            QDialog::update();
        }
        else
        {
            QDialog::reject();
        }
    }
}

void ScreenShotDialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        QPoint pt = event->pos();
        if(rect_.contains(pt, true))
        {
            is_tracking_ = true;
            tracking_offset_ = pt - rect_.topLeft();
            tracking_limit_ = background_.rect();
            tracking_limit_.adjust(tracking_offset_.x(),
                tracking_offset_.y(),
                tracking_offset_.x() - rect_.width(),
                tracking_offset_.y() - rect_.height());
        #ifdef Q_OS_WIN
            RECT clip_rect;
            clip_rect.left = tracking_limit_.left();
            clip_rect.top = tracking_limit_.top();
            clip_rect.right = tracking_limit_.right();
            clip_rect.bottom = tracking_limit_.bottom();
            ::ClipCursor(&clip_rect);
        #endif
        }
        else
        {
            is_catching_ = true;
            catching_start_ = pt;
        }
    }
    else if(event->button() == Qt::RightButton)
    {
        if(!rect_.isEmpty())
        {
            rect_.setCoords(0,0,-1,-1);
            QDialog::update();
        }
        else
        {
            QDialog::reject();
        }
    }
}

void ScreenShotDialog::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pt = event->pos();
    if(is_catching_)
    {
        rect_ = QRect(catching_start_, pt).normalized();
        QDialog::update();
    }
    else if(is_tracking_)
    {
    #ifndef Q_OS_WIN
        if(pt.x() < tracking_limit_.left())
        {
            pt.setX(tracking_limit_.left());
            QCursor::setPos(pt);
        }
        else if(pt.x() > tracking_limit_.right())
        {
            pt.setX(tracking_limit_.right());
            QCursor::setPos(pt);
        }
        if(pt.y() < tracking_limit_.top())
        {
            pt.setY(tracking_limit_.top());
            QCursor::setPos(pt);
        }
        else if(pt.y() > tracking_limit_.bottom())
        {
            pt.setY(tracking_limit_.bottom());
            QCursor::setPos(pt);
        }
    #endif
        rect_.moveTopLeft(pt - tracking_offset_);
        QDialog::update();
    }
    else if(rect_.contains(pt))
    {
        QDialog::setCursor(Qt::SizeAllCursor);
    }
    else
    {
        QDialog::setCursor(Qt::CrossCursor);
    }
}

void ScreenShotDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(is_catching_)
        {
            is_catching_ = false;
            QDialog::update();
        }
        else if(is_tracking_)
        {
            is_tracking_ = false;
        #ifdef Q_OS_WIN
            ::ClipCursor(nullptr);
        #endif
            QDialog::update();
        }
    }
}

void ScreenShotDialog::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(!rect_.isEmpty())
        {
            shot_ = background_.copy(rect_);
            QDialog::accept();
        }
    }
}

