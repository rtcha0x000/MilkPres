#ifndef TEAOBJPAGE_H
#define TEAOBJPAGE_H
#include <QList>
#include <QString>
#include "teaobj.h"


class TeaObjPage
{
private:
public:
    TeaObjPage();
    QList<TeaObj> list;
    QString title;
    void appendObj(TeaObj obj){
        list.append(obj);
    }
};

#endif // TEAOBJPAGE_H
