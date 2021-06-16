#include "wdobj.h"
#include "ui_wdobj.h"

WdObj::WdObj(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WdObj)
{
    ui->setupUi(this);
}

WdObj::~WdObj()
{
    delete ui;
}
