#include "ui_canvas.h"
#include "canvas.h"
#include "scanline.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtDebug>
#include <cmath>
#include <ctime>
#include <set>
#include <algorithm>

Canvas::Canvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Canvas)
{
    ui->setupUi(this);
    type = 0;
    num = 0;
    centerX = 0;
    centerY = 0;
    unit = 4;
    tran = false;
}

Canvas::~Canvas()
{
    delete ui;
}

void Canvas::setBar(QStatusBar *bar)
{
    statusbar = bar;
}

void Canvas::setType(int t)
{
    statusbar->clearMessage();
    statusbar->showMessage(QString("绘制中 。。。"));
    type = t;
    this->update();
}

void Canvas::setNum(int n)
{
    num = n;
    s.clear();
    if(num < 1) return;
    if(num > 10) num = 10;
    srand(clock());
    for(int i = 0;i < num;i++)
    {
        s.insert(rand()%(360/num)+360*i/num);
    }
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // 灰色背景
    painter.fillRect(0, 0, width(), height(), QColor("#31363b"));

    // 绘制表格
    painter.setPen(Qt::black);
    int i, j;
    for(i = 0;i <= height();i+=unit)
        painter.drawLine(0, i+centerY%unit, width(), i+centerY%unit);
    for(j = 0;j <= width();j+=unit)
        painter.drawLine(j+centerX%unit, 0, j+centerX%unit, height());

    // 绘制坐标轴
    painter.setPen(Qt::white);
    painter.drawLine(0, i/2+centerY+(i/unit%2==0?unit/2:0), width(), i/2+centerY+(i/unit%2==0?unit/2:0));
    painter.drawLine(j/2+centerX+(j/unit%2==0?unit/2:0), 0, j/2+centerX+(j/unit%2==0?unit/2:0), height());
    painter.translate(j/2+centerX-(j/unit%2==0?0:unit/2), i/2+centerY+(i/unit%2==0?unit:unit/2));
    painter.scale(unit, -unit);

    Polygon newpolygon;
    int r;
    std::set<int, std::less<int> >::iterator it;
    // 根据选项绘图
    switch(type)
    {
    // 五角星
    case 1:
        r = 50;
        newpolygon.addPoint(0, r);
        newpolygon.addPoint(sin(18.0*acos(-1)/180)*r/tan(54.0*acos(-1)/180), sin(18.0*acos(-1)/180)*r);
        newpolygon.addPoint(cos(18.0*acos(-1)/180)*r, sin(18.0*acos(-1)/180)*r);
        newpolygon.addPoint(sin(18.0*acos(-1)/180)*cos(18.0*acos(-1)/180)*r/sin(54.0*acos(-1)/180), -sin(18.0*acos(-1)/180)*sin(18.0*acos(-1)/180)*r/sin(54.0*acos(-1)/180));
        newpolygon.addPoint(cos(54.0*acos(-1)/180)*r, -sin(54.0*acos(-1)/180)*r);
        newpolygon.addPoint(0, -sin(18.0*acos(-1)/180)*r/sin(54.0*acos(-1)/180));
        newpolygon.addPoint(-cos(54.0*acos(-1)/180)*r, -sin(54.0*acos(-1)/180)*r);
        newpolygon.addPoint(-sin(18.0*acos(-1)/180)*cos(18.0*acos(-1)/180)*r/sin(54.0*acos(-1)/180), -sin(18.0*acos(-1)/180)*sin(18.0*acos(-1)/180)*r/sin(54.0*acos(-1)/180));
        newpolygon.addPoint(-cos(18.0*acos(-1)/180)*r, sin(18.0*acos(-1)/180)*r);
        newpolygon.addPoint(-sin(18.0*acos(-1)/180)*r/tan(54.0*acos(-1)/180), sin(18.0*acos(-1)/180)*r);
        newpolygon.paint(&painter);
        break;
    // 三角形
    case 2:
        r = 50;
        newpolygon.addPoint(0, cos(30.0*acos(-1)/180)*2*r/3);
        newpolygon.addPoint(0.5*r, -cos(30.0*acos(-1)/180)*r/3);
        newpolygon.addPoint(-0.5*r, -cos(30.0*acos(-1)/180)*r/3);
        newpolygon.paint(&painter);
        break;
    // 六芒星
    case 3:
        r = 50;
        newpolygon.addPoint(0, cos(30.0*acos(-1)/180)*2*r/3);
        newpolygon.addPoint(1.0*r/6, cos(30.0*acos(-1)/180)*r/3);
        newpolygon.addPoint(0.5*r, cos(30.0*acos(-1)/180)*r/3);
        newpolygon.addPoint(1.0*r/3, 0);
        newpolygon.addPoint(0.5*r, -cos(30.0*acos(-1)/180)*r/3);
        newpolygon.addPoint(1.0*r/6, -cos(30.0*acos(-1)/180)*r/3);
        newpolygon.addPoint(0, -cos(30.0*acos(-1)/180)*2*r/3);
        newpolygon.addPoint(-1.0*r/6, -cos(30.0*acos(-1)/180)*r/3);
        newpolygon.addPoint(-0.5*r, -cos(30.0*acos(-1)/180)*r/3);
        newpolygon.addPoint(-1.0*r/3, 0);
        newpolygon.addPoint(-0.5*r, cos(30.0*acos(-1)/180)*r/3);
        newpolygon.addPoint(-1.0*r/6, cos(30.0*acos(-1)/180)*r/3);
        newpolygon.paint(&painter);
        break;
    // 箭头
    case 4:
        newpolygon.addPoint(-50, 0);
        newpolygon.addPoint(-30, 20);
        newpolygon.addPoint(-30, 5);
        newpolygon.addPoint(50, 5);
        newpolygon.addPoint(50, -5);
        newpolygon.addPoint(-30, -5);
        newpolygon.addPoint(-30, -20);
        newpolygon.paint(&painter);
        break;
    // 随机生成
    case 5:
        r = 50;
        if(num < 1) break;
        for(it = s.begin();it != s.end();it++)
        {
            newpolygon.addPoint(cos(*it*acos(-1)/180)*r, sin(*it*acos(-1)/180)*r);
        }
        newpolygon.paint(&painter);
        break;
    default:
        type = 0;
    }
    painter.end();

    if(type != 0)
    {
        statusbar->clearMessage();
        statusbar->showMessage(QString("绘制结束。"));
    }
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        oriX = event->pos().x();
        oriY = event->pos().y();
        tran = true;
    }
    else if(event->button() == Qt::RightButton)
    {
        type = 0;
        centerX = 0;
        centerY = 0;
        unit = 4;
        tran = false;
        this->update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        tran = false;
        this->update();
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if(tran)
    {
        nowX = event->pos().x();
        nowY = event->pos().y();
        if(abs(centerX + nowX-oriX) <= (unit-1)*(250))
            centerX += nowX-oriX;
        if(abs(centerY + nowY-oriY) <= (unit-1)*(250))
            centerY += nowY-oriY;
        oriX = event->pos().x();
        oriY = event->pos().y();
        this->update();
    }
}

void Canvas::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0&&unit < 16)
    {
        unit += 1;
    }
    else if(event->delta() < 0&&unit > 1)
    {
        unit -= 1;
    }
    centerX = qMax(centerX, -(unit-1)*(250));
    centerX = qMin(centerX, (unit-1)*(250));
    centerY = qMax(centerY, -(unit-1)*(250));
    centerY = qMin(centerY, (unit-1)*(250));
    this->update();
}
