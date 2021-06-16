#ifndef WDCOM_H
#define WDCOM_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDialog>

namespace Ui { class WdCom; }


class WdCom : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase db;
    explicit WdCom(QWidget *parent = nullptr);
    ~WdCom();


private:

    Ui::WdCom *ui;
    int id_type;
    int id_com;
   QString id_number;
   int id_sector;
   int id_sost;
   int id_scena;
   int id_num;

public slots:
   void updateCmbNumber(int id);
   void updateCmbSector();
   void updateCmbSost();
   void updateCmbScena();
   void updateCmbCom();
   void onCbType(int index);
   void onCbNumber(int index);
   void onCbCom(int index);
   void onCbSector(int index);
   void onCbScena(int index);
   void onCbSost(int index);
   void on_pbSave_pressed();
   void on_pushButton_2_pressed();
   void on_spNum(int id);
   void updateCmbType();

signals:

    void loadDatabaseSignal(int id);

};

#endif // WDCOM_H
