#include "mainwin.h"
#include "./ui_mainwin.h"
#include<qpushbutton.h>
#include<QGraphicsLineItem>
#include<QGraphicsTextItem>
#include<qstringlist.h>
#include"MyGraphicsItem.h"
#include<qdebug.h>
#include<QList>
#include<QString>
#include"MyLineItem.h"
MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWin), avt(nullptr)
{
    ui->setupUi(this);

    pix = QPixmap(R"(E:\C++\TreeShow\img\yellow.jpg)").scaledToHeight(30);
    ui->cbx_moshi->addItem("二叉搜索树");

    scene = new QGraphicsScene(this);
    ui->view->setScene(scene); //QGraphicsView
    
    ui->led_data->setText("5,40,43,51,55,65,70,83,96,100");
    //connect(ui->btn_begin, &QPushButton::clicked, this, &MainWin::btn_begin_click);
    //connect(ui->btn_insert, &QPushButton::clicked, this, &MainWin::btn_insert_click);
    //connect(ui->btn_keepB, &QPushButton::clicked, this, &MainWin::btn_keepB_click);

}

MainWin::~MainWin()
{
    delete ui;
}

void MainWin::on_btn_begin_clicked()
{

    QString str = ui->led_data->text(); //5,40,43,51,55,65,70,83,96,100
    QStringList list = str.split(',');
    vector<int> data(list.size(), 0);
    for (size_t i=0; i < list.size(); ++i)
    {
        data[i] = list[i].toInt();
    }
    avt = AVLTree(data); // 移动拷贝  
    节点集合 = avt.节点集合();
    打印树();
}

void MainWin::on_btn_insert_clicked()
{
    QString str = ui->led_insert->text();
    if (str.isEmpty())
        return;
    int val = str.toInt();
    bool flag =  avt.insert(val);
    if (flag)
    {
        ui->te_message->append(QString("插入%1成功").arg(val));
        节点集合 = avt.节点集合();
        打印树();
    }
    else
    {
        ui->te_message->append("已有相同数，不需插入");
    }
}

void MainWin::on_btn_keepB_clicked()
{
    qDebug() << "按下按钮 qDebug";
}

void MainWin::on_btn_test_clicked()
{
    Tree* t = avt.失衡节点();
    if (t == nullptr)
        ui->te_message->append("没有发现失衡节点");
    else
    {
        ui->te_message->append(QString("失衡节点的值是%1").arg(t->val));
        QPoint ps = 网格到坐标(t->row, t->col);
        QList<QGraphicsItem*> ls = scene->items(ps);
        for (auto item : ls)
        {
            auto od = dynamic_cast<MyGraphicsItem*>(item);
            if (od != nullptr)
            {
                qDebug() << "找到失衡节点的图元";
                QPixmap pix(R"(E:\C++\TreeShow\img\green.jpg)");
                od->setPix(pix.scaledToHeight(30));
            }
        }
    }
}

void MainWin::打印树()
{
    //字宽 为30
    //单位长度为
    QPen pen(Qt::red);
    pen.setWidth(3);

    int 节点图元个数 = 节点图元池.size(); //图元用完后不要丢
    int 节点个数 = 节点集合.size(); // 图元个数大于节点个数，隐藏多余的图元
    //图元个数小于节点个数，添加调多余的图元
    int 直线图元个数 = 直线图元池.size();
    size_t myitem_i  = 0; //当前图元下标
    size_t line_i = 0;  //当前直线图元下标
    for (; myitem_i < 节点个数; myitem_i++)
    {
        Tree* ptr = 节点集合[myitem_i];
        
        int val = ptr->val;
        int x1 = ptr->row * 40;
        int y1 = ptr->col * 60; // 中心位置
        if (myitem_i < 节点图元个数)
        {

            节点图元池[myitem_i]->setText(QString::number(val));
            节点图元池[myitem_i]->setPos(QPointF(x1, y1));
        }
        else
        {
            MyGraphicsItem* item = new MyGraphicsItem(QPointF(x1, y1),
                QString::number(val), pix);
            节点图元池.push_back(item);
            scene->addItem(item);
        }
        节点图元池[myitem_i]->show();
        // 连接父节点到子节点的线
        for (size_t j = 0; j < 2; ++j)
        {
            Tree* child = nullptr;
            if (j == 0) child = ptr->left;
            else child = ptr->right;
            if (child != nullptr)
            {
                int x2 = child->row * 40;
                int y2 = child->col * 60;
                if (line_i < 直线图元个数) //调整图元位置
                {
                    直线图元池[line_i]->setLine(x1, y1, x2, y2);
                }
                else
                {
                    QGraphicsLineItem* line = new QGraphicsLineItem(x1, y1, x2, y2);
                    直线图元池.push_back(line);
                    scene->addItem(line);
                }
                直线图元池[line_i]->show();
                直线图元池[line_i]->setPen(pen);
                line_i++;
            }
        }
    }
    for (size_t k = line_i; line_i < 直线图元个数; ++k)
    {
        直线图元池[k]->hide();
    }
    // 图元池多出来的隐藏
    for (size_t k = myitem_i; k < 节点图元个数; k++)
    {
        节点图元池[k]->hide();
    }
    ui->te_message->append("打印二叉树成功");
}

QPoint MainWin::网格到坐标(int x, int y)
{
    return QPoint(x*40,y*60);
}



