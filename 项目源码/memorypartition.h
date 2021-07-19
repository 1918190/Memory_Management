#ifndef MEMORYPARTITION_H
#define MEMORYPARTITION_H

#include <QColor>
#include <QRandomGenerator>
#include <QString>

class MemoryPartition {
public:
  MemoryPartition();
  //构造函数
  QString name = "空闲"; //分区名称
  int start;             //分区开始位置
  int end;               //分区结束位置
  int size;              //分区大小
  QColor color =
      QColor::fromRgb(QRandomGenerator::global()->bounded(128, 255),
                      QRandomGenerator::global()->bounded(128, 255),
                      QRandomGenerator::global()->bounded(128, 255)); //分区颜色
};

#endif // MEMORYPARTITION_H
