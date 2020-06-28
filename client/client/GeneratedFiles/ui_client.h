/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created: Sun Jun 28 09:57:23 2020
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientClass
{
public:
    QLabel *label;
    QProgressBar *progressBar;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonSend;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonOpen;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonQuit;

    void setupUi(QDialog *ClientClass)
    {
        if (ClientClass->objectName().isEmpty())
            ClientClass->setObjectName(QString::fromUtf8("ClientClass"));
        ClientClass->resize(489, 324);
        label = new QLabel(ClientClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 150, 351, 31));
        progressBar = new QProgressBar(ClientClass);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(70, 90, 351, 23));
        progressBar->setValue(0);
        layoutWidget = new QWidget(ClientClass);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 230, 391, 51));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonSend = new QPushButton(layoutWidget);
        pushButtonSend->setObjectName(QString::fromUtf8("pushButtonSend"));

        horizontalLayout->addWidget(pushButtonSend);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonOpen = new QPushButton(layoutWidget);
        pushButtonOpen->setObjectName(QString::fromUtf8("pushButtonOpen"));

        horizontalLayout->addWidget(pushButtonOpen);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButtonQuit = new QPushButton(layoutWidget);
        pushButtonQuit->setObjectName(QString::fromUtf8("pushButtonQuit"));

        horizontalLayout->addWidget(pushButtonQuit);


        retranslateUi(ClientClass);
        QObject::connect(pushButtonOpen, SIGNAL(clicked()), ClientClass, SLOT(openFile()));
        QObject::connect(pushButtonSend, SIGNAL(clicked()), ClientClass, SLOT(start()));
        QObject::connect(pushButtonQuit, SIGNAL(clicked()), ClientClass, SLOT(close()));

        QMetaObject::connectSlotsByName(ClientClass);
    } // setupUi

    void retranslateUi(QDialog *ClientClass)
    {
        ClientClass->setWindowTitle(QApplication::translate("ClientClass", "\345\217\221\351\200\201\347\253\257", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ClientClass", "\345\217\221\351\200\201\347\253\257\345\260\261\347\273\252", 0, QApplication::UnicodeUTF8));
        pushButtonSend->setText(QApplication::translate("ClientClass", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
        pushButtonOpen->setText(QApplication::translate("ClientClass", "\346\211\223\345\274\200", 0, QApplication::UnicodeUTF8));
        pushButtonQuit->setText(QApplication::translate("ClientClass", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ClientClass: public Ui_ClientClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
