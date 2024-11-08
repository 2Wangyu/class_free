/********************************************************************************
** Form generated from reading UI file 'userinterface.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERINTERFACE_H
#define UI_USERINTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserInterface
{
public:
    QTextEdit *readline;
    QPushButton *GO;
    QTextEdit *readline_2;
    QLabel *label;
    QPushButton *GO_2;

    void setupUi(QWidget *UserInterface)
    {
        if (UserInterface->objectName().isEmpty())
            UserInterface->setObjectName(QString::fromUtf8("UserInterface"));
        UserInterface->resize(800, 600);
        readline = new QTextEdit(UserInterface);
        readline->setObjectName(QString::fromUtf8("readline"));
        readline->setGeometry(QRect(400, 240, 401, 361));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial Black"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        readline->setFont(font);
        GO = new QPushButton(UserInterface);
        GO->setObjectName(QString::fromUtf8("GO"));
        GO->setGeometry(QRect(640, 20, 151, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Algerian"));
        font1.setPointSize(16);
        GO->setFont(font1);
        readline_2 = new QTextEdit(UserInterface);
        readline_2->setObjectName(QString::fromUtf8("readline_2"));
        readline_2->setGeometry(QRect(0, 240, 401, 361));
        readline_2->setFont(font);
        label = new QLabel(UserInterface);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 20, 501, 161));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial Black"));
        font2.setPointSize(72);
        font2.setBold(true);
        font2.setWeight(75);
        label->setFont(font2);
        GO_2 = new QPushButton(UserInterface);
        GO_2->setObjectName(QString::fromUtf8("GO_2"));
        GO_2->setGeometry(QRect(640, 80, 151, 41));
        GO_2->setFont(font1);

        retranslateUi(UserInterface);

        QMetaObject::connectSlotsByName(UserInterface);
    } // setupUi

    void retranslateUi(QWidget *UserInterface)
    {
        UserInterface->setWindowTitle(QCoreApplication::translate("UserInterface", "Form", nullptr));
        GO->setText(QCoreApplication::translate("UserInterface", "GO", nullptr));
        label->setText(QCoreApplication::translate("UserInterface", "MYSQL", nullptr));
        GO_2->setText(QCoreApplication::translate("UserInterface", "SQL\350\204\232\346\234\254", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserInterface: public Ui_UserInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERINTERFACE_H
