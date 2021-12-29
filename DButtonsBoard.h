#ifndef DBUTTONSBOARD_H
#define DBUTTONSBOARD_H

#include "DWidget.h"
#include <QLayout>
#include <QPushButton>
#include <DArray.h>

class DButtonsBoard : public DWidget {
    Q_OBJECT
public:
    DButtonsBoard(QWidget *parent = nullptr);

    void x_addButton();
    void x_addButton(const QString &text);
    void x_removeAll();
    bool x_removeButton(int index);
    bool x_setButtonText(int index, const QString &text);
    const QPushButton * button(int index) const;

private slots:
    void catchClick(bool);
signals:
    void clicked(int index);
private:

    QBoxLayout *layoutMain;
    DArray<QPushButton*> buttons;
};

#endif // DBUTTONSBOARD_H
