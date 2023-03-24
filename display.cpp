#include "display.h"
#include "ui_display.h"
#include <QTextBrowser>
#include <QPushButton>
#include <QDebug>
static QList<TeaObjPage> curlist;
static bool next=false;

Display::Display(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Display)
{
    ui->setupUi(this);
    setWindowTitle("Presentation");
    setWindowIcon(QIcon(":/new/pics/TeaPres.ico"));
    setStyleSheet("background-color:white;color:black;");
    showFullScreen();
}

Display::~Display()
{
    delete ui;
}

void Display::mousePressEvent(QMouseEvent *event){
    next=true;
}

void Display::getObj(QList<TeaObjPage> list){
    curlist=list;
    displayObj();
}

void Display::displayObj(){
    for(int cnt=0;cnt<curlist.size();cnt++){
        next=false;
        QTextBrowser *tb=new QTextBrowser(this);
        tb->setFixedSize(QSize(width(),height()));
        tb->setStyleSheet("border-radius:0px;");
        tb->setEnabled(false);
        tb->show();
        for(int rcnt=0;rcnt<curlist[cnt].list.size();rcnt++){
            switch(curlist[cnt].list[rcnt].type){
            case TextBlock:{
                QTextBrowser *tb=new QTextBrowser(this);
                tb->setStyleSheet("border-radius:0px;");
                tb->setGeometry(curlist[cnt].list[rcnt].contents[0].toRect().x(),
                        curlist[cnt].list[rcnt].contents[0].toRect().y(),
                        curlist[cnt].list[rcnt].contents[1].toRect().x(),
                        curlist[cnt].list[rcnt].contents[1].toRect().y());
                tb->setText(curlist[cnt].list[rcnt].contents[2].toText());
                tb->setEnabled(false);
                tb->show();
                break;
            }
            case Rectangle:{

                break;
            }
            case Ellipse:{

                break;
            }
            case Picture:{
                //TODO: add code
                break;
            }
            }
        }
        while(!next)
            QApplication::processEvents();
    }
    QTextBrowser *tb=new QTextBrowser(this);
    tb->setStyleSheet("border-radius:0px;background-color:black;color:white;");
    tb->setFixedSize(QSize(width(),height()));
    tb->setHtml("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
                "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
                "p, li { white-space: pre-wrap; }"
                "</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">"
                "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Source Code Pro'; font-size:14pt;\">Press To Exit Presentation</span></p></body></html>");
    tb->setEnabled(false);
    tb->show();
    next=false;
    while(!next)
        QApplication::processEvents();
    showNormal();
    close();
}
