#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_EcoCampus.h"

class EcoCampus : public QMainWindow
{
    Q_OBJECT

public:
    EcoCampus(QWidget *parent = nullptr);
    ~EcoCampus();

private:
    Ui::EcoCampusClass ui;
};

