#include "DWidget.h"
#include <QPen>
#include <QPainter>
#include <QEvent>

void drawMainRect(QPainter *p, const QRect &r, int width, const QColor &rect_color, const QColor &area_color)
{
    if(p && width > 0)
    {
        QRect _r = QRect(0,0, r.width()-1, r.height()-1);
        QPen pen(QPen(rect_color, width));
//        pen.setStyle(Qt::DotLine);
        p->setPen(pen);
        p->setBrush(QBrush(area_color));

        p->drawRect(_r);
    }
}


void DWidget::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    drawRect(&p);
}
bool DWidget::eventFilter(QObject *watcher, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        emit clicked();
    }
    return false;
}
void DWidget::resizeEvent(QResizeEvent *event)
{
//    qDebug()<<"DWidget resize:" << this << size();
    emit resized();
}

void DWidget::drawRect(QPainter *p) {
    if(rect_drawable) {
        drawMainRect(p, rect(), rect_width, color_rect);
    }
}
DWidget::DWidget(QWidget *parent) : QWidget(parent)
{
    rect_drawable = true;
    color_rect = QColor(0,0,0,0);
    color_area = QColor(0,0,0,0);
    rect_width = 1;
    installEventFilter(this);


    setBackgroundRole(QPalette::Window);
    setAutoFillBackground(true);
}
DWidget::~DWidget()
{

}
void DWidget::enableRect(bool status)
{
    rect_drawable = status;
}
void DWidget::setRectColor(int r, int g, int b)
{
    color_rect = QColor(r,g,b);
}
void DWidget::setRectColor(QColor c)
{
    color_rect = c;
}
void DWidget::setRectWidth(int w)
{
    rect_width = w;
}
void DWidget::setMainColor(int r, int g, int b, int a)
{
    color_area = QColor(r,g,b,a);
    QPalette palette;
    palette.setColor(QPalette::All, QPalette::Window, color_area);
    setPalette(palette);
}
void DWidget::setMainColor(const QColor &c)
{
    color_area = c;
    QPalette palette;
    palette.setColor(QPalette::All, QPalette::Window, color_area);
    setPalette(palette);
}
void DWidget::enableMainColor(bool s)
{
    if(s) color_area.setAlpha(255);
    else color_area.setAlpha(0);
}
