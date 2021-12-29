#include "DDial.h"
#include <QPainter>
#include <QEvent>
#include <QGuiApplication>
#include <QMouseEvent>

#define RAD2DEG(X) (X*57.2958)
#define DEG2RAD(X) (X/57.2958)
#define DEG2QDEG(X) (X*16)
#define DIAL_RADIUS (draw_params[Dial].value)
#define CIRCLE (2.0*M_PI)
#define DDIAL_LINES_SHIFT (5)
#define DDIAL_LINES_LENGHT (3)
#define VALUE_RANGE (maxValue - minValue)
const DDial::DrawParam DDial::shared_param = {QColor(0,0,0), EMPTY_QCOLOR, 1, false};
void DDial::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    if(auto_scale)
    {
        auto range = width() < height() ? width() : height();
        DIAL_RADIUS = (auto_scale * range / 2) - draw_params[Status].value;
    }

    DrawParam dp = shared_param;
    dp = draw_params[Dial];
    if(dp.draw_it)
    {
        p.setPen(QPen(dp.color_supp, 1));
        p.setBrush(dp.color_main);
        p.drawEllipse(rect().center(), dp.value, dp.value);
    }
    dp = draw_params[Status];
    if(dp.draw_it)
    {
        p.setBrush(Qt::NoBrush);

        if(rad_current < 0.0)
            p.setPen(QPen(dp.color_supp, dp.value));
        else if(rad_current > 0.0)
            p.setPen(QPen(dp.color_main, dp.value));


        auto statusRadius = DIAL_RADIUS + 1;
        p.drawArc(this->rect().center().x() - statusRadius, this->rect().center().y() - statusRadius,
                  2 * statusRadius, 2 * statusRadius,
                  status_start_angle,
                  status_span_angle);
    }
    dp = draw_params[Lines];
    if(dp.draw_it)
    {
        QPointF markTop;
        QPointF markBot;

        const double step = CIRCLE / discrete_levels;
        const double linesRadius = DIAL_RADIUS + DDIAL_LINES_SHIFT;
        double pos = 0.0;
        p.setPen(QPen(dp.color_main, dp.value));

        for(int i=0;i!=discrete_levels;++i)
        {
            markBot.setX(sin(pos) * (linesRadius) + this->rect().center().x());
            markBot.setY(cos(pos) * (linesRadius) + this->rect().center().y());

            markTop.setX(sin(pos) * (linesRadius + DDIAL_LINES_LENGHT) + this->rect().center().x());
            markTop.setY(cos(pos) * (linesRadius + DDIAL_LINES_LENGHT) + this->rect().center().y());
            pos += step;

            p.drawLine(markTop, markBot);
        }
    }
    dp = draw_params[Rect];
    if(dp.draw_it)
    {
        drawMainRect(&p, rect(), dp.value, dp.color_main);
    }
    dp = draw_params[Pointer];
    if(dp.draw_it)
    {
        QPointF pointer(0.0, 0.0);
        double shift = 0.0;
        const double pointer_radius = dp.value;
        switch (mode)
        {
            case Mono: shift = M_PI/4;break;
            case Infinite:
            case Binary: shift = M_PI;break;
            case Discrete: shift = 0; break;
        }
        pointer.setX(   sin(-rad_current - shift) * (DIAL_RADIUS - pointer_radius) + this->rect().center().x()    );
        pointer.setY(   cos(-rad_current - shift) * (DIAL_RADIUS - pointer_radius) + this->rect().center().y()    );

        p.setBrush(dp.color_main);
        p.setPen(QPen(dp.color_supp, 1));
        p.drawEllipse(pointer, pointer_radius, pointer_radius);
    }
}
bool DDial::eventFilter(QObject *watcher, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        auto me = reinterpret_cast<QMouseEvent*>(event);
        QPoint firstClickLocal = me->pos();
        QPoint center = rect().center();
        double x_range = center.x() - firstClickLocal.x();
        double y_range = center.y() - firstClickLocal.y();
        double range = sqrt(x_range * x_range + y_range * y_range);
        if(range <= DIAL_RADIUS)
        {
            firstClick = me->globalPos();
            QGuiApplication::setOverrideCursor(QCursor(Qt::BlankCursor));
        }
        else
        {
            firstClick = QPoint(0,0);
        }
    }
    if(event->type() == QEvent::MouseButtonRelease)
    {
        QGuiApplication::restoreOverrideCursor();
        if(moved == false)
            emit click();
        moved = false;
        rad_move_buffer = 0.0;
    }
    if(event->type() == QEvent::MouseButtonDblClick)
    {
        emit dblClick();
    }
    if(event->type() == QEvent::MouseMove)
    {
        if(firstClick == QPoint(0,0))
            return false;
        moved = true;
        auto me = reinterpret_cast<QMouseEvent*>(event);
        QPoint pos = me->globalPos();
        if(pos.y() < firstClick.y())
        {
            switch (mode)
            {
                case Mono:
                if(rad_current - rad_speed < 0.0)
                    rad_current = 0.0;
                else
                    rad_current -= rad_speed;
                break;
            case Binary:
                if(rad_current - rad_speed < -rad_rotate_limit)
                    rad_current = -rad_rotate_limit;
                else
                    rad_current -= rad_speed;
                break;
            case Infinite:
                rad_current -= rad_speed;
                break;
            case Discrete:
                if(rad_move_buffer > 0.0)
                    rad_move_buffer = 0.0;
                rad_move_buffer -= rad_speed;
                break;
            }
        }
        else if(pos.y() > firstClick.y())
        {
            switch (mode)
            {
                case Mono:
                case Binary:
                if(rad_current + rad_speed > rad_rotate_limit)
                    rad_current = rad_rotate_limit;
                else
                    rad_current += rad_speed;
                break;
                case Infinite:
                    rad_current += rad_speed;
                break;
                case Discrete:
                if(rad_move_buffer < 0.0)
                    rad_move_buffer = 0.0;
                    rad_move_buffer += rad_speed;
                break;
            }
        }


        sendValue();
        const double residual_radians = (mode == Infinite) ? (
                                                                 rad_current - (int(rad_current / (CIRCLE)) * CIRCLE)
                                                             )
                                                           : rad_current;

        setAngle(residual_radians);


        QCursor cur;
        cur.setPos(firstClick);

        update();
    }
    return false;
}
DDial::DDial(QWidget *parent, DDialMode m) : QWidget(parent), mode(m)
{
    draw_params[Dial] = shared_param;
    draw_params[Status] = shared_param;
    draw_params[Lines] = shared_param;
    draw_params[Rect] = shared_param;
    draw_params[Pointer] = shared_param;
    restart();
    installEventFilter(this);
}
DDial::~DDial()
{

}


void DDial::x_setValueRange(double min, double max)
{
    minValue = min;
    maxValue = max;
    if(minValue > maxValue) std::swap(minValue, maxValue);
}
void DDial::x_setSensitivity(double s)
{
    if(s > 0.0)
        rad_speed = s;
}
void DDial::x_setDiscreteSensitivity(double s)
{
    if(s > 0.0)
        rad_move_buffer_limit = s;
}
void DDial::x_setDiscreteLevels(int n)
{
    if(n > 0)
        discrete_levels = n;
}
void DDial::x_setMode(DDial::DDialMode m)
{
    if(m != mode)
    {
        mode = m;
        restart();
        emit modeChanged();
    }
}
void DDial::x_setValue(double v)
{
    if(mode != Discrete)
    {
        double part = 0.0;
        bool up = false;
        if(mode == Binary)
        {
            if(in_range(0.0, minValue, v))
            {
                part = fabs(v) / minValue;
                up = true;
            }
            else if(in_range(0.0, maxValue, v))
            {
                part = fabs(v) / maxValue;
                up = true;
            }
        }
        else if(mode == Infinite || (v >= minValue && v <= maxValue))
        {
            part = (v - minValue) / VALUE_RANGE;
            up = true;
        }
        if(up)
        {
            rad_current = rad_rotate_limit * part;
            setAngle(rad_current);
            sendValue();
            update();
        }
    }
    else
    {
        int _v = v;
        x_setLevel(_v);
    }
}
void DDial::x_setLeftValue(double v)
{
    if(mode == Binary)
    {
        if(in_range(0.0, minValue, v))
        {
            double part = fabs(v) / fabs(minValue);
            rad_current = rad_rotate_limit * part * -1.0;
            setAngle(rad_current);
            update();
        }
    }
    else
        x_setValue(v);
}
void DDial::x_setRightValue(double v)
{
    if(mode == Binary)
    {
        if(in_range(0.0, maxValue, v))
        {
            double part = fabs(v) / maxValue;
            rad_current = rad_rotate_limit * part;
            setAngle(rad_current);
            update();
        }
    }
    else
        x_setValue(v);
}
void DDial::x_setValueByPercent(double percent)
{
    percent /= 100.0;
    switch (mode)
    {
        case Mono:
            if(percent >= 0.0 && percent <= 1.0)
                rad_current = rad_rotate_limit * percent;
        break;
        case Binary:
            if(percent >= 0.0 && percent <= 1.0)
                rad_current = 2.0 * rad_rotate_limit * percent;
        break;
        case Infinite:
            rad_current = rad_rotate_limit * percent;
        break;
        case Discrete:
            x_setLevel(discrete_levels * percent);
        break;
    }
}
void DDial::x_setLeftValueByPercent(double percent)
{
    percent /= 100.0;
    if(percent >= 0.0 && percent <= 1.0)
    {
        rad_current = rad_rotate_limit * percent * -1.0;
    }
}
void DDial::x_setRightValueByPercent(double percent)
{
    percent /= 100.0;
    if(percent >= 0.0 && percent <= 1.0)
    {
        rad_current = rad_rotate_limit * percent;
    }
}
void DDial::x_setLevel(int level)
{
    if(level >= 0 && level < discrete_levels)
    {
        current_level = level;
        rad_move_buffer = 0.0;
        rad_current = current_level * (CIRCLE / discrete_levels);
        sendValue();
        update();
    }
}
void DDial::x_rotateToRadian(double radians)
{
    bool up = false;
    switch (mode)
    {
        case Mono:
        case Binary:
            if(radians >= 0.0 && radians <= rad_rotate_limit)
            {
                rad_current = radians;
                up = true;
            }
        break;
        case Infinite:
            rad_current = radians;
            up = true;
        break;
        case Discrete:
            int l = radians / (CIRCLE / discrete_levels);
            x_setLevel(l);
        break;
    }

    if(up)
    {
        setAngle(rad_current);
        sendValue();
        update();
    }
}
void DDial::x_rotateToDegree(double degree)
{
    x_rotateToRadian(DEG2RAD(degree));
}

void DDial::x_setDrawParam(DDial::DrawPart part, DDial::DrawParam param)
{
    draw_params[part] = param;
}
void DDial::x_setDrawParam(DDial::DrawPart part, QColor c_main, QColor c_supp, int value, bool draw_it)
{
    draw_params[part] = {c_main, c_supp, value, draw_it};
}
void DDial::x_setDrawVisability(DDial::DrawPart part, bool v)
{
    draw_params[part].draw_it = v;
}
void DDial::x_setRadius(int r)
{
    if(r > 0 && r != DIAL_RADIUS)
    {
        DIAL_RADIUS = r;
        setFixedSize(2*r + draw_params[Status].value + DDIAL_LINES_LENGHT + 15, 2*r + draw_params[Status].value + DDIAL_LINES_LENGHT + 15);
    }
}
void DDial::x_setAutoScale(double s)
{
    auto_scale = s;
    setFixedSize(size());
    setMinimumSize(0,0);
    setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
}
void DDial::x_disableAutoScale()
{
    auto_scale = 0.0;
}
DDial::DDialMode DDial::x_mode() const
{
    return mode;
}

void DDial::restart()
{
    zeroProp();
    inition();
    setModeSpecific();
    draw_params[Rect].draw_it = false;
}
void DDial::zeroProp()
{
    status_start_angle = 0.0;
    status_span_angle = 0.0;

    rad_current = 0.0;
    rad_rotate_limit = 0.0;
    rad_speed = 0.05;
    rad_move_buffer = 0.0;
    rad_move_buffer_limit = 1.0;
    current_level = 0;
    discrete_levels = 0;
    minValue = 0.0;
    maxValue = 1.0;
    firstClick = QPoint(0,0);
    moved = false;
    auto_scale = 0.0;
}
void DDial::inition()
{
    //Dial
    draw_params[Dial].color_main = QColor(0,0,0);
    draw_params[Dial].color_supp = EMPTY_QCOLOR;
    draw_params[Dial].value = 12; //dial radius
    draw_params[Dial].draw_it = false;
    //Status
    draw_params[Status].color_main = QColor(255, 0, 0);
    draw_params[Status].color_supp = QColor(0, 0, 255);
    draw_params[Status].value = 3; //status width
    draw_params[Status].draw_it = false;
    //Lines
    draw_params[Lines].color_main = QColor(0,0,0);
    draw_params[Lines].color_supp = EMPTY_QCOLOR;
    draw_params[Lines].value = 2; //lines width
    draw_params[Lines].draw_it = false;
    //Rect
    draw_params[Rect].color_main = QColor(0,0,0); //Line color
    draw_params[Rect].color_supp = EMPTY_QCOLOR; //Fill color
    draw_params[Rect].value = 1; //rect width
    draw_params[Rect].draw_it = false;
    //Pointer
    draw_params[Pointer].color_main = QColor(0,255,0);
    draw_params[Pointer].color_supp = EMPTY_QCOLOR;
    draw_params[Pointer].value = 2; //Pointer radius
    draw_params[Pointer].draw_it = false;

    setFixedSize(2*DIAL_RADIUS + draw_params[Status].value + DDIAL_LINES_LENGHT + 15, 2*DIAL_RADIUS + draw_params[Status].value + DDIAL_LINES_LENGHT + 15);

}
void DDial::setModeSpecific()
{
    rad_current = 0.0;
    hideAll();
    draw_params[Dial].draw_it = true;
    draw_params[Pointer].draw_it = true;
    switch (mode)
    {
        case Infinite:
            status_start_angle = DEG2QDEG(RAD2DEG(DQDIAL_START_ANGLE__INFINITE));
            rad_rotate_limit = DQDIAL_ROTATE_LIMIT__INFINITE;
        break;
        case Binary:
            status_start_angle = DEG2QDEG(RAD2DEG(DQDIAL_START_ANGLE__BINARY));
            rad_rotate_limit = DQDIAL_ROTATE_LIMIT__BINRAY;
            draw_params[Status].draw_it = true;
        break;
        break;
        case Discrete:
            status_start_angle = DEG2QDEG(RAD2DEG(DQDIAL_START_ANGLE__DISCRETE));
            rad_rotate_limit = 0.0;
            draw_params[Lines].draw_it = true;
        break;
        case Mono:
            draw_params[Status].draw_it = true;
            status_start_angle = DEG2QDEG(RAD2DEG(DQDIAL_START_ANGLE__MONO));
            rad_rotate_limit =  DQDIAL_ROTATE_LIMIT__MONO ;
        break;
    }
}
void DDial::hideAll()
{
    for(auto it: draw_params)
        it.draw_it = false;
}

void DDial::setAngle(double r)
{
    status_span_angle = DEG2QDEG(RAD2DEG(r)) * -1.0;
}
void DDial::sendValue()
{
    double out = 0.0;
    switch (mode)
    {
        case Mono:
            out = (rad_current / rad_rotate_limit) * VALUE_RANGE + minValue;
        break;
        case Binary:
            if(rad_current < 0.0)
                out = fabs(rad_current / rad_rotate_limit) * minValue;
            else if(rad_current > 0.0)
                out = fabs(rad_current / rad_rotate_limit) * maxValue;
        break;
        case Infinite:
            out = (rad_current / CIRCLE) * VALUE_RANGE + minValue;
        break;
        case Discrete:
            if(rad_move_buffer >= rad_move_buffer_limit)
            {
                rad_move_buffer = 0.0;
                if(++current_level == discrete_levels)
                    current_level = 0;

                rad_current = current_level * (CIRCLE / discrete_levels);
                sendValue(current_level);
            }
            else if(rad_move_buffer <= -rad_move_buffer_limit)
            {
                rad_move_buffer = 0.0;
                if(--current_level == -1)
                    current_level = discrete_levels-1;

                rad_current = current_level * (CIRCLE / discrete_levels);
                sendValue(current_level);
            }
        break;
    }
    if(mode != Discrete)
    {
        sendValue(out);
    }
}
void DDial::sendValue(double v)
{
//    qDebug()<<"sendValue:" << v;
    emit valueChanged(v);
}

bool DDial::in_range(double e1, double e2, double v)
{
    if(e1 > e2) std::swap(e1, e2);
    return (v >= e1 && v <= e2);
}
