#ifndef DSPINBOX_H
#define DSPINBOX_H
#include "DWidget.h"
#include "DSection.h"
#include "DArray.h"
#include <QLayout>
#include <QLabel>

class DSpinBox : public DWidget
{
    Q_OBJECT
public:
    DSpinBox(QWidget *parent = nullptr, int n = 8);
    ~DSpinBox();
    int x_value();
    DNumberSection* x_section(int index);
    void x_loadCustomNumbers(const QVector<QPixmap> &cn);
    void x_loadCustomNumber(const QPixmap &pm, int index);

    void x_setValue(int v);
    void x_valueUp();
    void x_valueDown();
    void x_setMaxValue();
    void x_setMinValue();
    bool x_isMinValue();
    bool x_isMaxValue();
    int x_getMaxValue();
    int x_sections();
    void x_setName(QString n);
    DSpinBox* x_rateBox();


    void x_addSignSection();
    void x_addMultiplyRateBox(int n);
    void x_addDivisionRateBox(int n);
private:
    DSymbolSection *signSection;
    DSpinBox *rateBox;
    DArray<DNumberSection*> set;
    QHBoxLayout *layoutButtons;
    QHBoxLayout *layoutMain;
    QLabel *name;
private:
    int value;
    bool modifyAvailable;
private slots:
    void extractValue(int);
    void catchOverUp();
    void catchOverDown();
    void modifyValue(int);
    void zeroSection();
signals:
    void valueChanged(int);
};
#endif // DSPINBOX_H
