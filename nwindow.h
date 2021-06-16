#ifndef NWINDOW_H
#define NWINDOW_H

#include <QTableWidget>
#include <QWidget>
#include "wddoc.h"
#include "ui_wddoc.h"
#include "wdobj.h"
#include "ui_wdobj.h"
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsItemGroup>
#include <QTimer>

namespace Ui {
class NWindow;
}

class NWindow : public QWidget
{
    Q_OBJECT

public:
        QSqlDatabase db;
    explicit NWindow(QWidget *parent = nullptr);
    ~NWindow();
        int Id;
        int Pr;

        void paintEvent(QPaintEvent *);
        void drawBackground(QPainter &paint);
    //    void clear(QPainter &paint);
      //  void timerEvent(QTimerEvent *);
//        void initPos();

private:
    Ui::NWindow *ui;
    QGraphicsScene *scene = nullptr;
    // QMap<int, Obj> objects;
    //void drawBackground(QPainter *paint, const QRectF &rect) override;

public slots:
   void NWupdateTableObject(int id);
   void NWupdateTableCom(int id);
   void NWupdateTableRLS(int ind);
   void NWupdateTableDoc(int id);
   void on_tableCom_2_itemClicked(QTableWidgetItem * item);
   void on_pbInsertKom_2();
   void pb_pbInsDoc_click();
   void pb_pbInsObj_click();
signals:

    void updateParamCom(int id);
};

#endif // NWINDOW_H
