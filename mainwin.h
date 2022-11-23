#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include <vector>
using std::vector;


class QGraphicsScene;
class QPoint;
class MyGraphicsItem;
class QGraphicsLineItem;
class MyLineItem;


namespace w二叉树
{
    class Tree;
    class AVLTree;
    class RBTree;
}

using w二叉树::AVLTree;
using w二叉树::Tree;
using w二叉树::RBTree;


#pragma execution_character_set("utf-8")

QT_BEGIN_NAMESPACE
namespace Ui { class MainWin; }
QT_END_NAMESPACE

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    MainWin(QWidget *parent = nullptr);
    ~MainWin();

private:
    AVLTree* avl;
    RBTree* rb;


    MyGraphicsItem* unbptr = nullptr; //不平衡节点的标记

    Ui::MainWin *ui;
    QGraphicsScene* scene;
    vector<MyGraphicsItem*> w节点图元池;
    vector<MyLineItem*> w直线图元池;

    void w打印树(Tree * head);
    //void 打印树_RB();
    QPoint w网格到坐标(int x, int y);
    
private slots:

    void btn_begin_clicked_AVL();
    void btn_insert_clicked__AVL();
    void btn_keepB_clicked_AVL();
    void btn_focus_next_clicked_AVL();
    void btn_del_clicked_AVL();

	void moShiQieHuan(const QString& text);

	void btn_begin_clicked_RB();
	void btn_insert_clicked__RB();
	//void btn_keepB_clicked_RB();
	//void btn_focus_next_clicked_RB();
	//void btn_del_clicked_RB();



};
#endif // MAINWIN_H
