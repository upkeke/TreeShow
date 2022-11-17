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
    ui->cbx_moshi->addItem("����������");

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
    avt = AVLTree(data); // �ƶ�����  
    �ڵ㼯�� = avt.�ڵ㼯��();
    ��ӡ��();
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
        ui->te_message->append(QString("����%1�ɹ�").arg(val));
        �ڵ㼯�� = avt.�ڵ㼯��();
        ��ӡ��();
    }
    else
    {
        ui->te_message->append("������ͬ�����������");
    }
}

void MainWin::on_btn_keepB_clicked()
{
    qDebug() << "���°�ť qDebug";
}

void MainWin::on_btn_test_clicked()
{
    Tree* t = avt.ʧ��ڵ�();
    if (t == nullptr)
        ui->te_message->append("û�з���ʧ��ڵ�");
    else
    {
        ui->te_message->append(QString("ʧ��ڵ��ֵ��%1").arg(t->val));
        QPoint ps = ��������(t->row, t->col);
        QList<QGraphicsItem*> ls = scene->items(ps);
        for (auto item : ls)
        {
            auto od = dynamic_cast<MyGraphicsItem*>(item);
            if (od != nullptr)
            {
                qDebug() << "�ҵ�ʧ��ڵ��ͼԪ";
                QPixmap pix(R"(E:\C++\TreeShow\img\green.jpg)");
                od->setPix(pix.scaledToHeight(30));
            }
        }
    }
}

void MainWin::��ӡ��()
{
    //�ֿ� Ϊ30
    //��λ����Ϊ
    QPen pen(Qt::red);
    pen.setWidth(3);

    int �ڵ�ͼԪ���� = �ڵ�ͼԪ��.size(); //ͼԪ�����Ҫ��
    int �ڵ���� = �ڵ㼯��.size(); // ͼԪ�������ڽڵ���������ض����ͼԪ
    //ͼԪ����С�ڽڵ��������ӵ������ͼԪ
    int ֱ��ͼԪ���� = ֱ��ͼԪ��.size();
    size_t myitem_i  = 0; //��ǰͼԪ�±�
    size_t line_i = 0;  //��ǰֱ��ͼԪ�±�
    for (; myitem_i < �ڵ����; myitem_i++)
    {
        Tree* ptr = �ڵ㼯��[myitem_i];
        
        int val = ptr->val;
        int x1 = ptr->row * 40;
        int y1 = ptr->col * 60; // ����λ��
        if (myitem_i < �ڵ�ͼԪ����)
        {

            �ڵ�ͼԪ��[myitem_i]->setText(QString::number(val));
            �ڵ�ͼԪ��[myitem_i]->setPos(QPointF(x1, y1));
        }
        else
        {
            MyGraphicsItem* item = new MyGraphicsItem(QPointF(x1, y1),
                QString::number(val), pix);
            �ڵ�ͼԪ��.push_back(item);
            scene->addItem(item);
        }
        �ڵ�ͼԪ��[myitem_i]->show();
        // ���Ӹ��ڵ㵽�ӽڵ����
        for (size_t j = 0; j < 2; ++j)
        {
            Tree* child = nullptr;
            if (j == 0) child = ptr->left;
            else child = ptr->right;
            if (child != nullptr)
            {
                int x2 = child->row * 40;
                int y2 = child->col * 60;
                if (line_i < ֱ��ͼԪ����) //����ͼԪλ��
                {
                    ֱ��ͼԪ��[line_i]->setLine(x1, y1, x2, y2);
                }
                else
                {
                    QGraphicsLineItem* line = new QGraphicsLineItem(x1, y1, x2, y2);
                    ֱ��ͼԪ��.push_back(line);
                    scene->addItem(line);
                }
                ֱ��ͼԪ��[line_i]->show();
                ֱ��ͼԪ��[line_i]->setPen(pen);
                line_i++;
            }
        }
    }
    for (size_t k = line_i; line_i < ֱ��ͼԪ����; ++k)
    {
        ֱ��ͼԪ��[k]->hide();
    }
    // ͼԪ�ض����������
    for (size_t k = myitem_i; k < �ڵ�ͼԪ����; k++)
    {
        �ڵ�ͼԪ��[k]->hide();
    }
    ui->te_message->append("��ӡ�������ɹ�");
}

QPoint MainWin::��������(int x, int y)
{
    return QPoint(x*40,y*60);
}



