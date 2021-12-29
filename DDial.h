#ifndef DDIAL_H
#define DDIAL_H
#include <DWidget.h>
#include <QMap>


#define EMPTY_QCOLOR (QColor(0,0,0,0))
class DDial : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event) override;
    virtual bool eventFilter(QObject *watcher,QEvent *event) override;
public:
    enum DDialMode
    {
        Binary
        ,Mono
        ,Infinite
        ,Discrete
    };
    enum DrawPart
    {
        Dial
        ,Status
        ,Lines
        ,Rect
        ,Pointer
    };
    struct DrawParam
    {
        QColor color_main;
        QColor color_supp;
        int value;
        bool draw_it;
    };
    DDial(QWidget *parent = nullptr, DDialMode m = Infinite);
    ~DDial();


    void x_setValueRange(double min, double max);
    void x_setSensitivity(double s);
    void x_setDiscreteSensitivity(double s);
    void x_setDiscreteLevels(int n);
    void x_setMode(DDialMode m);

    void x_setValue(double v);
    void x_setLeftValue(double v);
    void x_setRightValue(double v);

    void x_setValueByPercent(double percent);
    void x_setLeftValueByPercent(double percent);
    void x_setRightValueByPercent(double percent);
    void x_setLevel(int level);

    void x_rotateToRadian(double radians);
    void x_rotateToDegree(double degree);

    void x_setDrawParam(DrawPart part, DrawParam param);
    void x_setDrawParam(DrawPart part, QColor c_main, QColor c_supp, int value, bool draw_it);
    void x_setDrawVisability(DrawPart part, bool v);
    void x_setRadius(int r);
    void x_setAutoScale(double s);
    void x_disableAutoScale();

    DDialMode x_mode() const;

private:
    void restart();
    void zeroProp();
    void inition();
    void setModeSpecific();
    void hideAll();
    void setAngle(double r);
    void sendValue();
    void sendValue(double v);
    bool in_range(double e1, double e2, double v);


    static const DrawParam shared_param;


    QMap<DrawPart, DrawParam> draw_params;
    DDialMode mode;

    double status_start_angle;
    double status_span_angle;

    double rad_current;
    double rad_rotate_limit;
    double rad_speed;
    double rad_move_buffer;
    double rad_move_buffer_limit;
    int current_level;
    //---------------------
    int discrete_levels;
    double maxValue;
    double minValue;
    //---------------------
    QPoint firstClick;
    bool moved;
    double auto_scale;

signals:
    void valueChanged(double);
    void click();
    void dblClick();
    void modeChanged();
};
#define DQDIAL_START_ANGLE__BINARY (M_PI/2.0)
#define DQDIAL_START_ANGLE__MONO ((M_PI/4.0) + M_PI)
#define DQDIAL_START_ANGLE__INFINITE (M_PI/2.0)
#define DQDIAL_START_ANGLE__DISCRETE (DQDIAL_START_ANGLE__MONO)

#define DQDIAL_ROTATE_LIMIT__BINRAY (M_PI * 0.75)
#define DQDIAL_ROTATE_LIMIT__MONO (1.5 * M_PI)
#define DQDIAL_ROTATE_LIMIT__INFINITE (2*M_PI)
#endif // DDIAL_H
