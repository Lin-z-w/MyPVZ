#ifndef STARTWIDGET_H
#define STARTWIDGET_H
#include <QPushButton>
#include <QWidget>

class StartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StartWidget(QWidget *parent = nullptr);

    void sendSlot();

private:
    QPushButton b;

signals:
    void startGame();
};

#endif // STARTWIDGET_H
