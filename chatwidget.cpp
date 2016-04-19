#include "chatwidget.h"
#include "ui_chatwidget.h"
#include "scrotdialog.h"
#include "rosterentry.h"
#include "rhconfig.h"
#include "photo_processing.h"
#include <Qtimer>

QHash<quint64, ChatWidget*> ChatWidget::windows_;

namespace {

enum {
    TRACKING_NONE,
    TRACKING_MOVE,
    TRACKING_LAYOUT,
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
    HITTEST_RIGHT,
    HITTEST_LAYOUT
};

} // anonymous namespace

ChatWidget::ChatWidget(RosterEntry *entry)
    : QWidget(0), ui(new Ui::ChatWidget), info_(entry),
    tracking_type_(TRACKING_NONE)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_QuitOnClose, false);
    this->setAttribute(Qt::WA_DeleteOnClose);

    QImage photo;
    if(!entry->photo().isEmpty() && photo.load(RHConfig::asPhotoPath(entry->photo())))
    {
        photo_processing::scale(photo, 56, 56);
        photo_processing::round(photo);
        ui->photoLabel->setPixmap(QPixmap::fromImage(photo));
    }

    windows_.insert(entry->uid(), this);
    QTimer::singleShot(0, this, SLOT(resetLabel()));
}

ChatWidget::~ChatWidget()
{
    delete ui;
}

ChatWidget* ChatWidget::open(RosterEntry *entry)
{
    QHash<quint64,ChatWidget*>::iterator it = windows_.find(entry->uid());
    if(it != windows_.end())
    {
        return it.value();
    }
    ChatWidget *instance = new ChatWidget(entry);
    instance->show();
    instance->activateWindow();
    return instance;
}

void ChatWidget::closeAll()
{
    while(!windows_.empty())
    {
        windows_.begin().value()->close();
    }
}

/*void ChatDialog::show_chat(BangChatResponse *msg)
{
    QTextCursor cursor = ui->outputEdit->textCursor();
    QTextCharFormat char_format = cursor.charFormat();

    QFont font(QStringLiteral("ËÎÌå"));
    font.setPointSize(10);

    QString display_name;
    if(msg->receiver_id == configuration::user_id())
    {
        display_name = user_->nickname();
        char_format.setFont(font);
        char_format.setForeground(QBrush(QColor(0, 100, 0)));

    }
    else
    {
        display_name += QStringLiteral("ÎÒ");
        char_format.setFont(font);
        char_format.setForeground(QBrush(QColor(0, 51, 113)));
    }

    cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
    cursor.setCharFormat(char_format);
    ui->outputEdit->setTextCursor(cursor);

    ui->outputEdit->insertPlainText(display_name);
    ui->outputEdit->insertPlainText(" ");
    ui->outputEdit->insertPlainText(msg->datetime.toString(QStringLiteral("HH:mm:ss")));
    ui->outputEdit->insertPlainText("\n");

    char_format.setFont(msg->font);
    char_format.setForeground(QBrush(msg->font_color));
    cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
    cursor.setCharFormat(char_format);
    ui->outputEdit->setTextCursor(cursor);

    ui->outputEdit->insertPlainText(msg->text);
    ui->outputEdit->insertPlainText("\n");

}*/

void ChatWidget::resizeEvent(QResizeEvent*)
{
    tracking_rect_ = ui->outputEdit->geometry();
    tracking_rect_.setTop(tracking_rect_.bottom());
    tracking_rect_.setBottom(tracking_rect_.top() + 3);
}

void ChatWidget::resetLabel()
{
    QFontMetrics metrics(ui->nameLabel->font());
    QString elided = metrics.elidedText(info_->name(), Qt::ElideRight,
        ui->nameLabel->width());
    ui->nameLabel->setText(elided);

    metrics = QFontMetrics(ui->introLabel->font());
    elided = metrics.elidedText(info_->intro(), Qt::ElideRight,
        ui->introLabel->width());
    ui->introLabel->setText(elided);
}

void ChatWidget::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    QRect rect = this->rect();
    rect.adjust(0, 0, -1, -1);
    p.setBrush(QColor(233,233,233));
    p.setPen(QColor(128,128,128));
    p.drawRect(rect);
}

void ChatWidget::closeEvent(QCloseEvent*)
{
    windows_.remove(info_->uid());
}

void ChatWidget::mousePressEvent(QMouseEvent *event)
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
            if(!this->isMaximized())
            {
                tracking_type_ = TRACKING_RESIZE;
                this->grabMouse();
            }
            break;
        case HITTEST_LAYOUT:
            tracking_type_ = TRACKING_LAYOUT;
            tracking_point_ = event->globalPos();
            tracking_height_ = ui->inputEdit->height();
            this->grabMouse();
            break;
        case HITTEST_CLIENT:
            if(!this->isMaximized())
            {
                tracking_type_ = TRACKING_MOVE;
                tracking_point_ = event->globalPos() - this->pos();
                this->grabMouse();
            }
            break;
        default:
            break;
        }
    }
}

void ChatWidget::mouseReleaseEvent(QMouseEvent*)
{
    switch(tracking_type_)
    {
    case TRACKING_MOVE:
    case TRACKING_RESIZE:
        this->releaseMouse();
        tracking_type_ = TRACKING_NONE;
        break;
    case TRACKING_LAYOUT:
        this->releaseMouse();
        tracking_type_ = TRACKING_NONE;
        tracking_rect_ = ui->outputEdit->geometry();
        tracking_rect_.setTop(tracking_rect_.bottom());
        tracking_rect_.setBottom(tracking_rect_.top() + 3);
        break;
    }
}

void ChatWidget::mouseMoveEvent(QMouseEvent *event)
{
    switch(tracking_type_)
    {
    case TRACKING_MOVE:
        this->move(event->globalPos() - tracking_point_);
        break;
    case TRACKING_LAYOUT:
    {
        int y = tracking_point_.y() - event->globalY() + tracking_height_;
        if(y > this->height() - 240)
        {
            y = this->height() - 240;
        }
        else if(y < 100)
        {
            y = 100;
        }
        ui->inputEdit->setFixedHeight(y);
        break;
    }
    case TRACKING_RESIZE:
    {
        QRect geo = this->geometry();
        switch(tracking_hittest_)
        {
        case HITTEST_TOP:
            geo.setTop(event->globalY());
            break;
        case HITTEST_TOPLEFT:
            geo.setTopLeft(event->globalPos());
            break;
        case HITTEST_TOPRIGHT:
            geo.setTopRight(event->globalPos());
            break;
        case HITTEST_LEFT:
            geo.setLeft(event->globalX());
            break;
        case HITTEST_BOTTOM:
            geo.setBottom(event->globalY());
            break;
        case HITTEST_BOTTOMLEFT:
            geo.setBottomLeft(event->globalPos());
            break;
        case HITTEST_BOTTOMRIGHT:
            geo.setBottomRight(event->globalPos());
            break;
        case HITTEST_RIGHT:
            geo.setRight(event->globalX());
            break;
        default:
            break;
        }
        ui->nameLabel->setText("");
        ui->introLabel->setText("");
        this->setGeometry(geo);
        resetLabel();
        break;
    }
    case TRACKING_NONE:
    {
        QPoint point = event->pos();
        if(this->isMaximized())
        {
            if(tracking_rect_.contains(point))
            {
                this->setCursor(Qt::SizeVerCursor);
                tracking_hittest_ = HITTEST_LAYOUT;
            }
            else
            {
                this->setCursor(Qt::ArrowCursor);
                tracking_hittest_ = HITTEST_CLIENT;
            }
            break;
        }

        QRect rect = this->rect();
        rect.adjust(1,1,-1,-1);

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
                if(tracking_rect_.contains(point))
                {
                    this->setCursor(Qt::SizeVerCursor);
                    tracking_hittest_ = HITTEST_LAYOUT;
                }
                else
                {
                    this->setCursor(Qt::ArrowCursor);
                    tracking_hittest_ = HITTEST_CLIENT;
                }
            }
        }
        break;
    }
    default:
        break;
    }
}

void ChatWidget::on_closeButton_clicked()
{
    this->close();
}

void ChatWidget::on_minimizeButton_clicked()
{
    this->showMinimized();
}

void ChatWidget::on_scrotButton_clicked()
{
    QTextCursor cursor = ui->inputEdit->textCursor();
    ScreenShotDialog scrot_dialog(this);
    if(scrot_dialog.exec() == QDialog::Accepted)
    {
        QTextCharFormat char_format = cursor.charFormat();
        cursor.insertImage(scrot_dialog.shot().toImage());
        cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
        cursor.setCharFormat(char_format);
        ui->inputEdit->setTextCursor(cursor);
    }
}

void ChatWidget::on_sendButton_clicked()
{
    QTextCharFormat char_format = ui->inputEdit->textCursor().charFormat();
    char_format.setFont(ui->inputEdit->document()->defaultFont());

    QTextCursor cursor = ui->outputEdit->textCursor();
    cursor.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
    cursor.setCharFormat(char_format);
    ui->outputEdit->setTextCursor(cursor);

    QTextDocument *doc = ui->inputEdit->document();
    for(QTextBlock block = doc->begin(); block != doc->end(); block = block.next())
    {
        for(QTextBlock::iterator it = block.begin(); it != block.end(); ++it)
        {
            QTextFragment fragment = it.fragment();
            if(fragment.isValid())
            {
                QTextImageFormat image_format = fragment.charFormat().toImageFormat();
                if(image_format.isValid())
                {
                    QVariant variant = doc->resource(QTextDocument::ImageResource,
                        image_format.name());
                    if(variant.canConvert<QImage>())
                    {
                        QImage image = variant.value<QImage>();
                        ui->outputEdit->textCursor().insertImage(image);
                    }
                }
                else
                {
                    QString text = fragment.text();
                    ui->outputEdit->insertPlainText(text);
                }
                cursor = ui->outputEdit->textCursor();
                cursor.setCharFormat(char_format);
                ui->outputEdit->setTextCursor(cursor);
            }
        }
    }
    ui->outputEdit->insertPlainText("\n");
    ui->inputEdit->clear();
}

void ChatWidget::on_maximizeButton_toggled(bool checked)
{
    if(checked)
    {
        this->showMaximized();
    }
    else
    {
        this->showNormal();
    }
}
