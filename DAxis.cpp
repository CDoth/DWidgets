#include "DAxis.h"
#include <QDebug>
#include <iostream>

DAxis::DAxis() {
    clear();
}
bool DAxis::draw(QPainter *p) {
    if(p) {

//        qDebug() << "draw axis:" << this << p;
        auto oldPen = p->pen();
        p->setPen(QPen(pen));
        p->drawLine(*this);
        p->setPen(oldPen);
    }
    return false;
}

void DAxis::clear() {


//    std::cout << "DAxis::clear"
//              << " autonegative: " << autonegative << " addr: " << (void*)&autonegative
//              << std::endl;

    autonegative = 0.0f;
    size = 0;
    autoscale = 0.9f;
    shift = 0;
    autoshift = true;
    inverted = false;
    negative = 0;


    setColor(Qt::black);
    setWidth(1);
}
void DAxis::setColor(QColor color) {
    pen.setColor(color);
}
void DAxis::setColor(int r, int g, int b, int a) {
    pen.setColor(QColor(r, g, b, a));
}
void DAxis::setWidth(int width) {
    pen.setWidth(width);
}
void DAxis::setAutoscale(float s) {
    autoscale = s;
    size = 0;
}
void DAxis::setSize(int s) {
    size = s;
    autoscale = 0.0f;
}
void DAxis::setNegative(int s) {
    negative = s;
    autonegative = 0.0f;
}
void DAxis::setAutonegative(float s) {
    autonegative = s;
    negative = 0;
}
void DAxis::update(int d) {

    size = autoscale ? d * autoscale : size;
    if(size > d) size = d;
    int freeSpace = d - size;
    if(autoshift || shift > freeSpace) {
        shift = freeSpace / 2;
    }
    if(autonegative) {
        negative = size * autonegative;
    }
    if(negative > size) {
        negative = size;
    }

//    std::cout << "DAxis::update: " << this
//             << " negative: " << negative << " " << (void*)&negative
//             << " autonegative: " << autonegative << " " << (void*)&autonegative
//             << " autoshift: " << autoshift
//             << " size: " << size
//             << " autoscale: " << autoscale
//             << " inverted: " << inverted
//             << std::endl;

}
//==============================================================
D2DAxes::D2DAxes() {
    anchor = QPoint(0,0);
    needUpdate = true;
}
void D2DAxes::draw(QPainter *p) {

    if(needUpdate) updatePoints(p);
    aw.draw(p);
    ah.draw(p);
}
void D2DAxes::setAnchor(Qt::Corner c) {

    needUpdate = true;
    aw.inverted = (c == Qt::TopRightCorner || c == Qt::BottomRightCorner) ? true : false;
    ah.inverted = (c == Qt::TopLeftCorner || c == Qt::TopRightCorner) ? true : false;
}
DAxis &D2DAxes::wAxis() {
    needUpdate = true;
    return aw;
}
DAxis &D2DAxes::hAxis() {
    needUpdate = true;
    return  ah;
}
const DAxis &D2DAxes::wAxisConst() const {
    return aw;
}
const DAxis &D2DAxes::hAxisConst() const {
    return ah;
}
QPoint D2DAxes::getAnchor() const {
    return anchor;
}
void D2DAxes::enableWNegative() {
    needUpdate = true;
    aw.autonegative = 0.5f;
}
void D2DAxes::enableHNegative() {
    needUpdate = true;
    ah.autonegative = 0.5f;
}
void D2DAxes::updatePoints(QPainter *p) {

    int w = p->device()->width();
    int h = p->device()->height();


    aw.update(w);
    ah.update(h);


    anchor = QPoint( aw.inverted ? w - aw.shift - aw.negative : aw.shift + aw.negative ,
                     ah.inverted ? ah.shift + ah.negative : h - ah.shift - ah.negative
                );

    aw.setPoints(QPoint(
                     aw.inverted ? anchor.x() + aw.negative : anchor.x() - aw.negative,
                     anchor.y()
                     ),
                 QPoint(
                     aw.inverted ? anchor.x() - aw.size + aw.negative : anchor.x() + aw.size - aw.negative,
                     anchor.y()
                     )
                 );
    ah.setPoints(QPoint(
                     anchor.x(),
                     ah.inverted ? anchor.y() - ah.negative : anchor.y() + ah.negative
                     ),
                 QPoint(
                     anchor.x(),
                     ah.inverted ? anchor.y() + ah.size - ah.negative : anchor.y() - ah.size + ah.negative
                       )
                 );
    needUpdate = false;
}
