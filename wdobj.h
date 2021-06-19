#ifndef WDOBJ_H
#define WDOBJ_H

#include <QWidget>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QTime>

namespace Ui {
class WdObj;
}

class WdObj : public QWidget
{
    Q_OBJECT

public:
    explicit WdObj(QWidget *parent = nullptr);
    ~WdObj();
        QSqlDatabase db;
        int id_rls;
        int numb;
       QString type;
       QString class_obj;
       QString sign;
       int k;
       int v;
       int vh;
       int x;
       int y;
       int z;
       double d;
       double peleng;
       QTime t;

Q_SIGNALS:
    void newInsObj(int id);

private:
    Ui::WdObj *ui;

public slots:
    void updateCmbType();
   void onCbType(int index);
   void updateCmbClass();
   void updateCmbSign(int index);
   void oncbClass(int index);
   void onCbSign(int index);
   void on_dsbKurs(double id);
   void on_sbNumb(int id);
   void on_dsbPeleng(double id);
   void on_dsbV(double id);
    void on_dsbVh(double id);
    void on_dsbD(double id);
   void on_pbSave_pressed();
   void on_pushButton_2_pressed();
   void on_time(QTime tim);
   void setIDRLS(int id);


};

#endif // WDOBJ_H
