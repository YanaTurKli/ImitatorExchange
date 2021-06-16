#include "wddoc.h"
#include "ui_wddoc.h"

WdDoc::WdDoc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WdDoc)
{
    ui->setupUi(this);
}

WdDoc::~WdDoc()
{
    delete ui;
}
