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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserInterface
{
public:
    QPushButton *pushButton;
    QTextEdit *readline;
    QPushButton *GO;
    QTextEdit *readline_2;

    void setupUi(QWidget *UserInterface)
    {
        if (UserInterface->objectName().isEmpty())
            UserInterface->setObjectName(QString::fromUtf8("UserInterface"));
        UserInterface->resize(800, 600);
        pushButton = new QPushButton(UserInterface);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(640, 10, 151, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("Algerian"));
        font.setPointSize(16);
        pushButton->setFont(font);
        readline = new QTextEdit(UserInterface);
        readline->setObjectName(QString::fromUtf8("readline"));
        readline->setGeometry(QRect(400, 240, 401, 361));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial Black"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        readline->setFont(font1);
        GO = new QPushButton(UserInterface);
        GO->setObjectName(QString::fromUtf8("GO"));
        GO->setGeometry(QRect(640, 50, 151, 41));
        GO->setFont(font);
        readline_2 = new QTextEdit(UserInterface);
        readline_2->setObjectName(QString::fromUtf8("readline_2"));
        readline_2->setGeometry(QRect(0, 240, 401, 361));
        readline_2->setFont(font1);

        retranslateUi(UserInterface);

        QMetaObject::connectSlotsByName(UserInterface);
    } // setupUi

    void retranslateUi(QWidget *UserInterface)
    {
        UserInterface->setWindowTitle(QCoreApplication::translate("UserInterface", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("UserInterface", "\345\210\233\345\273\272\346\225\260\346\215\256\345\272\223", nullptr));
        GO->setText(QCoreApplication::translate("UserInterface", "GO", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserInterface: public Ui_UserInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERINTERFACE_H
