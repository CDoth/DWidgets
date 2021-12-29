#ifndef DSECTION_H
#define DSECTION_H
#include "DWidget.h"
#include <QMap>

class DAbstractSection : public DWidget
{
    Q_OBJECT
protected:
    virtual bool eventFilter(QObject *watcher,QEvent *event) override;
public:
    DAbstractSection(QWidget *parent = nullptr);
    ~DAbstractSection();
    void x_setCustomImages(const QVector<QPixmap> &images);
    void x_setCustomImage(const QPixmap &pm, int index);
    void x_setFont(const QFont &f);
    void x_setFontSize(int size);
    void x_setColor(const QColor &c);
    void x_setBackgroundColor(const QColor &c);

    void x_valueUp();
    void x_valueDown();
protected:
    virtual void valueUp() = 0;
    virtual void valueDown() = 0;
protected:
    QPoint clickPoint;
    float moveBuffer;
    float moveLimit;
    float moveSpeed;
    bool moved;
protected:
    QFont font;
    QColor color;
    QColor backgroungColor;
    QColor rectColor;
    QMap<int, QPixmap> customImages;
signals:
    void dblClicked();
    void clicked();
    void valueChanged(int);
};
class DNumberSection : public DAbstractSection
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event) override;
public:
    DNumberSection(QWidget *parent = nullptr);
    ~DNumberSection();
    void x_setValue(int v);
    void x_setMinValue();
    void x_setMaxValue();
    bool x_isMinValue();
    bool x_isMaxValue();
    int x_value();
protected:
    virtual void valueUp() override;
    virtual void valueDown() override;
private:
    void changeValue(int v);
private:
    uint8_t value;
    bool zeroVisible;
signals:
    void tryOverUp();
    void tryOverDown();
};
class DSymbolSection : public DAbstractSection
{
protected:
    void paintEvent(QPaintEvent *event) override;
public:
    DSymbolSection(QWidget *parent = nullptr);
    ~DSymbolSection();
    void x_setValue(char v);
    void x_addValue(char v);
    void x_setFirstValue();
    void x_setLastValue();
    bool x_isFirstValue();
    bool x_isLastValue();
    char x_value();
    void x_removeValue(char v);
    void x_clearValueList();
protected:
    virtual void valueUp() override;
    virtual void valueDown() override;
private:
    void changeValue(QChar v);
private:
    QChar value;
    QString valueSet;
};
#endif // DSECTION_H
