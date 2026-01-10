// #ifndef GAME_NETWORK_ADAPTER_H
// #define GAME_NETWORK_ADAPTER_H

// #include <QObject>
// #include <QWebSocket>
// #include <QJsonObject>
// #include "game_logic.h"



// class GameNetworkAdapter : public QObject
// {
//     Q_OBJECT

// public:
//     explicit GameNetworkAdapter(WisielecGameLogic *logic, QObject *parent = nullptr);

//     // Połączenie z serwerem
//     void connectToServer(const QString &url);
//     void disconnect();

//     // Wysyłanie akcji
//     void sendSetWord(const QString &word);
//     void sendGuess(QChar letter);

//     bool isConnected() const;

// signals:
//     void connected();
//     void disconnected();
//     void error(const QString &message);
//     void serverMessage(const QString &message);

// private slots:
//     void onConnected();
//     void onDisconnected();
//     void onTextMessageReceived(const QString &message);
//     void onSocketError();

//     void onWordSetLocally(const QString &maskedWord);
//     void onLetterGuessedLocally(QChar letter, bool correct);

// private:
//     WisielecGameLogic *gameLogic;
//     QWebSocket socket;

//     void sendJson(const QJsonObject &obj);
//     void handleServerMessage(const QJsonObject &obj);
// };

// #endif // GAME_NETWORK_ADAPTER_H
