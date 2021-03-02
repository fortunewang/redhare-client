#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "rhscrollbar.h"
#include "questiondialog.h"
#include "chatwidget.h"
#include <QTimer>

#include "localtest.h"

namespace {

enum {
    TRACKING_NONE,
    TRACKING_MOVE,
    TRACKING_RESIZE
};

enum {
    HITTEST_CLIENT,
    HITTEST_TOP,
    HITTEST_TOPLEFT,
    HITTEST_TOPRIGHT,
    HITTEST_LEFT,
    HITTEST_BOTTOM,
    HITTEST_BOTTOMLEFT,
    HITTEST_BOTTOMRIGHT,
    HITTEST_RIGHT
};

} // anonymous namespace

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::MainWidget), tracking_type_(TRACKING_NONE)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);

    QMenu *main_menu = new QMenu(this);
    main_menu->addAction(QStringLiteral("设置"));
    ui->settingsButton->setMenu(main_menu);

    RHScrollBar::hook(ui->scrollArea);

    QTimer::singleShot(0, this, SLOT(onStartup()));
}

MainWidget::~MainWidget()
{
    delete ui;
}

/******************************************************************************
 * overrides
******************************************************************************/

void MainWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        switch(tracking_hittest_)
        {
        case HITTEST_TOP:
        case HITTEST_TOPLEFT:
        case HITTEST_TOPRIGHT:
        case HITTEST_LEFT:
        case HITTEST_BOTTOM:
        case HITTEST_BOTTOMLEFT:
        case HITTEST_BOTTOMRIGHT:
        case HITTEST_RIGHT:
            tracking_type_ = TRACKING_RESIZE;
            this->grabMouse();
            break;
        case HITTEST_CLIENT:
            tracking_type_ = TRACKING_MOVE;
            tracking_point_ = event->globalPosition().toPoint() - this->pos();
            this->grabMouse();
            break;
        default:
            break;
        }
    }
}

void MainWidget::mouseReleaseEvent(QMouseEvent*)
{
    switch(tracking_type_)
    {
    case TRACKING_MOVE:
    case TRACKING_RESIZE:
        this->releaseMouse();
        tracking_type_ = TRACKING_NONE;
        break;
    default:
        break;
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent *event)
{
    switch(tracking_type_)
    {
    case TRACKING_MOVE:
        this->move(event->globalPosition().toPoint() - tracking_point_);
        break;
    case TRACKING_RESIZE:
    {
        QRect geo = this->geometry();
        switch(tracking_hittest_)
        {
        case HITTEST_TOP:
            geo.setTop(event->globalPosition().y());
            break;
        case HITTEST_TOPLEFT:
            geo.setTopLeft(event->globalPosition().toPoint());
            break;
        case HITTEST_TOPRIGHT:
            geo.setTopRight(event->globalPosition().toPoint());
            break;
        case HITTEST_LEFT:
            geo.setLeft(event->globalPosition().x());
            break;
        case HITTEST_BOTTOM:
            geo.setBottom(event->globalPosition().y());
            break;
        case HITTEST_BOTTOMLEFT:
            geo.setBottomLeft(event->globalPosition().toPoint());
            break;
        case HITTEST_BOTTOMRIGHT:
            geo.setBottomRight(event->globalPosition().toPoint());
            break;
        case HITTEST_RIGHT:
            geo.setRight(event->globalPosition().x());
            break;
        default:
            break;
        }
        this->setGeometry(geo);
        break;
    }
    case TRACKING_NONE:
    {
        QPoint point = event->pos();
        QRect rect = this->rect();
        rect.adjust(1, 1, -1, -1);

        if(point.x() < rect.left())
        {
            if(point.y() < rect.top())
            {
                this->setCursor(Qt::SizeFDiagCursor);
                tracking_hittest_ = HITTEST_TOPLEFT;
            }
            else if(point.y() > rect.bottom())
            {
                this->setCursor(Qt::SizeBDiagCursor);
                tracking_hittest_ = HITTEST_BOTTOMLEFT;
            }
            else
            {
                this->setCursor(Qt::SizeHorCursor);
                tracking_hittest_ = HITTEST_LEFT;
            }
        }
        else if(point.x() > rect.right())
        {
            if(point.y() < rect.top())
            {
                this->setCursor(Qt::SizeBDiagCursor);
                tracking_hittest_ = HITTEST_TOPRIGHT;
            }
            else if(point.y() > rect.bottom())
            {
                this->setCursor(Qt::SizeFDiagCursor);
                tracking_hittest_ = HITTEST_BOTTOMRIGHT;
            }
            else
            {
                this->setCursor(Qt::SizeHorCursor);
                tracking_hittest_ = HITTEST_RIGHT;
            }
        }
        else
        {
            if(point.y() < rect.top())
            {
                this->setCursor(Qt::SizeVerCursor);
                tracking_hittest_ = HITTEST_TOP;
            }
            else if(point.y() > rect.bottom())
            {
                this->setCursor(Qt::SizeVerCursor);
                tracking_hittest_ = HITTEST_BOTTOM;
            }
            else
            {
                this->setCursor(Qt::ArrowCursor);
                tracking_hittest_ = HITTEST_CLIENT;
            }
        }
        break;
    }
    default:
        break;
    }
}

void MainWidget::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    QRect rect = this->rect();
    rect.adjust(0, 0, -1, -1);
    p.setBrush(QColor(233,233,233));
    p.setPen(QColor(128,128,128));
    p.drawRect(rect);
}

void MainWidget::enterEvent(QEnterEvent*)
{
    QRect rect = this->geometry();
    if(rect.top() <= 0)
    {
        this->move(rect.x(), 0);
    }
}

void MainWidget::leaveEvent(QEvent*)
{
    QRect rect = this->geometry();
    if(rect.top() <= 0)
    {
        this->move(rect.x(), -rect.height() + 2);
    }
}

void MainWidget::closeEvent(QCloseEvent *event)
{
    if(!QuestionDialog::question(this, QStringLiteral("确定要退出吗？")))
    {
        event->ignore();
    }
    ChatWidget::closeAll();
}

/******************************************************************************
 * slots
******************************************************************************/

void MainWidget::onStartup()
{
#ifdef REDHARE_LOCALTEST
    rh_localtest_roster();
#endif
}

void MainWidget::onTrayDoubleClicked()
{
    this->showNormal();
    this->activateWindow();
    QRect rect = QWidget::geometry();
    if(rect.top() <= 0)
    {
        QWidget::move(rect.x(), 0);
    }
}

void MainWidget::onTrayMenuActivate()
{
    this->showNormal();
    this->activateWindow();
    QRect rect = QWidget::geometry();
    if(rect.top() <= 0)
    {
        QWidget::move(rect.x(), 0);
    }
}

void MainWidget::onTrayMenuExit()
{
    this->close();
}

void MainWidget::on_closeButton_clicked()
{
    this->close();
}

void MainWidget::on_minimizeButton_clicked()
{
    this->showMinimized();
}
