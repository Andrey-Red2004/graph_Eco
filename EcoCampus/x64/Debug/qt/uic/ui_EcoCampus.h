/********************************************************************************
** Form generated from reading UI file 'EcoCampus.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ECOCAMPUS_H
#define UI_ECOCAMPUS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EcoCampusClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EcoCampusClass)
    {
        if (EcoCampusClass->objectName().isEmpty())
            EcoCampusClass->setObjectName("EcoCampusClass");
        EcoCampusClass->resize(600, 400);
        menuBar = new QMenuBar(EcoCampusClass);
        menuBar->setObjectName("menuBar");
        EcoCampusClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EcoCampusClass);
        mainToolBar->setObjectName("mainToolBar");
        EcoCampusClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(EcoCampusClass);
        centralWidget->setObjectName("centralWidget");
        EcoCampusClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(EcoCampusClass);
        statusBar->setObjectName("statusBar");
        EcoCampusClass->setStatusBar(statusBar);

        retranslateUi(EcoCampusClass);

        QMetaObject::connectSlotsByName(EcoCampusClass);
    } // setupUi

    void retranslateUi(QMainWindow *EcoCampusClass)
    {
        EcoCampusClass->setWindowTitle(QCoreApplication::translate("EcoCampusClass", "EcoCampus", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EcoCampusClass: public Ui_EcoCampusClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ECOCAMPUS_H
