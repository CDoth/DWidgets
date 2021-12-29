#include "DSection.h"
#include <QGuiApplication>
#include <QEvent>
#include <QMouseEvent>

#include <QPainter>
bool DAbstractSection::eventFilter(QObject *watcher, QEvent *event)
{
    if(!isEnabled())
        return false;
    if(event->type() == QEvent::HoverEnter)
    {
        QGuiApplication::setOverrideCursor(QCursor(Qt::SizeVerCursor));
    }
    if(event->type() == QEvent::HoverLeave)
    {
        QGuiApplication::restoreOverrideCursor();
    }
    if(event->type() == QEvent::MouseButtonPress)
    {
        auto me = reinterpret_cast<QMouseEvent*>(event);
        clickPoint = me->globalPos();
        QGuiApplication::setOverrideCursor(QCursor(Qt::BlankCursor));
    }
    if(event->type() == QEvent::MouseButtonDblClick)
    {
        emit dblClicked();
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        QGuiApplication::restoreOverrideCursor();
        moveBuffer = 0.0f;
        if(moved == false)
            emit clicked();
        moved = false;
    }
    if(event->type() == QEvent::MouseMove)
    {
        moved = true;
        auto me = reinterpret_cast<QMouseEvent*>(event);
        QPoint pos = me->globalPos();
        if(pos.y() > clickPoint.y())
        {
            moveBuffer += moveSpeed;
            if(moveBuffer > moveLimit)
            {
                valueDown();
                moveBuffer = 0.0f;
            }
        }
        else if(pos.y() < clickPoint.y())
        {
            moveBuffer -= moveSpeed;
            if(moveBuffer < -moveLimit)
            {
                valueUp();
                moveBuffer = 0.0f;
            }
        }

        QCursor cur;
        cur.setPos(clickPoint);
        update();
    }
    if(event->type() == QEvent::Wheel)
    {
        QWheelEvent *we = reinterpret_cast<QWheelEvent*>(event);
        if(we->angleDelta().y() > 0)
        {
            valueUp();
        }
        else
        {
            valueDown();
        }
    }
    return false;
}

DAbstractSection::DAbstractSection(QWidget *parent) : DWidget(parent)
{
    clickPoint = QPoint(0,0);
    moveBuffer = 0.0f;
    moveLimit = 1.0f;
    moveSpeed = 0.1f;
    moved = false;
//    //-----------
    font = QFont("Times", 9, QFont::Bold);
    color = Qt::black;
    rectColor = Qt::black;
    backgroungColor = QColor(0,0,0,0);
    //-----------
    installEventFilter(this);
    setAttribute(Qt::WA_Hover);
}
DAbstractSection::~DAbstractSection()
{

}

void DAbstractSection::x_setCustomImages(const QVector<QPixmap> &images)
{
    for(int i=0;i!=images.size(); ++i)
    {
        customImages[i] = images[i];
    }
}
void DAbstractSection::x_setCustomImage(const QPixmap &pm, int index)
{
    customImages[index] = pm;
}
void DAbstractSection::x_setFont(const QFont &f)
{
    font = f;
}
void DAbstractSection::x_setFontSize(int size)
{
    font.setPointSize(size);
}
void DAbstractSection::x_setColor(const QColor &c)
{
    color = c;
}
void DAbstractSection::x_setBackgroundColor(const QColor &c)
{
    backgroungColor = c;
}
void DAbstractSection::x_valueUp()
{
    valueUp();
}
void DAbstractSection::x_valueDown()
{
    valueDown();
}
//===========================================================================================
//--------------------------------------------------------------------------- DNumberSection:
#define DNUMBERSECTION_MIN_VALUE (0)
#define DNUMBERSECTION_MAX_VALUE (9)


void DNumberSection::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    drawMainRect(&p, rect(), 1, rectColor);
    auto pm = customImages.find(value);

    if(pm != customImages.end())
    {
        p.drawPixmap(rect(), *pm);
    }
    else
    {
        p.setFont(font);
        p.setPen(color);
        p.drawText(rect(), Qt::AlignCenter, QString("%1").arg(value));
    }
    if(!isEnabled())
    {
        p.setBrush(QColor(0,0,0, 25));
        p.drawRect(rect());
    }


//    qDebug()<<"DNumberSection::paintEvent";
}
DNumberSection::DNumberSection(QWidget *parent) : DAbstractSection(parent)
{
    value = 0;
    setFixedSize(16,20);
}
DNumberSection::~DNumberSection()
{

}
void DNumberSection::x_setValue(int v)
{
    changeValue(v);
}
void DNumberSection::x_setMinValue()
{
    changeValue(DNUMBERSECTION_MIN_VALUE);
}
void DNumberSection::x_setMaxValue()
{
    changeValue(DNUMBERSECTION_MAX_VALUE);
}
bool DNumberSection::x_isMinValue()
{
    return (value == DNUMBERSECTION_MIN_VALUE);
}
bool DNumberSection::x_isMaxValue()
{
    return (value == DNUMBERSECTION_MAX_VALUE);
}
int DNumberSection::x_value()
{
    return value;
}
void DNumberSection::valueUp()
{
    if(value < DNUMBERSECTION_MAX_VALUE)
    {
        changeValue(value + 1);
    }
    else if(value == DNUMBERSECTION_MAX_VALUE)
    {
        emit tryOverUp();
    }
}
void DNumberSection::valueDown()
{
    if(value > DNUMBERSECTION_MIN_VALUE)
    {
        changeValue(value - 1);
    }
    else if(value == DNUMBERSECTION_MIN_VALUE)
    {
        emit tryOverDown();
    }
}
void DNumberSection::changeValue(int v)
{
    if(v != value)
    {
        value = v;
        emit valueChanged(value);
        update();
    }
}
//--------------------------------------------------------------------------- DSymbolSection:
#define DSYMBOLSECTION_EMPTY_SYMBOL (' ')
void DSymbolSection::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    drawMainRect(&p, rect(), 1, rectColor);
    int si = valueSet.indexOf(value);
    auto pm = customImages.find(si);
    if(pm != customImages.end())
    {
        p.drawPixmap(rect(), *pm);
    }
    else
    {
        p.setFont(font);
        p.setPen(color);
        p.drawText(rect(), Qt::AlignCenter, QString("%1").arg(value));
    }
    if(!isEnabled())
    {
        p.setBrush(QColor(0,0,0, 25));
        p.drawRect(rect());
    }
}
DSymbolSection::DSymbolSection(QWidget *parent) : DAbstractSection(parent)
{
    value = DSYMBOLSECTION_EMPTY_SYMBOL;
    setFixedSize(16,20);
}
DSymbolSection::~DSymbolSection()
{

}
void DSymbolSection::x_setValue(char v)
{
    x_addValue(v);
    changeValue(v);
}
void DSymbolSection::x_addValue(char v)
{
    if(valueSet.indexOf(v) == -1)
    {
        valueSet.push_back(v);
    }
}
void DSymbolSection::x_setFirstValue()
{
    changeValue(valueSet.front());
}
void DSymbolSection::x_setLastValue()
{
    changeValue(valueSet.back());
}
bool DSymbolSection::x_isFirstValue()
{
    return (value == valueSet.front());
}
bool DSymbolSection::x_isLastValue()
{
    return (value == valueSet.back());
}
char DSymbolSection::x_value()
{
    return value.toLatin1();
}
void DSymbolSection::x_removeValue(char v)
{
    valueSet.remove(v);
}
void DSymbolSection::x_clearValueList()
{
    valueSet.clear();
}
void DSymbolSection::valueUp()
{
    int i = valueSet.indexOf(value);
    if(i < valueSet.size() - 1)
    {
        changeValue(valueSet[i+1]);
    }
}
void DSymbolSection::valueDown()
{
    int i = valueSet.indexOf(value);
    if(i > 0)
    {
        changeValue(valueSet[i-1]);
    }
}
void DSymbolSection::changeValue(QChar v)
{
    int i = valueSet.indexOf(v);
    if(i != -1)
    {
        value = v;
        emit valueChanged(i);
        update();
    }
}
