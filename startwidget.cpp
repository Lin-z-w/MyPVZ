#include "startwidget.h"

StartWidget::StartWidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("MyPvZ");
    b.setParent(this);
    b.setText("Start");

    connect(&b, &QPushButton::released, this, &StartWidget::sendSlot);

}

void StartWidget::sendSlot() {
    emit startGame();
}
