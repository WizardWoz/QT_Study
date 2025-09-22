#include "serialportassistant.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SerialPortAssistant window;
    window.show();
    return app.exec();
}
