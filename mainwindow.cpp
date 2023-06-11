#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPainter"
#include "QPixmap"
#include "cmath"
#include "poland.h"
#include "QPainterPath"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    resize(800, 600);
    QPushButton* button = new QPushButton(this);
    (*button).setGeometry(width()*0.85, height()*0.017, 0.12*width(), 0.06*height());//размер в процентах
    (*button).setText("Draw");
    connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
    ui->lineEdit->setGeometry(width() - width()*18.5/20, height()*0.017, 0.4*width(), 0.06*height());
    ui->label->setGeometry(width() - width()*18.5/20, height() - height()*18/20, width()*15/20, height()*16/20);
}


void MainWindow::buttonClicked() {
    QPixmap pm(width()*15/20, height()*16/20);
    QPainter painter;
    QPen pencil;
    QPainterPath path;
    painter.begin(&pm);
    pm.fill(0xdae3ff);

    QString func = ui->lineEdit->text();
    if (func == "") {
        ui->label->setPixmap(pm);
        return;
    }
    double xmin = -3.14*2;
    double xmax = 3.14*2;
    double ymin = -3.14*2, ymax = 3.14*2;
    int xgmin = 0;
    int xgmax = pm.width();
    int ygmin = 0;
    int ygmax = pm.height();
    double kx = (xgmax - xgmin) / (xmax - xmin);
    double ky = (ygmin - ygmax) / (ymax - ymin);
    double x0 = xgmin - kx * xmin;
    double y0 = ygmin - ky * ymax;
    double x, y;
    int xg = 0, yg = 0;
    x = xmin;
    double stepx = (xmax - xmin) / (xgmax - xgmin);
    double ans = 0;
    QString temp = func;
    pencil.setColor(0x9900cc);
    painter.setPen(pencil);
    temp.replace("x", "(" + QString::number(x) + ")");
    int prr = solve(temp.toUtf8().constData(), ans);
    path.moveTo(x, ans);

    while (x <= xmax) {
        QString sss = func;
        sss.replace("x", "(" + QString::number(x) + ")");
        int prr = solve(sss.toUtf8().constData(), ans);
        y = ans;
        xg = x0 + kx * x;
        yg = y0 + ky * y;
        path.lineTo(xg, yg);
        painter.drawPath(path);
        x += stepx;
    }
    pencil.setColor(0x7b0631);
    pencil.setWidth(1);
    painter.setPen(pencil);
    painter.drawLine(0, y0, pm.width(), y0);
    painter.drawLine(x0, 0, x0, pm.height());
    ui->label->setPixmap(pm);
}

MainWindow::~MainWindow()
{
    delete ui;
}
