#include "DSwitchButton.h"
#include <QPainter>
#include <QEvent>

#define DSWITCHBUTTON_RADIUS (5)
#define DSWITCHBUTTON_SIZE (2 * radius + 5)
void DSwitchButton::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

//    drawMainRect(&p, this->rect());

    auto it = custom.find(state);
    if(it != custom.end())
    {
        p.drawPixmap(rect(), *it);
    }
    else
    {
        p.setBrush(state ? colorOn : colorOff);
        p.setPen(p.brush().color());
        p.drawEllipse(rect().center(), radius, radius);
    }
}
bool DSwitchButton::eventFilter(QObject *watcher, QEvent *event)
{
    if(!isEnabled())
        return false;
    if(event->type() == QEvent::MouseButtonPress)
    {
        x_setState(!state);
    }
    return false;
}
DSwitchButton::DSwitchButton(QWidget *parent) : DWidget(parent)
{
    state = false;
    fixed = false;
    radius = DSWITCHBUTTON_RADIUS;
    setFixedSize(DSWITCHBUTTON_SIZE, DSWITCHBUTTON_SIZE);


    colorOn = Qt::gray;
    colorOff = Qt::black;
    setMainColor(QColor(0,0,0,0));
}
DSwitchButton::~DSwitchButton()
{

}
bool DSwitchButton::x_state()
{
    return state;
}
void DSwitchButton::x_setState(bool s)
{
    if(s != state && !fixed)
    {
//        qDebug()<<"set state:" << this << "set:" << s << "state:" << state;
        state = s;
        emit switched(state);
        update();
    }
}
void DSwitchButton::x_disable()
{
    x_setState(false);
}
void DSwitchButton::x_enable()
{
    x_setState(true);
//    qDebug()<<"setEnable for: " << this << "state:" << state;
}
void DSwitchButton::x_fixState()
{
    fixed = true;
}
void DSwitchButton::x_fixEnable()
{
    x_setState(true);
    fixed = true;
}
void DSwitchButton::x_fixDisable()
{
    x_setState(false);
    fixed = true;
}
void DSwitchButton::x_unFix()
{
    fixed = false;
}
int DSwitchButton::x_radius()
{
    return radius;
}
void DSwitchButton::x_setRadius(int r)
{
    if(r > 0)
    {
        radius = r;
        setFixedSize(DSWITCHBUTTON_SIZE, DSWITCHBUTTON_SIZE);
        update();
    }
}
void DSwitchButton::x_setColors(const QColor &on, const QColor &off)
{
    colorOn = on;
    colorOff = off;
}
void DSwitchButton::x_setColorOn(const QColor &c)
{
    colorOn = c;
}
void DSwitchButton::x_setColorOff(const QColor &c)
{
    colorOff = c;
}
void DSwitchButton::x_setCustomPixmap(const QPixmap &on, const QPixmap &off)
{
    custom[true] = on;
    custom[false] = off;
}
void DSwitchButton::x_setCustomPixmapOn(const QPixmap &pm)
{
    custom[true] = pm;
}
void DSwitchButton::x_setCustomPixmapOff(const QPixmap &pm)
{
    custom[false] = pm;
}
