#ifndef TEATYPE_H
#define TEATYPE_H

#include <QString>

enum TeaType {  //defines types of objects in TeaPres, see TeaObjCont
    TextBlock,
    Rectangle,
    Ellipse,
    Picture
};

inline QString getTeaObjName(TeaType obj){
    switch(obj){
    case TextBlock:return "TextBlock";
    case Rectangle:return "Rectangle";
    case Ellipse:return "Ellipse";
    case Picture:return "Picture";
    }
}

inline TeaType fromTeaObjName(QString str){
    if(str=="TextBlock")return TextBlock;
    else if(str=="Rectangle")return Rectangle;
    else if(str=="Ellipse")return Ellipse;
    else return Picture;
}

#endif // TEATYPE_H
