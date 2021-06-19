#ifndef WDDOC_H
#define WDDOC_H

#include <QWidget>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

namespace Ui {
class WdDoc;
}

class WdDoc : public QWidget
{
    Q_OBJECT

public:
        QSqlDatabase db;
    explicit WdDoc(QWidget *parent = nullptr);
    ~WdDoc();
        int id_rls;
        QString numb;

Q_SIGNALS:
    void newInsDoc(int id);
private:
    Ui::WdDoc *ui;
public slots:
      void setIDRLS(int id);
      void updateCmbNumb();
      void onCbNumb(int id);
      void on_pushButton_2_pressed();
      void on_pbSave_pressed();
};

#endif // WDDOC_H
