#ifndef __REDHARE__ROSTERENTRYWIDGET__H__
#define __REDHARE__ROSTERENTRYWIDGET__H__

#include <QWidget>

namespace Ui {
class RosterEntryWidget;
}

class RosterEntry;

class RosterEntryWidget : public QWidget
{
    Q_OBJECT
public:
    RosterEntryWidget(RosterEntry *entry, QWidget *parent = 0);
    ~RosterEntryWidget();
signals:
    void sigClicked(RosterEntryWidget*);
public slots:
    void setSelected(bool selected);
protected:
    virtual void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
    virtual void mousePressEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    virtual void mouseDoubleClickEvent(QMouseEvent*) Q_DECL_OVERRIDE;
private:
    Ui::RosterEntryWidget *ui;
    RosterEntry *info_;
};

#endif // __REDHARE__ROSTERENTRYWIDGET__H__
