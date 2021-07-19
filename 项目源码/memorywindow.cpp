#include "memorywindow.h"
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QPoint>

MemoryWindow::MemoryWindow(QWidget *parent) : QWidget(parent) {}

void MemoryWindow::deleteLabel() {
  for (int i = 0; i < JobList.size(); i++) {
    delete JobList.at(i);
  }
  JobList.clear();
}

void MemoryWindow::change() {
  deleteLabel();
  for (int i = 0; i < paintList->size(); i++) {
    if (paintList->at(i).name != "空闲") {
      QLabel *label = new QLabel(this);
      label->setGeometry(
          paintList->at(i).start + paintList->at(i).size / 2 - 20, 25, 40, 20);

      label->setStyleSheet("background:transparent");
      label->setAutoFillBackground(false);
      label->setText(paintList->at(i).name);
      label->adjustSize();
      label->setVisible(true);
      JobList.append(label);
    }
  }
  update();
}

void MemoryWindow::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  //绘图前准备画笔、画刷
  QPen pen; //画笔。绘制图形边线，由颜色、宽度、线风格等参数组成
  pen.setColor(QColor(10, 10, 10));
  QBrush brush; //画刷。填充几何图形的调色板，由颜色和填充风格组成
  brush.setStyle(Qt::SolidPattern);
  QPainter painter(
      this); //可在QPaintDevice上绘制各种图形。QPaintDevice有之类QWidget、QImage、QOpenGLPaintDevice等
  painter.setPen(pen);
  for (int i = 0; i < paintList->size(); i++) {
    if (paintList->at(i).name != "空闲") {
      QColor color = paintList->at(i).color;
      brush.setColor(color);
      painter.setBrush(brush);
      painter.drawRect(paintList->at(i).start, 0, paintList->at(i).size, 98);
    }
  }
}
