#ifndef WDGRAPHICVIEW_H
#define WDGRAPHICVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>

class WdGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit WdGraphicView(QWidget *parent = 0);
    ~WdGraphicView();

public Q_SLOTS:
    void onCourse(double course);

private slots:
//    void slotAlarmTimer();  /* слот для обработчика переполнения таймера
//                             * в нём будет производиться перерисовка
//                             * виджета
//                             * */

private:
    QGraphicsScene      *scene;     // Объявляем сцену для отрисовки
        double course = 0.0;
    QGraphicsItemGroup  *group_1;   // Объявляем первую группу элементов
    QGraphicsItemGroup  *group_2;   // Объявляем вторую группу элементов

    /* Таймер для задержки отрисовки.
     * Дело в том, что при создании окна и виджета
     * необходимо некоторое время, чтобы родительский слой
     * развернулся, чтобы принимать от него адекватные параметры
     * ширины и высоты
     * */
    QTimer              *timer;

private:
    /* Перегружаем событие изменения размера окна,
     * чтобы перехватывать его
     * */
//    void resizeEvent(QResizeEvent *event);
//    /* Метод для удаления всех элементов
//     * из группы элементов
//     * */
    void deleteItemsFromGroup(QGraphicsItemGroup *group_1);
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief отрисовка фона
     * @param painter
     * @param rect
     */
    void drawBackground(QPainter *painter, const QRectF &rect) override;
};

#endif // WDGRAPHICVIEW_H
