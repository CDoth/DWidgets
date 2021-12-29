#include "DPlot.h"


DPlotPointGroup::DPlotPointGroup(DPlotDrawRange *global, const QString &_name) : name(_name), globalRange(global) {
    draw = true;
    defaultArgumentShift = 1.0f;
    defaultProductShift = 1.0f;


    base = nullptr;
    base_iterations = 0;
    base_pos = 0;
    base_step = 0.0f;
    base_start = 0.0f;
    base_source = nullptr;

    pushPos = 0;
    startPos = 0;

    t = SingleValue;

    drawMap[Point] = DrawUnitContext({QPen(Qt::red, 7), true});
    drawMap[ConnectionLine] = DrawUnitContext({QPen(Qt::black, 1), true});
    drawMap[HorizontalLine] = DrawUnitContext({QPen(Qt::blue, 1), false});
    drawMap[VerticalLine] = DrawUnitContext({QPen(Qt::blue, 1), false});
}
void DPlotPointGroup::setName(const QString &n) {
    name = n;
}
const QString &DPlotPointGroup::getName() const {
    return name;
}
bool DPlotPointGroup::setPoint(int index, float arg, float prod) {
    if(index >= 0 && index < argument.size()) {
        if(argument[index] != arg && (argument[index] == range.minArgument || argument[index] == range.maxArgument)) {
            updateArgumentRange();
        } else {
            updateArgumentRange(arg);
        }

        if(product[index] != prod && (product[index] == range.minProduct || product[index] == range.maxProduct)) {
            updateArgumentRange();
        } else {
            updateArgumentRange(prod);
        }

        argument[index] = arg;
        product[index] = prod;

        return true;
    }
    return false;
}
bool DPlotPointGroup::setProduct(int index, float prod) {
    if(index >= 0 && index < product.size()) {

        if(product[index] != prod && (product[index] == range.minProduct || product[index] == range.maxProduct)) {
            updateArgumentRange();
        } else {
            updateArgumentRange(prod);
        }

        product[index] = prod;

        return true;
    }
    return false;
}
bool DPlotPointGroup::setArgument(int index, float arg) {
    if(index >= 0 && index < argument.size()) {

        if(argument[index] != arg && (argument[index] == range.minArgument || argument[index] == range.maxArgument)) {
            updateArgumentRange();
        } else {
            updateArgumentRange(arg);
        }

        argument[index] = arg;

        return true;
    }
    return false;
}
void DPlotPointGroup::addPoint(float arg, float prod) {
    if(t == SingleValue) {
        switchToPairValueMode();
    }
    if(pushPos) {
        product.movePart(0, startPos, product.size() - startPos);
        argument.movePart(0, startPos, argument.size() - startPos);
        startPos = 0;
        pushPos = 0;
    }



    argument.push_back(arg);
    product.push_back(prod);


    qDebug() << "addPoint:" << "arg:" << arg << "prod:" << prod << "pushPos:" << pushPos << "size:" << argument.size();
    FOR_VALUE(argument.size(), i) {
        std::cout << argument[i] << " ";
    }
    std::cout << std::endl;


    updateArgumentRange(arg);
    updateProductRange(prod);
}
void DPlotPointGroup::addPoint(float value) {
    if(t == PairValue) {
        switchToSingleValueMode();
    }
    if(startPos) {
        product.movePart(0, startPos, product.size() - startPos);
        startPos = 0;
        pushPos = 0;
    }
    product.push_back(value);
    updateProductRange(value);
}
void DPlotPointGroup::addLivePoint(float arg, float prod) {
    if(argument.empty()) {
        return addPoint(arg, prod);
    }
    if(t == SingleValue) {
        switchToPairValueMode();
    }

    if(argument[pushPos] != arg) {
        if(argument[pushPos] == range.minArgument || argument[pushPos] == range.maxArgument) {
            argument[pushPos] = arg;
            updateArgumentRange();
        } else {
            argument[pushPos] = arg;
            updateArgumentRange(arg);
        }
    }



//    argument[pushPos] = arg;
//    updateArgumentRange(arg);


    product[pushPos] = prod;
    updateProductRange(prod);

    qDebug() << "addLivePoint:" << "arg:" << arg << "prod:" << prod << "pushPos:" << pushPos << "size:" << argument.size();

    FOR_VALUE(argument.size(), i) {
        std::cout << argument[i] << " ";
    }
    std::cout << std::endl;

    if(++pushPos == argument.size()) {
        pushPos = 0;
    }
    startPos = pushPos;
}
void DPlotPointGroup::addLivePoint(float value) {
    if(product.empty()) {
        return addPoint(value);
    }
    if(t == PairValue) {
        switchToSingleValueMode();
    }
    product[pushPos] = value;
    updateProductRange(value);


    if(++pushPos == product.size()) {
        pushPos = 0;
    }
    startPos = pushPos;


}
void DPlotPointGroup::setSize(int size) {
    argument.reform(size);
    product.reform(size);
}
int DPlotPointGroup::size() const {
    return argument.size();
}
void DPlotPointGroup::setUnitDrawable(DPlotPointGroup::DrawUnit u, bool s) {
    drawMap[u].draw = s;
}
void DPlotPointGroup::setUnitSize(DPlotPointGroup::DrawUnit u, int size) {
    drawMap[u].pen.setWidth(size);
}
void DPlotPointGroup::setUnitColor(DPlotPointGroup::DrawUnit u, const QColor &color) {
    drawMap[u].pen.setColor(color);
}
void DPlotPointGroup::setUnitColor(DPlotPointGroup::DrawUnit u, int r, int g, int b, int a) {
    drawMap[u].pen.setColor(QColor(r, g, b, a));
}
bool DPlotPointGroup::fillByBaseFunction() {
    if(base == nullptr || base_iterations <= 0 || base_step == 0.0f) {
        return false;
    }
    draw = false;

    if(argument.size() != base_iterations) {
        argument.reform(base_iterations);
        product.reform(base_iterations);
    }
    float arg = base_start;
    float prod = 0.0f;
    FOR_VALUE(base_iterations, i) {
        base(arg, prod, i, base_source);
        argument[i] = arg;
        product[i] = prod;
        base_pos = i;
        base_lastarg = arg;
        arg += base_step;
    }
    updateRange();

    draw = true;

    return true;
}
void DPlotPointGroup::addBasePoint() {
    float arg = argument.size() ? base_lastarg + base_step : base_start;


    float prod = 0.0f;
    base(arg, prod, base_pos++, base_source);

//    qDebug() << "addBasePoint" << arg << base_lastarg << "prod:" << prod;

    base_lastarg = arg;

    addPoint(arg, prod);
}
void DPlotPointGroup::addLiveBasePoint() {

    float arg = argument.size() ? base_lastarg + base_step : base_start;


    float prod = 0.0f;
    base(arg, prod, base_pos++, base_source);

//    qDebug() << "addLiveBasePoint" << arg << base_lastarg << "prod:" << prod;

    base_lastarg = arg;

    addLivePoint(arg, prod);
}
void DPlotPointGroup::switchToSingleValueMode() {
    t = SingleValue;
    argument.clear();
    product.clear();
    pushPos = 0;
}
void DPlotPointGroup::switchToPairValueMode() {
    t = PairValue;
    argument.clear();
    product.clear();
    pushPos = 0;
}
void DPlotPointGroup::updateArgumentRange(float newArgument) {

    if(argument.size() > 1) {
        if(newArgument < range.minArgument) {
            range.minArgument = newArgument;
        }
        if(newArgument > range.maxArgument) {
            range.maxArgument = newArgument;
        }
    } else if(argument.size() == 1){
        range.minArgument = range.maxArgument = newArgument;
    }
}
void DPlotPointGroup::updateProductRange(float newProduct) {
    if(product.size() > 1) {
        if(newProduct < range.minProduct) {
            range.minProduct = newProduct;
        }
        if(newProduct > range.maxProduct) {
            range.maxProduct = newProduct;
        }
    } else if(product.size() == 1) {
        range.minProduct = range.maxProduct = newProduct;
    }
}
void DPlotPointGroup::updateArgumentRange() {
    if(argument.empty()) {
        range.minArgument = 0;
        range.maxArgument = 0;
        return;
    }
    auto b = argument.constBegin();
    auto e = argument.constEnd();


    range.minArgument = argument.front();
    range.maxArgument = argument.front();

    ++b;
    while(b!=e) {
        float v = *b++;
        if(v < range.minArgument) range.minArgument = v;
        if(v > range.maxArgument) range.maxArgument = v;

//        if(globalRange && globalRange->updatable) {
//            if(v < globalRange->minArgument) globalRange->minArgument = v;
//            if(v > globalRange->maxArgument) globalRange->maxArgument = v;
//        }

    }
}
void DPlotPointGroup::updateProductRange() {
    if(product.empty()) {
        range.minProduct = 0;
        range.maxProduct = 0;
        return;
    }
    auto b = product.constBegin();
    auto e = product.constEnd();

    range.minProduct = product.front();
    range.maxProduct = product.front();


    ++b;
    while(b!=e) {
        float v = *b++;
        if(v < range.minProduct) range.minProduct = v;
        if(v > range.maxProduct) range.maxProduct = v;

        if(globalRange && globalRange->updatable) {
            if(v < globalRange->minProduct) globalRange->minProduct = v;
            if(v > globalRange->maxProduct) globalRange->maxProduct = v;
        }

    }
}
void DPlotPointGroup::updateRange() {
    updateArgumentRange();
    updateProductRange();
}


//======================================================================================== DPlot
void DPlot::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    drawMainRect(&p, this->rect());
    draw(&p);
}
DPlot::DPlot(QWidget *parent) : DWidget(parent) {
    __drawIt = nullptr;
    __drawEnd = nullptr;
    lastPoint = QPoint(0,0);

    connect(this, SIGNAL(resized()), this, SLOT(slot_updateAxes()));
}
DPlotPointGroup *DPlot::addGroup(const QString &name) {
    if(name.isEmpty()) {
        return nullptr;
    }
    DPlotPointGroup *g = getGroup(name);
    if(g) return g;
    g = new DPlotPointGroup(&globalRange, name);
    groups.push_back(g);
    __drawEnd = groups.end();
    return g;
}
DPlotPointGroup *DPlot::getGroup(int index) {
    if(index >= 0 && index < groups.size()) {
        return groups[index];
    }
    return nullptr;
}
DPlotPointGroup *DPlot::getGroup(const QString &name) {
    FOR_VALUE(groups.size(), i) {
        if(groups[i]->getName() == name) {
            return groups[i];
        }
    }
    return nullptr;
}
void DPlot::setGlobalRangeUsage(bool s) {
    if(s && !globalRange.updatable) {
        updateGlobalRange();
    }
    globalRange.updatable = s;
}



void DPlot::draw(QPainter *p) {

    axes.draw(p);
    QPoint anchor = axes.getAnchor();
    int ArgumentPos = 0;
    int ProductPos = 0;

    __drawIt = groups.constBegin();
    int index = 0;
    QPoint point;
    updateGlobalRange();

    while(__drawIt != __drawEnd) {
        DPlotPointGroup *g = *__drawIt++;
        if(g->draw) {
            index = g->startPos;
            lastPoint = QPoint(0,0);



            if(g->t == DPlotPointGroup::SingleValue) {

//                qDebug() << "DPlot::draw: SingleValue:" << g << "size:" << g->product.size() << "-------"; qwe
                FOR_VALUE(g->product.size(), point_index) {

                    if(index == g->product.size()) {
                        index = 0;
                    }

                    float minProd = globalRange.updatable ? globalRange.minProduct : g->range.minProduct;
                    float productRange = globalRange.updatable ? (globalRange.maxProduct - globalRange.minProduct) : (g->range.maxProduct - g->range.minProduct);

                    int XPos = getPartF(0, g->product.size(), point_index) * axes.wAxisConst().getSize();
                    int YPos = getPartF(minProd, productRange, g->product[index]) * axes.hAxisConst().getSize();

                    point = QPoint (
                                axes.wAxisConst().isInverted() ? anchor.x() - XPos : anchor.x() + XPos,
                                axes.hAxisConst().isInverted() ? anchor.y() + YPos : anchor.y() - YPos);

#define DRAW_UNIT(X, ACTION) \
    dc = g->drawMap[X]; \
    if(dc.draw) {p->setPen(dc.pen); ACTION; }

                DPlotPointGroup::DrawUnitContext dc;
                DRAW_UNIT(DPlotPointGroup::Point, p->drawPoint(point));
                if(!lastPoint.isNull()) {
                    DRAW_UNIT(DPlotPointGroup::ConnectionLine, p->drawLine(lastPoint, point));
                }
                DRAW_UNIT(DPlotPointGroup::HorizontalLine, p->drawLine(point, QPoint(anchor.x(), point.y())));
                DRAW_UNIT(DPlotPointGroup::VerticalLine, p->drawLine(point, QPoint(point.x(), anchor.y())));


#undef DRAW_UNIT
                lastPoint = point;

                    ++index;



                }
            } else {


                float minArg = globalRange.updatable ? globalRange.minArgument : g->range.minArgument;
                float minProd = globalRange.updatable ? globalRange.minProduct : g->range.minProduct;
                float argumentRange = globalRange.updatable ? (globalRange.maxArgument - globalRange.minArgument) : (g->range.maxArgument - g->range.minArgument);
                float productRange = globalRange.updatable ? (globalRange.maxProduct - globalRange.minProduct) : (g->range.maxProduct - g->range.minProduct);


                qDebug() << "DPlot::draw: group:" << g << "size:" << g->size() << "-------"
                         << "global: minarg:" << globalRange.minArgument << "maxarg:" << globalRange.maxArgument;

                FOR_VALUE(g->size(), i) {

                    ArgumentPos = getPartF(minArg, argumentRange, g->getArgument()[i]) * axes.wAxisConst().getSize();
                    ProductPos = getPartF(minProd, productRange, g->getProduct()[i]) * axes.hAxisConst().getSize();



                    point = QPoint (
                                axes.wAxisConst().isInverted() ? anchor.x() - ArgumentPos : anchor.x() + ArgumentPos,
                                axes.hAxisConst().isInverted() ? anchor.y() + ProductPos : anchor.y() - ProductPos);


                    qDebug() << "DPlot::draw:"
                             << "index:" << i
                             << "arg:" << g->getArgument()[i] << "prod:" << g->getProduct()[i]
                                << "ArgumentPos:" << ArgumentPos << "ProductPos:" << ProductPos
                                << "minArg:" << minArg << "argRange:" << argumentRange
                                << "minProd:" << minProd << "prodRange:" << productRange
                                << "point:" << point;



#define DRAW_UNIT(X, ACTION) \
    dc = g->drawMap[X]; \
    if(dc.draw) {p->setPen(dc.pen); ACTION; }

                DPlotPointGroup::DrawUnitContext dc;
                DRAW_UNIT(DPlotPointGroup::Point, p->drawPoint(point));
                if(!lastPoint.isNull()) {
                    DRAW_UNIT(DPlotPointGroup::ConnectionLine, p->drawLine(lastPoint, point));
                }
                DRAW_UNIT(DPlotPointGroup::HorizontalLine, p->drawLine(point, QPoint(anchor.x(), point.y())));
                DRAW_UNIT(DPlotPointGroup::VerticalLine, p->drawLine(point, QPoint(point.x(), anchor.y())));


#undef DRAW_UNIT
                lastPoint = point;

                } //draw one group end
            } // draw PairValue group end



        } //check group drawable end
    } //draw all groups end


}
void DPlot::updateGlobalRange() {
    if(groups.empty()) {
        globalRange.minArgument = 0;
        globalRange.maxArgument = 0;
        globalRange.minProduct = 0;
        globalRange.maxProduct = 0;
        return;
    }

    auto b = groups.constBegin();
    auto e = groups.constEnd();

    globalRange.minArgument = (*b)->range.minArgument;
    globalRange.maxArgument = (*b)->range.maxArgument;
    globalRange.minProduct = (*b)->range.minProduct;
    globalRange.maxProduct = (*b)->range.maxProduct;
    ++b;
    while(b != e) {
        DPlotDrawRange &__range = (*b++)->range;

        if(__range.minArgument < globalRange.minArgument) globalRange.minArgument = __range.minArgument;
        if(__range.maxArgument > globalRange.maxArgument) globalRange.maxArgument = __range.maxArgument;

        if(__range.minProduct < globalRange.minProduct) globalRange.minProduct = __range.minProduct;
        if(__range.maxProduct > globalRange.maxProduct) globalRange.maxProduct = __range.maxProduct;

    }
//    FOR_VALUE(groups.size(), i) {
//        if(groups[i]->size()) {
//            auto b = groups[i]->argument.constBegin();
//            auto e = groups[i]->argument.constEnd();
//            globalRange.minArgument = *b;
//            globalRange.maxArgument = *b;
//            ++b;
//            while(b!=e) {
//                float v = *b++;
//                if(v < globalRange.minArgument) globalRange.minArgument = v;
//                if(v > globalRange.maxArgument) globalRange.maxArgument = v;
//            }
//            b = groups[i]->product.constBegin();
//            e = groups[i]->product.constEnd();
//            while(b!=e) {
//                float v = *b++;
//                if(v < globalRange.minProduct) globalRange.minProduct = v;
//                if(v > globalRange.maxProduct) globalRange.maxProduct = v;
//            }
//        }
//    }
}
void DPlot::slot_updateAxes() {
    axes.update();
}
//================================================================================================= DPlotSettings
DPlotSettings::DPlotSettings(QWidget *parent) : DWidget(parent) {
    buttonTestPoint = new QPushButton("add", this);
    buttonTestLivePoint = new QPushButton("add live", this);
    connect(buttonTestPoint, SIGNAL(clicked(bool)), this, SLOT(slot_addPoint(bool)));
    connect(buttonTestLivePoint, SIGNAL(clicked(bool)), this, SLOT(slot_addLivePoint(bool)));
    layoutMain = new QVBoxLayout(this);
    layoutMain->addWidget(buttonTestPoint);
    layoutMain->addWidget(buttonTestLivePoint);
}
void DPlotSettings::slot_addPoint(bool) {

    if(plot) {
        auto g = plot->getGroup(0);

        if(g) {
            //test1:
//            g->addPoint(random.generate() % 100);
            //test2:
            g->addBasePoint();
            //test3:
//            g->addPoint(random.generate() % 100, random.generate() % 100);
            //test4:
//            g->addLivePoint(random.generate() % 100);
            //test5:
//            g->addPoint(random.generate() % 100);

            plot->update();
        } else {
            qDebug() <<"can't get group";
        }
    } else {
        qDebug() << "no target plot";
    }
}
void DPlotSettings::slot_addLivePoint(bool) {
    if(plot) {
        auto g = plot->getGroup(0);

        if(g) {
            //test1:
//            g->addLivePoint(random.generate() % 100);
            //test2:
            g->addLiveBasePoint();
            //test3:
//            g->addPoint(random.generate() % 100, random.generate() % 100);
            //test4:
//            g->addLivePoint(random.generate() % 100);
            //test5:
//            g->addLivePoint(random.generate() % 100);

            plot->update();
        } else {
            qDebug() <<"can't get group";
        }
    } else {
        qDebug() << "no target plot";
    }
}

