#ifndef SEARCHRECORD_H
#define SEARCHRECORD_H

#include <QString>
#include <QStringList>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>
#include <QTextEdit>
#include <QTextTable>
#include <QTextDocument>
#include <regex>
#include <QByteArray>

class SearchRecord
{
public:
    SearchRecord();

    void selectFunction(QTextEdit* textEdit, const QString& dbName, const QString& attrList, const QString& tableList, const QString& whereClause);

private:
    bool containAll(const QStringList& list1, const QStringList& list2);

    QList<int> get_index_list(const QStringList& list1, const QStringList& list2);

    QStringList sort_by_sequence(QStringList& list, const QList<QStringList>& attrs_in_tables , const QList<QList<int>>& sequence);
};

#endif // SEARCHRECORD_H

