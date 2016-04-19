#ifndef __REDHARE__CLIENTSOCKET__H__
#define __REDHARE__CLIENTSOCKET__H__

#include <QTcpSocket>

class ClientSocket: public QObject
{
    Q_OBJECT
public:
    void connectToServer(const QHostAddress &address, quint16 port);
    void disconnectFromServer();
    static ClientSocket* instance();
signals:
    void sigSocketError(const QString &error);
    void sigSocketConnected();
    void sigSocketDisconnected();
    void sigSignupResult(const QVariant &result);
    void sigLoginResult(const QVariant &result);
public:
    void signup(const QString &username, const QString &password);
    void login(const QString &username, const QString &password);
private:

};

#endif // __REDHARE__CLIENTSOCKET__H__

