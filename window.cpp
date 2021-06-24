#include "window.h"
#include "nwindow.h"
#include "ui_window.h"
#include "QStackedWidget"
#include "wdcom.h"


Window::Window(QWidget *parent)
    : QMainWindow(parent)
     , ui(new Ui::Window)
{
    ui->setupUi(this);
    ui->stackW->setCurrentIndex(0);
    this->setWindowTitle("Окно режима ИУС");

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    //имя базы данных
    db.setDatabaseName("postgres");
    //имя пользователя
    db.setUserName("postgres");
    //его пароль
    db.setPassword("134032");
    /*открываем подключение; если неудачно - выводим сообщение об ошибке*/
    if (!db.open())
    QMessageBox::critical(NULL,QObject::tr("Ошибка"),db.lastError().text());
    else
    QMessageBox::information(this,"BD","Подключение успешно",QMessageBox::Ok);

    /* Инициализируем виджет с графикой */
    graphic = new WdGraphicView();
    /* и добавляем его на слой */
    connect(this, SIGNAL(setCourse(double)), graphic, SLOT(onSetCourse(double)));
      ui->IUSgraphicsLayout->addWidget(graphic);

    rls1 = new NWindow();
    connect(rls1, SIGNAL(updateCom()), this, SLOT(slotUpdateComRLS()));

    rls2 = new NWindow();
    connect(rls2, SIGNAL(updateCom()), this, SLOT(slotUpdateComRLS()));

    setTables();
    updateTableRLS();

    connect(ui->IUSpbInsertKom,SIGNAL(clicked()),this,SLOT(pb_pbInsert_click()));
    w2 = new WdCom();
    connect(w2, SIGNAL(loadDatabaseSignal(int,int)), this, SLOT(slotRLS(int,int)));

}


Window::~Window()
{
    delete ui;
}

void Window::pb_pbInsert_click()
{
   w2->show();


}
void Window::setTables()
{
        QSqlQuery query;
        query.exec("UPDATE rls set status ='Выключено' where numb=1");
        query.exec("UPDATE rls set status ='Выключено' where numb=2");
        query.exec("DELETE from report");

    QStringList headers;

    headers.clear();
    headers << "Номер";
    headers << "Тип";
    headers << "Принята";
    headers << "Обработана";
    headers << "Доклад";

    ui->IUStableCom->setColumnCount(5);
    ui->IUStableCom->setHorizontalHeaderLabels(headers);
    ui->IUStableCom->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->IUStableCom->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->IUStableCom->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->IUStableCom->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->IUStableCom->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);

    headers.clear();
    headers << "Тип";
    headers << "Номер";
    headers << "Состояние";
    headers << "Сектор\nответ.";
    headers << "Макс.\nдальность";
    headers << "Миним.\nдальность";
    headers << "Макси.\nвысота";
    headers << "Миним.\nвысота";
    headers << "Сценарий";
    headers << "Темп\nобзора";


    ui->IUStableRLS->setColumnCount(10);
    ui->IUStableRLS->setHorizontalHeaderLabels(headers);
    ui->IUStableRLS->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->IUStableRLS->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->IUStableRLS->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->IUStableRLS->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->IUStableRLS->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui->IUStableRLS->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    ui->IUStableRLS->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
    ui->IUStableRLS->horizontalHeader()->setSectionResizeMode(7, QHeaderView::Stretch);
    ui->IUStableRLS->horizontalHeader()->setSectionResizeMode(8, QHeaderView::Stretch);
    ui->IUStableRLS->horizontalHeader()->setSectionResizeMode(9, QHeaderView::Stretch);

    headers.clear();
    headers << "Номер";
    headers << "Принад-\nлежность";
    headers << "Класс";
    headers << "Тип";
    headers << "P";
    headers << "D";
    headers << "K";
    headers << "V";
    headers << "Vh";
    headers << "Х";
    headers << "Y";
    headers << "H";
    headers << "Время\nобнаруж.";
    headers << "Ek";
    headers << "Ev";
    headers << "Evh";

    ui->IUStableObject->setColumnCount(16);
    ui->IUStableObject->setHorizontalHeaderLabels(headers);
    ui->IUStableObject->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->IUStableObject->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->IUStableObject->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->IUStableObject->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->IUStableObject->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui->IUStableObject->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    ui->IUStableObject->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
    ui->IUStableObject->horizontalHeader()->setSectionResizeMode(7, QHeaderView::Stretch);
    ui->IUStableObject->horizontalHeader()->setSectionResizeMode(8, QHeaderView::Stretch);
    ui->IUStableObject->horizontalHeader()->setSectionResizeMode(9, QHeaderView::Stretch);
    ui->IUStableObject->horizontalHeader()->setSectionResizeMode(10, QHeaderView::Stretch);
    ui->IUStableObject->horizontalHeader()->setSectionResizeMode(11, QHeaderView::Stretch);
    ui->IUStableObject->horizontalHeader()->setSectionResizeMode(12, QHeaderView::Stretch);
    ui->IUStableObject->horizontalHeader()->setSectionResizeMode(13, QHeaderView::Stretch);
    ui->IUStableObject->horizontalHeader()->setSectionResizeMode(14, QHeaderView::Stretch);
    ui->IUStableObject->horizontalHeader()->setSectionResizeMode(15, QHeaderView::Stretch);

    headers.clear();
    headers << "Номер";
    headers << "Тип";
    headers << "Cформирован";
    headers << "Ошибка";

    ui->IUStableDoc->setColumnCount(4);
    ui->IUStableDoc->setHorizontalHeaderLabels(headers);
    ui->IUStableDoc->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->IUStableDoc->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->IUStableDoc->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->IUStableDoc->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
}

int Window::isOnRLS(int id)
{
      QString sql_str = QString("select * from rls where id_rls=%1 and status='Включено' ").arg(id);
       QSqlQuery query(sql_str);
       if (query.size()==1) {
            return 0;//выключено
       }
       else
           return 1;//включено
}

void Window::slotUpdateComRLS()
{

    updateTableDoc();
    updateTableCom();
    updateTableObject();
    updateTableRLS();
}

void Window::updateTableRLS()
{
  //  ui->IUStableRLS->clear();
    ui->IUStableRLS->setRowCount(0);

    QSqlQuery query("select * from rls");
        int row =0;
        while(query.next()) {
                ui->IUStableRLS->insertRow(row);

                QTableWidgetItem * nm1 = new QTableWidgetItem(query.value(2).toString());
                nm1->setData(Qt::UserRole, query.value(0));
                nm1->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableRLS->setItem(row,0, nm1);

                QTableWidgetItem * nm2 = new QTableWidgetItem(query.value(1).toString());
                nm2->setData(Qt::UserRole, query.value(0));
                nm2->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableRLS->setItem(row,1,nm2);

                QTableWidgetItem * nm3 = new QTableWidgetItem(query.value(3).toString());
                nm3->setData(Qt::UserRole, query.value(0));
                nm3->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableRLS->setItem(row,2,nm3);

                QTableWidgetItem * nm4 = new QTableWidgetItem(query.value(9).toString());
                nm4->setData(Qt::UserRole, query.value(0));
                nm4->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableRLS->setItem(row,3,nm4);

                QTableWidgetItem * nm5 = new QTableWidgetItem(query.value(4).toString());
                nm5->setData(Qt::UserRole, query.value(0));
                nm5->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableRLS->setItem(row,4,nm5);

                QTableWidgetItem * nm6 = new QTableWidgetItem(query.value(5).toString());
                nm6->setData(Qt::UserRole, query.value(0));
                nm6->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableRLS->setItem(row,5,nm6);

                QTableWidgetItem * nm7 = new QTableWidgetItem(query.value(6).toString());
                nm7->setData(Qt::UserRole, query.value(0));
                nm7->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableRLS->setItem(row,6,nm7);

                QTableWidgetItem * nm8 = new QTableWidgetItem(query.value(7).toString());
                nm8->setData(Qt::UserRole, query.value(0));
                nm8->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableRLS->setItem(row,7,nm8);

                QTableWidgetItem * nm9 = new QTableWidgetItem(query.value(10).toString());
                nm9->setData(Qt::UserRole, query.value(0));
                nm9->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableRLS->setItem(row,8,nm9);

                QTableWidgetItem * nm10 = new QTableWidgetItem(query.value(11).toString());
                nm10->setData(Qt::UserRole, query.value(0));
                nm10->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableRLS->setItem(row,9,nm10);

                ++row;
        }
}

void Window::updateTableObject()
{

   // ui->IUStableObject->clear();
    QString sql_str;
    ui->IUStableObject->setRowCount(0);


     if(isOnRLS(1)==0) sql_str = QString("select * from objects where id_rls=1  ");
     if(isOnRLS(2)==0) sql_str = QString("select * from objects where id_rls=2  ");
     if((isOnRLS(1)==0)&&(isOnRLS(2)==0)) sql_str = QString("select * from objects ");

    QSqlQuery query(sql_str);
        int row =0;
        while(query.next()) {
                ui->IUStableObject->insertRow(row);

                QTableWidgetItem * nm1 = new QTableWidgetItem(query.value(2).toString());
                nm1->setData(Qt::UserRole, query.value(0));
                nm1->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableObject->setItem(row,0, nm1);

                QTableWidgetItem * nm2 = new QTableWidgetItem(query.value(3).toString());
                nm2->setData(Qt::UserRole, query.value(0));
                nm2->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableObject->setItem(row,1,nm2);

                QTableWidgetItem * nm3 = new QTableWidgetItem(query.value(4).toString());
                nm3->setData(Qt::UserRole, query.value(0));
                nm3->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableObject->setItem(row,2,nm3);

                QTableWidgetItem * nm4 = new QTableWidgetItem(query.value(5).toString());
                nm4->setData(Qt::UserRole, query.value(0));
                nm4->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableObject->setItem(row,3,nm4);

                if(query.value(16).toInt()<0)
                {
                    int p=query.value(17).toInt()+180;
                    QString pel =QString("%1").arg(p);
                    QTableWidgetItem * nm5 = new QTableWidgetItem(pel);
                    nm5->setData(Qt::UserRole, query.value(0));
                    nm5->setTextAlignment(Qt::AlignHCenter);
                    ui->IUStableObject->setItem(row,4,nm5);

                    int d=-(query.value(16).toInt());
                    QString dal =QString("%1").arg(d);
                    QTableWidgetItem * nm6 = new QTableWidgetItem(dal);
                    nm6->setData(Qt::UserRole, query.value(0));
                    nm6->setTextAlignment(Qt::AlignHCenter);
                    ui->IUStableObject->setItem(row,5,nm6);
                }
                else
                {
                    QTableWidgetItem * nm5 = new QTableWidgetItem(query.value(17).toString());
                    nm5->setData(Qt::UserRole, query.value(0));
                    nm5->setTextAlignment(Qt::AlignHCenter);
                    ui->IUStableObject->setItem(row,4,nm5);

                    QTableWidgetItem * nm6 = new QTableWidgetItem(query.value(16).toString());
                    nm6->setData(Qt::UserRole, query.value(0));
                    nm6->setTextAlignment(Qt::AlignHCenter);
                    ui->IUStableObject->setItem(row,5,nm6);
                }

                QTableWidgetItem * nm7 = new QTableWidgetItem(query.value(6).toString());
                nm7->setData(Qt::UserRole, query.value(0));
                nm7->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableObject->setItem(row,6,nm7);

                QTableWidgetItem * nm8 = new QTableWidgetItem(query.value(7).toString());
                nm8->setData(Qt::UserRole, query.value(0));
                nm8->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableObject->setItem(row,7,nm8);

                QTableWidgetItem * nm9 = new QTableWidgetItem(query.value(8).toString());
                nm9->setData(Qt::UserRole, query.value(0));
                nm9->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableObject->setItem(row,8,nm9);

                QTableWidgetItem * nm10 = new QTableWidgetItem(query.value(9).toString());
                nm10->setData(Qt::UserRole, query.value(0));
                nm10->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableObject->setItem(row,9,nm10);

                QTableWidgetItem * nm11 = new QTableWidgetItem(query.value(10).toString());
                nm11->setData(Qt::UserRole, query.value(0));
                nm11->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableObject->setItem(row,10,nm11);

                QTableWidgetItem * nm12 = new QTableWidgetItem(query.value(11).toString());
                nm12->setData(Qt::UserRole, query.value(0));
                nm12->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableObject->setItem(row,11,nm12);

                QTableWidgetItem * nm13 = new QTableWidgetItem(query.value(12).toString());
                nm13->setData(Qt::UserRole, query.value(0));
                nm13->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableObject->setItem(row,12,nm13);

                QTableWidgetItem * nm14 = new QTableWidgetItem(query.value(13).toString());
                nm14->setData(Qt::UserRole, query.value(0));
                nm14->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableObject->setItem(row,13,nm14);

                QTableWidgetItem * nm15 = new QTableWidgetItem(query.value(14).toString());
                nm15->setData(Qt::UserRole, query.value(0));
                nm15->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableObject->setItem(row,14,nm15);

                QTableWidgetItem * nm16 = new QTableWidgetItem(query.value(15).toString());
                nm16->setData(Qt::UserRole, query.value(0));
                nm16->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableObject->setItem(row,15,nm16);
                ++row;
        }
}
void Window::updateTableCom()
{
//   ui->IUStableCom->clear();
    ui->IUStableCom->setRowCount(0);
    QString sql_str;

    if(isOnRLS(1)==0) sql_str = QString("select * from report where  id_rls=1  ");
    if(isOnRLS(2)==0) sql_str = QString("select * from report where  id_rls=2  ");
    if((isOnRLS(1)==0)&&(isOnRLS(2)==0)) sql_str = QString("select * from report ");

    QSqlQuery query(sql_str);
        int row =0;
        while(query.next()) {
                ui->IUStableCom->insertRow(row);

                QTableWidgetItem * nm1 = new QTableWidgetItem(query.value(3).toString());
                nm1->setData(Qt::UserRole, query.value(0));
                nm1->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableCom->setItem(row,0, nm1);

                if(query.value(4)==1){
                    QTableWidgetItem * nm2 = new QTableWidgetItem("Изменение соcтояния");
                    nm2->setData(Qt::UserRole, query.value(0));
                    nm2->setTextAlignment(Qt::AlignHCenter);
                    ui->IUStableCom->setItem(row,1,nm2);
                }
                 if(query.value(4)==2)
                {
                    QTableWidgetItem * nm2 = new QTableWidgetItem("Смена сценария");
                    nm2->setData(Qt::UserRole, query.value(0));
                    nm2->setTextAlignment(Qt::AlignHCenter);
                    ui->IUStableCom->setItem(row,1,nm2);
                }
                if(query.value(4)==3){

                    QTableWidgetItem * nm2 = new QTableWidgetItem("Изменение сектора ответственности");
                    nm2->setData(Qt::UserRole, query.value(0));
                    nm2->setTextAlignment(Qt::AlignHCenter);
                    ui->IUStableCom->setItem(row,1,nm2);
                }
                if(query.value(4)==4){

                    QTableWidgetItem * nm2 = new QTableWidgetItem("Изменение темпа обзора");
                    nm2->setData(Qt::UserRole, query.value(0));
                    nm2->setTextAlignment(Qt::AlignHCenter);
                    ui->IUStableCom->setItem(row,1,nm2);
                }

                QTableWidgetItem * nm3 = new QTableWidgetItem("Да");
                nm3->setData(Qt::UserRole, query.value(0));
                nm3->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableCom->setItem(row,2,nm3);

                if(query.value(7)==false){
                QTableWidgetItem * nm4 = new QTableWidgetItem("Нет");
                nm4->setData(Qt::UserRole, query.value(0));
                nm4->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableCom->setItem(row,3,nm4);
                }
                else
                {

                    QTableWidgetItem * nm4 = new QTableWidgetItem("Да");
                    nm4->setData(Qt::UserRole, query.value(0));
                    nm4->setTextAlignment(Qt::AlignHCenter);
                    ui->IUStableCom->setItem(row,3,nm4);
                }

                if(query.value(6)==false){
                QTableWidgetItem * nm5 = new QTableWidgetItem("Нет");
                nm5->setData(Qt::UserRole, query.value(0));
                nm5->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableCom->setItem(row,4,nm5);
                }
                else
                {

                    QTableWidgetItem * nm5 = new QTableWidgetItem("Да");
                    nm5->setData(Qt::UserRole, query.value(0));
                    nm5->setTextAlignment(Qt::AlignHCenter);
                    ui->IUStableCom->setItem(row,4,nm5);
                }
                ++row;
        }


}
void Window::updateTableDoc()
{
    ui->IUStableDoc->setRowCount(0);

    QString sql_str;

    if(isOnRLS(1)==0) sql_str = QString("select * from report where issign=true and id_rls=1  ");
    if(isOnRLS(2)==0) sql_str = QString("select * from report where issign=true and  id_rls=2  ");
    if((isOnRLS(1)==0)&&(isOnRLS(2)==0)) sql_str = QString("select * from report where issign=true ");
      QSqlQuery query(sql_str);
int row =0;
        while(query.next()) {
                ui->IUStableDoc->insertRow(row);

                QTableWidgetItem * nm1 = new QTableWidgetItem(query.value(3).toString());
                nm1->setData(Qt::UserRole, query.value(0));
                nm1->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableDoc->setItem(row,0, nm1);

                if(query.value(4)==1)
                {
                    QTableWidgetItem * nm2 = new QTableWidgetItem("Изменение соcтояния");
                    nm2->setData(Qt::UserRole, query.value(0));
                    nm2->setTextAlignment(Qt::AlignHCenter);
                    ui->IUStableDoc->setItem(row,1,nm2);
                }
                 if(query.value(4)==2)
                {
                    QTableWidgetItem * nm2 = new QTableWidgetItem("Смена сценария");
                    nm2->setData(Qt::UserRole, query.value(0));
                    nm2->setTextAlignment(Qt::AlignHCenter);
                    ui->IUStableDoc->setItem(row,1,nm2);
                }
                if(query.value(4)==3)
                {

                    QTableWidgetItem * nm2 = new QTableWidgetItem("Изменение сектора ответственности");
                    nm2->setData(Qt::UserRole, query.value(0));
                    nm2->setTextAlignment(Qt::AlignHCenter);
                    ui->IUStableDoc->setItem(row,1,nm2);
                }
                if(query.value(4)==4)
                {

                    QTableWidgetItem * nm2 = new QTableWidgetItem("Изменение темпа обзора");
                    nm2->setData(Qt::UserRole, query.value(0));
                    nm2->setTextAlignment(Qt::AlignHCenter);
                    ui->IUStableDoc->setItem(row,1,nm2);
                }
                QTableWidgetItem * nm3 = new QTableWidgetItem("Да");
                nm3->setData(Qt::UserRole, query.value(0));
                nm3->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableDoc->setItem(row,2,nm3);


                QTableWidgetItem * nm4 = new QTableWidgetItem(query.value(5).toString());
                nm4->setData(Qt::UserRole, query.value(0));
                nm4->setTextAlignment(Qt::AlignHCenter);
                ui->IUStableDoc->setItem(row,3,nm4);

                ++row;

        }
}

void Window::updateDatabaseSlot()
{
//    updateTableRLS();
}

void Window::slotRLS(int id,int type)
{
    updateTableCom();
    if (id==1)
    {
    rls1->show();
    rls1->setTables();
    rls1->setIdRLS(id);
    }
    else
    {
        rls2->show();
        rls2->setTables();
        rls2->setIdRLS(id);
    }
    startTimer(1000);
}
void Window::timerEvent(QTimerEvent *)
{
    emit setCourse(0.0);
}
