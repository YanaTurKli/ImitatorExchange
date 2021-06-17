#include "nwindow.h"
#include "ui_nwindow.h"

NWindow::NWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NWindow)
{
    ui->setupUi(this);

    /* Инициализируем виджет с графикой */
    graphic = new NWdGraphicView();
    /* и добавляем его на слой */
    connect(this, SIGNAL(setIdRLS(int)), graphic, SLOT(onSetIdRLS(int)));
//    connect(this, SIGNAL(setTarget(Target)), tw, SLOT(onTargetSet(Target)));
//    connect(this, SIGNAL(delTarget(Target)), tw, SLOT(onTargetDelete(Target)));
      ui->RLSgraphicsLayout->addWidget(graphic);

    ui->stackW->setCurrentIndex(1);
        connect(ui->RLSpbInsertKom,SIGNAL(released()),this,SLOT(on_pbInsertKom_2()));
            connect(ui->RLSpbInsDoc,SIGNAL(clicked()),this,SLOT(pb_pbInsDoc_click()));
            connect(ui->RLSpbInsObj,SIGNAL(clicked()),this,SLOT(pb_pbInsObj_click()));
}

NWindow::~NWindow()
{
    delete ui;
}
void NWindow::pb_pbInsDoc_click()
{
    WdDoc *w2 = new WdDoc();
   w2->show();
    w2->setWindowTitle("Формирование доклада");
   //connect(w2, SIGNAL(loadDatabaseSignal(int)), this, SLOT(newRls(int)));


}
void NWindow::pb_pbInsObj_click()
{
    WdObj *w2 = new WdObj();
   w2->show();
    w2->setWindowTitle("Добавление/редактирование обстановки");
   //connect(w2, SIGNAL(loadDatabaseSignal(int)), this, SLOT(newRls(int)));


}

void NWindow::NWupdateTableCom(int id)
{
    Pr=id;/*
    ui->RLStableCom->clear();*/
    ui->RLStableCom->setRowCount(0);

    QStringList headers;
    headers.clear();
    headers << "Номер";
    headers << "Тип";
    headers << "Принята";
    headers << "Обработана";
    headers << "Доклад";


    ui->RLStableCom->setColumnCount(5);
    ui->RLStableCom->setHorizontalHeaderLabels(headers);
    ui->RLStableCom->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->RLStableCom->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->RLStableCom->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->RLStableCom->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->RLStableCom->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui->RLStableCom->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);

    QString sql_str = QString("select * from report where id_rls=%1 and issign=false").arg(id);
    QSqlQuery query(sql_str);
        int row =0;
        while(query.next()) {
                ui->RLStableCom->insertRow(row);

                QTableWidgetItem * nm1 = new QTableWidgetItem(query.value(3).toString());
                nm1->setData(Qt::UserRole, query.value(0));
                nm1->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableCom->setItem(row,0, nm1);

                if(query.value(4)==1){
                    QTableWidgetItem * nm2 = new QTableWidgetItem("Изменение сотояния");
                    nm2->setData(Qt::UserRole, query.value(0));
                    nm2->setTextAlignment(Qt::AlignHCenter);
                    ui->RLStableCom->setItem(row,1,nm2);
                }
                else
                {
                    QTableWidgetItem * nm2 = new QTableWidgetItem("Изменение чего то");
                    nm2->setData(Qt::UserRole, query.value(0));
                    nm2->setTextAlignment(Qt::AlignHCenter);
                    ui->RLStableCom->setItem(row,1,nm2);
                }

                QTableWidgetItem * nm3 = new QTableWidgetItem("Да");
                nm3->setData(Qt::UserRole, query.value(0));
                nm3->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableCom->setItem(row,2,nm3);

                if(query.value(7)==false){
                QTableWidgetItem * nm4 = new QTableWidgetItem("Нет");
                nm4->setData(Qt::UserRole, query.value(0));
                nm4->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableCom->setItem(row,3,nm4);
                }
                else
                {

                    QTableWidgetItem * nm4 = new QTableWidgetItem("Да");
                    nm4->setData(Qt::UserRole, query.value(0));
                    nm4->setTextAlignment(Qt::AlignHCenter);
                    ui->RLStableCom->setItem(row,3,nm4);
                }

                if(query.value(6)==false){
                QTableWidgetItem * nm5 = new QTableWidgetItem("Нет");
                nm5->setData(Qt::UserRole, query.value(0));
                nm5->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableCom->setItem(row,4,nm5);
                }
                else
                {

                    QTableWidgetItem * nm5 = new QTableWidgetItem("Да");
                    nm5->setData(Qt::UserRole, query.value(0));
                    nm5->setTextAlignment(Qt::AlignHCenter);
                    ui->RLStableCom->setItem(row,4,nm5);
                }
                ++row;
        }
        ui->label_2->setText(QString("%1").arg(id));
        this->setWindowTitle("Абонент"+QString("%1").arg(id));
        ui->RLStableRLS->clear();
        ui->RLStableRLS->setRowCount(0);


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
        headers << "Сигнал";

        ui->RLStableRLS->setColumnCount(11);
        ui->RLStableRLS->setHorizontalHeaderLabels(headers);
        ui->RLStableRLS->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
        ui->RLStableRLS->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        ui->RLStableRLS->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
        ui->RLStableRLS->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
        ui->RLStableRLS->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
        ui->RLStableRLS->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
        ui->RLStableRLS->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
        ui->RLStableRLS->horizontalHeader()->setSectionResizeMode(7, QHeaderView::Stretch);
        ui->RLStableRLS->horizontalHeader()->setSectionResizeMode(8, QHeaderView::Stretch);
        ui->RLStableRLS->horizontalHeader()->setSectionResizeMode(9, QHeaderView::Stretch);
        ui->RLStableRLS->horizontalHeader()->setSectionResizeMode(10, QHeaderView::Stretch);

        sql_str = QString("select * from rls where id_rls=%1").arg(id);
        QSqlQuery query2(sql_str);
            row =0;
            while(query2.next()) {

                 ui->label->setText(query2.value(2).toString());
                    ui->RLStableRLS->insertRow(row);

                    QTableWidgetItem * nm1 = new QTableWidgetItem(query2.value(2).toString());
                    nm1->setData(Qt::UserRole, query2.value(0));
                    nm1->setTextAlignment(Qt::AlignHCenter);
                    ui->RLStableRLS->setItem(row,0, nm1);

                    QTableWidgetItem * nm2 = new QTableWidgetItem(query2.value(1).toString());
                    nm2->setData(Qt::UserRole, query2.value(0));
                    nm2->setTextAlignment(Qt::AlignHCenter);
                    ui->RLStableRLS->setItem(row,1,nm2);

                    QTableWidgetItem * nm3 = new QTableWidgetItem("Выключено");
                    nm3->setData(Qt::UserRole, query2.value(0));
                    nm3->setTextAlignment(Qt::AlignHCenter);
                    ui->RLStableRLS->setItem(row,2,nm3);

                    QTableWidgetItem * nm4 = new QTableWidgetItem(query2.value(9).toString());
                    nm4->setData(Qt::UserRole, query2.value(0));
                    nm4->setTextAlignment(Qt::AlignHCenter);
                    ui->RLStableRLS->setItem(row,3,nm4);

                    QTableWidgetItem * nm5 = new QTableWidgetItem(query2.value(4).toString());
                    nm5->setData(Qt::UserRole, query2.value(0));
                    nm5->setTextAlignment(Qt::AlignHCenter);
                    ui->RLStableRLS->setItem(row,4,nm5);

                    QTableWidgetItem * nm6 = new QTableWidgetItem(query2.value(5).toString());
                    nm6->setData(Qt::UserRole, query2.value(0));
                    nm6->setTextAlignment(Qt::AlignHCenter);
                    ui->RLStableRLS->setItem(row,5,nm6);

                    QTableWidgetItem * nm7 = new QTableWidgetItem(query2.value(6).toString());
                    nm7->setData(Qt::UserRole, query2.value(0));
                    nm7->setTextAlignment(Qt::AlignHCenter);
                    ui->RLStableRLS->setItem(row,6,nm7);

                    QTableWidgetItem * nm8 = new QTableWidgetItem(query2.value(7).toString());
                    nm8->setData(Qt::UserRole, query2.value(0));
                    nm8->setTextAlignment(Qt::AlignHCenter);
                    ui->RLStableRLS->setItem(row,7,nm8);

                    QTableWidgetItem * nm9 = new QTableWidgetItem(query2.value(9).toString());
                    nm9->setData(Qt::UserRole, query2.value(0));
                    nm9->setTextAlignment(Qt::AlignHCenter);
                    ui->RLStableRLS->setItem(row,8,nm9);

                    QTableWidgetItem * nm10 = new QTableWidgetItem(query2.value(10).toString());
                    nm10->setData(Qt::UserRole, query2.value(0));
                    nm10->setTextAlignment(Qt::AlignHCenter);
                    ui->RLStableRLS->setItem(row,9,nm10);

                    QTableWidgetItem * nm11 = new QTableWidgetItem(query2.value(8).toString());
                    nm11->setData(Qt::UserRole, query2.value(0));
                    nm11->setTextAlignment(Qt::AlignHCenter);
                    ui->RLStableRLS->setItem(row,10,nm11);
                    ++row;
            }
            ui->RLStableObject->clear();
            ui->RLStableObject->setRowCount(0);

            headers.clear();
            headers << "Номер";
            headers << "Принад-\nлежность";
            headers << "Класс";
            headers << "Тип";
            headers << "Курс";
            headers << "Скорость";
            headers << "Скорость\nпо\nвысоте";
            headers << "Х";
            headers << "Y";
            headers << "H";
            headers << "Время\nобнаруж.";
            headers << "Ek";
            headers << "Ev";
            headers << "Evh";

            ui->RLStableObject->setColumnCount(14);
            ui->RLStableObject->setHorizontalHeaderLabels(headers);
            ui->RLStableObject->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
            ui->RLStableObject->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
            ui->RLStableObject->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
            ui->RLStableObject->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
            ui->RLStableObject->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
            ui->RLStableObject->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
            ui->RLStableObject->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
            ui->RLStableObject->horizontalHeader()->setSectionResizeMode(7, QHeaderView::Stretch);
            ui->RLStableObject->horizontalHeader()->setSectionResizeMode(8, QHeaderView::Stretch);
            ui->RLStableObject->horizontalHeader()->setSectionResizeMode(9, QHeaderView::Stretch);
            ui->RLStableObject->horizontalHeader()->setSectionResizeMode(10, QHeaderView::Stretch);
            ui->RLStableObject->horizontalHeader()->setSectionResizeMode(11, QHeaderView::Stretch);
            ui->RLStableObject->horizontalHeader()->setSectionResizeMode(12, QHeaderView::Stretch);
            ui->RLStableObject->horizontalHeader()->setSectionResizeMode(13, QHeaderView::Stretch);

            headers.clear();
            headers << "Номер";
            headers << "Тип";
            headers << "Cформирован";
            headers << "Ошибка";

            ui->RLStableDoc->setColumnCount(4);
            ui->RLStableDoc->setHorizontalHeaderLabels(headers);
            ui->RLStableDoc->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
            ui->RLStableDoc->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
            ui->RLStableDoc->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
            ui->RLStableDoc->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
            ui->RLStableDoc->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
             emit updateParamCom(id);
}
void NWindow::NWupdateTableRLS(int ind)
{
    ui->label_2->setText(QString("%1").arg(ind));
    ui->RLStableRLS->clear();
    ui->RLStableRLS->setRowCount(0);

    QStringList headers;
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
    headers << "Сигнал";

    ui->RLStableRLS->setColumnCount(11);
    ui->RLStableRLS->setHorizontalHeaderLabels(headers);
    ui->RLStableRLS->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->RLStableRLS->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->RLStableRLS->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->RLStableRLS->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->RLStableRLS->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui->RLStableRLS->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    ui->RLStableRLS->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
    ui->RLStableRLS->horizontalHeader()->setSectionResizeMode(7, QHeaderView::Stretch);
    ui->RLStableRLS->horizontalHeader()->setSectionResizeMode(8, QHeaderView::Stretch);
    ui->RLStableRLS->horizontalHeader()->setSectionResizeMode(9, QHeaderView::Stretch);
    ui->RLStableRLS->horizontalHeader()->setSectionResizeMode(10, QHeaderView::Stretch);

    QString sql_str = QString("select * from rls where id_rls=%1").arg(ind);
    QSqlQuery query(sql_str);
        int row =0;
        while(query.next()) {

             ui->label->setText(query.value(2).toString());
                ui->RLStableRLS->insertRow(row);

                QTableWidgetItem * nm1 = new QTableWidgetItem(query.value(2).toString());
                nm1->setData(Qt::UserRole, query.value(0));
                nm1->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableRLS->setItem(row,0, nm1);

                QTableWidgetItem * nm2 = new QTableWidgetItem(query.value(1).toString());
                nm2->setData(Qt::UserRole, query.value(0));
                nm2->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableRLS->setItem(row,1,nm2);

                QTableWidgetItem * nm3 = new QTableWidgetItem(query.value(3).toString());
                nm3->setData(Qt::UserRole, query.value(0));
                nm3->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableRLS->setItem(row,2,nm3);

                QTableWidgetItem * nm4 = new QTableWidgetItem(query.value(9).toString());
                nm4->setData(Qt::UserRole, query.value(0));
                nm4->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableRLS->setItem(row,3,nm4);

                QTableWidgetItem * nm5 = new QTableWidgetItem(query.value(4).toString());
                nm5->setData(Qt::UserRole, query.value(0));
                nm5->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableRLS->setItem(row,4,nm5);

                QTableWidgetItem * nm6 = new QTableWidgetItem(query.value(5).toString());
                nm6->setData(Qt::UserRole, query.value(0));
                nm6->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableRLS->setItem(row,5,nm6);

                QTableWidgetItem * nm7 = new QTableWidgetItem(query.value(6).toString());
                nm7->setData(Qt::UserRole, query.value(0));
                nm7->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableRLS->setItem(row,6,nm7);

                QTableWidgetItem * nm8 = new QTableWidgetItem(query.value(7).toString());
                nm8->setData(Qt::UserRole, query.value(0));
                nm8->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableRLS->setItem(row,7,nm8);

                QTableWidgetItem * nm9 = new QTableWidgetItem(query.value(9).toString());
                nm9->setData(Qt::UserRole, query.value(0));
                nm9->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableRLS->setItem(row,8,nm9);

                QTableWidgetItem * nm10 = new QTableWidgetItem(query.value(10).toString());
                nm10->setData(Qt::UserRole, query.value(0));
                nm10->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableRLS->setItem(row,9,nm10);

                QTableWidgetItem * nm11 = new QTableWidgetItem(query.value(8).toString());
                nm11->setData(Qt::UserRole, query.value(0));
                nm11->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableRLS->setItem(row,10,nm11);
                ++row;
        }
}
void NWindow::NWupdateTableObject(int id)
{
    ui->RLStableObject->clear();
    ui->RLStableObject->setRowCount(0);

    QStringList headers;
    headers.clear();
    headers << "Номер";
    headers << "Принад-\nлежность";
    headers << "Класс";
    headers << "Тип";
    headers << "Курс";
    headers << "Скорость";
    headers << "Скорость\nпо\nвысоте";
    headers << "Х";
    headers << "Y";
    headers << "H";
    headers << "Время\nобнаруж.";
    headers << "Ek";
    headers << "Ev";
    headers << "Evh";

    ui->RLStableObject->setColumnCount(14);
    ui->RLStableObject->setHorizontalHeaderLabels(headers);
    ui->RLStableObject->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->RLStableObject->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->RLStableObject->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->RLStableObject->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->RLStableObject->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    ui->RLStableObject->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    ui->RLStableObject->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
    ui->RLStableObject->horizontalHeader()->setSectionResizeMode(7, QHeaderView::Stretch);
    ui->RLStableObject->horizontalHeader()->setSectionResizeMode(8, QHeaderView::Stretch);
    ui->RLStableObject->horizontalHeader()->setSectionResizeMode(9, QHeaderView::Stretch);
    ui->RLStableObject->horizontalHeader()->setSectionResizeMode(10, QHeaderView::Stretch);
    ui->RLStableObject->horizontalHeader()->setSectionResizeMode(11, QHeaderView::Stretch);
    ui->RLStableObject->horizontalHeader()->setSectionResizeMode(12, QHeaderView::Stretch);
    ui->RLStableObject->horizontalHeader()->setSectionResizeMode(13, QHeaderView::Stretch);

    QString sql_str = QString("select * from objects where id_rls=%1").arg(id);
    QSqlQuery query(sql_str);
        int row =0;
        while(query.next()) {
                ui->RLStableObject->insertRow(row);

                QTableWidgetItem * nm1 = new QTableWidgetItem(query.value(2).toString());
                nm1->setData(Qt::UserRole, query.value(0));
                nm1->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableObject->setItem(row,0, nm1);

                QTableWidgetItem * nm2 = new QTableWidgetItem(query.value(3).toString());
                nm2->setData(Qt::UserRole, query.value(0));
                nm2->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableObject->setItem(row,1,nm2);

                QTableWidgetItem * nm3 = new QTableWidgetItem(query.value(4).toString());
                nm3->setData(Qt::UserRole, query.value(0));
                nm3->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableObject->setItem(row,2,nm3);

                QTableWidgetItem * nm4 = new QTableWidgetItem(query.value(5).toString());
                nm4->setData(Qt::UserRole, query.value(0));
                nm4->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableObject->setItem(row,3,nm4);

                QTableWidgetItem * nm5 = new QTableWidgetItem(query.value(6).toString());
                nm5->setData(Qt::UserRole, query.value(0));
                nm5->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableObject->setItem(row,4,nm5);

                QTableWidgetItem * nm6 = new QTableWidgetItem(query.value(7).toString());
                nm6->setData(Qt::UserRole, query.value(0));
                nm6->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableObject->setItem(row,5,nm6);

                QTableWidgetItem * nm7 = new QTableWidgetItem(query.value(8).toString());
                nm7->setData(Qt::UserRole, query.value(0));
                nm7->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableObject->setItem(row,6,nm7);

                QTableWidgetItem * nm8 = new QTableWidgetItem(query.value(9).toString());
                nm8->setData(Qt::UserRole, query.value(0));
                nm8->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableObject->setItem(row,7,nm8);

                QTableWidgetItem * nm9 = new QTableWidgetItem(query.value(10).toString());
                nm9->setData(Qt::UserRole, query.value(0));
                nm9->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableObject->setItem(row,8,nm9);

                QTableWidgetItem * nm10 = new QTableWidgetItem(query.value(11).toString());
                nm10->setData(Qt::UserRole, query.value(0));
                nm10->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableObject->setItem(row,9,nm10);

                QTableWidgetItem * nm11 = new QTableWidgetItem(query.value(12).toString());
                nm11->setData(Qt::UserRole, query.value(0));
                nm11->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableObject->setItem(row,10,nm11);

                QTableWidgetItem * nm12 = new QTableWidgetItem(query.value(13).toString());
                nm12->setData(Qt::UserRole, query.value(0));
                nm12->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableObject->setItem(row,11,nm12);

                QTableWidgetItem * nm13 = new QTableWidgetItem(query.value(14).toString());
                nm13->setData(Qt::UserRole, query.value(0));
                nm13->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableObject->setItem(row,12,nm13);

                QTableWidgetItem * nm14 = new QTableWidgetItem(query.value(15).toString());
                nm14->setData(Qt::UserRole, query.value(0));
                nm14->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableObject->setItem(row,13,nm14);
                ++row;
        }
}
void NWindow::NWupdateTableDoc(int id)
{
//    ui->tableCom->clear();
//    ui->tableCom->setRowCount(0);

    QStringList headers;
    headers.clear();
    headers << "Номер";
    headers << "Тип";
    headers << "Cформирован";
    headers << "Ошибка";

    ui->RLStableDoc->setColumnCount(4);
    ui->RLStableDoc->setHorizontalHeaderLabels(headers);
    ui->RLStableDoc->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->RLStableDoc->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->RLStableDoc->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->RLStableDoc->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui->RLStableDoc->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    QString sql_str = QString("select * from report where issign=true and id_rls=%1").arg(id);
    QSqlQuery query(sql_str);
        int row =0;
        while(query.next()) {
                ui->RLStableDoc->insertRow(row);

                QTableWidgetItem * nm1 = new QTableWidgetItem(query.value(3).toString());
                nm1->setData(Qt::UserRole, query.value(0));
                nm1->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableDoc->setItem(row,0, nm1);

                if(query.value(4)==1){
                    QTableWidgetItem * nm2 = new QTableWidgetItem("Изменение сотояния");
                    nm2->setData(Qt::UserRole, query.value(0));
                    nm2->setTextAlignment(Qt::AlignHCenter);
                    ui->RLStableDoc->setItem(row,1,nm2);
                }
                else
                {
                    QTableWidgetItem * nm2 = new QTableWidgetItem("Изменение чего то");
                    nm2->setData(Qt::UserRole, query.value(0));
                    nm2->setTextAlignment(Qt::AlignHCenter);
                    ui->RLStableDoc->setItem(row,1,nm2);
                }

                QTableWidgetItem * nm3 = new QTableWidgetItem("Да");
                nm3->setData(Qt::UserRole, query.value(0));
                nm3->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableDoc->setItem(row,2,nm3);


                QTableWidgetItem * nm4 = new QTableWidgetItem(query.value(5).toString());
                nm4->setData(Qt::UserRole, query.value(0));
                nm4->setTextAlignment(Qt::AlignHCenter);
                ui->RLStableDoc->setItem(row,3,nm4);

                ++row;
        }
}

void NWindow::on_RLStableCom_itemClicked(QTableWidgetItem *item)
{
        Id = item->data(Qt::UserRole).toInt();

}

void NWindow::on_pbInsertKom_2()
{
    QSqlQuery *quer = new QSqlQuery(db);
    QString str_sql=QString("UPDATE report set issend =true "
    "where id_report=%1").arg(Id);

   quer->exec(str_sql);
   if(quer->isActive())
   {
       QMessageBox::information(this,"Запрос","Команда сформирована",QMessageBox::Ok);
   }
   else
   {
       QMessageBox::information(this,"Запрос",str_sql,QMessageBox::Ok);
   }

   ui->RLStableCom->setRowCount(0);

   QString sql_str = QString("select * from report where id_rls=%1 and issign=false").arg(Pr);
   QSqlQuery query(sql_str);
       int row =0;
       while(query.next()) {
               ui->RLStableCom->insertRow(row);

               QTableWidgetItem * nm1 = new QTableWidgetItem(query.value(3).toString());
               nm1->setData(Qt::UserRole, query.value(0));
               nm1->setTextAlignment(Qt::AlignHCenter);
               ui->RLStableCom->setItem(row,0, nm1);

               if(query.value(4)==1){
                   QTableWidgetItem * nm2 = new QTableWidgetItem("Изменение сотояния");
                   nm2->setData(Qt::UserRole, query.value(0));
                   nm2->setTextAlignment(Qt::AlignHCenter);
                   ui->RLStableCom->setItem(row,1,nm2);
               }
               else
               {
                   QTableWidgetItem * nm2 = new QTableWidgetItem("Изменение чего то");
                   nm2->setData(Qt::UserRole, query.value(0));
                   nm2->setTextAlignment(Qt::AlignHCenter);
                   ui->RLStableCom->setItem(row,1,nm2);
               }

               QTableWidgetItem * nm3 = new QTableWidgetItem("Да");
               nm3->setData(Qt::UserRole, query.value(0));
               nm3->setTextAlignment(Qt::AlignHCenter);
               ui->RLStableCom->setItem(row,2,nm3);

               if(query.value(7)==false){
               QTableWidgetItem * nm4 = new QTableWidgetItem("Нет");
               nm4->setData(Qt::UserRole, query.value(0));
               nm4->setTextAlignment(Qt::AlignHCenter);
               ui->RLStableCom->setItem(row,3,nm4);
               }
               else
               {

                   QTableWidgetItem * nm4 = new QTableWidgetItem("Да");
                   nm4->setData(Qt::UserRole, query.value(0));
                   nm4->setTextAlignment(Qt::AlignHCenter);
                   ui->RLStableCom->setItem(row,3,nm4);
               }

               if(query.value(6)==false){
               QTableWidgetItem * nm5 = new QTableWidgetItem("Нет");
               nm5->setData(Qt::UserRole, query.value(0));
               nm5->setTextAlignment(Qt::AlignHCenter);
               ui->RLStableCom->setItem(row,4,nm5);
               }
               else
               {

                   QTableWidgetItem * nm5 = new QTableWidgetItem("Да");
                   nm5->setData(Qt::UserRole, query.value(0));
                   nm5->setTextAlignment(Qt::AlignHCenter);
                   ui->RLStableCom->setItem(row,4,nm5);
               }
               ++row;
       }
   NWupdateTableRLS(Pr);
   NWupdateTableObject(Pr);
       emit setIdRLS(Pr);

}
