#include "wdcom.h"
#include "ui_wdcom.h"

WdCom::WdCom(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::WdCom)
{
    ui->setupUi(this);

    this->setWindowTitle("Формирование команды");
    db = QSqlDatabase::database("QPSQL");
    updateCmbType();
    ui->pbSave->setEnabled(false);
    connect(ui->cbType,SIGNAL(activated(int)),this,SLOT(onCbType(int)));
    connect(ui->cbNumber,SIGNAL(activated(int)),this,SLOT(onCbNumber(int)));
    connect(ui->cbCom,SIGNAL(activated(int)),this,SLOT(onCbCom(int)));
    connect(ui->cbSost,SIGNAL(activated(int)),this,SLOT(onCbSost(int)));
    connect(ui->cbScena,SIGNAL(activated(int)),this,SLOT(onCbScena(int)));
    connect(ui->cbSector,SIGNAL(activated(int)),this,SLOT(onCbSector(int)));
    connect(ui->pbSave,SIGNAL(clicked()),this,SLOT(on_pbSave_pressed()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(on_pushButton_2_pressed()));
    connect(ui->spNum,SIGNAL(valueChanged(int)),this,SLOT(on_spNum(int)));
    connect(ui->dsbTemp,SIGNAL(valueChanged(double)),this,SLOT(on_sbTemp(double)));


}

WdCom::~WdCom()
{delete ui;

}


void WdCom::updateCmbType()
{
    ui->cbType->clear();
    ui->cbType->addItem("не выбрано",-1 );
    ui->cbType->addItem("Обзорная двухкоординатная",1);
    ui->cbType->addItem("Обзорная двухкоординатная",2);

    ui->cbCom->setEnabled(false);
    ui->cbNumber->setEnabled(false);
    ui->cbScena->setEnabled(false);
    ui->cbSector->setEnabled(false);
    ui->cbSost->setEnabled(false);
    ui->dsbTemp->setEnabled(false);
    ui->spNum->setEnabled(false);
}

void WdCom::updateCmbNumber(int id)
{
    if (id==1){
        ui->cbNumber->clear();
        ui->cbNumber->addItem("не выбрано",-1 );
        ui->cbNumber->addItem("1",1);
    }
    if(id==2){
        ui->cbNumber->clear();
        ui->cbNumber->addItem("не выбрано",-1 );
        ui->cbNumber->addItem("2",1);
    }


}

void WdCom::updateCmbSector()
{
    ui->cbSector->clear();
    ui->cbSector->addItem("не выбрано",-1 );
    ui->cbSector->addItem("1",1);
    ui->cbSector->addItem("2",2);
    ui->cbSector->addItem("3",3);
    ui->cbSector->addItem("4",4);
}

void WdCom::updateCmbSost()
{
    ui->cbSost->clear();
    ui->cbSost->addItem("не выбрано",-1 );
    ui->cbSost->addItem("Включить",1);
    ui->cbSost->addItem("Выключить",2);
}

void WdCom::updateCmbScena()
{
    ui->cbScena->clear();
    ui->cbScena->addItem("не выбрано",-1 );
    ui->cbScena->addItem("Мирное время",1);
    ui->cbScena->addItem("Военное время",2);
}


void WdCom::updateCmbCom()
{
    ui->cbCom->clear();
    ui->cbCom->addItem("не выбрано",-1 );
    ui->cbCom->addItem("Изменение состояния",1);
    ui->cbCom->addItem("Изменение сценария",2);
    ui->cbCom->addItem("Изменение сектора ответственности ",3);
     ui->cbCom->addItem("Изменение темпа обзора ",4);
}

void WdCom::onCbType(int index)
{
    id_type = ui->cbType->itemData(index, Qt::UserRole).toInt();

    ui->cbNumber->setEnabled(true);
    updateCmbNumber(id_type);
}

void WdCom::onCbNumber(int index)
{
   id_number=ui->cbNumber->itemText(index);
   ui->cbCom->setEnabled(true);
   ui->spNum->setEnabled(true);
   updateCmbCom();
}

void WdCom::onCbCom(int index)
{
    if (index==1)
    {
        ui->cbScena->setEnabled(false);
        ui->cbSector->setEnabled(false);
        ui->cbSost->setEnabled(true);
        ui->dsbTemp->setEnabled(false);
        updateCmbSost();
    }
    if(index==2)
    {
        ui->cbScena->setEnabled(true);
        ui->cbSector->setEnabled(false);
        ui->cbSost->setEnabled(false);
        ui->dsbTemp->setEnabled(false);
        updateCmbScena();
    }
    if(index==3)
    {
        ui->cbScena->setEnabled(false);
        ui->cbSector->setEnabled(true);
        ui->cbSost->setEnabled(false);
        ui->dsbTemp->setEnabled(false);
        updateCmbSector();
    }
    if(index==4)
    {
        ui->cbScena->setEnabled(false);
        ui->cbSector->setEnabled(false);
        ui->cbSost->setEnabled(false);
        ui->dsbTemp->setEnabled(true);
    }
    id_com=index;
}

void WdCom::onCbSector(int index)
{
    id_sector = index;
    ui->pbSave->setEnabled(true);
}

void WdCom::onCbScena(int index)
{
    id_scena = ui->cbScena->itemData(index, Qt::UserRole).toInt();
    ui->pbSave->setEnabled(true);
}

void WdCom::onCbSost(int index)
{
    id_sost = ui->cbSost->itemData(index, Qt::UserRole).toInt();
    ui->pbSave->setEnabled(true);
}
void WdCom::on_spNum(int id)
{
    id_num=id;
}
void WdCom::on_sbTemp(double id)
{
    temp=id;
        ui->pbSave->setEnabled(true);
}
void WdCom::on_pbSave_pressed()
{
    QSqlQuery *quer = new QSqlQuery(db);
    QSqlQuery *quer2 = new QSqlQuery(db);
    QString str_sql=" ";

   str_sql=QString("INSERT INTO report (id_rls,id_odject,numb, type_rep,error, issign,issend)"
" VALUES (%1,%2,%3,%4,'%5', false, false)").arg(id_number).arg(1).arg(id_num).arg(id_com).arg("");

   quer->exec(str_sql);
   if(quer->isActive())
   {
       QMessageBox::information(this,"Запрос","Команда сформирована",QMessageBox::Ok);
   }
   else
   {
       QMessageBox::information(this,"Запрос",str_sql,QMessageBox::Ok);
   }
       QString sost;
   if(id_com==1)
   {
       if(id_sost==1)
           sost="Включено";
       else
             sost="Выключено";
       str_sql=QString("UPDATE rls set status ='%1' "
        "where id_rls=%2").arg(sost).arg(id_number);

   }
   if(id_com==2){
       if(id_scena==1)
           sost="Мирное время";
       else
             sost="Военное время";
       str_sql=QString("UPDATE rls set scenario ='%1' "
        "where id_rls=%2").arg(sost).arg(id_number);
   }
   if(id_com==3){
       str_sql=QString("UPDATE rls set sector = %1 "
        "where id_rls=%2").arg(id_sector).arg(id_number);
   }
   if(id_com==4){

       str_sql=QString("UPDATE rls set temp =%1 "
        "where id_rls=%2").arg(temp).arg(id_number);
   }

   quer2->exec(str_sql);
   if(quer2->isActive())
   {
       QMessageBox::information(this,"Запрос","Команда доставлена",QMessageBox::Ok);
   }
   else
   {
       QMessageBox::information(this,"Запрос",str_sql,QMessageBox::Ok);
   }


   emit loadDatabaseSignal(id_number.toInt(),id_com);
   updateCmbType();
   ui->cbNumber->clear();
   ui->cbNumber->addItem("не выбрано",-1 );
   updateCmbSector();
   updateCmbSost();
   updateCmbCom();
   hide();
}

void WdCom::on_pushButton_2_pressed()
{
    hide();
}


