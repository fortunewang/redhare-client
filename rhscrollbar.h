#ifndef __REDHARE__RHSCROLLBAR__H__
#define __REDHARE__RHSCROLLBAR__H__

#include <QAbstractScrollArea>
#include <QScrollBar>

class RHScrollBar: public QScrollBar
{
public:
    static void hook(QAbstractScrollArea *area);
protected:
    virtual void enterEvent(QEvent*) Q_DECL_OVERRIDE;
    virtual void leaveEvent(QEvent*) Q_DECL_OVERRIDE;
private:
    RHScrollBar(QWidget *parent);
private:
    void loadStyleSheet(const QString &filename);
};

#endif // __REDHARE__RHSCROLLBAR__H__

