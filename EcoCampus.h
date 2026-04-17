#pragma once

#include <QtWidgets/QMainWindow>
#include <QGraphicsScene>
#include "ui_EcoCampus.h"
#include "CampusController.h"

class EcoCampus : public QMainWindow
{
    Q_OBJECT

public:
    EcoCampus(QWidget *parent = nullptr);
    ~EcoCampus();

private:
    Ui::EcoCampusClass ui;
    CampusController controller_;
    QGraphicsScene* scene_ = nullptr;

    void dibujarGrafo();

private slots:
    void on_btnDFS_clicked();
    void on_btnBFS_clicked();
    void on_chkMovilidad_stateChanged(int state);
    void onSceneSelectionChanged();
};

