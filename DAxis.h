#ifndef DAXIS_H
#define DAXIS_H
#include <QColor>
#include <QPainter>
#include <QWidget>

class DAxis : public QLine {
public:

    friend class D2DAxes;
    DAxis();
    bool draw(QPainter *p);
    void clear();

    void setColor(QColor color);
    void setColor(int r, int g, int b, int a = 255);
    void setWidth(int width);
    void setAutoscale(float s);
    void setSize(int s);
    void setNegative(int s);
    void setAutonegative(float s);

    QColor getColor() const {return pen.color();}
    int getWidth() const {return pen.width();}
    int getSize() const {return size;}
    float getAutoscale() const {return autoscale;}
    int getShift() const {return shift;}
    int getNegativeValue() const {return negative;}
    float getAutonegative() const {return autonegative;}
    bool isAutoshifted() const {return autoshift;}
    bool isInverted() const {return inverted;}



private:
    void update(int d);
private:
    QPen pen;
    int size;
    float autoscale;
    int shift;
    bool autoshift;
    bool inverted;
    int negative;
    float autonegative;
};


class D2DAxes {
public:
    D2DAxes();

    void draw(QPainter *p);
    void setAnchor(Qt::Corner c);

    DAxis& wAxis();
    DAxis& hAxis();
    const DAxis& wAxisConst() const;
    const DAxis& hAxisConst() const;
    QPoint getAnchor() const;
    void enableWNegative();
    void enableHNegative();
    void update() {needUpdate = true;}

private:
    void updatePoints(QPainter *p);
private:
    QPoint anchor;
    DAxis aw, ah;
    bool needUpdate;
};

#endif // DAXIS_H
