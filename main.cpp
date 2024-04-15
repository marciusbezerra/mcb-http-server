#include <QCoreApplication>
#include "main.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    quint16 port = 8080;
    if (argc > 1) {
        port = QString(argv[1]).toUShort();
    }

    MCBHttpServer server(port);

    return a.exec();
}
