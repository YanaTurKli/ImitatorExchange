#ifndef NWDGRAPHICVIEW_H
#define NWDGRAPHICVIEW_H


#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

class NWdGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
            QSqlDatabase db;
    explicit NWdGraphicView(QWidget *parent = 0);
    ~NWdGraphicView();

public Q_SLOTS:

    void onSetIdRLS(int id);
private slots:


private:
    QGraphicsScene      *scene;     // Объявляем сцену для отрисовки
        double course = 30.0;
    int Id;
    QTimer              *timer;
    struct objects
    {
        int numb;
        QString type;
    };

    QMap<int,objects> objs;

private:

    /**
     * @brief отрисовка фона
     * @param painter
     * @param rect
     */
    void drawBackground(QPainter *paint, const QRectF &rect) override;

    /**
     * @brief отрисовка переднего плана
     * @param painter
     * @param rect
     */
    void drawForeground(QPainter *paint, const QRectF &rect);
};


#endif // NWDGRAPHICVIEW_H
