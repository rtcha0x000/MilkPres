#ifndef TEAOBJCONT_H
#define TEAOBJCONT_H
#include <QString>
#include <QColor>
#include <QRect>
#include <QImage>

class TeaObjCont
{
public:
    TeaObjCont();
private:
    QString str;
public:
    static TeaObjCont fromText(QString text){
        TeaObjCont obj;
        obj.str=text;
        return obj;
    }
    static TeaObjCont setColor(QColor color){
        TeaObjCont obj;
        obj.str=QString::number(color.red())+" "+QString::number(color.green())+" "+QString::number(color.blue());
        return obj;
    }
    static TeaObjCont setRect(QRect rect){
        TeaObjCont obj;
        obj.str=QString::number(rect.x())+" "+QString::number(rect.y());
        return obj;
    }
    static TeaObjCont setImage();    //TODO: add function here
    QColor toColor(){
        return qRgb(str.mid(0,str.indexOf(" ")).toInt(),
                    str.mid(str.indexOf(" ")+1,str.lastIndexOf(" ")-str.indexOf(" ")-1).toInt(),
                    str.mid(str.lastIndexOf(" ")+1,str.size()-str.lastIndexOf(" ")-1).toInt());
    }
    QRect toRect(){
        QRect rt;
        rt.setX(str.mid(0,str.indexOf(" ")).toInt());
        rt.setY(str.mid(str.indexOf(" ")+1,str.size()-str.indexOf(" ")-1).toInt());
        return rt;
    }
    QImage toImage();   //TODO: add function here
    QString toText(){
        return str;
    }
};

#endif // TEAOBJCONT_H
