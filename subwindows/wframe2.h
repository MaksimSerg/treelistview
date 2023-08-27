#ifndef WFRAME2_H
#define WFRAME2_H

#include <QObject>

#include "ddialog.h"
#include "src/widgets/treelist/dtreelist.h"

namespace Ui {class WFrame2;}

class WFrame2: public DDialog
{
    Q_OBJECT

public:
    explicit WFrame2(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    virtual ~WFrame2();

private:
    void initTree(DTreeList *tree);
    QString defaultCellValue(const int r, const int c);

protected:
    void changeEvent(QEvent * event) override;

private:
    Ui::WFrame2 *ui;
    DTreeList *tree1;
    DTreeList *tree2;
    DTreeList *tree3;
    DTreeList *tree4;
};

#endif // WFRAME1_H
