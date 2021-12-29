#ifndef DPLOT_H
#define DPLOT_H
#include <DArray.h>
#include <QColor>
#include <QMap>
#include <QPainter>
#include <DWidget.h>
#include "DAxis.h"
#include <QPushButton>
#include <QRandomGenerator>
#include <QLayout>

typedef void (*BASEFUNC)(float &X, float &Y, float T, void *opaque);
struct DPlotDrawRange {
    DPlotDrawRange() :
        minArgument(0.0f)
      ,maxArgument(0.0f)
      ,minProduct(0.0f)
      ,maxProduct(0.0f)
      ,updatable(true) {}
    float minArgument;
    float maxArgument;
    float minProduct;
    float maxProduct;
    volatile bool updatable;

};

class DPlotPointGroup {
    enum Type {
        SingleValue
        ,PairValue
    };

public:
    friend class DPlot;
    enum DrawUnit {
        Point
        ,ConnectionLine
        ,HorizontalLine
        ,VerticalLine
    };
    struct DrawUnitContext {
        QPen pen;
        bool draw;
    };

    void setHorizontalScalce(float scale);
    void setVerticalScalce(float scale);
    void setLiveMode(bool s);
    void ingoreLivePoints() {setLiveMode(false);}
    void acceptLivePoints() {setLiveMode(true);}

    DPlotPointGroup(DPlotDrawRange *global, const QString &name);
    void setName(const QString &n);
    const QString& getName() const;

    bool setPoint(int index, float arg, float prod);
    bool setProduct(int index, float prod);
    bool setArgument(int index, float arg);
//-----------------------------------------------------------------------
    void addPoint(float arg, float prod);
    void addPoint(float value);
    void addLivePoint(float arg, float prod);
    void addLivePoint(float value);
    void setSize(int size);
    int size() const;
//-----------------------------------------------------------------------
    void setUnitDrawable(DrawUnit u, bool s);
    void setUnitSize(DrawUnit u, int size);
    void setUnitColor(DrawUnit u, const QColor &color);
    void setUnitColor(DrawUnit u, int r, int g, int b, int a = 255);
//-----------------------------------------------------------------------
    void setBaseFunction(BASEFUNC bf) {base = bf;}
    void setBaseFunctionIterations(int iters) {base_iterations = iters;}
    void setBaseFunctionStep(float step) {base_step = step;}
    void setBaseFunctionStartArgument(float startArgument) {base_start = startArgument;}
    void setBaseFunctionSource(void *source) {base_source = source;}
    bool fillByBaseFunction();
    void addBasePoint();
    void addLiveBasePoint();
//-----------------------------------------------------------------------
    void switchToSingleValueMode();
    void switchToPairValueMode();
//-----------------------------------------------------------------------
    const DArray<float>& getProduct() const {return product;}
    const DArray<float>& getArgument() const {return argument;}
    QColor getUnitColor(DrawUnit u) const {return drawMap[u].pen.color();}
    int getUnitSize(DrawUnit u) const {return drawMap[u].pen.width();}
    bool isUnitDrawable(DrawUnit u) const {return drawMap[u].draw;}



private:
    void updateProductRange(float newProduct);
    void updateArgumentRange(float newArgument);

    void updateArgumentRange();
    void updateProductRange();
    void updateRange();
private:
    volatile bool draw;
    QString name;
private:
    DArray<float> product;
    DArray<float> argument;
    Type t;



    float defaultArgumentShift;
    float defaultProductShift;

    DPlotDrawRange range;
    DPlotDrawRange *globalRange;


    BASEFUNC base;
    int base_iterations;
    int base_pos;
    float base_step;
    float base_start;
    float base_lastarg;
    void *base_source;
private:
    int pushPos;
    int startPos;
private:
    QMap<DrawUnit, DrawUnitContext> drawMap;
private:
};
class DPlot : public DWidget {
    Q_OBJECT
protected:
    void paintEvent(QPaintEvent *event) override;
public:
    friend class DPlotSettings;
    DPlot(QWidget *parent = nullptr);
    DPlotPointGroup* addGroup(const QString &name);
    DPlotPointGroup* getGroup(int index);
    DPlotPointGroup* getGroup(const QString &name);

    void setGlobalRangeUsage(bool s);
    bool usingGlobalRange() const {return globalRange.updatable;}
private:
    void draw(QPainter *p);
    void updateGlobalRange();
private slots:
    void slot_updateAxes();
private:
    D2DAxes axes;
    DArray<DPlotPointGroup*> groups;
    DArray<DPlotPointGroup*>::const_iterator __drawIt;
    DArray<DPlotPointGroup*>::const_iterator __drawEnd;
    DPlotDrawRange globalRange;
private:
    QPoint lastPoint;
};
class DPlotSettings : public DWidget {
    Q_OBJECT
public:
    DPlotSettings(QWidget *parent = nullptr);

    void setTarget(DPlot *target) {plot = target;}
private slots:
    void slot_addPoint(bool);
    void slot_addLivePoint(bool);

private:

    QRandomGenerator random;
    QPushButton *buttonTestPoint;
    QPushButton *buttonTestLivePoint;
    QVBoxLayout *layoutMain;
    // Global
    // 1. Axes: invert
    // 2. Cursor targeting
    // 3. Cursor attach pos info
    // 4. Global range
    // 5. Show: min/max
    // 6. Show: groups number
    // 7. Global scaling
    // 8. Global on/off live mode

    // Group:
    // 1. Set/show unit color
    // 2. Set/show unit width
    // 3. Set/show unit drawable
    // 4. Scaling
    // 5. On/off live mode

    DPlot *plot;
};

#endif // DPLOT_H

