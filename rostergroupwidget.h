#ifndef __REDHARE__ROSTERGROUPWIDGET__H__
#define __REDHARE__ROSTERGROUPWIDGET__H__

#include <QWidget>

class QVBoxLayout;
class RosterGroupHeaderWidget;
class RosterEntryWidget;
class RosterEntry;

class RosterGroupWidget: public QWidget
{
    Q_OBJECT
public:
    RosterGroupWidget(const QString &title, QWidget *parent = 0);
    QString title() const;
signals:
    void sigEntryClicked(RosterEntryWidget*);
public slots:
    void addEntry(RosterEntry *entry);
protected:
    virtual void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;
private:
    bool is_expanded_;
    QVBoxLayout *layout_;
    RosterGroupHeaderWidget *header_;
    QList<RosterEntryWidget*> nodes_;
private slots:
    void onHeaderClicked();
};

#endif // __REDHARE__ROSTERGROUPWIDGET__H__
