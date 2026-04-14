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

    // 【关键】让 centralwidget 对鼠标事件透明，事件直接传递给 MainWindow
    ui->centralwidget->setAttribute(Qt::WA_TransparentForMouseEvents);
    // 可选：开启鼠标跟踪，便于调试（不影响拖拽）
    setMouseTracking(true);

    x = 200; y = 200; r = 100; c = Qt::blue;
    bStyle=Qt::NoBrush;

    width=1;
    connect(ui->actOpen, &QAction::triggered, this, [this](){
        SettingDialog *dlg = new SettingDialog(this);

        connect(this,&MainWindow::moved,dlg,&SettingDialog::initialize);
        dlg->initialize(x, y, r);
        dlg->show();
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
    QPainter p(this);
    QPen pen(c,width);
    p.setPen(pen);
    p.setBrush(QBrush(c,bStyle));
    p.drawEllipse(x - r, y - r, 2 * r, 2 * r);
}


void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        x=event->pos().x();
        y=event->pos().y();
        emit moved(x,y,r);
        update();
    }

}

