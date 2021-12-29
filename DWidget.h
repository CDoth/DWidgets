#ifndef DWIDGET_H
#define DWIDGET_H
#include <QWidget>
#include <QDebug>
#define CREATE_WIDGET \
    _alloc(); _place(); _init(); _connect();

void drawMainRect(QPainter *p, const QRect &r, int width = 1, const QColor &rect_color = QColor(0,0,0), const QColor &area_color = QColor(0,0,0,0));
class DWidget : public QWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event) override;
    virtual bool eventFilter(QObject *watcher,QEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    void drawRect(QPainter *p);
public:
    DWidget(QWidget *parent = nullptr);
    ~DWidget();
    void enableRect(bool status);
    void setRectColor(int r, int g, int b);
    void setRectColor(QColor c);
    void setRectWidth(int w);

    void setMainColor(int r, int g, int b, int a = 255);
    void setMainColor(const QColor &c);
    void enableMainColor(bool s);
private:
    QColor color_rect;
    int rect_width;
    bool rect_drawable;
    QColor color_area;
signals:
    void clicked();
    void resized();
};
#endif // DWIDGET_H
