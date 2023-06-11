#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPainter>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QPushButton *button;
    ~MainWindow();

private slots:
    void buttonClicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
