#ifndef WDGRAPHICVIEW_H
#define WDGRAPHICVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

class WdGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
            QSqlDatabase db;
    explicit WdGraphicView(QWidget *parent = 0);
    ~WdGraphicView();

public Q_SLOTS:
        void onSetCourse(double course);

private slots:


private:
    QGraphicsScene      *scene;     // Объявляем сцену для отрисовки
        double course = 0.0;

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
    int isOnRLS(int id);
};

#endif // WDGRAPHICVIEW_H
