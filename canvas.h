#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QStatusBar>
#include <set>

namespace Ui {
class Canvas;
}

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();

    // 设定主程序状态栏
    void setBar(QStatusBar *bar);
    // 设定绘图方式
    void setType(int t);
    // 设定随机生成顶点数
    void setNum(int n);

private:
    Ui::Canvas *ui;
    QStatusBar *statusbar;
    // 用于计算鼠标拖动时的偏移量
    int oriX, oriY, nowX, nowY, centerX, centerY;
    // 单元格大小
    int unit;
    // 鼠标拖动中
    bool tran;
    // 绘图方式
    int type;
    // 随机生成顶点数
    int num;
    // 随机生成的顶点位置
    std::set<int, std::less<int> > s;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
};

#endif // CANVAS_H
