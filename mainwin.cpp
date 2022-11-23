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
    
    w打印树(avl->head);
}
// 插入数据后，如果树不平衡，不能继续插入，树平衡后会恢复插入
void MainWin::btn_insert_clicked__AVL()
{
    QString str = ui->led_insert->text();
    if (str.isEmpty())
        return;

    int val = str.toInt();
    bool flag =  avl->insert(val);
    if (flag) 
    {
		ui->btn_insert->setEnabled(false); //禁用插入按钮，直到二叉树平衡
		ui->btn_del->setEnabled(false);//禁用删除按钮
        ui->te_message->append(QString("插入%1成功").arg(val));
        if (avl->w树是否平衡())
        {
            ui->te_message->append(QString("插入%1后二叉树平衡").arg(val));
        }
        else
        {
            ui->te_message->append(QString("插入%1后二叉树不平衡").arg(val));
        }
        w打印树(avl->head);
    }
    else
    {
        ui->te_message->append("已有相同数，不需插入");
    }
}

void MainWin::btn_keepB_clicked_AVL()
{
	if (unbptr != nullptr)
	{
		qDebug() << "取消失衡节点打印";
		//QPixmap pix(R"(E:\C++\TreeShow\img\green.jpg)");
		unbptr->setBackColor(NodeColor::yellow);
		// 对这个图元所在这片区域立刻进行重绘
		scene->update(unbptr->sceneBoundingRect());
		unbptr = nullptr;
	}
	ui->btn_insert->setEnabled(true); //禁用插入按钮，直到二叉树平衡
	ui->btn_del->setEnabled(true);//禁用删除按钮
    if (avl->w树是否平衡())
    {
        scene->update();
		return;
    }
    avl->w保持平衡();
    w打印树(avl->head);

}

void MainWin::btn_focus_next_clicked_AVL()
{
    if (unbptr != nullptr)
    {
		qDebug() << "取消失衡节点打印";
		//QPixmap pix(R"(E:\C++\TreeShow\img\green.jpg)");
        unbptr->setBackColor(NodeColor::yellow);
		// 对这个图元所在这片区域立刻进行重绘
		scene->update(unbptr->sceneBoundingRect());
        unbptr = nullptr;
        return;
    }

    Tree* t = avl->w失衡节点();
    if (t == nullptr)
        ui->te_message->append("没有发现失衡节点");
    else
    {
        ui->te_message->append(QString("失衡节点的值是%1").arg(t->val));
        QPoint ps = w网格到坐标(t->row, t->col);
        QTransform trm;
        QGraphicsItem* ls = scene->itemAt(ps,trm);
        unbptr = qgraphicsitem_cast<MyGraphicsItem*>(ls);
		if (unbptr != nullptr)
		{
			qDebug() << "找到失衡节点的图元";
			QPixmap pix(R"(E:\C++\TreeShow\img\green.jpg)");
            unbptr->setBackColor(NodeColor::green);
            // 对这个图元所在这片区域立刻进行重绘
            scene->update(unbptr->sceneBoundingRect());
		}
    }
}

// 删除 指定节点和与它相结的直线
void MainWin::btn_del_clicked_AVL()
{
    QList<QGraphicsItem*> itemList = scene->selectedItems();
    for (auto item : itemList)
    {
        auto it = qgraphicsitem_cast<MyGraphicsItem*>(item);
        if (it != nullptr)
        {
            // 界面逻辑
            qDebug() << QString("将要被删除的节点的值x =%1").arg(it->getVal());
            ui->te_message->append(QString("被删除的节点的值是%1")
                .arg(it->getVal()));
            if (avl->pop(it->getVal())) // 删除成功
            {
				ui->btn_insert->setEnabled(false); //禁用插入按钮，直到二叉树平衡
				ui->btn_del->setEnabled(false);//禁用删除按钮
                w打印树(avl->head);
            }
		}
    }
}

void MainWin::moShiQieHuan(const QString& text)
{
    for (auto item : w节点图元池)
    {
        item->hide();
    }
	for (auto item : w直线图元池)
	{
		item->hide();
	}
    scene->update();
    if (text == "二叉平衡树")
    {
        qDebug() << "二叉平衡树激活";
        ui->btn_begin->disconnect();
        ui->btn_insert->disconnect();
        ui->btn_keepB->disconnect();
        ui->btn_focus_next->disconnect();
        ui->btn_focus_next->setText("锁定失衡节点");
        ui->btn_del->disconnect();

		connect(ui->btn_begin, &QPushButton::clicked, this, &MainWin::btn_begin_clicked_AVL);
		connect(ui->btn_insert, &QPushButton::clicked, this, &MainWin::btn_insert_clicked__AVL);
		connect(ui->btn_keepB, &QPushButton::clicked, this, &MainWin::btn_keepB_clicked_AVL);
		connect(ui->btn_focus_next, &QPushButton::clicked, this, &MainWin::btn_focus_next_clicked_AVL);
		connect(ui->btn_del, &QPushButton::clicked, this, &MainWin::btn_del_clicked_AVL);
    }
    if (text == "红黑树")
    {
        qDebug() << "红黑树激活";
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
	w打印树(rb->head);
}

void MainWin::btn_insert_clicked__RB()
{
	QString str = ui->led_insert->text();
	if (str.isEmpty())
		return;

	int val = str.toInt();
	rb->insert(val);
    w打印树(rb->head);
}

void MainWin::w打印树(Tree* head)
{
    vector<Tree*> 节点集合 = w节点集合(head);
    int 节点图元个数 = w节点图元池.size(); //图元用完后不要丢
    int 节点个数 = 节点集合.size(); // 图元个数大于节点个数，隐藏多余的图元
    //图元个数小于节点个数，添加调多余的图元
    int 直线图元个数 = w直线图元池.size();
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

            w节点图元池[myitem_i]->setVal(val);
            w节点图元池[myitem_i]->setPos(QPointF(x1, y1));
            w节点图元池[myitem_i]->setBackColor(ptr->color);
        }
        else
        {
            MyGraphicsItem* item = new MyGraphicsItem(QPointF(x1, y1),
                val, ptr->color);
            w节点图元池.push_back(item);
            scene->addItem(item);
        }
        w节点图元池[myitem_i]->show();
        w节点图元池[myitem_i]->clearLines();
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
                QTransform transform;
                auto point = w网格到坐标(child->row, child->col);
                //auto end = dynamic_cast<MyGraphicsItem*>(scene->itemAt(point, transform));
                auto end = qgraphicsitem_cast<MyGraphicsItem*>(scene->itemAt(point, transform));
                if (line_i < 直线图元个数) //调整图元位置
                {
                    w直线图元池[line_i]->setTwo(w节点图元池[myitem_i],end);
                }
                else
                {
                    MyLineItem* line = new MyLineItem(w节点图元池[myitem_i], end);
                    w直线图元池.push_back(line);
                    scene->addItem(line);
                }
                // 由于直线与2个图元连接，把直线添加到2个图元中
                w节点图元池[myitem_i]->addLine(w直线图元池[line_i]);
				end->addLine(w直线图元池[line_i]);
                w直线图元池[line_i]->show();
                line_i++;
            }
        }
    }
    for (size_t k = line_i; k < 直线图元个数; ++k)
    {
        w直线图元池[k]->hide();
    }
    // 图元池多出来的隐藏
    for (size_t k = myitem_i; k < 节点图元个数; k++)
    {
        w节点图元池[k]->hide();
    }
    scene->update();
    ui->te_message->append("打印二叉树成功");
}



QPoint MainWin::w网格到坐标(int x, int y)
{
    return QPoint(x*40,y*60);
}



