#include "nwdgraphicview.h"

NWdGraphicView::NWdGraphicView(QWidget *parent) : QGraphicsView(parent)
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
}
NWdGraphicView::~NWdGraphicView()
{

}


void NWdGraphicView::onSetIdRLS(int id)
{
    this->Id = id;
    scene->update();
}


void  NWdGraphicView::drawBackground(QPainter *paint, const QRectF &rect)
{
    Q_UNUSED(rect)

    paint->setRenderHint(QPainter::Antialiasing);

    // отрисовка сторон света
    QPen pen(Qt::black, 1, Qt::SolidLine);
    paint->setPen(pen);

    int radius = qMin(this->width(), this->height()) / 2 - 20;
    paint->drawEllipse(QPoint(0, 0), radius, radius);
    paint->drawEllipse(QPoint(0, 0), radius + 10, radius + 10);

    QVector<QString> cardinalPointName = {"N", "NE", "E", "SE", "S", "SW", "W","NW"};
    for (int i = 0; i < 360; i += 15) {
        if (i % 90 == 0)
            paint->drawText(QPoint(-5, -radius), cardinalPointName[i / 45]);
        else if (i % 45 == 0)
            paint->drawText(QPoint(-10, -radius), cardinalPointName[i / 45]);

        if (i % 45 == 0)
            paint->drawLine(radius + 10, 0, radius + 20, 0);
        else
            paint->drawLine(radius, 0, radius + 10, 0);

        paint->rotate(15);
    }

    // отрисовка своего корабля
    pen.setColor(Qt::darkGray);
    pen.setWidth(2);
    paint->setPen(pen);

    paint->rotate(this->course);
    QPolygonF polygon;
    polygon << QPointF(0, 0)
            << QPointF(5, 10)
            << QPointF(5, 20)
            << QPointF(-5, 20)
            << QPointF(-5, 10)
            << QPointF(0, 0);
    paint->drawPolygon(polygon);

    QPainterPath path;
    path.addPolygon(polygon);

    QBrush brush;
    brush.setColor(Qt::gray);
    brush.setStyle(Qt::SolidPattern);
    paint->fillPath(path, brush);
    paint->setRenderHint(QPainter::Antialiasing);


}

void NWdGraphicView::drawForeground(QPainter *paint, const QRectF &rect)
{
    Q_UNUSED(rect)

    paint->setRenderHint(QPainter::Antialiasing);

 double peleng = 180;
 double d= 99;
     QString sql_str = QString("select * from objects where id_rls=%1 ").arg(Id) ;
     QSqlQuery query(sql_str);
         while(query.next()) {
             peleng= query.value(17).toInt();
             d= query.value(16).toInt();
        double dx = d * qSin(qDegreesToRadians(peleng));
        double dy = -d * qCos(qDegreesToRadians(peleng));
        paint->translate(dx, dy);
        paint->rotate(peleng - 180);

        if (query.value(3).toString()=="Свой")
        {
            QPen pen(Qt::green, 1, Qt::SolidLine);
            paint->setPen(pen);

        }
        else{
            QPen pen(Qt::red, 1, Qt::SolidLine);
            paint->setPen(pen);
        }
        if(query.value(4).toString()=="Воздушный")
        {
                    paint->drawLine(-10, 0, 10, 0);
                    paint->drawLine(0, 20, 0, 0);

               }
        if(query.value(4).toString()=="Надводный")
        {
            QPolygonF polygon;
            polygon << QPointF(0, 0)
                    << QPointF(5, 10)
                    << QPointF(5, 20)
                    << QPointF(-5, 20)
                    << QPointF(-5, 10)
                    << QPointF(0, 0);
            paint->drawPolygon(polygon);
        }

        paint->rotate(180 - peleng);
        paint->translate(-dx, -dy);
    }
}
