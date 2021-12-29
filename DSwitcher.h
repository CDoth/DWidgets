#ifndef DSWITCHER_H
#define DSWITCHER_H
#include "DWidget.h"
#include "DSwitchButton.h"
#include <QLayout>
#include <QLabel>

class DLabel : public QLabel {
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event) override;
public:
    DLabel(const QString &text, QWidget *parent = nullptr) : QLabel(text, parent) {}
};

class DSwitcher : public DWidget
{
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *watcher, QEvent *event) override;
public:
    DSwitcher(QWidget *parent = nullptr, int positions = 2);
    ~DSwitcher();

    void x_setValue(int v);
    void x_setFirst();
    void x_setLast();
    int x_getValue();
    int x_size();

    void x_setName(const QString &name, int i);
    QString x_name(int i);
    void x_addPosition(const QString &name);
    void x_removePosition(int i);
    void x_removePosition(const QString &name);

    void x_setRadius(int r);
private:
    int getIndex(DSwitchButton *b);
    DSwitchButton* getButton(int i);
    void setCurrent(DSwitchButton* b);
private:
    struct namedButton
    {
        DSwitchButton *button;
        DLabel *label;

        QHBoxLayout *layout;
    };
    QVector<namedButton> buttons;

    DSwitchButton *currentOn;


//    QGridLayout *layoutMain;
    QVBoxLayout *layoutMain;

private slots:
    void catchSwitched(bool);
signals:
    void valueChanged(int);
};
#endif // DSWITCHER_H
