#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QBrush>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void moved(int x,int y, int r);
protected:
    void paintEvent(QPaintEvent *event);

    //
    virtual void mouseMoveEvent(QMouseEvent *event) override;

    //

private:
    Ui::MainWindow *ui;
    int x,y,r;
    QColor c;
    Qt::BrushStyle bStyle;
    int width;
};
#endif // MAINWINDOW_H
