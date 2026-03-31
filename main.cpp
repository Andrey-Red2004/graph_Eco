#include "EcoCampus.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    EcoCampus window;
    window.show();
    return app.exec();
}
