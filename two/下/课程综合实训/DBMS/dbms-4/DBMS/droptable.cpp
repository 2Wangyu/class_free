#include "droptable.h"
#include "QDir"
droptable::droptable()
{

}

void droptable::drop(QString tablename,QString basename){
    QDir *dir2 = new QDir(QDir::currentPath());
    dir2->cdUp();

//    QString dname = QString::fromStdString(dbName);
//    QString name = QString::fromStdString(tableName);
    QString dirPath = dir2->path() + "/DBMS/data"+ "/" + basename+ "/" + tablename;
    QDir dir(dirPath);
    if (dir.exists()) {
           if (dir.removeRecursively()) {
               QMessageBox::information(nullptr, "Warning", "删除"+tablename+"成功");
               qDebug() << "Folder deleted successfully.";
           } else {
               QMessageBox::information(nullptr, "Warning", "删除"+tablename+"失败");
               qDebug() << "Failed to delete folder.";
           }
       }

}
