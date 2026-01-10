#include "mainwindow.h"
#include <QMessageBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPainter>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    gameLogic = new game_logic(this);

    connect(gameLogic, &game_logic::wordSet,
            this, &MainWindow::onWordSet);
    connect(gameLogic, &game_logic::letterGuessed,
            this, &MainWindow::onLetterGuessed);
    connect(gameLogic, &game_logic::gameStateChanged,
            this, &MainWindow::onGameStateChanged);
    connect(gameLogic, &game_logic::errorsChanged,
            this, &MainWindow::onErrorsChanged);

    createHangmanImages();
    setupUI();
    setWindowTitle("Wisielec");
    resize(800, 600);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    stackedWidget->addWidget(createMenuWidget());
    stackedWidget->addWidget(createSetupWidget());
    stackedWidget->addWidget(createGameWidget());
}

QWidget* MainWindow::createMenuWidget()
{
    QWidget *widget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->setSpacing(20);
    layout->setAlignment(Qt::AlignCenter);

    QLabel *title = new QLabel("WISIELEC", this);
    QFont f = title->font();
    f.setPointSize(32);
    f.setBold(true);
    title->setFont(f);
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    QPushButton *btnSolo = new QPushButton("Gra Solo", this);
    btnSolo->setMinimumSize(200, 60);
    connect(btnSolo, &QPushButton::clicked, this, &MainWindow::startSoloGame);
    layout->addWidget(btnSolo);

    QPushButton *btnDuo = new QPushButton("Gra we Dwoje", this);
    btnDuo->setMinimumSize(200, 60);
    connect(btnDuo, &QPushButton::clicked, this, &MainWindow::startDuoMode);
    layout->addWidget(btnDuo);

    return widget;
}

QWidget* MainWindow::createSetupWidget()
{
    QWidget *widget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->setAlignment(Qt::AlignCenter);

    QLabel *info = new QLabel("Gracz 1: Wpisz słowo", this);
    info->setFont(QFont("Arial", 16));
    layout->addWidget(info);

    wordInput = new QLineEdit(this);
    wordInput->setEchoMode(QLineEdit::Password);
    wordInput->setMaximumWidth(400);
    layout->addWidget(wordInput);

    QPushButton *btnStart = new QPushButton("Start", this);
    btnStart->setMinimumHeight(50);
    btnStart->setMaximumWidth(200);
    connect(btnStart, &QPushButton::clicked, this, &MainWindow::confirmDuoWord);
    layout->addWidget(btnStart);

    QPushButton *btnBack = new QPushButton("Powrót", this);
    btnBack->setMaximumWidth(100);
    connect(btnBack, &QPushButton::clicked, this, &MainWindow::backToMenu);
    layout->addWidget(btnBack);

    return widget;
}

QWidget* MainWindow::createGameWidget()
{
    QWidget *widget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);

    QHBoxLayout *topBar = new QHBoxLayout();
    QPushButton *btnMenu = new QPushButton("Menu", this);
    connect(btnMenu, &QPushButton::clicked, this, &MainWindow::backToMenu);
    topBar->addWidget(btnMenu);
    topBar->addStretch();
    mainLayout->addLayout(topBar);

    QHBoxLayout *gameArea = new QHBoxLayout();

    QVBoxLayout *leftCol = new QVBoxLayout();
    hangmanLabel = new QLabel(this);
    hangmanLabel->setAlignment(Qt::AlignCenter);
    hangmanLabel->setStyleSheet("border: 2px solid #ccc; background: white;");
    leftCol->addWidget(hangmanLabel);

    errorsLabel = new QLabel("Błędy: 0/0", this);
    errorsLabel->setAlignment(Qt::AlignCenter);
    QFont errFont = errorsLabel->font();
    errFont.setPointSize(14);
    errorsLabel->setFont(errFont);
    leftCol->addWidget(errorsLabel);

    gameArea->addLayout(leftCol, 1);

    QVBoxLayout *rightCol = new QVBoxLayout();

    maskedWordLabel = new QLabel(this);
    maskedWordLabel->setAlignment(Qt::AlignCenter);
    QFont wordFont = maskedWordLabel->font();
    wordFont.setPointSize(24);
    wordFont.setBold(true);
    maskedWordLabel->setFont(wordFont);
    rightCol->addWidget(maskedWordLabel);

    statusLabel = new QLabel("Wybierz literę...", this);
    statusLabel->setAlignment(Qt::AlignCenter);
    rightCol->addWidget(statusLabel);

    QWidget *keyboardContainer = new QWidget();
    QGridLayout *grid = new QGridLayout(keyboardContainer);
    grid->setSpacing(5);

    QString letters = "AĄBCĆDEĘFGHIJKLŁMNŃOÓPQRSŚTUVWXYZŹŻ";
    int row = 0, col = 0;

    for (QChar c : letters) {
        QPushButton *btn = new QPushButton(QString(c), this);
        btn->setFixedSize(40, 40);
        btn->setStyleSheet("font-weight: bold; font-size: 14px;");
        connect(btn, &QPushButton::clicked, this, &MainWindow::onLetterButtonClicked);

        letterButtons[c] = btn;
        grid->addWidget(btn, row, col);

        col++;
        if (col > 8) {
            col = 0;
            row++;
        }
    }
    rightCol->addWidget(keyboardContainer);

    gameArea->addLayout(rightCol, 1);
    mainLayout->addLayout(gameArea);

    return widget;
}

void MainWindow::createHangmanImages()
{
    for (int i = 0; i <= 8; i++) {
        QPixmap pixmap(300, 400);
        pixmap.fill(Qt::white);
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        QPen pen(Qt::black, 4);
        painter.setPen(pen);

        if (i >= 0) painter.drawLine(50, 380, 250, 380);
        if (i >= 1) painter.drawLine(100, 380, 100, 50);
        if (i >= 2) painter.drawLine(100, 50, 200, 50);
        if (i >= 3) painter.drawLine(200, 50, 200, 100);
        if (i >= 4) painter.drawEllipse(175, 100, 50, 50);
        if (i >= 5) painter.drawLine(200, 150, 200, 250);
        if (i >= 6) painter.drawLine(200, 170, 160, 210);
        if (i >= 7) painter.drawLine(200, 170, 240, 210);
        if (i >= 8) {
            painter.drawLine(200, 250, 170, 320);
            painter.drawLine(200, 250, 230, 320);
            painter.setPen(QPen(Qt::red, 2));
            painter.drawArc(180, 125, 40, 20, 0, -180 * 16);
        }
        painter.end();
        hangmanImages[i] = pixmap;
    }
}

void MainWindow::startSoloGame()
{
    resetKeyboard();
    gameLogic->generateRandomWord();
    stackedWidget->setCurrentIndex(2);
}

void MainWindow::startDuoMode()
{
    wordInput->clear();
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::confirmDuoWord()
{
    QString word = wordInput->text();
    if (word.isEmpty()) return;

    if (!game_logic::isValidWord(word.toUpper())) {
        QMessageBox::warning(this, "Błąd", "Tylko litery i spacje");
        return;
    }

    if (!gameLogic->setWord(word)) {
        return;
    }

    resetKeyboard();
    stackedWidget->setCurrentIndex(2);
}

void MainWindow::backToMenu()
{
    gameLogic->resetGame();
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::resetKeyboard()
{
    for (auto btn : letterButtons) {
        btn->setEnabled(true);
        btn->setStyleSheet("font-weight: bold; font-size: 14px;");
    }
    updateHangmanImage();
}

void MainWindow::onLetterButtonClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    QChar c = btn->text()[0];
    gameLogic->guessLetter(c);
}

void MainWindow::onWordSet(const QString &maskedWord)
{
    maskedWordLabel->setText(maskedWord);
    statusLabel->setText("Zgaduj");
    updateHangmanImage();
}

void MainWindow::onLetterGuessed(QChar letter, bool correct)
{
    if (letterButtons.contains(letter)) {
        QPushButton *btn = letterButtons[letter];
        btn->setEnabled(false);
        if (correct) {
            btn->setStyleSheet("background-color: #4CAF50; color: white; font-weight: bold;");
        } else {
            btn->setStyleSheet("background-color: #f44336; color: white; font-weight: bold;");
        }
    }
    maskedWordLabel->setText(gameLogic->getMaskedWord());
    updateHangmanImage();
}

void MainWindow::onGameStateChanged(game_logic::GameState newState)
{
    if (newState == game_logic::GameState::Won || newState == game_logic::GameState::Lost) {
        showGameResult();
    }
}

void MainWindow::onErrorsChanged(int errors)
{
    errorsLabel->setText(QString("Błędy: %1/%2").arg(errors).arg(gameLogic->getMaxErrors()));
}

void MainWindow::updateHangmanImage()
{
    int currentErrors = gameLogic->getErrors();
    int maxErrors = gameLogic->getMaxErrors();

    int imageIndex = 0;

    if (currentErrors > 0 && maxErrors > 0) {
        float ratio = (float)currentErrors / (float)maxErrors;
        imageIndex = std::round(ratio * 8.0f);

        if (imageIndex == 0) imageIndex = 1;

        if (currentErrors >= maxErrors) imageIndex = 8;
    }

    if (hangmanImages.contains(imageIndex)) {
        hangmanLabel->setPixmap(hangmanImages[imageIndex]);
    }
}

void MainWindow::showGameResult()
{
    bool won = (gameLogic->getState() == game_logic::GameState::Won);
    QString msg = won ? "WYGRANA" : "PRZEGRANA";
    QString wordMsg = "\nSłowo: " + gameLogic->getWord();

    QMessageBox::information(this, "Koniec", msg + wordMsg);

    backToMenu();
}
