/********************************************************************************
** Form generated from reading UI file 'signupwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUPWIDGET_H
#define UI_SIGNUPWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_signupwidget
{
public:
    QLineEdit *lineEdit;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLabel *label_4;
    QPushButton *pushButton;
    QLabel *label;
    QPushButton *pushButton_2;
    QLabel *label_6;
    QLineEdit *lineEdit_4;

    void setupUi(QWidget *signupwidget)
    {
        if (signupwidget->objectName().isEmpty())
            signupwidget->setObjectName(QString::fromUtf8("signupwidget"));
        signupwidget->resize(600, 600);
        lineEdit = new QLineEdit(signupwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(80, 240, 261, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font.setPointSize(16);
        lineEdit->setFont(font);
        label_3 = new QLabel(signupwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(360, 230, 161, 51));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Algerian"));
        font1.setPointSize(16);
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignCenter);
        lineEdit_2 = new QLineEdit(signupwidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(80, 320, 261, 41));
        lineEdit_2->setFont(font);
        label_4 = new QLabel(signupwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(380, 320, 111, 51));
        label_4->setFont(font1);
        label_4->setAlignment(Qt::AlignCenter);
        pushButton = new QPushButton(signupwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(50, 520, 191, 51));
        pushButton->setFont(font1);
        label = new QLabel(signupwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(230, 70, 441, 101));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Algerian"));
        font2.setPointSize(72);
        label->setFont(font2);
        label->setAlignment(Qt::AlignCenter);
        pushButton_2 = new QPushButton(signupwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(340, 520, 171, 51));
        pushButton_2->setFont(font1);
        label_6 = new QLabel(signupwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(390, 410, 111, 51));
        label_6->setFont(font1);
        label_6->setAlignment(Qt::AlignCenter);
        lineEdit_4 = new QLineEdit(signupwidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(80, 410, 261, 41));
        lineEdit_4->setFont(font);

        retranslateUi(signupwidget);

        QMetaObject::connectSlotsByName(signupwidget);
    } // setupUi

    void retranslateUi(QWidget *signupwidget)
    {
        signupwidget->setWindowTitle(QCoreApplication::translate("signupwidget", "Form", nullptr));
        label_3->setText(QCoreApplication::translate("signupwidget", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_4->setText(QCoreApplication::translate("signupwidget", "\345\257\206\347\240\201", nullptr));
        pushButton->setText(QCoreApplication::translate("signupwidget", "\346\263\250\345\206\214", nullptr));
        label->setText(QCoreApplication::translate("signupwidget", "Sign ", nullptr));
        pushButton_2->setText(QCoreApplication::translate("signupwidget", "\351\200\200\345\207\272", nullptr));
        label_6->setText(QCoreApplication::translate("signupwidget", "ENSURE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class signupwidget: public Ui_signupwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUPWIDGET_H
