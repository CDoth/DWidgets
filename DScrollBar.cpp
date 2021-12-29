#include "DScrollBar.h"
#include <QEvent>
#include <QMouseEvent>
#include <QPainter>

#define EMPTY_CLICK (-1)
void DScrollBar::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    drawMainRect(&p, rect(), 2, QColor(0,255,0));
}
bool DScrollBar::eventFilter(QObject *watcher, QEvent *event)
{
     if(event->type() == QEvent::MouseButtonPress)
     {
         if(watcher == this &&  scrollClick == EMPTY_CLICK)
         {
             auto me = reinterpret_cast<QMouseEvent*>(event);
             scrollClick = scroll->height()/2;
             int nextPos = me->y() - scrollClick;
             changePos(nextPos);
         }
         if(watcher == scroll)
         {
             auto me = reinterpret_cast<QMouseEvent*>(event);
             scrollClick = me->y();
         }
     }
     if(event->type() == QEvent::MouseButtonRelease)
     {
         scrollClick = EMPTY_CLICK;
     }
     if(event->type() == QEvent::MouseMove)
     {
        if(watcher == this && scrollClick != EMPTY_CLICK)
        {
            auto me = reinterpret_cast<QMouseEvent*>(event);
            int nextPos = me->y() - scrollClick;
            changePos(nextPos);
        }
     }
     return false;
}
DScrollBar::DScrollBar(QWidget *parent, DWidget *scrollWidget) : DWidget(parent), scroll(nullptr), defaultScroll(false)
{
    if(scrollWidget == nullptr)
        initDefaultScroll();
    else
        scroll = scrollWidget;
    _init();
}
DScrollBar::~DScrollBar()
{
    if(scroll && defaultScroll)
        delete scroll;
}
void DScrollBar::scrollUp(float step)
{
    step = step ? step : scrollStep;
    int pos = scroll->y() + step * height();
    changePos(pos);
}
void DScrollBar::scrollDown(int step)
{
    step = step ? step : scrollStep;
    int pos = scroll->y() - step * height();
    changePos(pos);
}
void DScrollBar::setScrollPos(float p, bool gens)
{
    changePos(height() * p, gens);
}
void DScrollBar::setScrollTop()
{
    changePos(0);
}
void DScrollBar::setScrollBottom()
{
    changePos(height());
}
void DScrollBar::setScrollStep(float step)
{
    scrollStep = (step <= 0.0) ? 0.1 : step;
}
void DScrollBar::setCustomScroll(DWidget *scrollWidget)
{
    if(scrollWidget)
    {
        if(scroll && defaultScroll)
            delete scroll;
        scroll = scrollWidget;
        scroll->setParent(this);
        scroll->setFixedWidth(width() - 1);
        scroll->move(0,0);
        defaultScroll = false;
    }
}

void DScrollBar::setScrollHeight(int pixels)
{
    scroll->setFixedHeight(pixels);
}
void DScrollBar::setScrollHeight(float partOf)
{
//    qDebug()<<"setScrollHeight:" << partOf;
    if(partOf > 0.0 && partOf < 1.0)
        scroll->setFixedHeight(partOf * height());
    update();
}
DWidget *DScrollBar::setDefaultScroll()
{
    if(!defaultScroll)
    {
        scroll->setParent(nullptr);
        scroll = new DWidget(this);
        initDefaultScroll();
    }
    return scroll;
}
DWidget *DScrollBar::getScroll()
{
    return scroll;
}
bool DScrollBar::isDefaultScroll()
{
    return defaultScroll;
}
void DScrollBar::_init()
{
    scroll->installEventFilter(this);
    installEventFilter(this);
    scrollClick = EMPTY_CLICK;
    setFixedWidth(20);
    scroll->setFixedWidth(width() - 1);
    scroll->move(0,0);
}
void DScrollBar::changePos(int pos, bool gens)
{
    if(pos < 0) pos = 0;
    if(pos + scroll->height() > height()) pos = height() - scroll->height();
    if(pos != scroll->y())
    {
        scroll->move(0, pos);
        float total = height() - scroll->height();
        float part = double(scroll->y()) / total;
        if(gens)
            emit posChanged(part);
    }
}
void DScrollBar::initDefaultScroll()
{
    scroll = new DWidget(this);
    scroll->setMainColor(255, 0, 0);
    scroll->setRectColor(0,0,0);
    scroll->setRectWidth(1);
    scroll->setGeometry(0,0, width() - 1, 15);
    defaultScroll = true;
}
