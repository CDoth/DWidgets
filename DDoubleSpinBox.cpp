#include "DDoubleSpinBox.h"

DDoubleSpinBox::DDoubleSpinBox(QWidget *parent, int left, int right) : DWidget(parent)
{
    signSection = nullptr;
    rateBox = nullptr;
    name = nullptr;
    if(left < 0) left = 0;
    if(right < 0) right = 0;
    layoutButtons = new QHBoxLayout();
    layoutMain = new QHBoxLayout(this);
    FOR_VALUE(left, i)
    {
        auto section = new DNumberSection(this);
        connect(section, SIGNAL(tryOverUp()), this, SLOT(catchOverUp()));
        connect(section, SIGNAL(tryOverDown()), this, SLOT(catchOverDown()));
        connect(section, SIGNAL(dblClicked()), this, SLOT(zeroSection()));
        connect(section, SIGNAL(valueChanged(int)), this, SLOT(extractValue(int)));

        layoutButtons->addWidget(section);
        leftSet.push_back(section);
    }
    if(right > 0)
    {
        pointSection = new DSymbolSection(this);
        pointSection->x_setValue('.');
        layoutButtons->addWidget(pointSection);
        FOR_VALUE(right, i)
        {
            auto section = new DNumberSection(this);
            connect(section, SIGNAL(tryOverUp()), this, SLOT(catchOverUp()));
            connect(section, SIGNAL(tryOverDown()), this, SLOT(catchOverDown()));
            connect(section, SIGNAL(dblClicked()), this, SLOT(zeroSection()));
            connect(section, SIGNAL(valueChanged(int)), this, SLOT(extractValue(int)));

            layoutButtons->addWidget(section);
            rightSet.push_back(section);
        }
    }

    layoutButtons->setSpacing(0);
    layoutButtons->setAlignment(Qt::AlignLeft);

    layoutMain->addLayout(layoutButtons);
    layoutMain->setAlignment(Qt::AlignRight);

    leftValue = 0;
    rightValue = 0;
    value = 0.0;
    modifyAvailable = true;
}

DDoubleSpinBox::~DDoubleSpinBox()
{

}
void DDoubleSpinBox::x_loadCustomNumbers(const QVector<QPixmap> &cn)
{

}
void DDoubleSpinBox::x_loadCustomNumber(const QPixmap &pm, int index)
{

}
DNumberSection *DDoubleSpinBox::x_leftSection(int index)
{
    if(index >=0 && index < leftSet.size())
        return leftSet[index];
    return nullptr;
}
DNumberSection *DDoubleSpinBox::x_rightSection(int index)
{
    if(index >= 0 && index < rightSet.size())
        return rightSet[index];
    return nullptr;
}
double DDoubleSpinBox::x_value()
{
    return value;
}
int DDoubleSpinBox::x_leftValue()
{
    return leftValue;
}
double DDoubleSpinBox::x_rightValue()
{
    return rightValue;
}
void DDoubleSpinBox::x_setValue(double v)
{
    setValue(v);
}
void DDoubleSpinBox::x_setLeftValue(int v)
{
    double _v = (double)v + rightValue;
    setValue(_v);
}
void DDoubleSpinBox::x_setRightValue(double v)
{
    int _v = v + leftValue;
    setValue(_v);
}
int DDoubleSpinBox::x_sections()
{
    return (leftSet.size() + rightSet.size());
}
int DDoubleSpinBox::x_leftSections()
{
    return leftSet.size();
}
int DDoubleSpinBox::x_rightSections()
{
    return rightSet.size();
}
void DDoubleSpinBox::x_valueUp()
{
    setValue(value + getStep());
}
void DDoubleSpinBox::x_valueDown()
{
    setValue(value - getStep());
}
void DDoubleSpinBox::x_leftValueUp()
{
    setValue(value + 1.0);
}
void DDoubleSpinBox::x_leftValueDown()
{
    setValue(value - 1.0);
}
void DDoubleSpinBox::x_setMaxValue()
{
    setValue(x_getMaxValue());
}
void DDoubleSpinBox::x_setMinValue()
{
    setValue(0.0);
}
void DDoubleSpinBox::x_setLeftMaxValue()
{
    setValue(x_getLeftMaxValue());
}
void DDoubleSpinBox::x_setLeftMinValue()
{
    setValue(rightValue);
}
void DDoubleSpinBox::x_setRightMaxValue()
{
    setValue((double)leftValue + x_getRightMaxValue());
}
void DDoubleSpinBox::x_setRightMinValue()
{
    setValue((double)leftValue);
}
bool DDoubleSpinBox::x_isMaxValue()
{
    return (value == x_getMaxValue());
}
bool DDoubleSpinBox::x_isMinValue()
{
    return (value == 0.0);
}
double DDoubleSpinBox::x_getMaxValue()
{
    return (x_getLeftMaxValue() + x_getRightMaxValue());
}
int DDoubleSpinBox::x_getLeftMaxValue()
{
    return (pow(10, leftSet.size()) - 1);
}
double DDoubleSpinBox::x_getRightMaxValue()
{
    return (1.0 - getStep());
}
void DDoubleSpinBox::x_setName(QString n)
{
    if(n.back() != ':') n.push_back(':');
    if(name == nullptr)
    {
        name = new QLabel(n, this);
        layoutMain->insertWidget(0, name, 0, Qt::AlignCenter);
    }
    else
        name->setText(n);
}
DDoubleSpinBox *DDoubleSpinBox::x_rateBox()
{
    return rateBox;
}
void DDoubleSpinBox::x_addSignSection()
{
    if(signSection == nullptr)
    {
        signSection = new DSymbolSection(this);
        signSection->x_setValue(' ');
        signSection->x_addValue('-');
        connect(signSection, SIGNAL(valueChanged(int)), this, SLOT(extractValue(int)));
        layoutButtons->insertWidget(0, signSection);
    }
}
void DDoubleSpinBox::x_addMultiplyRateBox(int left, int right)
{
    if(rateBox)
    {
        layoutButtons->removeWidget(rateBox);
        delete rateBox;
        rateBox = nullptr;
    }

    rateBox = new DDoubleSpinBox(this, left, right);
    rateBox->x_addSignSection();
    rateBox->signSection->x_clearValueList();
    rateBox->signSection->x_setValue('*');
    rateBox->x_setValue(1.0);
    connect(rateBox, SIGNAL(valueChanged(double)), this, SLOT(extractValue(double)));
    layoutButtons->addWidget(rateBox);
}
void DDoubleSpinBox::x_addDivisionRateBox(int left, int right)
{
    if(rateBox)
    {
        layoutButtons->removeWidget(rateBox);
        delete rateBox;
        rateBox = nullptr;
    }

    rateBox = new DDoubleSpinBox(this, left, right);
    rateBox->x_addSignSection();
    rateBox->signSection->x_clearValueList();
    rateBox->signSection->x_setValue('/');
    rateBox->x_setValue(1.0);
    connect(rateBox, SIGNAL(valueChanged(double)), this, SLOT(extractValue2(double)));
    layoutButtons->addWidget(rateBox);
}

double DDoubleSpinBox::getStep()
{
    return pow(10, -(rightSet.size()));
}

void DDoubleSpinBox::setValue(double v)
{
    if(v != value && v >= 0 && v <= x_getMaxValue())
    {
        modifyAvailable = false;

        leftValue = static_cast<int>(v);
        rightValue = v - static_cast<double>(leftValue);
        value = v;


//        qDebug()<<"setValue:" << v << "left:" << leftValue << "right:" << rightValue << "total:" << value;

        auto b = leftSet.begin();
        auto e = leftSet.end();
        int rate = 1;
        while(b != e)
        {
            int digit = (leftValue%(rate*10))/rate;
            rate *= 10;
            (*--e)->x_setValue(digit);
        }


        b = rightSet.begin();
        e = rightSet.end();
        int __rv = std::round(rightValue * pow(10, rightSet.size()));
        rate = 1.0;
        while(b != e)
        {
            int digit = (__rv%(rate*10))/rate;
            rate *= 10;
            (*--e)->x_setValue(digit);
        }

        modifyAvailable = true;
        double fv = getFinalValue();
//        qDebug()<<"setValue:" << value << "final:" << fv;
        emit valueChanged(fv);
    }
}
double DDoubleSpinBox::getFinalValue()
{
    double v = value;
    if(signSection && signSection->x_value() == '-')
        v *= -1;
    if(rateBox)
    {
        if(rateBox->signSection->x_value() == '*')
            v *= rateBox->x_value();
        else if(rateBox->signSection->x_value() == '/' && rateBox->x_value() != 0)
            v /= rateBox->x_value();
    }
    return v;
}
void DDoubleSpinBox::extractValue(int)
{
    if(modifyAvailable)
    {
        double rate = 1.0;
        value = 0;
        leftValue = 0;
        auto b = leftSet.begin();
        auto e = leftSet.end();
        while(b != e)
        {
            leftValue += (*--e)->x_value() * rate;
            rate *= 10.0;
        }

        rate = 10.0;
        rightValue = 0;
        b = rightSet.begin();
        e = rightSet.end();
        while(b != e)
        {
            rightValue += (*b++)->x_value() / rate;
            rate *= 10.0;
        }

        value = (double)leftValue + rightValue;

        double fv = getFinalValue();
//        qDebug()<<"extractValue:" << value << "final:" << fv << this->isEnabled();
        emit valueChanged(fv);
    }
}
void DDoubleSpinBox::extractValue2(double)
{
    extractValue(0);
}
void DDoubleSpinBox::catchOverUp()
{
    if(value != x_getMaxValue())
    {
        DNumberSection *b = reinterpret_cast<DNumberSection*>(QObject::sender());
        int i = leftSet.indexOf(b);
        if(i != -1)
        {
            x_setValue(value + pow(10, leftSet.size()-i-1));
        }
        else
        {
            i = rightSet.indexOf(b);
            if(i != -1)
            {
//                qDebug()<<"right OverUp: value:" << value << "step:" << pow(10, -(i+1)) << "new value:" << value + pow(10, -(i+1));
                x_setValue(value + pow(10, -(i+1)));
            }
        }
    }
}
void DDoubleSpinBox::catchOverDown()
{
    if(value != 0.0)
    {
        DNumberSection *b = reinterpret_cast<DNumberSection*>(QObject::sender());
        int i = leftSet.indexOf(b);
        if(i != -1)
        {
            x_setValue(value - pow(10, leftSet.size()-i-1));
        }
        else
        {
            i = rightSet.indexOf(b);
            if(i != -1)
            {
                x_setValue(value - pow(10, -(i+1)));
            }
        }
    }
}
void DDoubleSpinBox::zeroSection()
{
    DNumberSection *b = reinterpret_cast<DNumberSection*>(QObject::sender());
    if(leftSet.contain(b)|| rightSet.contain(b))
    {
        b->x_setMinValue();
    }
}
