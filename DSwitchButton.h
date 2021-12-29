#ifndef DSWITCHBUTTON_H
#define DSWITCHBUTTON_H
#include "DWidget.h"
#include <QMap>

class DSwitchButton : public DWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *watcher, QEvent *event) override;
public:
    DSwitchButton(QWidget *parent = nullptr);
    ~DSwitchButton();
    bool x_state();
    void x_setState(bool s);
    void x_disable();
    void x_enable();
    void x_fixState();
    void x_fixEnable();
    void x_fixDisable();
    void x_unFix();

    int x_radius();
    void x_setRadius(int r);



    void x_setColors(const QColor &on, const QColor &off);
    void x_setColorOn(const QColor &c);
    void x_setColorOff(const QColor &c);
    void x_setCustomPixmap(const QPixmap &on, const QPixmap &off);
    void x_setCustomPixmapOn(const QPixmap &pm);
    void x_setCustomPixmapOff(const QPixmap &pm);
private:

    QColor colorOn;
    QColor colorOff;
    QMap<bool, QPixmap> custom;
    bool state;
    bool fixed;

    int radius;
signals:
    void switched(bool);
};
#endif // DSWITCHBUTTON_H
