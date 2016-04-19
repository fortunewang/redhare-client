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

    int tracking_type_;     // ָʾ��갴�µĲ���(�ޡ��ƶ����塢�༭���֡��ı��С)
    QPoint tracking_point_; // �ƶ�����ʱ�������ĳ�ʼglobalPos��Դ������Ͻǵ�ƫ��
                            // �༭����ʱ�������ĳ�ʼglobalPos
    int tracking_height_;   // �༭����ʱ����inputEdit��ʼ�ĸ߶�
    int tracking_hittest_;  // mouseMoveEvent�и��µ�ָ������ж�
                            // Ӱ��tracking_type_���ж��Լ��ı��Сʱ����Ϊ
    QRect tracking_rect_;   // resizeEvent�и��µı༭�����ж���

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
