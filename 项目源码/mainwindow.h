#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "memorypartition.h"
#include "memorywindow.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QStandardItemModel>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr); //构造函数
  void init();                           //初始化并给表设置模型
  void displayJob();                     //显示作业需求表表头
  void displayIdleMemory();              //显示空闲分区表表头
  void displayAllMemory();               //显示所有分区表表头
  void displayMemoryData(); //显示空闲分区表与所有分区表数据
  void processingWaiting(int method); //处理未分配的作业
  void firstAdaptation();             //首次适应算法
  void bestAdaptation();              //最佳适应算法
  bool checkJob();                    //检查作业输入是否正确
  void addRecord(int start, int isPutIn, int waitJob = 0); //添加日志记录
  ~MainWindow();                                           //析构函数

private slots:
  void on_pushButton_clicked();
  //进行下一个分配
  void on_horizontalSlider_valueChanged(int value);
  //调整内存大小
  void on_pushButton_4_clicked();
  //向需求表中插入作业
  void on_pushButton_3_clicked();
  //开始分配
  void on_pushButton_2_clicked();
  //结束分配，并初始化系统
  void on_pushButton_5_clicked();
  //导入默认请求序列
  void on_pushButton_6_clicked();
  //清空作业需求表
  void on_pushButton_7_clicked();
  //删除作业表中某一行数据
signals:
  void paintJob();
  //内存窗口绘制信号

private:
  bool isNumber(QString str);
  //字符串是否为纯数字
  int current = 0;         //当前作业序号
  Ui::MainWindow *ui;      // ui界面
  MemoryWindow *memWindow; //内存分区显示窗口
  QStandardItemModel *JobModel = new QStandardItemModel(0, 4); //作业需求表
  QStandardItemModel *RecordModel = new QStandardItemModel(this); //日志记录表
  QStandardItemModel *IdleMemoryModel =
      new QStandardItemModel(0, 4); //空闲分区表
  QStandardItemModel *AllMemoryModel =
      new QStandardItemModel(0, 4);  //所有分区表
  QList<MemoryPartition> MemoryList; //内存分区序列
  QList<int> WaitingList;            //未分配序列
};
#endif // MAINWINDOW_H
