#ifndef QUESTIONDIALOG_H
#define QUESTIONDIALOG_H

#include <QDialog>

namespace Ui {
class QuestionDialog;
}

class QuestionDialog : public QDialog
{
    Q_OBJECT

public:
    QuestionDialog(QWidget *parent, const QString &text);
    ~QuestionDialog();

    static bool question(QWidget *parent, const QString &text);

protected:
    virtual void mousePressEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    virtual void mouseMoveEvent(QMouseEvent*) Q_DECL_OVERRIDE;
    virtual void paintEvent(QPaintEvent*) Q_DECL_OVERRIDE;

private:
    Ui::QuestionDialog *ui;
    bool is_tracking_;
    QPoint tracking_offset_;
};

#endif // QUESTIONDIALOG_H
