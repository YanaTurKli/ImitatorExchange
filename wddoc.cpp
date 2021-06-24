#include "wddoc.h"
#include "ui_wddoc.h"

WdDoc::WdDoc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WdDoc)
{
    ui->setupUi(this);
    db = QSqlDatabase::database("QPSQL");
    ui->pbSave->setEnabled(false);

    connect(ui->cbNumb,SIGNAL(activated(int)),this,SLOT(onCbNumb(int)));
    connect(ui->pbSave,SIGNAL(clicked()),this,SLOT(on_pbSave_pressed()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(on_pushButton_2_pressed()));
    ui->textEdit->clear();

}

WdDoc::~WdDoc()
{
    delete ui;
}

void WdDoc::setIDRLS(int id)
{
    id_rls=id;
    updateCmbNumb();

}
void WdDoc::updateCmbNumb()
{
    int row =1;
    ui->cbNumb->clear();
    ui->cbNumb->addItem("не выбрано",-1 );

    QString str_sql=QString ("select numb from report where id_rls=%1 and issign ='false'").arg(id_rls);
    QSqlQuery quer(str_sql);
        while(quer.next()) {
            ui->cbNumb->addItem(quer.value(0).toString(),row);
            row++;
        }
}

void WdDoc::onCbNumb(int index)
{
       numb=ui->cbNumb->itemText(index);
        ui->pbSave->setEnabled(true);
}
void WdDoc::on_pbSave_pressed()
{
    QString error = ui->textEdit->toPlainText();
    QSqlQuery *quer = new QSqlQuery(db);
    QString str_sql=" ";
   str_sql=QString("UPDATE report set  issign = true, error = '%3' where numb =%1 and id_rls =%2"
"").arg(numb).arg(id_rls).arg(error);

   quer->exec(str_sql);
   if(quer->isActive())
   {
       QMessageBox::information(this,"Запрос","Доклад сформирован",QMessageBox::Ok);
   }
   else
   {
       QMessageBox::information(this,"Запрос",str_sql,QMessageBox::Ok);
   }

    ui->textEdit->clear();
   emit newInsDoc(id_rls);
   hide();
}

void WdDoc::on_pushButton_2_pressed()
{
    hide();
}
