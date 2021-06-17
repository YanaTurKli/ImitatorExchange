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
#include "nwdgraphicview.h"

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
Q_SIGNALS:
    void setIdRLS(int id);

private:
    Ui::NWindow *ui;
        NWdGraphicView *graphic;
    // QMap<int, Obj> objects;
    //void drawBackground(QPainter *paint, const QRectF &rect) override;

public slots:
   void NWupdateTableObject(int id);
   void NWupdateTableCom(int id);
   void NWupdateTableRLS(int ind);
   void NWupdateTableDoc(int id);
   void on_RLStableCom_itemClicked(QTableWidgetItem * item);
   void on_pbInsertKom_2();
   void pb_pbInsDoc_click();
   void pb_pbInsObj_click();
signals:

    void updateParamCom(int id);
};

#endif // NWINDOW_H
