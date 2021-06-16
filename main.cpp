#include "window.h"

#include <QApplication>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window w;
    w.move(0,0);
    w.show();
    return a.exec();
}
