#ifndef MEMORYWINDOW_H
#define MEMORYWINDOW_H
#include "memorypartition.h"
#include <QLabel>
#include <QList>
#include <QWidget>

class MemoryWindow : public QWidget {
  Q_OBJECT
public:
  explicit MemoryWindow(QWidget *parent = nullptr);
  //构造函数
  void deleteLabel();
  //删除窗口上的名称
  QList<MemoryPartition> *paintList;
  //分区列表

private slots:
  void change();
  //更新窗口状态

protected:
  void paintEvent(QPaintEvent *event);
  //绘制分区

private:
  QList<QLabel *> JobList; //作业名称列表
  int flag = 0;            //是否要更新窗口
};

#endif // MEMORYWINDOW_H
