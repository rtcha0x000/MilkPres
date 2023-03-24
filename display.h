#ifndef DISPLAY_H
#define DISPLAY_H

#include <QDialog>
#include <QMouseEvent>
#include "teaobjpage.h"

namespace Ui {
class Display;
}

class Display : public QDialog
{
    Q_OBJECT

public:
    explicit Display(QWidget *parent = nullptr);
    ~Display();

private slots:
    void mousePressEvent(QMouseEvent *event);
    void getObj(QList<TeaObjPage> list);

private:
    Ui::Display *ui;
    void displayObj();
};

#endif // DISPLAY_H
