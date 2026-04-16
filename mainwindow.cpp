#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QDebug>
#include "settingdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(1600, 1000);

    //initialize初始化对象
    x = 200;
    y = 200;
    r = 100;
    c = Qt::blue;
    bStyle=Qt::SolidPattern;
    width=1;

    //修改按钮的信号与槽函数
    connect(ui->actOpen, &QAction::triggered, this, [this](){
        SettingDialog *dlg = new SettingDialog(this);

        //当想要将画笔颜色以及画刷格式的设置保存在对话框里时下面的代码是多余的
        //connect(this,&MainWindow::moved,dlg,&SettingDialog::initialize);

        dlg->initialize(x, y, r,c,bStyle,width);
        dlg->show();
        //获取文本框里的数据，并赋值给对象
        connect(dlg, &SettingDialog::sendData, this, [this](int newX, int newY, int newR, QColor co,Qt::BrushStyle newBrush,int newW){
            x = newX; y = newY; r = newR; c = co;
            bStyle=newBrush;
            width=newW;
           // update();
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    //设置画笔与画刷以及画圆
    QPainter p(this);
    QPen pen(c,width);
    p.setPen(pen);
    p.setBrush(QBrush(c,bStyle));
    p.drawEllipse(x - r, y - r, 2 * r, 2 * r);
}


void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //获取
    if(event->buttons()&Qt::LeftButton)
    {
        x=event->pos().x();
        y=event->pos().y();
        emit moved(x,y,r);
        update();
    }
}

