#ifndef __REDHARE__ROSTERWIDGET__H__
#define __REDHARE__ROSTERWIDGET__H__

#include <QWidget>

class QVBoxLayout;
class RosterEntryWidget;
class RosterGroupWidget;
class RosterEntry;

class RosterWidget: public QWidget
{
    Q_OBJECT
public:
    explicit RosterWidget(QWidget *parent = 0);
public slots:
    void addGroup(const QString &group);
    void addEntry(RosterEntry *entry);
protected:
    virtual void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
    virtual void mousePressEvent(QMouseEvent*) Q_DECL_OVERRIDE;
private:
    QVBoxLayout *layout_;
    QList<RosterGroupWidget*> nodes_;
    RosterEntryWidget *selected_;
private:
    RosterGroupWidget* findGroup(const QString &title);
private slots:
    void onEntryClicked(RosterEntryWidget *node);
};

#endif // __REDHARE__ROSTERWIDGET__H__

