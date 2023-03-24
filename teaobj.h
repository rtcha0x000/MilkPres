#ifndef TEAOBJ_H
#define TEAOBJ_H
#include <QList>
#include "TeaType.h"
#include "teaobjcont.h"


class TeaObj
{
public:
    TeaObj();
    QList<QString> title;
    TeaType type;
    QList<TeaObjCont> contents;
    void empty(){
        title.empty();
        contents.empty();
        type=TextBlock;
        return;
    }
};

#endif // TEAOBJ_H
