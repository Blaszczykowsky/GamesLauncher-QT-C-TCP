#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QStackedWidget>
#include <QMap>
#include "game_logic.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startSoloGame();
    void startDuoMode();
    void confirmDuoWord();
    void onLetterButtonClicked();
    void backToMenu();

    void onWordSet(const QString &maskedWord);
    void onLetterGuessed(QChar letter, bool correct);
    void onGameStateChanged(game_logic::GameState newState);
    void onErrorsChanged(int errors);

private:
    void setupUI();
    void createHangmanImages();
    void updateHangmanImage();
    void showGameResult();
    void resetKeyboard();

    QWidget* createMenuWidget();
    QWidget* createSetupWidget();
    QWidget* createGameWidget();

    game_logic *gameLogic;
    QStackedWidget *stackedWidget;

    QLineEdit *wordInput;

    QLabel *hangmanLabel;
    QLabel *maskedWordLabel;
    QLabel *errorsLabel;
    QLabel *statusLabel;
    QMap<QChar, QPushButton*> letterButtons;

    QMap<int, QPixmap> hangmanImages;
};

#endif
