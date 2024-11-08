#ifndef PICKKING_H
#define PICKKING_H
#include<QList>
#include<QString>
#include<QObject>
#include<QWidget>
struct node{
    node *next;
    int val;
};
class PickKing
{
private:
    node *headnode;
public:
    PickKing();
    ~PickKing();
    void CreatingRing(int num);
    QList<QString> StartJR(int listingnum);

};

#endif // PICKKING_H
