#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include<QColor>
#include<QBrush>
namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = nullptr);
    ~SettingDialog();
    void initialize(int x,int y,int r);

signals:
    void sendData(int x,int y,int r,QColor color,Qt::BrushStyle fillStyle,int w);

private:
    Ui::SettingDialog *ui;
    QColor m_color;
};

#endif // SETTINGDIALOG_H
