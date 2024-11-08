
////#include <QMessageBox>
////#include<QtSql/QSqlDatabase>
////#include<QtSql/QSqlQuery>


//#include <QCoreApplication>
//#include <QtSql/QSqlDatabase>
//#include <QtSql/QSqlQuery>
//#include <QDebug>

//class DatabaseConnector {
//public:
//    DatabaseConnector(QSqlDatabase& db) : db(db) {}

//    bool connectToDatabase() {
//        if (!db.open()) {
//            qDebug() << "Failed to connect to database.";
//            return false;
//        } else {
//            qDebug() << "Connected to database.";
//            return true;
//        }
//    }

//    QString queryValue(const QString& query, const QVariantMap& params = QVariantMap()) {
//        QSqlQuery queryObj(db);
//        if (queryObj.exec(query)) {
//            if (queryObj.next()) {
//                return queryObj.value(0).toString();
//            }
//        } else {
//            qDebug() << "Failed to execute query.";
//        }
//        return QString();
//    }

//    QStringList queryValues(const QString& query, const QVariantMap& params = QVariantMap()) {
//        QSqlQuery queryObj(db);
//        QStringList results;
//        if (queryObj.exec(query)) {
//            while (queryObj.next()) {
//                results.append(queryObj.value(0).toString());
//            }
//        } else {
//            qDebug() << "Failed to execute query.";
//        }
//        return results;
//    }

//    QVariant queryData(const QString& query, const QVariantMap& params = QVariantMap()) {
//        QSqlQuery queryObj(db);
//        QVariant data;
//        if (queryObj.exec(query)) {
//            while (queryObj.next()) {
//                data.setValue(queryObj.value(0).toInt()); // 读取查询结果中的第一列数据，存储在QVariant变量中，并转换为int类型
//                qDebug() << data.toInt(); // 输出int类型的数据
//                data.setValue(queryObj.value(1).toString()); // 读取查询结果中的第二列数据，存储在QVariant变量中，并转换为QString类型
//                qDebug() << data.toString(); // 输出QString类型的数据
//                data.setValue(queryObj.value(2).toDouble()); // 读取查询结果中的第三列数据，存储在QVariant变量中，并转换为double类型
//                qDebug() << data.toDouble(); // 输出double类型的数据
//            }
//        } else {
//            qDebug() << "Failed to execute query.";
//        }
//        return data;
//    }

//private:
//    QSqlDatabase& db;
//};
