#include "wdgraphicview.h"

WdGraphicView::WdGraphicView(QWidget *parent) : QGraphicsView(parent)
{
    /* Немного поднастроим отображение виджета и его содержимого */
       this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключим скроллбар по горизонтали
       this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключим скроллбар по вертикали
       this->setAlignment(Qt::AlignCenter);                        // Делаем привязку содержимого к центру
       this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);    // Растягиваем содержимое по виджету

       /* Также зададим минимальные размеры виджета
        * */
       this->setMinimumHeight(100);
       this->setMinimumWidth(100);

       scene = new QGraphicsScene();   // Инициализируем сцену для отрисовки
       this->setScene(scene);          // Устанавливаем сцену в виджет

//       group_1 = new QGraphicsItemGroup(); // Инициализируем первую группу элементов
//       group_2 = new QGraphicsItemGroup(); // Инициализируем вторую группу элементов

//       scene->addItem(group_1);            // Добавляем первую группу в сцену
//       scene->addItem(group_2);            // Добавляем вторую группу в сцену

//       timer = new QTimer();               // Инициализируем Таймер
//       timer->setSingleShot(true);
//       // Подключаем СЛОТ для отрисовки к таймеру
//       connect(timer, SIGNAL(timeout()), this, SLOT(drawBackground()));
//       timer->start(50);                   // Стартуем таймер на 50 миллисекунд
}
WdGraphicView::~WdGraphicView()
{

}

void WdGraphicView::onCourse(double course)
{
    this->course = course;
    scene->update();
}

//void WdGraphicView::onTargetSet(Target target)
//{
//    targets.insert(target.id, target);
//    scene->update();
//}

//void WdGraphicView::onTargetDelete(Target target)
//{
//    targets.remove(target.id);
//    scene->update();
//}

void WdGraphicView::mousePressEvent(QMouseEvent *event)
{
//    double rad = 1;
//    QPointF pt = mapToScene(event->pos());
//    scene->addEllipse(pt.x()-rad, pt.y()-rad, rad*2.0, rad*2.0,
//                      QPen(), QBrush(Qt::SolidPattern));
}

void  WdGraphicView::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect)

    painter->setRenderHint(QPainter::Antialiasing);

    // отрисовка сторон света
    QPen pen(Qt::black, 1, Qt::SolidLine);
    painter->setPen(pen);

    int radius = qMin(this->width(), this->height()) / 2 - 20;
    painter->drawEllipse(QPoint(0, 0), radius, radius);
    painter->drawEllipse(QPoint(0, 0), radius + 10, radius + 10);

    QVector<QString> cardinalPointName = {"N", "NE", "E", "SE", "S", "SW", "W","NW"};
    for (int i = 0; i < 360; i += 15) {
        if (i % 90 == 0)
            painter->drawText(QPoint(-5, -radius), cardinalPointName[i / 45]);
        else if (i % 45 == 0)
            painter->drawText(QPoint(-10, -radius), cardinalPointName[i / 45]);

        if (i % 45 == 0)
            painter->drawLine(radius + 10, 0, radius + 20, 0);
        else
            painter->drawLine(radius, 0, radius + 10, 0);

        painter->rotate(15);
    }

    // отрисовка своего корабля
    pen.setColor(Qt::darkGray);
    pen.setWidth(2);
    painter->setPen(pen);

    painter->rotate(this->course);
    QPolygonF polygon;
    polygon << QPointF(0, 0)
            << QPointF(5, 10)
            << QPointF(5, 20)
            << QPointF(-5, 20)
            << QPointF(-5, 10)
            << QPointF(0, 0);
    painter->drawPolygon(polygon);

    QPainterPath path;
    path.addPolygon(polygon);

    QBrush brush;
    brush.setColor(Qt::gray);
    brush.setStyle(Qt::SolidPattern);
    painter->fillPath(path, brush);
};

//void WdGraphicView::drawForeground(QPainter *painter, const QRectF &rect)
//{
//    Q_UNUSED(rect)

//    painter->setRenderHint(QPainter::Antialiasing);

//    QPen pen(Qt::blue, 1, Qt::SolidLine);
//    painter->setPen(pen);

//    for (QMapIterator<int, Target> it(targets); it.hasNext();) {
//        it.next();

//        Target const &target = it.value();
//        double dx = target.range * qSin(qDegreesToRadians(target.bearing));
//        double dy = -target.range * qCos(qDegreesToRadians(target.bearing));
//        painter->translate(dx, dy);
//        painter->rotate(target.bearing - 180);

//        switch (target.typeId) {
//        case TargetType::Surface:
//        {
//            QPolygonF polygon;
//            polygon << QPointF(0, 0)
//                    << QPointF(5, 10)
//                    << QPointF(5, 25)
//                    << QPointF(-5, 25)
//                    << QPointF(-5, 10)
//                    << QPointF(0, 0);
//            painter->drawPolygon(polygon);
//        }
//            break;
//        case TargetType::Subsurface:
//            painter->drawEllipse(0, 0, 10, 10);
//            break;
//        case TargetType::Air:
//            painter->drawLine(-10, 0, 10, 0);
//            painter->drawLine(0, 20, 0, 0);
//            break;
//        default:
//            break;
//        }

//        painter->rotate(180 - target.bearing);
//        painter->translate(-dx, -dy);
//    }
//}
