#include "parkingshow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ParkingShow *w=new ParkingShow();
    w->show();
    //enter1 *thread=new enter1(w);
//   thread->start();


    return a.exec();
}
