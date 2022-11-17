#include "mainwin.h"

#include <QApplication>


class B1
{
public:
    virtual void func1() = 0;
    virtual void func2()
    {
        printf("this is B1");
    }

};
class B2 :public B1
{
public:
    // Í¨¹ý B1 ¼Ì³Ð
    virtual void func1() override
    {
        printf("kkk");
    }
    virtual void func2()
    {
        B1::func2();
    }
};
int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWin w;
    //w.show();
    //return a.exec();
    B2 b;
    b.func2();
}
