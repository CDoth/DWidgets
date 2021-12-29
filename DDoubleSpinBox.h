#ifndef DDOUBLESPINBOX_H
#define DDOUBLESPINBOX_H
#include "DWidget.h"
#include "DSection.h"
#include "DArray.h"
#include <QLayout>
#include <QLabel>

class DDoubleSpinBox : public DWidget
{
    Q_OBJECT
public:
    DDoubleSpinBox(QWidget *parent = nullptr, int left = 2, int right = 3);
    ~DDoubleSpinBox();

    void x_loadCustomNumbers(const QVector<QPixmap> &cn);
    void x_loadCustomNumber(const QPixmap &pm, int index);

public:
    DNumberSection* x_leftSection(int index);
    DNumberSection* x_rightSection(int index);
    double x_value();
    int x_leftValue();
    double x_rightValue();
    void x_setValue(double v);
    void x_setLeftValue(int v);
    void x_setRightValue(double v);
    int x_sections();
    int x_leftSections();
    int x_rightSections();
    void x_valueUp();
    void x_valueDown();
    void x_leftValueUp();
    void x_leftValueDown();
    void x_setMaxValue();
    void x_setMinValue();
    void x_setLeftMaxValue();
    void x_setLeftMinValue();
    void x_setRightMaxValue();
    void x_setRightMinValue();
    bool x_isMaxValue();
    bool x_isMinValue();
    double x_getMaxValue();
    int x_getLeftMaxValue();
    double x_getRightMaxValue();
    void x_setName(QString n);

    DDoubleSpinBox* x_rateBox();
    void x_addSignSection();
    void x_addMultiplyRateBox(int left, int right);
    void x_addDivisionRateBox(int left, int right);

private:
    double getStep();
    void setValue(double v);
    double getFinalValue();
private:
    DSymbolSection *signSection;
    DSymbolSection *pointSection;
    DDoubleSpinBox *rateBox;
    DArray<DNumberSection*> leftSet;
    DArray<DNumberSection*> rightSet;
    QHBoxLayout *layoutButtons;
    QHBoxLayout *layoutMain;
    QLabel *name;
private:
    int leftValue;
    double rightValue;
    double value;
    bool modifyAvailable;
private slots:
    void extractValue(int);
    void extractValue2(double);
    void catchOverUp();
    void catchOverDown();
    void zeroSection();
signals:
    void leftValueChanged(int);
    void rightValueChanged(double);
    void valueChanged(double);
};

#endif // DDOUBLESPINBOX_H
