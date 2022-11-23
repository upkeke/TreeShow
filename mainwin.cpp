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
#include <QTransform>

#include"AVLTree.h"
#include "RBTree.h"





MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWin)
{
    avl = new AVLTree();
    rb = new RBTree(nullptr);

    //avl(new AVLTree(nullptr))
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->view->setScene(scene); //QGraphicsView
    
    ui->led_data->setText("50,5,43,76,59,13,83,66,120,4");
    //ui->led_data->setText("50,23,5,43");

    connect(ui->btn_begin, &QPushButton::clicked, this, &MainWin::btn_begin_clicked_AVL);
    connect(ui->btn_insert, &QPushButton::clicked, this, &MainWin::btn_insert_clicked__AVL);
    connect(ui->btn_keepB, &QPushButton::clicked, this, &MainWin::btn_keepB_clicked_AVL);
    connect(ui->btn_focus_next, &QPushButton::clicked, this, &MainWin::btn_focus_next_clicked_AVL);
    connect(ui->btn_del, &QPushButton::clicked, this, &MainWin::btn_del_clicked_AVL);

    connect(ui->cbx_moshi, &QComboBox::currentTextChanged, this, &MainWin::moShiQieHuan);

}

MainWin::~MainWin()
{
    delete ui;
    delete avl;
    delete rb;

}

void MainWin::btn_begin_clicked_AVL()
{

    QString str = ui->led_data->text(); //5,40,43,51,55,65,70,83,96,100
    QStringList list = str.split(',');
    vector<int> data(list.size(), 0);
    for (size_t i=0; i < list.size(); ++i)
    {
        data[i] = list[i].toInt();
    }
    *avl = AVLTree(data);
    
    w��ӡ��(avl->head);
}
// �������ݺ��������ƽ�⣬���ܼ������룬��ƽ����ָ�����
void MainWin::btn_insert_clicked__AVL()
{
    QString str = ui->led_insert->text();
    if (str.isEmpty())
        return;

    int val = str.toInt();
    bool flag =  avl->insert(val);
    if (flag) 
    {
		ui->btn_insert->setEnabled(false); //���ò��밴ť��ֱ��������ƽ��
		ui->btn_del->setEnabled(false);//����ɾ����ť
        ui->te_message->append(QString("����%1�ɹ�").arg(val));
        if (avl->w���Ƿ�ƽ��())
        {
            ui->te_message->append(QString("����%1�������ƽ��").arg(val));
        }
        else
        {
            ui->te_message->append(QString("����%1���������ƽ��").arg(val));
        }
        w��ӡ��(avl->head);
    }
    else
    {
        ui->te_message->append("������ͬ�����������");
    }
}

void MainWin::btn_keepB_clicked_AVL()
{
	if (unbptr != nullptr)
	{
		qDebug() << "ȡ��ʧ��ڵ��ӡ";
		//QPixmap pix(R"(E:\C++\TreeShow\img\green.jpg)");
		unbptr->setBackColor(NodeColor::yellow);
		// �����ͼԪ������Ƭ�������̽����ػ�
		scene->update(unbptr->sceneBoundingRect());
		unbptr = nullptr;
	}
	ui->btn_insert->setEnabled(true); //���ò��밴ť��ֱ��������ƽ��
	ui->btn_del->setEnabled(true);//����ɾ����ť
    if (avl->w���Ƿ�ƽ��())
    {
        scene->update();
		return;
    }
    avl->w����ƽ��();
    w��ӡ��(avl->head);

}

void MainWin::btn_focus_next_clicked_AVL()
{
    if (unbptr != nullptr)
    {
		qDebug() << "ȡ��ʧ��ڵ��ӡ";
		//QPixmap pix(R"(E:\C++\TreeShow\img\green.jpg)");
        unbptr->setBackColor(NodeColor::yellow);
		// �����ͼԪ������Ƭ�������̽����ػ�
		scene->update(unbptr->sceneBoundingRect());
        unbptr = nullptr;
        return;
    }

    Tree* t = avl->wʧ��ڵ�();
    if (t == nullptr)
        ui->te_message->append("û�з���ʧ��ڵ�");
    else
    {
        ui->te_message->append(QString("ʧ��ڵ��ֵ��%1").arg(t->val));
        QPoint ps = w��������(t->row, t->col);
        QTransform trm;
        QGraphicsItem* ls = scene->itemAt(ps,trm);
        unbptr = qgraphicsitem_cast<MyGraphicsItem*>(ls);
		if (unbptr != nullptr)
		{
			qDebug() << "�ҵ�ʧ��ڵ��ͼԪ";
			QPixmap pix(R"(E:\C++\TreeShow\img\green.jpg)");
            unbptr->setBackColor(NodeColor::green);
            // �����ͼԪ������Ƭ�������̽����ػ�
            scene->update(unbptr->sceneBoundingRect());
		}
    }
}

// ɾ�� ָ���ڵ����������ֱ��
void MainWin::btn_del_clicked_AVL()
{
    QList<QGraphicsItem*> itemList = scene->selectedItems();
    for (auto item : itemList)
    {
        auto it = qgraphicsitem_cast<MyGraphicsItem*>(item);
        if (it != nullptr)
        {
            // �����߼�
            qDebug() << QString("��Ҫ��ɾ���Ľڵ��ֵx =%1").arg(it->getVal());
            ui->te_message->append(QString("��ɾ���Ľڵ��ֵ��%1")
                .arg(it->getVal()));
            if (avl->pop(it->getVal())) // ɾ���ɹ�
            {
				ui->btn_insert->setEnabled(false); //���ò��밴ť��ֱ��������ƽ��
				ui->btn_del->setEnabled(false);//����ɾ����ť
                w��ӡ��(avl->head);
            }
		}
    }
}

void MainWin::moShiQieHuan(const QString& text)
{
    for (auto item : w�ڵ�ͼԪ��)
    {
        item->hide();
    }
	for (auto item : wֱ��ͼԪ��)
	{
		item->hide();
	}
    scene->update();
    if (text == "����ƽ����")
    {
        qDebug() << "����ƽ��������";
        ui->btn_begin->disconnect();
        ui->btn_insert->disconnect();
        ui->btn_keepB->disconnect();
        ui->btn_focus_next->disconnect();
        ui->btn_focus_next->setText("����ʧ��ڵ�");
        ui->btn_del->disconnect();

		connect(ui->btn_begin, &QPushButton::clicked, this, &MainWin::btn_begin_clicked_AVL);
		connect(ui->btn_insert, &QPushButton::clicked, this, &MainWin::btn_insert_clicked__AVL);
		connect(ui->btn_keepB, &QPushButton::clicked, this, &MainWin::btn_keepB_clicked_AVL);
		connect(ui->btn_focus_next, &QPushButton::clicked, this, &MainWin::btn_focus_next_clicked_AVL);
		connect(ui->btn_del, &QPushButton::clicked, this, &MainWin::btn_del_clicked_AVL);
    }
    if (text == "�����")
    {
        qDebug() << "���������";
		ui->btn_begin->disconnect();
		ui->btn_insert->disconnect();
		ui->btn_keepB->disconnect();
		ui->btn_focus_next->disconnect();
		ui->btn_focus_next->setText("next");
		ui->btn_del->disconnect();

        connect(ui->btn_begin, &QPushButton::clicked, this, &MainWin::btn_begin_clicked_RB);
        connect(ui->btn_insert, &QPushButton::clicked, this, &MainWin::btn_insert_clicked__RB);
    }
}

void MainWin::btn_begin_clicked_RB()
{
	QString str = ui->led_data->text(); 
	QStringList list = str.split(',');
	vector<int> data(list.size(), 0);
	for (size_t i = 0; i < list.size(); ++i)
	{
        //rb->insert(list[i].toInt());

		data[i] = list[i].toInt();
	}
	*rb = RBTree(data);
	w��ӡ��(rb->head);
}

void MainWin::btn_insert_clicked__RB()
{
	QString str = ui->led_insert->text();
	if (str.isEmpty())
		return;

	int val = str.toInt();
	rb->insert(val);
    w��ӡ��(rb->head);
}

void MainWin::w��ӡ��(Tree* head)
{
    vector<Tree*> �ڵ㼯�� = w�ڵ㼯��(head);
    int �ڵ�ͼԪ���� = w�ڵ�ͼԪ��.size(); //ͼԪ�����Ҫ��
    int �ڵ���� = �ڵ㼯��.size(); // ͼԪ�������ڽڵ���������ض����ͼԪ
    //ͼԪ����С�ڽڵ��������ӵ������ͼԪ
    int ֱ��ͼԪ���� = wֱ��ͼԪ��.size();
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

            w�ڵ�ͼԪ��[myitem_i]->setVal(val);
            w�ڵ�ͼԪ��[myitem_i]->setPos(QPointF(x1, y1));
            w�ڵ�ͼԪ��[myitem_i]->setBackColor(ptr->color);
        }
        else
        {
            MyGraphicsItem* item = new MyGraphicsItem(QPointF(x1, y1),
                val, ptr->color);
            w�ڵ�ͼԪ��.push_back(item);
            scene->addItem(item);
        }
        w�ڵ�ͼԪ��[myitem_i]->show();
        w�ڵ�ͼԪ��[myitem_i]->clearLines();
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
                QTransform transform;
                auto point = w��������(child->row, child->col);
                //auto end = dynamic_cast<MyGraphicsItem*>(scene->itemAt(point, transform));
                auto end = qgraphicsitem_cast<MyGraphicsItem*>(scene->itemAt(point, transform));
                if (line_i < ֱ��ͼԪ����) //����ͼԪλ��
                {
                    wֱ��ͼԪ��[line_i]->setTwo(w�ڵ�ͼԪ��[myitem_i],end);
                }
                else
                {
                    MyLineItem* line = new MyLineItem(w�ڵ�ͼԪ��[myitem_i], end);
                    wֱ��ͼԪ��.push_back(line);
                    scene->addItem(line);
                }
                // ����ֱ����2��ͼԪ���ӣ���ֱ����ӵ�2��ͼԪ��
                w�ڵ�ͼԪ��[myitem_i]->addLine(wֱ��ͼԪ��[line_i]);
				end->addLine(wֱ��ͼԪ��[line_i]);
                wֱ��ͼԪ��[line_i]->show();
                line_i++;
            }
        }
    }
    for (size_t k = line_i; k < ֱ��ͼԪ����; ++k)
    {
        wֱ��ͼԪ��[k]->hide();
    }
    // ͼԪ�ض����������
    for (size_t k = myitem_i; k < �ڵ�ͼԪ����; k++)
    {
        w�ڵ�ͼԪ��[k]->hide();
    }
    scene->update();
    ui->te_message->append("��ӡ�������ɹ�");
}



QPoint MainWin::w��������(int x, int y)
{
    return QPoint(x*40,y*60);
}



