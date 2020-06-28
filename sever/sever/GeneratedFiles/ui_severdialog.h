/********************************************************************************
** Form generated from reading UI file 'severdialog.ui'
**
** Created: Wed Jun 24 17:41:37 2020
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEVERDIALOG_H
#define UI_SEVERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SeverDialogClass
{
public:
    QProgressBar *progressBar;
    QPushButton *ButtonRecive;
    QPushButton *ButtonQuit;
    QLabel *label;

    void setupUi(QDialog *SeverDialogClass)
    {
        if (SeverDialogClass->objectName().isEmpty())
            SeverDialogClass->setObjectName(QString::fromUtf8("SeverDialogClass"));
        SeverDialogClass->setEnabled(true);
        SeverDialogClass->resize(431, 274);
        progressBar = new QProgressBar(SeverDialogClass);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(90, 90, 231, 23));
        progressBar->setValue(0);
        ButtonRecive = new QPushButton(SeverDialogClass);
        ButtonRecive->setObjectName(QString::fromUtf8("ButtonRecive"));
        ButtonRecive->setGeometry(QRect(80, 180, 75, 23));
        ButtonQuit = new QPushButton(SeverDialogClass);
        ButtonQuit->setObjectName(QString::fromUtf8("ButtonQuit"));
        ButtonQuit->setGeometry(QRect(260, 180, 75, 23));
        label = new QLabel(SeverDialogClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(90, 130, 201, 21));

        retranslateUi(SeverDialogClass);
        QObject::connect(ButtonRecive, SIGNAL(clicked()), SeverDialogClass, SLOT(start()));
        QObject::connect(ButtonQuit, SIGNAL(clicked()), SeverDialogClass, SLOT(close()));

        QMetaObject::connectSlotsByName(SeverDialogClass);
    } // setupUi

    void retranslateUi(QDialog *SeverDialogClass)
    {
        SeverDialogClass->setWindowTitle(QApplication::translate("SeverDialogClass", "\346\234\215\345\212\241\347\253\257", 0, QApplication::UnicodeUTF8));
        ButtonRecive->setText(QApplication::translate("SeverDialogClass", "\346\216\245\346\224\266", 0, QApplication::UnicodeUTF8));
        ButtonQuit->setText(QApplication::translate("SeverDialogClass", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SeverDialogClass", "\346\234\215\345\212\241\347\253\257\345\260\261\347\273\252", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SeverDialogClass: public Ui_SeverDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEVERDIALOG_H
