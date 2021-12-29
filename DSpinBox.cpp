#include "DSpinBox.h"

#define DSPINBOX_MAX_SECTIONS (32)
DSpinBox::DSpinBox(QWidget *parent, int n) : DWidget(parent)
{
    signSection = nullptr;
    rateBox = nullptr;
    name = nullptr;
    if(n <= 0) n = 1;
    if(n > DSPINBOX_MAX_SECTIONS) n = DSPINBOX_MAX_SECTIONS;
    layoutButtons = new QHBoxLayout();
    layoutMain = new QHBoxLayout(this);
    FOR_VALUE(n, i)
    {
        auto section = new DNumberSection(this);
        connect(section, SIGNAL(tryOverUp()), this, SLOT(catchOverUp()));
        connect(section, SIGNAL(tryOverDown()), this, SLOT(catchOverDown()));
        connect(section, SIGNAL(dblClicked()), this, SLOT(zeroSection()));
        connect(section, SIGNAL(valueChanged(int)), this, SLOT(extractValue(int)));

        layoutButtons->addWidget(section);
        set.push_back(section);
    }
    layoutButtons->setSpacing(0);
    layoutButtons->setAlignment(Qt::AlignLeft);

    layoutMain->addLayout(layoutButtons);
    layoutMain->setAlignment(Qt::AlignRight);

    value = 0;
    modifyAvailable = true;
}
DSpinBox::~DSpinBox()
{

}
int DSpinBox::x_value()
{
    return value;
}
DNumberSection *DSpinBox::x_section(int index)
{
    if(index >=0 && index < set.size())
        return set[index];
    return nullptr;
}
void DSpinBox::x_loadCustomNumbers(const QVector<QPixmap> &cn)
{
    FOR_VALUE(set.size(), i)
    {
        set[i]->x_setCustomImages(cn);
    }
}
void DSpinBox::x_loadCustomNumber(const QPixmap &pm, int index)
{
    FOR_VALUE(set.size(), i)
    {
        set[i]->x_setCustomImage(pm, index);
    }
}
int DSpinBox::x_getMaxValue()
{
    return (pow(10, set.size()) - 1);
}
int DSpinBox::x_sections()
{
    return set.size();
}
void DSpinBox::x_setName(QString n)
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
DSpinBox *DSpinBox::x_rateBox()
{
    return rateBox;
}
void DSpinBox::x_addSignSection()
{
    if(signSection == nullptr)
    {
        signSection = new DSymbolSection(this);
        signSection->x_addValue('-');
        connect(signSection, SIGNAL(valueChanged(int)), this, SLOT(extractValue(int)));
        layoutButtons->insertWidget(0, signSection);
    }
}
void DSpinBox::x_addMultiplyRateBox(int n)
{
    if(rateBox)
    {
        layoutButtons->removeWidget(rateBox);
        delete rateBox;
        rateBox = nullptr;
    }

    rateBox = new DSpinBox(this, n);
    rateBox->x_addSignSection();
    rateBox->signSection->x_clearValueList();
    rateBox->signSection->x_setValue('*');
    rateBox->x_setValue(1);
    connect(rateBox, SIGNAL(valueChanged(int)), this, SLOT(extractValue(int)));
    layoutButtons->addWidget(rateBox);
}
void DSpinBox::x_addDivisionRateBox(int n)
{
    if(rateBox)
    {
        layoutButtons->removeWidget(rateBox);
        delete rateBox;
        rateBox = nullptr;
    }
    rateBox = new DSpinBox(this, n);
    rateBox->x_addSignSection();
    rateBox->signSection->x_clearValueList();
    rateBox->signSection->x_setValue('/');
    rateBox->x_setValue(1);
    connect(rateBox, SIGNAL(valueChanged(int)), this, SLOT(extractValue(int)));
    layoutButtons->addWidget(rateBox);
}
void DSpinBox::x_setValue(int v)
{
    int rate = 1;
    modifyAvailable = false;
    if(v >= 0 && v <= x_getMaxValue())
    {
        auto b = set.begin();
        auto e = set.end();
        while(b != e)
        {
            int digit = (v%(rate*10))/rate;
            rate *= 10;
            (*--e)->x_setValue(digit);
        }
        value = v;
    }
    modifyAvailable = true;
    extractValue(0);
}
void DSpinBox::x_valueUp()
{
    x_setValue(value + 1);
}
void DSpinBox::x_valueDown()
{
    x_setValue(value - 1);
}
void DSpinBox::x_setMaxValue()
{
    x_setValue(x_getMaxValue());
}
void DSpinBox::x_setMinValue()
{
    x_setValue(0);
}
bool DSpinBox::x_isMinValue()
{
    return (value == 0);
}
bool DSpinBox::x_isMaxValue()
{
    return (value == x_getMaxValue());
}
void DSpinBox::catchOverUp()
{
    DNumberSection *b = reinterpret_cast<DNumberSection*>(QObject::sender());
    int i = set.indexOf(b);
    if(i != -1 && value != x_getMaxValue())
    {
//        int nv = value + pow(10, set.size()-i-1);
//        qDebug()<<"catchOverUp: value:" << value << "max:" << x_getMaxValue() << "new value:" << nv;
        x_setValue(value + pow(10, set.size()-i-1));
    }
    /*
    modifyAvailable = false;
    DNumberSection *b = reinterpret_cast<DNumberSection*>(QObject::sender());
    auto it = set.contain(b);
    if(it != set.end() && it != set.begin())
    {
        auto base = it;
        while(it != set.begin())
        {
            if(!(*--it)->x_isMaxValue())
            {
                (*it)->x_valueUp();
                while(it != base)
                {
                    (*++it)->x_setMinValue();
                }
                modifyAvailable = true;
                extractValue(0);
                return;
            }
        }
    }
    modifyAvailable = true;
    */
}
void DSpinBox::catchOverDown()
{
    DNumberSection *b = reinterpret_cast<DNumberSection*>(QObject::sender());
    int i = set.indexOf(b);
    if(i != -1 && value != 0)
    {
        x_setValue(value - pow(10, set.size()-i-1));
    }
    /*
    modifyAvailable = false;
    DNumberSection *b = reinterpret_cast<DNumberSection*>(QObject::sender());
    auto it = set.contain(b);
    if(it != set.end() && it != set.begin())
    {
        auto base = it;
        while(it != set.begin())
        {
            if(!(*--it)->x_isMinValue())
            {
                (*it)->x_valueDown();
                while(it != base)
                {
                    (*++it)->x_setMaxValue();
                }
                modifyAvailable = true;
                extractValue(0);
                return;
            }
        }
    }
    modifyAvailable = true;
    */
}
void DSpinBox::extractValue(int)
{
    if(modifyAvailable)
    {
        int rate = 1;
        value = 0;
        auto b = set.begin();
        auto e = set.end();
        while(b != e)
        {
            value += (*--e)->x_value() * rate;
            rate *= 10;
        }
        if(signSection && signSection->x_value() == '-')
            value *= -1;
        if(rateBox)
        {
            if(rateBox->signSection->x_value() == '*')
                value *= rateBox->x_value();
            if(rateBox->signSection->x_value() == '/' && rateBox->x_value() != 0)
                value /= rateBox->x_value();
        }

//        qDebug()<<"extractValue:" << value;
        emit valueChanged(value);
    }
}
void DSpinBox::modifyValue(int v)
{
    if(modifyAvailable)
    {
        DNumberSection *b = reinterpret_cast<DNumberSection*>(QObject::sender());
        int i = set.indexOf(b);
        if(i != -1)
        {
            int rate = pow(10, set.size()-i-1);
            int add = v * rate;

            int left = value / (rate*10);
            int right = value % rate;
            value = left * (rate*10) + (v*rate) + right;

            qDebug()<<"modifyValue" << "index:" << i << rate << add << "value:" << value;
        }
    }
}
void DSpinBox::zeroSection()
{
    DNumberSection *b = reinterpret_cast<DNumberSection*>(QObject::sender());
    if(set.contain(b))
    {
        b->x_setMinValue();
    }
}
