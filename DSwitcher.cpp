#include "DSwitcher.h"
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include "daran.h"

void DSwitcher::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
//    drawMainRect(&p, rect());

    if(buttons.size())
    {

        QRect r(layoutMain->contentsMargins().left(),
                layoutMain->contentsMargins().top(),
                buttons.first().button->width() - 1,
                buttons.last().button->y() + buttons.last().button->height() - layoutMain->contentsMargins().bottom());

        p.setBrush(Qt::black);
        p.drawRoundedRect(r, buttons.first().button->x_radius(), buttons.first().button->x_radius());
    }
}
bool DSwitcher::eventFilter(QObject *watcher, QEvent *event)
{
    if(!isEnabled())
        return false;
    if(event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick)
    {
        if(buttons.size() == 2)
        {
            int i = getIndex(currentOn);
            x_setValue(!i);
        }
        if(buttons.size() > 2)
        {
            auto me = reinterpret_cast<QMouseEvent*>(event);
            int h = buttons.last().button->y() + buttons.last().button->height();
//            if(me->y() >= layoutMain->margin() && me->y() < h)
//            {
//                int s = h / buttons.size();
//                int i = me->y() / s;
//                x_setValue(i);
//            }
        }
    }
    if(event->type() == QEvent::Wheel)
    {
        QWheelEvent *we = reinterpret_cast<QWheelEvent*>(event);
        if(we->angleDelta().y() > 0)
        {
            int i = getIndex(currentOn);
            if(i > 0)
                x_setValue(i-1);
        }
        else
        {
            int i = getIndex(currentOn);
            if(i < buttons.size() - 1)
                x_setValue(i+1);
        }
    }
    if(event->type() == QEvent::MouseMove)
    {
        auto me = reinterpret_cast<QMouseEvent*>(event);
        int h = buttons.last().button->y() + buttons.last().button->height();
//        if(me->y() >= layoutMain->margin() && me->y() < h)
//        {
//            int s = h / buttons.size();
//            int i = me->y() / s;
//            x_setValue(i);
//        }
    }
    return false;
}
DSwitcher::DSwitcher(QWidget *parent, int positions) : DWidget(parent)
{
//    layoutMain = new QGridLayout(this);
    layoutMain = new QVBoxLayout(this);

//    layoutMain->setSpacing(4);
//    layoutMain->setMargin(5);
    layoutMain->setSizeConstraint(QLayout::SetFixedSize);
    layoutMain->setAlignment(Qt::AlignCenter);
    currentOn = nullptr;
    if(positions > 0)
    {
        FOR_VALUE(positions, i)
        {
            x_addPosition(QString("Name%1").arg(i));
        }
        currentOn = buttons[0].button;
        currentOn->x_fixEnable();
    }
}
DSwitcher::~DSwitcher()
{
}
void DSwitcher::x_setValue(int v)
{
    auto b = getButton(v);
    if(b && b != currentOn)
    {
        currentOn->x_unFix();
        currentOn->x_disable();
        setCurrent(b);
        emit valueChanged(v);
//        qDebug()<<"valueChanged:" << currentOn << getIndex(currentOn);
    }
}
void DSwitcher::x_setFirst()
{
    x_setValue(0);
}
void DSwitcher::x_setLast()
{
    x_setValue(buttons.size());
}
int DSwitcher::x_getValue()
{
    return getIndex(currentOn);
}
int DSwitcher::x_size()
{
    return buttons.size();
}
void DSwitcher::x_setName(const QString &name, int i)
{
    if(i >= 0 && i < buttons.size())
        buttons[i].label->setText(name);
}
QString DSwitcher::x_name(int i)
{
    if(i >= 0 && i < buttons.size())
        return buttons[i].label->text();
    return QString();
}
void DSwitcher::x_addPosition(const QString &name)
{
    namedButton b;
    b.button = new DSwitchButton(this);
    b.label = new DLabel(name, this);
    b.layout = new QHBoxLayout;
    b.layout->addWidget(b.button);
    b.layout->addWidget(b.label);
    layoutMain->addLayout(b.layout);

    b.label->setFont(QFont("Times", 7, QFont::Bold));
//    b.label->setAlignment(Qt::AlignTop);
//    b.label->setScaledContents(true);
//    b.label->set



//    layoutMain->addWidget(b.button, buttons.size(), 0);
//    layoutMain->addWidget(b.label, buttons.size(), 1);

    connect(b.button, SIGNAL(switched(bool)), this, SLOT(catchSwitched(bool)));
    buttons.push_back(b);
    if(currentOn == nullptr)
    {
        setCurrent(b.button);
    }
    update();
}
void DSwitcher::x_removePosition(int i)
{
    if(i >= 0 && i < buttons.size())
    {
        auto b = buttons[i];
        if(b.button == currentOn)
        {
            if(buttons.size() > 1)
            {
                if(i > 0) setCurrent(getButton(i-1));
                else setCurrent(getButton(i+1));
            }
            else
                currentOn = nullptr;
        }
        layoutMain->removeWidget(b.label);
        layoutMain->removeWidget(b.button);
        delete b.label;
        delete b.button;
        buttons.remove(i);

        update();
    }
}
void DSwitcher::x_removePosition(const QString &name)
{
    FOR_VALUE(buttons.size(), i)
    {
        if(buttons[i].label->text() == name)
        {
            x_removePosition(i);
            break;
        }
    }
}
void DSwitcher::x_setRadius(int r)
{
    if(r > 0)
    {
        FOR_VALUE(buttons.size(), i)
                buttons[i].button->x_setRadius(r);
    }
}
int DSwitcher::getIndex(DSwitchButton *b)
{
    FOR_VALUE(buttons.size(), i)
    {
        if(buttons[i].button == b)
            return i;
    }
    return -1;
}
DSwitchButton *DSwitcher::getButton(int i)
{
    if(i>=0 && i<buttons.size())
        return buttons[i].button;
    return nullptr;
}
void DSwitcher::setCurrent(DSwitchButton *b)
{
    currentOn = b;
    currentOn->x_fixEnable();
}
void DSwitcher::catchSwitched(bool s)
{
    DSwitchButton *b = reinterpret_cast<DSwitchButton*>(QObject::sender());
    if(s && b != currentOn && buttons.size() > 2)
    {
        x_setValue(getIndex(b));
    }
}

void DLabel::paintEvent(QPaintEvent *event) {
    QLabel::paintEvent(event);
    QPainter p(this);

//    drawMainRect(&p, this->rect());

}
