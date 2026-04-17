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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EcoCampusClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;
    QWidget *panelControls;
    QVBoxLayout *verticalLayout;
    QGroupBox *grpRecorridos;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *layoutInicio;
    QLabel *lblInicio;
    QSpinBox *spnInicio;
    QPushButton *btnDFS;
    QPushButton *btnBFS;
    QGroupBox *grpResultados;
    QFormLayout *formLayout;
    QLabel *labelTiempo;
    QLabel *lblTiempo;
    QLabel *labelVisitados;
    QLabel *lblVisitados;
    QCheckBox *chkMovilidad;
    QSpacerItem *verticalSpacer;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *EcoCampusClass)
    {
        if (EcoCampusClass->objectName().isEmpty())
            EcoCampusClass->setObjectName("EcoCampusClass");
        EcoCampusClass->resize(900, 600);
        menuBar = new QMenuBar(EcoCampusClass);
        menuBar->setObjectName("menuBar");
        EcoCampusClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(EcoCampusClass);
        mainToolBar->setObjectName("mainToolBar");
        EcoCampusClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(EcoCampusClass);
        centralWidget->setObjectName("centralWidget");
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setMinimumSize(QSize(400, 300));

        horizontalLayout->addWidget(graphicsView);

        panelControls = new QWidget(centralWidget);
        panelControls->setObjectName("panelControls");
        verticalLayout = new QVBoxLayout(panelControls);
        verticalLayout->setObjectName("verticalLayout");
        grpRecorridos = new QGroupBox(panelControls);
        grpRecorridos->setObjectName("grpRecorridos");
        verticalLayout_2 = new QVBoxLayout(grpRecorridos);
        verticalLayout_2->setObjectName("verticalLayout_2");
        layoutInicio = new QHBoxLayout();
        layoutInicio->setObjectName("layoutInicio");
        lblInicio = new QLabel(grpRecorridos);
        lblInicio->setObjectName("lblInicio");

        layoutInicio->addWidget(lblInicio);

        spnInicio = new QSpinBox(grpRecorridos);
        spnInicio->setObjectName("spnInicio");
        spnInicio->setMinimum(1);

        layoutInicio->addWidget(spnInicio);

        verticalLayout_2->addLayout(layoutInicio);

        btnDFS = new QPushButton(grpRecorridos);
        btnDFS->setObjectName("btnDFS");

        verticalLayout_2->addWidget(btnDFS);

        btnBFS = new QPushButton(grpRecorridos);
        btnBFS->setObjectName("btnBFS");

        verticalLayout_2->addWidget(btnBFS);

        verticalLayout->addWidget(grpRecorridos);

        grpResultados = new QGroupBox(panelControls);
        grpResultados->setObjectName("grpResultados");
        formLayout = new QFormLayout(grpResultados);
        formLayout->setObjectName("formLayout");
        labelTiempo = new QLabel(grpResultados);
        labelTiempo->setObjectName("labelTiempo");

        formLayout->setWidget(0, QFormLayout::LabelRole, labelTiempo);

        lblTiempo = new QLabel(grpResultados);
        lblTiempo->setObjectName("lblTiempo");

        formLayout->setWidget(0, QFormLayout::FieldRole, lblTiempo);

        labelVisitados = new QLabel(grpResultados);
        labelVisitados->setObjectName("labelVisitados");

        formLayout->setWidget(1, QFormLayout::LabelRole, labelVisitados);

        lblVisitados = new QLabel(grpResultados);
        lblVisitados->setObjectName("lblVisitados");

        formLayout->setWidget(1, QFormLayout::FieldRole, lblVisitados);

        verticalLayout->addWidget(grpResultados);

        chkMovilidad = new QCheckBox(panelControls);
        chkMovilidad->setObjectName("chkMovilidad");

        verticalLayout->addWidget(chkMovilidad);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout->addWidget(panelControls);

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
        grpRecorridos->setTitle(QCoreApplication::translate("EcoCampusClass", "Recorridos", nullptr));
        lblInicio->setText(QCoreApplication::translate("EcoCampusClass", "Inicio", nullptr));
        btnDFS->setText(QCoreApplication::translate("EcoCampusClass", "DFS", nullptr));
        btnBFS->setText(QCoreApplication::translate("EcoCampusClass", "BFS", nullptr));
        grpResultados->setTitle(QCoreApplication::translate("EcoCampusClass", "Resultados", nullptr));
        labelTiempo->setText(QCoreApplication::translate("EcoCampusClass", "Tiempo", nullptr));
        lblTiempo->setText(QCoreApplication::translate("EcoCampusClass", "0 \302\265s", nullptr));
        labelVisitados->setText(QCoreApplication::translate("EcoCampusClass", "Visitados", nullptr));
        lblVisitados->setText(QCoreApplication::translate("EcoCampusClass", "0", nullptr));
        chkMovilidad->setText(QCoreApplication::translate("EcoCampusClass", "Movilidad Reducida", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EcoCampusClass: public Ui_EcoCampusClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ECOCAMPUS_H
