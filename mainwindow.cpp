#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mrichtextedit.h"
#include <QStyle>
#include <QColor>
#include <QLineEdit>
#include <QTextEdit>
#include <QDebug>
#include <QFileDialog>
#include <QTextBrowser>
static int numpage,curpage;
static bool maxed=false,refresh=false;
static QString filedir;
static TeaType curtype;
static TeaObj curobj;    //stores the object being added
static QList<TeaObjPage> objlist;  //here we store all the document's info

void MainWindow::displayForm(TeaType type){
    curobj.empty(); //empty current object
    while(ui->formLayout->rowCount())
        ui->formLayout->removeRow(ui->formLayout->rowCount()-1);
    switch(type){
    case TextBlock:{
        curobj.type=TextBlock;
        curobj.title.append("Position");
        curobj.title.append("Size");
        curobj.title.append("RichText");
        curobj.contents.append(TeaObjCont::fromText(""));
        curobj.contents.append(TeaObjCont::fromText(""));
        curobj.contents.append(TeaObjCont::fromText(""));
        QLabel *lab=new QLabel,*lab_1=new QLabel,*lab_2=new QLabel;
        QLineEdit *lineEdit=new QLineEdit,*lineEdit_2=new QLineEdit;
        QPushButton *textEdit=new QPushButton;
        lab->setText("Position:");
        lab->setStyleSheet("font:20px \"Source Code Pro\";");
        lab_1->setText("Size:");
        lab_1->setStyleSheet("font:20px \"Source Code Pro\";");
        lab_2->setText("Richtext:");
        lab_2->setStyleSheet("font:20px \"Source Code Pro\";");
        lineEdit->setPlaceholderText("Input X Y");
        lineEdit->setStyleSheet("QLineEdit{border-radius:0px;font:20px \"Source Code Pro\";border:1px solid #009265;}QLineEdit:hover{background-color:#98CBBB}");
        lineEdit_2->setPlaceholderText("Input X Y");
        lineEdit_2->setStyleSheet("QLineEdit{border-radius:0px;font:20px \"Source Code Pro\";border:1px solid #009265;}QLineEdit:hover{background-color:#98CBBB}");
        textEdit->setText("Input Rich Text");
        textEdit->setStyleSheet("QPushButton{border-radius:0px;font:20px \"Source Code Pro\";border:1px solid #009265;}QPushButton:hover{background-color:#98CBBB}");
        ui->formLayout->addRow(lab,lineEdit);
        ui->formLayout->addRow(lab_1,lineEdit_2);
        ui->formLayout->addRow(lab_2,textEdit);
        connect(lineEdit,SIGNAL(textChanged(QString)),this,SLOT(writeObjCont1(QString)));
        connect(lineEdit_2,SIGNAL(textChanged(QString)),this,SLOT(writeObjCont2(QString)));
        connect(textEdit,SIGNAL(clicked()),this,SLOT(editRichText()));
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
    curtype=type;
}

void MainWindow::refreshCont(){
    refresh=true;
    ui->treeWidget->clear();
    for(int cnt=0;cnt<objlist.count();cnt++){
        QTreeWidgetItem *newItem=new QTreeWidgetItem,*newItem_2=new QTreeWidgetItem;
        newItem->setText(0,objlist[cnt].title);
        newItem->setFlags(Qt::ItemIsEnabled|Qt::ItemIsEditable);
        for(int rcnt=0;rcnt<objlist[cnt].list.count();rcnt++){
            newItem_2=new QTreeWidgetItem;
            newItem_2->setText(0,getTeaObjName(objlist[cnt].list[rcnt].type));
            newItem->addChild(newItem_2);
            for(int rrcnt=0;rrcnt<objlist[cnt].list[rcnt].title.count();rrcnt++){
                QTreeWidgetItem *newItem_3=new QTreeWidgetItem;
                QLineEdit *btn=new QLineEdit;
                btn->setStyleSheet("QLineEdit{border-radius:0px;font:20px \"Source Code Pro\";border:1px solid #009265;}QLineEdit:hover{background-color:#98CBBB}");
                btn->setText(objlist[cnt].list[rcnt].contents[rrcnt].toText());
                connect(btn,SIGNAL(textChanged(QString)),this,SLOT(writeObj(QString)));
                newItem_3->setText(0,objlist[cnt].list[rcnt].title[rrcnt]);
                newItem_2->addChild(newItem_3);
                ui->treeWidget->setItemWidget(newItem_3,1,btn);
            }
        }
        ui->treeWidget->addTopLevelItem(newItem);
        ui->treeWidget->expandItem(newItem);
        ui->treeWidget->expandItem(newItem_2);
    }
    refresh=false;
}

void MainWindow::editRichText(){
    MRichTextEdit *r=new MRichTextEdit;
    r->show();
    connect(r,SIGNAL(sendText(QString)),this,SLOT(writeObjCont3(QString)));
}

void MainWindow::writeObj(QString text){
    int cnt=0,rcnt=0,rrcnt=0;
    for(;cnt<ui->treeWidget->topLevelItemCount();cnt++)
        if(ui->treeWidget->currentItem()->parent()->parent()==ui->treeWidget->topLevelItem(cnt))
            break;
    for(;rcnt<ui->treeWidget->itemAt(1,cnt)->childCount();rcnt++)
        if(ui->treeWidget->currentItem()->parent()==ui->treeWidget->itemAt(1,cnt)->child(rcnt))
            break;
    for(;rrcnt<ui->treeWidget->itemAt(1,cnt)->child(rcnt)->childCount();rrcnt++)
        if(ui->treeWidget->currentItem()==ui->treeWidget->itemAt(1,cnt)->child(rcnt)->child(rrcnt))
            objlist[cnt].list[rcnt].contents[rrcnt]=TeaObjCont::fromText(text);
}

void MainWindow::writeObjCont1(QString text){
    curobj.contents[0]=TeaObjCont::fromText(text);
    return;
}

void MainWindow::writeObjCont2(QString text){
    curobj.contents[1]=TeaObjCont::fromText(text);
    return;
}

void MainWindow::writeObjCont3(QString text){
    curobj.contents[2]=TeaObjCont::fromText(text);
    return;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("TeaPres");
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QIcon(":/new/pics/TeaPres.ico"));
    ui->pushButton->setIcon(QApplication::style()->standardIcon((QStyle::StandardPixmap)1));
    ui->pushButton_2->setIcon(QApplication::style()->standardIcon((QStyle::StandardPixmap)4));
    ui->pushButton_3->setIcon(QApplication::style()->standardIcon((QStyle::StandardPixmap)3));
    numpage=0;
    TeaObjPage page;
    page.title="Page_0";
    objlist.append(page);
    refreshCont();
    ui->treeWidget->setColumnWidth(0,400);
    displayForm(TextBlock);
    showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    showMinimized();
}

void MainWindow::on_pushButton_2_clicked()
{
    if(maxed){
        showNormal();
        maxed=false;
    }
    else{
        showMaximized();
        maxed=true;
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QApplication::quit();
}

void MainWindow::on_pushButton_11_clicked()
{
    objlist[curpage].appendObj(curobj);
    refreshCont();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch(index){
    case 0:displayForm(TextBlock);break;
    case 1:displayForm(Rectangle);break;
    case 2:displayForm(Ellipse);break;
    case 3:displayForm(Picture);break;
    }
}

bool MainWindow::isTopLevel(QTreeWidgetItem *item){
    for(int cnt=0;cnt<ui->treeWidget->topLevelItemCount();cnt++)
        if(item==ui->treeWidget->topLevelItem(cnt))
            return true;
    return false;
}

void MainWindow::on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if(ui->treeWidget->currentColumn()||!isTopLevel(current))
        return;
    for(int cnt=0;cnt<ui->treeWidget->topLevelItemCount();cnt++)
        if(current==ui->treeWidget->topLevelItem(cnt))
            curpage=cnt;
    ui->label_2->setText("Add Object(Current Page:"+current->text(0)+"):");
}

void MainWindow::on_pushButton_9_clicked()
{
    if(filedir=="")
        filedir=QFileDialog::getSaveFileName(this,"Open File","","TeaPres Presentations (*.abp)");
    ui->label_4->setText(filedir);
    QFileInfo info(filedir);
    ui->label_3->setText(info.fileName());
    QFile f(filedir);
    f.open(QIODevice::WriteOnly|QIODevice::Truncate);
    QTextStream out(&f);
    for(int cnt=0;cnt<objlist.count();cnt++){
        out<<objlist[cnt].title<<"\n";
        for(int rcnt=0;rcnt<objlist[cnt].list.count();rcnt++){
            out<<getTeaObjName(objlist[cnt].list[rcnt].type)<<"\n";
            for(int rrcnt=0;rrcnt<objlist[cnt].list[rcnt].title.count();rrcnt++){
                out<<objlist[cnt].list[rcnt].title[rrcnt]<<":";
                QString tmp=objlist[cnt].list[rcnt].contents[rrcnt].toText();
                if(objlist[cnt].list[rcnt].title[rrcnt]=="RichText"){
                    for(int ncnt=0;ncnt<tmp.size();ncnt++)
                        if(tmp[ncnt]=='\n')
                            tmp.remove(ncnt,1);
                    tmp+="\n%end";
                }
                out<<tmp<<"\n";
            }
            out<<"%end\n";
        }
        out<<"%end\n";
    }
    f.close();
}

void MainWindow::on_pushButton_12_clicked()
{
    numpage++;
    TeaObjPage page;
    page.title="Page_"+QString::number(numpage);
    objlist.append(page);
    refreshCont();
}

void MainWindow::on_pushButton_6_clicked()
{
    if(isTopLevel(ui->treeWidget->currentItem())){
        for(int cnt=0;cnt<ui->treeWidget->topLevelItemCount();cnt++)
            if(ui->treeWidget->currentItem()==ui->treeWidget->topLevelItem(cnt))
                objlist.takeAt(cnt);
    }
    else if(isTopLevel(ui->treeWidget->currentItem()->parent())){
        int cnt=0;
        for(;cnt<ui->treeWidget->topLevelItemCount();cnt++)
            if(ui->treeWidget->currentItem()->parent()==ui->treeWidget->topLevelItem(cnt))
                break;
        for(int rcnt=0;rcnt<ui->treeWidget->currentItem()->parent()->childCount();rcnt++)
            if(ui->treeWidget->currentItem()==ui->treeWidget->currentItem()->parent()->child(rcnt))
                objlist[cnt].list.takeAt(rcnt);
    }
    else return;
    refreshCont();
}

void MainWindow::on_pushButton_4_clicked()
{
    if(isTopLevel(ui->treeWidget->currentItem()))
        objlist.move(curpage,curpage-1);
    int cnt=0;
    bool foundtop=false;
    for(;cnt<ui->treeWidget->topLevelItemCount();cnt++)
        if(ui->treeWidget->currentItem()->parent()==ui->treeWidget->topLevelItem(cnt)){
            foundtop=true;
            break;
        }
    if(foundtop)
        for(int rcnt=0;rcnt<ui->treeWidget->currentItem()->parent()->childCount();rcnt++)
            if(ui->treeWidget->currentItem()==ui->treeWidget->currentItem()->parent()->child(rcnt))
                objlist[cnt].list.move(rcnt,rcnt-1);
    qDebug()<<1;
    refreshCont();
}

void MainWindow::on_pushButton_5_clicked()
{
    if(isTopLevel(ui->treeWidget->currentItem()))
        objlist.move(curpage,curpage+1);
    int cnt=0;
    bool foundtop=false;
    for(;cnt<ui->treeWidget->topLevelItemCount();cnt++)
        if(ui->treeWidget->currentItem()->parent()==ui->treeWidget->topLevelItem(cnt)){
            foundtop=true;
            break;
        }
    if(foundtop)
        for(int rcnt=0;rcnt<ui->treeWidget->currentItem()->parent()->childCount();rcnt++)
            if(ui->treeWidget->currentItem()==ui->treeWidget->currentItem()->parent()->child(rcnt))
                objlist[cnt].list.move(rcnt,rcnt+1);
    qDebug()<<1;
    refreshCont();
}

void MainWindow::on_pushButton_8_clicked()
{
    QString tmp=QFileDialog::getOpenFileName(this,"Open File","","TeaPres Presentations (*.abp)");
    if(tmp=="")
        return;
    filedir=tmp;
    ui->label_4->setText(filedir);
    QFileInfo info(filedir);
    ui->label_3->setText(info.fileName());
    objlist.clear();
    QFile f(filedir);
    f.open(QIODevice::ReadOnly);
    QTextStream in(&f);
    while(!in.atEnd()){
        QString str=in.readLine();
        TeaObjPage page;
        page.title=str;
        bool finish=false;
        while(!finish){
            TeaObj obj;
            QString rstr=in.readLine();
            obj.type=fromTeaObjName(rstr);
            bool rfinish=false;
            while(!rfinish){
                QString rrstr=in.readLine(),title,value;
                int cnt=0;
                if(rrstr=="%end"){
                    rfinish=true;
                    continue;
                }
                for(;cnt<rrstr.size();cnt++){
                    if(rrstr[cnt]==':')
                        break;
                    title+=rrstr[cnt];
                }
                cnt++;
                for(;cnt<rrstr.size();cnt++)
                    value+=rrstr[cnt];
                obj.title.append(title);
                TeaObjCont cont=TeaObjCont::fromText(value);
                obj.contents.append(cont);
            }
            if(rstr=="%end"){
                finish=true;
                continue;
            }
            page.list.append(obj);
        }
        if(str=="%end")
            continue;
        objlist.append(page);
    }
    f.close();
    refreshCont();
}

void MainWindow::on_pushButton_10_clicked()
{
    objlist.clear();
    refreshCont();
    ui->label_3->setText("Untitled");
    ui->label_4->setText("<Untitled>");
    filedir="";
}

void MainWindow::on_pushButton_13_clicked()
{
    Display d;
    d.show();
    connect(this,SIGNAL(sendObj(QList<TeaObjPage>)),&d,SLOT(getObj(QList<TeaObjPage>)));
    emit sendObj(objlist);
    d.exec();
}

void MainWindow::on_pushButton_14_clicked()
{
    filedir=QFileDialog::getSaveFileName(this,"Open File","","TeaPres Presentations (*.abp)");
    ui->label_4->setText(filedir);
    QFileInfo info(filedir);
    ui->label_3->setText(info.fileName());
    QFile f(filedir);
    f.open(QIODevice::WriteOnly|QIODevice::Truncate);
    QTextStream out(&f);
    for(int cnt=0;cnt<objlist.count();cnt++){
        out<<objlist[cnt].title<<"\n";
        for(int rcnt=0;rcnt<objlist[cnt].list.count();rcnt++){
            out<<getTeaObjName(objlist[cnt].list[rcnt].type)<<"\n";
            for(int rrcnt=0;rrcnt<objlist[cnt].list[rcnt].title.count();rrcnt++){
                out<<objlist[cnt].list[rcnt].title[rrcnt]<<":";
                QString tmp=objlist[cnt].list[rcnt].contents[rrcnt].toText();
                if(objlist[cnt].list[rcnt].title[rrcnt]=="RichText"){
                    for(int ncnt=0;ncnt<tmp.size();ncnt++)
                        if(tmp[ncnt]=='\n')
                            tmp.remove(ncnt,1);
                    tmp+="\n%end";
                }
                out<<tmp<<"\n";
            }
            out<<"%end\n";
        }
        out<<"%end\n";
    }
    f.close();
}

void MainWindow::on_pushButton_7_clicked()
{
    QTextBrowser *tb=new QTextBrowser;
    tb->setStyleSheet("border-radius:0px;");
    tb->setFixedSize(QSize(width(),height()));
    tb->setHtml("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
                                       "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
                                       "p, li { white-space: pre-wrap; }\n"
                                       "</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
                                       "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:14pt; font-weight:600;\">About TeaPres</span></p>\n"
                                       "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:14pt;\">TeaPres is developed by Baboon Software</span></p>\n"
                                       "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:14pt;\">(C)2022-2023 Baboon Software</span></p>\n"
                                       "<p "
                                                               "style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans Serif'; font-size:14pt;\"><br /></p>\n"
                                       "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:14pt;\">Libaries:</span></p>\n"
                                       "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:14pt;\">Qt 5.13.1</span></p>\n"
                                       "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:14pt;\">(C)Qt Company Ltd.</span></p>\n"
                                       "<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans Serif'; font-size:14pt;\"><br /></p>\n"
                                       ""
                                                               "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:14pt;\">MRichTextEditor</span></p>\n"
                                       "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:14pt;\">(C)</span><span style=\" font-family:'Sans Serif'; font-size:14pt; color:#000000;\">Ji\305\231\303\255 Proch\303\241zka (Hobrasoft)</span></p>\n"
                                       "<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans Serif'; font-size:14pt; font-style:italic; color:#000000;\"><br /></p>\n"
                                       "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:14pt; font-style:italic; color:#000000;\">This work is licensed under GNU AGPL"
                                                               " 3.0</span></p>\n"
                                       "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:14pt; font-style:italic; color:#000000;\">Visit </span><a href=\"https://www.gnu.org/licenses/agpl-3.0.html\"><span style=\" font-family:'Sans Serif'; font-size:14pt; text-decoration: underline; color:#000000;\">AGPL 3.0</span></a></p></body></html>");
    tb->setEnabled(false);
    tb->show();
}
