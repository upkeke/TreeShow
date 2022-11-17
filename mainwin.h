#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include"AVTree.h"

using ������::AVLTree;
using ������::Tree;
using ������::vector;
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
    vector<vector<int>> ����; // ����ÿ���ڵ������
    vector<Tree*> �ڵ㼯��; // ��������ռ�
    Ui::MainWin *ui;
    QGraphicsScene* scene;
    QPixmap pix;
    vector<MyGraphicsItem*> �ڵ�ͼԪ��;
    vector<QGraphicsLineItem*> ֱ��ͼԪ��;
    //vector<MyLineItem*> ֱ��ͼԪ��;

    void ��ӡ��();
    QPoint ��������(int x, int y);
private slots:
    void on_btn_begin_clicked();
    void on_btn_insert_clicked();
    void on_btn_keepB_clicked();

    void on_btn_test_clicked();

};
#endif // MAINWIN_H
