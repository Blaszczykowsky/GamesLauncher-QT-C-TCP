// #include "game_network_adapter.h"
// #include <QJsonDocument>

// GameNetworkAdapter::GameNetworkAdapter(WisielecGameLogic *logic, QObject *parent)
//     : QObject(parent), gameLogic(logic)
// {
//     // Połącz sygnały WebSocket
//     connect(&socket, &QWebSocket::connected, this, &GameNetworkAdapter::onConnected);
//     connect(&socket, &QWebSocket::disconnected, this, &GameNetworkAdapter::onDisconnected);
//     connect(&socket, &QWebSocket::textMessageReceived, this, &GameNetworkAdapter::onTextMessageReceived);
//     connect(&socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::errorOccurred),
//             this, &GameNetworkAdapter::onSocketError);

//     // Opcjonalnie: Śledź lokalne zmiany i wysyłaj na serwer
//     connect(gameLogic, &WisielecGameLogic::wordSet,
//             this, &GameNetworkAdapter::onWordSetLocally);
//     connect(gameLogic, &WisielecGameLogic::letterGuessed,
//             this, &GameNetworkAdapter::onLetterGuessedLocally);
// }

// void GameNetworkAdapter::connectToServer(const QString &url)
// {
//     socket.open(QUrl(url));
// }

// void GameNetworkAdapter::disconnect()
// {
//     socket.close();
// }

// void GameNetworkAdapter::sendSetWord(const QString &word)
// {
//     QJsonObject obj;
//     obj["typ"] = "set_word";
//     obj["slowo"] = word;
//     sendJson(obj);
// }

// void GameNetworkAdapter::sendGuess(QChar letter)
// {
//     QJsonObject obj;
//     obj["typ"] = "guess";
//     obj["litera"] = QString(letter);
//     sendJson(obj);
// }

// bool GameNetworkAdapter::isConnected() const
// {
//     return socket.state() == QAbstractSocket::ConnectedState;
// }

// void GameNetworkAdapter::onConnected()
// {
//     emit connected();

//     // Wyślij hello message
//     QJsonObject hello;
//     hello["typ"] = "hello";
//     hello["nazwa"] = "Gracz";
//     sendJson(hello);
// }

// void GameNetworkAdapter::onDisconnected()
// {
//     emit disconnected();
// }

// void GameNetworkAdapter::onTextMessageReceived(const QString &message)
// {
//     QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
//     if (doc.isObject()) {
//         handleServerMessage(doc.object());
//     }
// }

// void GameNetworkAdapter::onSocketError()
// {
//     emit error(socket.errorString());
// }

// void GameNetworkAdapter::onWordSetLocally(const QString &maskedWord)
// {
//     // Słowo zostało ustawione lokalnie - opcjonalnie wyślij na serwer
//     Q_UNUSED(maskedWord);
// }

// void GameNetworkAdapter::onLetterGuessedLocally(QChar letter, bool correct)
// {
//     // Litera została zgadnięta lokalnie - opcjonalnie wyślij na serwer
//     Q_UNUSED(letter);
//     Q_UNUSED(correct);
// }

// void GameNetworkAdapter::sendJson(const QJsonObject &obj)
// {
//     if (!isConnected()) return;

//     QString message = QString::fromUtf8(QJsonDocument(obj).toJson(QJsonDocument::Compact));
//     socket.sendTextMessage(message);
// }

// void GameNetworkAdapter::handleServerMessage(const QJsonObject &obj)
// {
//     QString typ = obj.value("typ").toString();

//     if (typ == "state") {
//         // Zaktualizuj stan gry na podstawie wiadomości z serwera
//         // gameLogic->... (zależnie od protokołu)
//     }
//     else if (typ == "info" || typ == "error") {
//         emit serverMessage(obj.value("wiadomosc").toString());
//     }
//     // ... inne typy wiadomości
// }
