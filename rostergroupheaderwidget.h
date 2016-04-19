#ifndef __REDHARE__ROSTERGROUPHEADERWIDGET__H__
#define __REDHARE__ROSTERGROUPHEADERWIDGET__H__

#include <QWidget>

namespace Ui {
class RosterGroupHeaderWidget;
}

class RosterGroupHeaderWidget : public QWidget
{
    Q_OBJECT
public:
    RosterGroupHeaderWidget(const QString &title, QWidget *parent = 0);
    ~RosterGroupHeaderWidget();
    QString title() const;
signals:
    void sigClicked();
public slots:
    void setExpanded(bool expanded);
protected:
    virtual void mousePressEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    virtual void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
private:
    Ui::RosterGroupHeaderWidget *ui;
};

#endif // __REDHARE__ROSTERGROUPHEADERWIDGET__H__
