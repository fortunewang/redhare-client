#ifndef __REDHARE__SCROTDIALOG__H__
#define __REDHARE__SCROTDIALOG__H__

#include <QDialog>

class ScreenShotDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ScreenShotDialog(QWidget *parent = 0);
    const QPixmap& shot() { return shot_; }
protected:
    void showEvent(QShowEvent*);
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);

private:
    bool is_catching_;
    bool is_tracking_;
    QRect rect_;
    QRect tracking_limit_;
    QPoint catching_start_;
    QPoint tracking_offset_;
    QPixmap shot_;
    QPixmap background_;
    QPixmap darker_background_;
};

#endif // __REDHARE__SCROTDIALOG__H__
