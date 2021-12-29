#ifndef DSCROLLBAR_H
#define DSCROLLBAR_H
#include "DWidget.h"

class DScrollBar : public DWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event) override;
    virtual bool eventFilter(QObject *watcher,QEvent *event) override;
public:
    DScrollBar(QWidget *parent = nullptr, DWidget *scrollWidget = nullptr);
    ~DScrollBar();
    void scrollUp(float step = 0);
    void scrollDown(int step = 0);
    void setScrollPos(float p, bool gens = true);
    void setScrollTop();
    void setScrollBottom();
    void setScrollStep(float step);
    void setCustomScroll(DWidget *scrollWidget);
    void setScrollHeight(int pixels);
    void setScrollHeight(float partOf);
    DWidget* setDefaultScroll();
    DWidget* getScroll();
    bool isDefaultScroll();


private:
    void _init();

private:
    void changePos(int pos, bool gens = true);
    void initDefaultScroll();
private:
    DWidget *scroll;
    bool defaultScroll;
    int scrollClick;
private:
    float scrollStep;
signals:
    void posChanged(float);
public slots:

};
#endif // DSCROLLBAR_H
