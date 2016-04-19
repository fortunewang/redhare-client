#ifndef __REDHARE__MAINWIDGET__H__
#define __REDHARE__MAINWIDGET__H__

#include <QWidget>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

public slots:
    void onTrayDoubleClicked();
    void onTrayMenuActivate();
    void onTrayMenuExit();

protected:
    virtual void mousePressEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    virtual void mouseMoveEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    virtual void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
    virtual void enterEvent(QEvent*) Q_DECL_OVERRIDE;
    virtual void leaveEvent(QEvent*) Q_DECL_OVERRIDE;
    virtual void closeEvent(QCloseEvent*) Q_DECL_OVERRIDE;

private:
    Ui::MainWidget *ui;
    QPoint tracking_offset_;

    int tracking_type_;
    int tracking_hittest_;
    QPoint tracking_point_;

private slots:
    void onStartup();
    void on_closeButton_clicked();
    void on_minimizeButton_clicked();
};

#endif // __REDHARE__MAINWIDGET__H__
