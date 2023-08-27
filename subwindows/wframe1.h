#ifndef WFRAME1_H
#define WFRAME1_H

#include <QObject>

#include "ddialog.h"
#include "src/widgets/treelist/dtreelist.h"

namespace Ui {class WFrame1;}

class WFrame1:public DDialog
{
    Q_OBJECT

public:
    explicit WFrame1(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    virtual ~WFrame1();

private:
    void initTree1();
    void initTree2();
    void initTree3();
    QString defaultCellValue(const int r, const int c);
    QList<QStandardItem *> createRowsRecursive(int columnCount, int &r, int depth=1);

protected:
    void changeEvent(QEvent * event) override;

private:
    Ui::WFrame1 *ui;
    DTreeList *tree1;
    DTreeList *tree2;
    DTreeList *tree3;
};

#endif // WFRAME1_H
