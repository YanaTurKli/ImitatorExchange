#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include "wdcom.h"
#include "nwindow.h"
#include <QDialog>
#include "ui_wdcom.h"
#include <wdgraphicview.h>
#include <QMainWindow>
#include <QGraphicsView>

//QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
//QT_END_NAMESPACE

class Window : public QMainWindow
{
    Q_OBJECT

public:
     explicit Window(QWidget *parent = 0);
    ~Window();
    QSqlDatabase db;

private:

    Ui::Window *ui;
    WdGraphicView *graphic;

public slots:
   void pb_pbInsert_click();
   void updateTableRLS();
   void updateTableObject(int id);
   void updateDatabaseSlot();
   void updateTableCom(int id);
   void newRls(int id);
   void updateTableDoc(int id);


};
#endif // WINDOW_H
