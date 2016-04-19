#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include <QtGlobal>
#include <QHash>

namespace Ui {
class ChatWidget;
}

class RosterEntry;

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    ChatWidget(RosterEntry *entry);
    ~ChatWidget();
    static ChatWidget* open(RosterEntry *entry);
    static void closeAll();
protected:
    virtual void resizeEvent(QResizeEvent*) Q_DECL_OVERRIDE;
    virtual void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
    virtual void closeEvent(QCloseEvent*) Q_DECL_OVERRIDE;
    virtual void mousePressEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    virtual void mouseMoveEvent(QMouseEvent*) Q_DECL_OVERRIDE;
private:
    Ui::ChatWidget *ui;
    RosterEntry *info_;

    int tracking_type_;     // 指示鼠标按下的操作(无、移动窗体、编辑布局、改变大小)
    QPoint tracking_point_; // 移动窗体时，是鼠标的初始globalPos相对窗口左上角的偏移
                            // 编辑布局时，是鼠标的初始globalPos
    int tracking_height_;   // 编辑布局时，是inputEdit初始的高度
    int tracking_hittest_;  // mouseMoveEvent中更新的指针落点判断
                            // 影响tracking_type_的判断以及改变大小时的行为
    QRect tracking_rect_;   // resizeEvent中更新的编辑布局判定区

    static QHash<quint64, ChatWidget*> windows_;
private slots:
    void resetLabel();
    void on_closeButton_clicked();
    void on_minimizeButton_clicked();
    void on_scrotButton_clicked();
    void on_sendButton_clicked();
    void on_maximizeButton_toggled(bool checked);
};

#endif // CHATWIDGET_H
