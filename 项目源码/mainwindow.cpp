#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#define INF 2000
#define BESTMETHOD 1
#define FIRSTMETHOD 0
#define REQUIRE -1
#define INIT 0
#define FRONT 1
#define BACK 2
#define BOTH 3
#define YES 1
#define NO 0
#define SUCCESS 1
#define FAILURE 0
#define FRESH 2
#define DEFAULTNUM 11

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowFlags(windowFlags() &
                 ~Qt::WindowMaximizeButtonHint); // 禁止最大化按钮
  setFixedSize(this->width(), this->height());
  this->setWindowTitle("MemoryManager");
  this->setWindowIcon(QIcon(":/image/memory.jpeg"));
  init();
  setStyleSheet(
      //设置滑块显示
      "QSlider::groove:horizontal{"
      "border: 1px solid #bbb;"
      "background: white;"
      "height: 50px;"
      "width:802px;"
      "border-radius: 4px;"
      "}"
      "QSlider::sub-page:horizontal{"
      "border: 1px solid #bbb;"
      "background: rgba(80,166,234,1);"
      "height: 50px;"
      "width:802px;"
      "border-radius: 4px;"
      "}"
      "QSlider::handle:horizontal{"
      "background: qlineargradient(x1:0, y1:0, x2:1, y2:1,  stop:0 #eee, "
      "stop:1 #ccc);"
      "border: 1px solid #777;"
      "border-image: url(:/new/image/image/little door.png);"
      "background: grey;"
      "border-radius:4px;"
      "width: 30px;"
      "height: 30px;"
      "margin-top: -2px;"
      "margin-bottom: -2px;"
      "}");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::init() {
  memWindow = new MemoryWindow(ui->widget);
  memWindow->paintList = &MemoryList;
  ui->widget->setGeometry((this->width() - 640) / 2, 200, 640, 100);
  connect(this, SIGNAL(paintJob()), memWindow, SLOT(change()));
  ui->tableView->setModel(JobModel);
  displayJob();
  ui->tableView_2->setModel(IdleMemoryModel);
  displayIdleMemory();
  ui->tableView_3->setModel(AllMemoryModel);
  displayAllMemory();
  ui->listView->setModel(RecordModel);
}

bool MainWindow::isNumber(QString str) {
  for (int i = 0; i < str.length(); i++) {
    if (str.at(i) < '0' || str.at(i) > '9') {
      return false; //当不是数字字符时返回false
    }
  }
  return true;
}

void MainWindow::displayJob() {
  JobModel->setColumnCount(4);
  JobModel->setRowCount(0);
  JobModel->setHeaderData(0, Qt::Horizontal, QObject::tr("作业名"));
  JobModel->setHeaderData(1, Qt::Horizontal, QObject::tr("大小")); //指定标题行
  JobModel->setHeaderData(2, Qt::Horizontal, QObject::tr("操作"));
  JobModel->setHeaderData(3, Qt::Horizontal, QObject::tr("状态"));
  ui->tableView->setColumnWidth(0, 150); //设置列的宽度
  ui->tableView->setColumnWidth(1, 100);
  ui->tableView->setColumnWidth(2, 100);
  ui->tableView->setColumnWidth(3, 100);
  //设置表格内容不可编辑
  /*ui->tableView->horizontalHeader()->setSectionResizeMode(
       QHeaderView::ResizeToContents);*/
  ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void MainWindow::displayIdleMemory() {
  IdleMemoryModel->setColumnCount(4);
  IdleMemoryModel->setRowCount(0);
  IdleMemoryModel->setHeaderData(0, Qt::Horizontal, QObject::tr("内存块状态"));
  IdleMemoryModel->setHeaderData(1, Qt::Horizontal,
                                 QObject::tr("起始位置")); //指定标题行
  IdleMemoryModel->setHeaderData(2, Qt::Horizontal, QObject::tr("终止位置"));
  IdleMemoryModel->setHeaderData(3, Qt::Horizontal, QObject::tr("大小"));
  ui->tableView_2->setColumnWidth(0, 100); //设置列的宽度
  ui->tableView_2->setColumnWidth(1, 100);
  ui->tableView_2->setColumnWidth(2, 100);
  ui->tableView_2->setColumnWidth(3, 100);
  //设置表格内容不可编辑
  /*ui->tableView_2->horizontalHeader()->setSectionResizeMode(
       QHeaderView::ResizeToContents);*/
  ui->tableView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void MainWindow::displayAllMemory() {
  AllMemoryModel->setColumnCount(4);
  AllMemoryModel->setRowCount(0);
  AllMemoryModel->setHeaderData(0, Qt::Horizontal, QObject::tr("内存块状态"));
  AllMemoryModel->setHeaderData(1, Qt::Horizontal,
                                QObject::tr("起始位置")); //指定标题行
  AllMemoryModel->setHeaderData(2, Qt::Horizontal, QObject::tr("终止位置"));
  AllMemoryModel->setHeaderData(3, Qt::Horizontal, QObject::tr("大小"));
  ui->tableView_3->setColumnWidth(0, 100); //设置列的宽度
  ui->tableView_3->setColumnWidth(1, 100);
  ui->tableView_3->setColumnWidth(2, 100);
  ui->tableView_3->setColumnWidth(3, 100);
  //设置表格内容不可编辑
  /*ui->tableView_3->horizontalHeader()->setSectionResizeMode(
       QHeaderView::ResizeToContents);*/
  ui->tableView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
  ui->tableView_3->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void MainWindow::displayMemoryData() {
  IdleMemoryModel->clear();
  displayIdleMemory();
  AllMemoryModel->clear();
  displayAllMemory();
  for (int i = 0; i < MemoryList.size(); i++) {
    QString name = MemoryList[i].name;
    QString start = QString::number(MemoryList[i].start);
    QString end = QString::number(MemoryList[i].end);
    QString size = QString::number(MemoryList[i].size);
    QStandardItem *first = new QStandardItem(name);
    QStandardItem *second = new QStandardItem(start);
    QStandardItem *third = new QStandardItem(end);
    QStandardItem *fourth = new QStandardItem(size);
    QList<QStandardItem *> data;
    data.append(first);
    data.append(second);
    data.append(third);
    data.append(fourth);
    AllMemoryModel->appendRow(data);
    if (MemoryList[i].name == "空闲") {
      QStandardItem *first = new QStandardItem(name);
      QStandardItem *second = new QStandardItem(start);
      QStandardItem *third = new QStandardItem(end);
      QStandardItem *fourth = new QStandardItem(size);
      QList<QStandardItem *> idleData;
      idleData.append(first);
      idleData.append(second);
      idleData.append(third);
      idleData.append(fourth);
      IdleMemoryModel->appendRow(idleData);
    } else {
      AllMemoryModel->item(i, 0)->setBackground(QBrush(MemoryList[i].color));
    }
  }
}

void MainWindow::processingWaiting(int method) {
  if (method == FIRSTMETHOD) {
    for (int j = 0; j < WaitingList.size(); j++) {
      for (int i = 0; i < MemoryList.size(); i++) {
        if ((MemoryList[i].name == "空闲") &&
            (MemoryList[i].size >=
             JobModel->item(WaitingList[j], 1)->text().toInt())) {
          MemoryPartition temp;
          temp.start = MemoryList[i].start;
          temp.end = temp.start +
                     JobModel->item(WaitingList[j], 1)->text().toInt() - 1;
          temp.name = JobModel->item(WaitingList[j], 0)->text();
          temp.size = temp.end - temp.start + 1;
          MemoryList[i].start = temp.end + 1;
          MemoryList[i].size = MemoryList[i].end - MemoryList[i].start + 1;
          if (MemoryList[i].size == 0) {
            MemoryList.removeAt(i);
          }
          MemoryList.insert(i, temp);
          JobModel->item(WaitingList[j], 3)->setText("已重新分配");
          JobModel->item(WaitingList[j], 3)
              ->setForeground(QBrush(QColor(25, 204, 37)));
          addRecord(temp.start, FRESH, j);
          WaitingList.removeAt(j);
          j--;
          break;
        }
      }
    }
  } else if (method == BESTMETHOD) {
    int merge = REQUIRE;
    int least = INF;
    for (int j = 0; j < WaitingList.size(); j++) {
      for (int i = 0; i < MemoryList.size(); i++) {
        if ((MemoryList[i].name == "空闲") &&
            (MemoryList[i].size >=
             JobModel->item(WaitingList[j], 1)->text().toInt())) {
          if (MemoryList[i].size < least) {
            merge = i;
            least = MemoryList[i].size;
          }
        }
      }
      if (merge != REQUIRE) {
        MemoryPartition temp;
        temp.start = MemoryList[merge].start;
        temp.end =
            temp.start + JobModel->item(WaitingList[j], 1)->text().toInt() - 1;
        temp.name = JobModel->item(WaitingList[j], 0)->text();
        temp.size = temp.end - temp.start + 1;
        MemoryList[merge].start = temp.end + 1;
        MemoryList[merge].size =
            MemoryList[merge].end - MemoryList[merge].start + 1;
        if (MemoryList[merge].size == 0) {
          MemoryList.removeAt(merge);
        }
        MemoryList.insert(merge, temp);
        JobModel->item(WaitingList[j], 3)->setText("已重新分配");
        JobModel->item(WaitingList[j], 3)
            ->setForeground(QBrush(QColor(25, 204, 37)));
        addRecord(temp.start, FRESH, j);
        WaitingList.removeAt(j);
        j--;
      }
    }
  }
}

void MainWindow::firstAdaptation() {
  MemoryPartition temp;
  int merge = INIT;
  int i = 0;
  if (JobModel->item(current, 2)->text() == "申请") {
    for (i = 0; i < MemoryList.size(); i++) {
      if ((MemoryList[i].name == "空闲") &&
          (MemoryList[i].size >= JobModel->item(current, 1)->text().toInt())) {
        temp.start = MemoryList[i].start;
        temp.end = temp.start + JobModel->item(current, 1)->text().toInt() - 1;
        temp.name = JobModel->item(current, 0)->text();
        temp.size = temp.end - temp.start + 1;
        MemoryList[i].start = temp.end + 1;
        MemoryList[i].size = MemoryList[i].end - MemoryList[i].start + 1;
        if (MemoryList[i].size == 0) {
          MemoryList.removeAt(i);
        }
        MemoryList.insert(i, temp);
        merge = REQUIRE;
        JobModel->item(current, 3)->setText("已分配");
        JobModel->item(current, 3)->setForeground(QBrush(QColor(25, 204, 37)));
        addRecord(temp.start, SUCCESS);
        break;
      }
    }
    if (merge != REQUIRE) { //记得判断无法计入的情况
      addRecord(0, FAILURE);
      WaitingList.append(current);
      JobModel->item(current, 3)->setText("未分配");
      JobModel->item(current, 3)->setForeground(Qt::red);
    }
  } else if (JobModel->item(current, 2)->text() == "释放") {
    for (i = 0; i < MemoryList.size(); i++) {
      if (MemoryList[i].name == JobModel->item(current, 0)->text()) {
        addRecord(MemoryList[i].start, SUCCESS);
        JobModel->item(current, 3)->setText("已分配");
        JobModel->item(current, 3)->setForeground(QBrush(QColor(25, 204, 37)));
        if ((i != 0) && MemoryList[i - 1].name == "空闲") {
          merge += 1;
        }
        if ((i != MemoryList.size()) && MemoryList[i + 1].name == "空闲") {
          merge += 2;
        }
        if (merge == INIT) {
          MemoryList[i].name = "空闲";
        } else if (merge == FRONT) {
          MemoryList[i - 1].size += JobModel->item(current, 1)->text().toInt();
          MemoryList[i - 1].end =
              MemoryList[i - 1].start + MemoryList[i - 1].size - 1;
          MemoryList.removeAt(i);
        } else if (merge == BACK) {
          MemoryList[i + 1].size += JobModel->item(current, 1)->text().toInt();
          MemoryList[i + 1].start =
              MemoryList[i + 1].end - MemoryList[i + 1].size + 1;
          MemoryList.removeAt(i);
        } else if (merge == BOTH) {
          MemoryList[i - 1].end = MemoryList[i + 1].end;
          MemoryList[i - 1].size =
              MemoryList[i - 1].end - MemoryList[i - 1].start + 1;
          MemoryList.removeAt(i);
          MemoryList.removeAt(i);
        }
        break;
      }
    }
    processingWaiting(FIRSTMETHOD);
  }
  displayMemoryData();
}

void MainWindow::bestAdaptation() {
  MemoryPartition temp;
  int merge = INIT;
  int least = INF;
  int i = 0;
  if (JobModel->item(current, 2)->text() == "申请") {
    merge = REQUIRE;
    for (i = 0; i < MemoryList.size(); i++) {
      if ((MemoryList[i].name == "空闲") &&
          (MemoryList[i].size >= JobModel->item(current, 1)->text().toInt())) {
        if (MemoryList[i].size < least) {
          merge = i;
          least = MemoryList[i].size;
        }
      }
    }
    if (merge != REQUIRE) {
      temp.start = MemoryList[merge].start;
      temp.end = temp.start + JobModel->item(current, 1)->text().toInt() - 1;
      temp.name = JobModel->item(current, 0)->text();
      temp.size = temp.end - temp.start + 1;
      MemoryList[merge].start = temp.end + 1;
      MemoryList[merge].size =
          MemoryList[merge].end - MemoryList[merge].start + 1;
      if (MemoryList[merge].size == 0) {
        MemoryList.removeAt(merge);
      }
      MemoryList.insert(merge, temp);
      JobModel->item(current, 3)->setText("已分配");
      JobModel->item(current, 3)->setForeground(QBrush(QColor(25, 204, 37)));
      addRecord(temp.start, SUCCESS);
    } else if (merge == REQUIRE) { //记得判断无法计入的情况
      addRecord(0, FAILURE);
      WaitingList.append(current);
      JobModel->item(current, 3)->setText("未分配");
      JobModel->item(current, 3)->setForeground(Qt::red);
    }
  } else if (JobModel->item(current, 2)->text() == "释放") {
    for (i = 0; i < MemoryList.size(); i++) {
      if (MemoryList[i].name == JobModel->item(current, 0)->text()) {
        addRecord(MemoryList[i].start, SUCCESS);
        JobModel->item(current, 3)->setText("已分配");
        JobModel->item(current, 3)->setForeground(QBrush(QColor(25, 204, 37)));
        if ((i != 0) && MemoryList[i - 1].name == "空闲") {
          merge += 1;
        }
        if ((i != MemoryList.size()) && MemoryList[i + 1].name == "空闲") {
          merge += 2;
        }
        if (merge == INIT) {
          MemoryList[i].name = "空闲";
        } else if (merge == FRONT) {
          MemoryList[i - 1].size += JobModel->item(current, 1)->text().toInt();
          MemoryList[i - 1].end =
              MemoryList[i - 1].start + MemoryList[i - 1].size - 1;
          MemoryList.removeAt(i);
        } else if (merge == BACK) {
          MemoryList[i + 1].size += JobModel->item(current, 1)->text().toInt();
          MemoryList[i + 1].start =
              MemoryList[i + 1].end - MemoryList[i + 1].size + 1;
          MemoryList.removeAt(i);
        } else if (merge == BOTH) {
          MemoryList[i - 1].end = MemoryList[i + 1].end;
          MemoryList[i - 1].size =
              MemoryList[i - 1].end - MemoryList[i - 1].start + 1;
          MemoryList.removeAt(i);
          MemoryList.removeAt(i);
        }
        break;
      }
    }
    processingWaiting(BESTMETHOD);
  }
  displayMemoryData();
}

bool MainWindow::checkJob() {
  if (ui->lineEdit->text().isEmpty()) {
    QMessageBox::warning(this, "ERROR", "未输入作业名！");
    return false;
  } else if (ui->lineEdit_2->text().isEmpty()) {
    QMessageBox::warning(this, "ERROR", "未输入作业大小！");
    return false;
  } else if (!isNumber(ui->lineEdit_2->text())) {
    QMessageBox::warning(this, "ERROR", "作业大小不是数字！");
    return false;
  } else if (ui->comboBox_3->currentText() == "申请") {
    for (int i = 0; i < JobModel->rowCount(); i++) {
      if (JobModel->item(i, 0)->text() == ui->lineEdit->text()) {
        QMessageBox::warning(this, "ERROR", "已存在以该名称命名的作业！");
        return false;
      }
    }
  } else if (ui->comboBox_3->currentText() == "释放") {
    int hasRequest = NO;
    for (int i = 0; i < JobModel->rowCount(); i++) {
      if (JobModel->item(i, 0)->text() == ui->lineEdit->text()) {
        if (JobModel->item(i, 2)->text() == "释放") {
          QMessageBox::warning(this, "ERROR", "该作业已经被释放！");
          return false;
        } else {
          hasRequest = YES;
          if (JobModel->item(i, 1)->text() != ui->lineEdit_2->text()) {
            QMessageBox::warning(this, "ERROR", "该作业释放大小输入错误！");
            return false;
          }
        }
      }
    }
    if (hasRequest == NO) {
      QMessageBox::warning(this, "ERROR", "该作业还未被申请！");
      return false;
    }
  }
  return true;
}

void MainWindow::addRecord(int start, int isPutIn, int waitJob) {
  if (isPutIn == SUCCESS) {
    QString string = tr("%1%2了%3 K内存空间,起始位置为%4")
                         .arg(JobModel->item(current, 0)->text())
                         .arg(JobModel->item(current, 2)->text())
                         .arg(JobModel->item(current, 1)->text())
                         .arg(start);
    QStandardItem *item = new QStandardItem(string);
    RecordModel->appendRow(item);
    RecordModel->item(RecordModel->rowCount() - 1)
        ->setForeground(QBrush(QColor(25, 204, 37)));
  } else if (isPutIn == FAILURE) {
    QString string = tr("%1%2%3 K内存空间失败,当前内存空间不足")
                         .arg(JobModel->item(current, 0)->text())
                         .arg(JobModel->item(current, 2)->text())
                         .arg(JobModel->item(current, 1)->text());
    QStandardItem *item = new QStandardItem(string);
    RecordModel->appendRow(item);
    RecordModel->item(RecordModel->rowCount() - 1)->setForeground(Qt::red);
  } else if (isPutIn == FRESH) {
    QString string = tr("%1重新%2了%3 K内存空间,起始位置为%4")
                         .arg(JobModel->item(WaitingList[waitJob], 0)->text())
                         .arg(JobModel->item(WaitingList[waitJob], 2)->text())
                         .arg(JobModel->item(WaitingList[waitJob], 1)->text())
                         .arg(start);
    QStandardItem *item = new QStandardItem(string);
    RecordModel->appendRow(item);
    RecordModel->item(RecordModel->rowCount() - 1)
        ->setForeground(QBrush(QColor(53, 0, 255)));
  }
}

void MainWindow::on_pushButton_clicked() {
  if (ui->comboBox->currentText() == "首次适应算法") {
    firstAdaptation();
  } else if (ui->comboBox->currentText() == "最佳适应算法") {
    bestAdaptation();
  }
  emit paintJob();
  current++;
  if (current == JobModel->rowCount()) { //溢出
    ui->pushButton->setEnabled(false);
    return;
  }
}

void MainWindow::on_horizontalSlider_valueChanged(int value) {
  ui->label_3->setText(tr("%1").arg(value));
  ui->widget->setGeometry((this->width() - value) / 2, 200, value, 100);
}

void MainWindow::on_pushButton_4_clicked() {
  if (checkJob()) {
    QString name = ui->lineEdit->text();
    QString size = ui->lineEdit_2->text();
    QString request = ui->comboBox_3->currentText();
    QString state = "待分配";
    QStandardItem *first = new QStandardItem(name);
    QStandardItem *second = new QStandardItem(size);
    QStandardItem *third = new QStandardItem(request);
    QStandardItem *fourth = new QStandardItem(state);
    QList<QStandardItem *> data;
    data.append(first);
    data.append(second);
    data.append(third);
    data.append(fourth);
    JobModel->appendRow(data);
    JobModel->item(JobModel->rowCount() - 1, 3)
        ->setForeground(QBrush(QColor(53, 0, 255)));
  }
}

void MainWindow::on_pushButton_3_clicked() {
  memWindow->resize(ui->widget->width(), 100); //重置
  MemoryPartition all;
  all.start = 0;
  all.end = ui->widget->width() - 1;
  all.size = all.end - all.start + 1;
  MemoryList.append(all);
  displayMemoryData();
  ui->pushButton_4->setEnabled(false);
  ui->pushButton_3->setEnabled(false);
  ui->pushButton_5->setEnabled(false);
  ui->pushButton_6->setEnabled(false);
  ui->pushButton_7->setEnabled(false);
  ui->spinBox->setEnabled(false);
  ui->horizontalSlider->setEnabled(false);
  ui->comboBox_3->setEnabled(false);
  ui->lineEdit->setEnabled(false);
  ui->lineEdit_2->setEnabled(false);
  ui->lineEdit->clear();
  ui->lineEdit_2->clear();
  if (JobModel->rowCount() != 0) {
    ui->pushButton->setEnabled(true);
  }
}

void MainWindow::on_pushButton_2_clicked() {
  ui->pushButton_4->setEnabled(true);
  ui->pushButton_6->setEnabled(true);
  ui->pushButton_5->setEnabled(true);
  ui->pushButton_3->setEnabled(true);
  ui->pushButton->setEnabled(false);
  ui->pushButton_7->setEnabled(true);
  ui->spinBox->setEnabled(true);
  ui->horizontalSlider->setEnabled(true);
  ui->comboBox_3->setEnabled(true);
  ui->lineEdit->setEnabled(true);
  ui->lineEdit_2->setEnabled(true);
  current = 0;
  if (RecordModel->rowCount() != 0) {
    RecordModel->clear();
  }
  IdleMemoryModel->clear();
  displayIdleMemory();
  AllMemoryModel->clear();
  displayAllMemory();
  MemoryList.clear();
  WaitingList.clear();
  memWindow->deleteLabel();
  for (int i = 0; i < JobModel->rowCount(); i++) {
    JobModel->item(i, 3)->setText("待分配");
    JobModel->item(i, 3)->setForeground(QBrush(QColor(53, 0, 255)));
  }
  QMessageBox::information(NULL, "提示", "清除成功！", QMessageBox::Yes);
}

void MainWindow::on_pushButton_5_clicked() {
  QString name[DEFAULTNUM] = {"作业1", "作业2", "作业3", "作业2",
                              "作业4", "作业3", "作业1", "作业5",
                              "作业6", "作业7", "作业6"};
  QString size[DEFAULTNUM] = {"130", "60",  "100", "60", "200", "100",
                              "130", "140", "60",  "50", "60"};
  QString request[DEFAULTNUM] = {"申请", "申请", "申请", "释放", "申请", "释放",
                                 "释放", "申请", "申请", "申请", "释放"};
  QString state = "待分配";
  JobModel->clear();
  displayJob();
  for (int i = 0; i < DEFAULTNUM; i++) {
    QStandardItem *first = new QStandardItem(name[i]);
    QStandardItem *second = new QStandardItem(size[i]);
    QStandardItem *third = new QStandardItem(request[i]);
    QStandardItem *fourth = new QStandardItem(state);
    QList<QStandardItem *> data;
    data.append(first);
    data.append(second);
    data.append(third);
    data.append(fourth);
    JobModel->appendRow(data);
    JobModel->item(i, 3)->setForeground(QBrush(QColor(53, 0, 255)));
  }
}

void MainWindow::on_pushButton_6_clicked() {
  JobModel->clear();
  displayJob();
}

void MainWindow::on_pushButton_7_clicked() {
  if ((ui->spinBox->value() > JobModel->rowCount()) ||
      (ui->spinBox->value() == 0)) {
    QMessageBox::warning(this, "ERROR", "表中没有该行！");
  } else {
    if (JobModel->item(ui->spinBox->value() - 1, 2)->text() == "申请") {
      for (int i = 0; i < JobModel->rowCount(); i++) {
        if (JobModel->item(i, 0)->text() ==
            JobModel->item(ui->spinBox->value() - 1, 0)->text()) {
          if (JobModel->item(i, 2)->text() == "释放") {
            QMessageBox::warning(
                this, "ERROR",
                "该行与后面的释放有联系，无法删除，请先删除该作业的释放操作！");
            return;
          }
        }
      }
    }
    JobModel->removeRow(ui->spinBox->value() - 1);
  }
}
