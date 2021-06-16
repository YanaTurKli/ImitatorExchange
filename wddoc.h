#ifndef WDDOC_H
#define WDDOC_H

#include <QWidget>

namespace Ui {
class WdDoc;
}

class WdDoc : public QWidget
{
    Q_OBJECT

public:
    explicit WdDoc(QWidget *parent = nullptr);
    ~WdDoc();

private:
    Ui::WdDoc *ui;
};

#endif // WDDOC_H
