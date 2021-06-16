#ifndef WDOBJ_H
#define WDOBJ_H

#include <QWidget>

namespace Ui {
class WdObj;
}

class WdObj : public QWidget
{
    Q_OBJECT

public:
    explicit WdObj(QWidget *parent = nullptr);
    ~WdObj();

private:
    Ui::WdObj *ui;
};

#endif // WDOBJ_H
