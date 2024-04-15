#ifndef MAIN_H
#define MAIN_H

#include <QtCore>
#include <QtNetwork>

class MCBHttpServer : public QObject {
    Q_OBJECT
public:
    MCBHttpServer(quint16 port, QObject *parent = nullptr) : QObject(parent), tcpServer(new QTcpServer(this)) {
        connect(tcpServer, &QTcpServer::newConnection, this, &MCBHttpServer::handleConnection);

        if (!tcpServer->listen(QHostAddress::Any, port)) {
            qCritical() << "Não foi possível iniciar o servidor na porta" << port;
            exit(EXIT_FAILURE);
        }

        qDebug() << "Servidor rodando na porta" << tcpServer->serverPort();
    }

private slots:
    void handleConnection() {
        QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
        connect(clientSocket, &QTcpSocket::readyRead, this, [this, clientSocket]() {
            QByteArray requestData = clientSocket->readAll();
            qDebug().noquote() << requestData;

            // Resposta simples para manter a conexão HTTP válida
            clientSocket->write("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nRequest recebida.\n");
            clientSocket->disconnectFromHost();
        });
    }

private:
    QTcpServer *tcpServer;
};

#endif // MAIN_H
