#include "settingdialog.h"
#include "ui_settingdialog.h"
#include <QColorDialog>
SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    ui->combofill->addItem("实心",static_cast<int>(Qt::SolidPattern));
    ui->combofill->addItem("水平线",static_cast<int>(Qt::HorPattern));
    ui->combofill->addItem("交叉网络",static_cast<int>(Qt::CrossPattern));
    ui->combofill->addItem("无填充",static_cast<int>(Qt::NoBrush));
//Qt::NoBrush Qt::SolidPattern Qt::HorPattern Qt::CrossPattern


    m_color=Qt::blue;

    connect(ui->btnPen,&QPushButton::clicked,this,[this](){
        QColor  temp=QColorDialog::getColor(m_color,this,"请选择颜色");
        m_color=temp;
    });

    connect(ui->btnOk,&QPushButton::clicked,this,[this]
    {
        int x=ui->EditX->text().toInt();
        int y=ui->EditY->text().toInt();
        int r=ui->EditR->text().toInt();
        Qt::BrushStyle fillStyle=static_cast<Qt::BrushStyle>(ui->combofill->currentData().toInt());
        emit sendData(x,y,r,m_color,fillStyle,ui->spinWidth->value());//发送sendData信号并将读入的数据传入sendData函数当中
        accept();               //关闭当前对话框
    });

}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::initialize(int x,int y,int r,QColor c,Qt::BrushStyle bs,int w)
{
    ui->EditX->setText(QString::number(x));
    ui->EditY->setText(QString::number(y));
    ui->EditR->setText(QString::number(r));
    m_color = c;
    ui->combofill->setCurrentIndex(ui->combofill->findData(static_cast<int>(bs)));
    ui->spinWidth->setValue(w);
}
