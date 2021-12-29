#include "DButtonsBoard.h"


DButtonsBoard::DButtonsBoard(QWidget *parent) : DWidget(parent) {

    layoutMain = new QBoxLayout(QBoxLayout::Direction::TopToBottom, this);
}
void DButtonsBoard::x_addButton() {
    x_addButton(QString());
}
void DButtonsBoard::x_addButton(const QString &text) {
    auto b = new QPushButton(text, this);
    connect(b, SIGNAL(clicked(bool)), this, SLOT(catchClick(bool)));
    layoutMain->addWidget(b);
    buttons.push_back(b);
}
void DButtonsBoard::x_removeAll() {
    FOR_VALUE(buttons.size(), i) {
        disconnect(buttons[i], SIGNAL(clicked(bool)), this, SLOT(catchClick(bool)));
        layoutMain->removeWidget(buttons[i]);
        delete buttons[i];
    }
    buttons.clear();
}
bool DButtonsBoard::x_removeButton(int index) {
    if(index >= 0 && index < buttons.size()) {
        disconnect(buttons[index], SIGNAL(clicked(bool)), this, SLOT(catchClick(bool)));
        layoutMain->removeWidget(buttons[index]);
        delete buttons[index];
        return true;
    }
    return false;
}
bool DButtonsBoard::x_setButtonText(int index, const QString &text) {
    if(index >= 0 && index < buttons.size()) {
        buttons[index]->setText(text);
        return true;
    }
    return false;
}
const QPushButton *DButtonsBoard::button(int index) const {
    if(index >= 0 && index < buttons.size()) {
        return buttons[index];
    }
    return nullptr;
}
void DButtonsBoard::catchClick(bool) {

    QPushButton *b = reinterpret_cast<QPushButton*>(QObject::sender());
    emit clicked(buttons.indexOf(b));

}
