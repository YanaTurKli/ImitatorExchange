#include "wdobj.h"
#include "ui_wdobj.h"

WdObj::WdObj(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WdObj)
{
    ui->setupUi(this);
    db = QSqlDatabase::database("QPSQL");
    updateCmbType();
    ui->pbSave->setEnabled(false);
    connect(ui->cbType,SIGNAL(activated(int)),this,SLOT(onCbType(int)));
    connect(ui->cbClass,SIGNAL(activated(int)),this,SLOT(oncbClass(int)));
    connect(ui->cbSign,SIGNAL(activated(int)),this,SLOT(onCbSign(int)));
    connect(ui->dsbKurs,SIGNAL(valueChanged(double)),this,SLOT(on_dsbKurs(double)));
    connect(ui->dsbKurs,SIGNAL(valueChanged(double)),this,SLOT(on_spNum(double)));
    connect(ui->sbNumb,SIGNAL(valueChanged(int)),this,SLOT(on_sbNumb(int)));
    connect(ui->dsbPeleng,SIGNAL(valueChanged(double)),this,SLOT(on_dsbPeleng(double)));
    connect(ui->dsbV,SIGNAL(valueChanged(double)),this,SLOT(on_dsbV(double)));
    connect(ui->dsbVh,SIGNAL(valueChanged(double)),this,SLOT(on_dsbVh(double)));
    connect(ui->dsbD,SIGNAL(valueChanged(double)),this,SLOT(on_dsbD(double)));
    connect(ui->timeEd,SIGNAL(timeChanged(QTime)),this,SLOT(on_time(QTime)));

    connect(ui->pbSave,SIGNAL(clicked()),this,SLOT(on_pbSave_pressed()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(on_pushButton_2_pressed()));

       ui->cbSign->setEnabled(false);

       ui->cbSign->clear();
       ui->cbSign->addItem("не выбрано",-1 );
       ui->cbClass->clear();
       ui->cbClass->addItem("не выбрано",-1 );
}

WdObj::~WdObj()
{
    delete ui;
}
void WdObj::setIDRLS(int id)
{
 id_rls=id;
}
void WdObj::updateCmbType()
{
    ui->cbType->clear();
    ui->cbType->addItem("не выбрано",-1 );
    ui->cbType->addItem("Свой",1);
    ui->cbType->addItem("Чужой",2);

    ui->pbSave->setEnabled(false);
}

void WdObj::updateCmbClass()
{
        ui->cbClass->clear();
        ui->cbClass->addItem("не выбрано",-1 );
        ui->cbClass->addItem("Воздушный",1);
        ui->cbClass->addItem("Надводный",1);

}
void WdObj::updateCmbSign(int id)
{
    if (class_obj=="Воздушный"){
        ui->cbSign->clear();
        ui->cbSign->addItem("не выбрано",-1 );
        ui->cbSign->addItem("Самолет",1);
        ui->cbSign->addItem("Вертолет",2);
    }
    if(class_obj=="Надводный"){
        ui->cbSign->clear();
        ui->cbSign->addItem("не выбрано",-1 );
        ui->cbSign->addItem("Корабль",1);
    }
}

void WdObj::onCbType(int index)
{
    int i;
    i = ui->cbType->itemData(index, Qt::UserRole).toInt();
    if (i==1)
    {
        type="Свой";
    }
    else
    {
        type="Чужой";
    }
        updateCmbClass();
}

void WdObj::oncbClass(int index)
{
   class_obj=ui->cbClass->itemText(index);
   ui->cbSign->setEnabled(true);
   updateCmbSign(id_rls);
}

void WdObj::onCbSign(int index)
{
   sign=ui->cbSign->itemText(index);

}


void WdObj::on_dsbKurs(double id)
{
    k=id;
}
void WdObj::on_sbNumb(int id)
{
    numb=id;
}
void WdObj::on_dsbPeleng(double id)
{
    peleng=id;
}
void WdObj::on_dsbV(double id)
{
    v=id;
}
void WdObj::on_dsbVh(double id)
{
    vh=id;
}
void WdObj::on_dsbD(double id)
{
    d=id;
}
void WdObj::on_pbSave_pressed()
{
    QSqlQuery *quer = new QSqlQuery(db);
    QString str_sql=" ";
    int n=0;
    QSqlQuery query("select id_object from objects order by id_object");
        while(query.next()) {
           n= query.value(0).toInt();
        }
         n++;

   str_sql=QString("INSERT INTO objects (id_object,id_rls,numb, type_obj,class_obj,sign,k,v,vh,x,y,z,t,ek,ev,evh,d,peleng)"
" VALUES (%12,%1,%2,'%3','%4','%5',%6,%7,%8,1,1,1,'%9',1,1,1,%10,%11)"
"").arg(id_rls).arg(numb).arg(type).arg(class_obj).arg(sign).arg(k).arg(v).arg(vh).arg(t.toString()).arg(d).arg(peleng).arg(n);

   quer->exec(str_sql);
   if(quer->isActive())
   {
       QMessageBox::information(this,"Запрос","Объект добавлен",QMessageBox::Ok);
   }
   else
   {
       QMessageBox::information(this,"Запрос",str_sql,QMessageBox::Ok);
   }


   emit newInsObj(id_rls);
   hide();
}

void WdObj::on_pushButton_2_pressed()
{
    hide();
}

void WdObj::on_time(QTime tim)
{
    t = tim;
       ui->pbSave->setEnabled(true);
}

