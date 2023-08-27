#ifndef DDIALOG_H
#define DDIALOG_H

#include <QObject>
#include <QDialog>

class DDialog: public QDialog
{
    Q_OBJECT

public:
    explicit DDialog(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

protected:
    void closeEvent(QCloseEvent *) override;
};

#endif // DDIALOG_H
