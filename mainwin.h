#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include"AVTree.h"

using 二叉树::AVLTree;
using 二叉树::Tree;
using 二叉树::vector;
class QGraphicsScene;
class QPoint;
class MyGraphicsItem;
class QGraphicsLineItem;
class MyGraphicsItem;

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
    
    AVLTree avt;
    vector<vector<int>> 坐标; // 保存每个节点的坐标
    vector<Tree*> 节点集合; // 后序遍历收集
    Ui::MainWin *ui;
    QGraphicsScene* scene;
    QPixmap pix;
    vector<MyGraphicsItem*> 节点图元池;
    vector<QGraphicsLineItem*> 直线图元池;
    //vector<MyLineItem*> 直线图元池;

    void 打印树();
    QPoint 网格到坐标(int x, int y);
private slots:
    void on_btn_begin_clicked();
    void on_btn_insert_clicked();
    void on_btn_keepB_clicked();

    void on_btn_test_clicked();

};
#endif // MAINWIN_H
