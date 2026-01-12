#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QStatusBar>
#include "../agents/RandomAgent.h"
#include "../agents/GreedyAgent.h"
#include "../agents/MinimaxAgent.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Gravity Reversi - Antigravity Protocol");
    resize(700, 750);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Setup Selection UI
    QHBoxLayout *topLayout = new QHBoxLayout();
    
    m_blackTypeCombo = new QComboBox(this);
    m_blackTypeCombo->addItem("Humain", "human");
    m_blackTypeCombo->addItem("Random Agent", "random");
    m_blackTypeCombo->addItem("Greedy Agent", "greedy");
    m_blackTypeCombo->addItem("Minimax Agent (d=5)", "minimax");
    
    m_whiteTypeCombo = new QComboBox(this);
    m_whiteTypeCombo->addItem("Humain", "human");
    m_whiteTypeCombo->addItem("Random Agent", "random");
    m_whiteTypeCombo->addItem("Greedy Agent", "greedy");
    m_whiteTypeCombo->addItem("Minimax Agent (d=5)", "minimax");

    m_newGameButton = new QPushButton("Nouvelle Partie", this);
    
    topLayout->addWidget(new QLabel("Noir :"));
    topLayout->addWidget(m_blackTypeCombo);
    topLayout->addStretch();
    topLayout->addWidget(m_newGameButton);
    topLayout->addStretch();
    topLayout->addWidget(new QLabel("Blanc :"));
    topLayout->addWidget(m_whiteTypeCombo);

    mainLayout->addLayout(topLayout);

    QHBoxLayout *contentLayout = new QHBoxLayout();
    
    m_boardWidget = new BoardWidget(this);
    contentLayout->addWidget(m_boardWidget, 3);

    m_historyList = new QListWidget(this);
    m_historyList->setMaximumWidth(150);
    contentLayout->addWidget(m_historyList, 1);

    mainLayout->addLayout(contentLayout);

    setCentralWidget(centralWidget);

    connect(m_boardWidget, &BoardWidget::cellClicked, this, &MainWindow::handleCellClicked);
    connect(m_blackTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::handlePlayerTypeChanged);
    connect(m_whiteTypeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::handlePlayerTypeChanged);
    connect(m_newGameButton, &QPushButton::clicked, this, &MainWindow::resetGame);

    m_board.reset();
    m_boardWidget->setBoard(m_board);
    
    setupPlayers();
    updateStatusBar();
}

MainWindow::~MainWindow() {
    delete m_blackPlayer;
    delete m_whitePlayer;
}

void MainWindow::setupPlayers() {
    QString blackType = m_blackTypeCombo->currentData().toString();
    QString whiteType = m_whiteTypeCombo->currentData().toString();

    // Only recreate if type changed
    auto createAgent = [this](IPlayer*& player, const QString& type, bool isWhite) {
        bool typeChanged = false;
        if (type == "human") {
            if (player != nullptr) {
                delete player;
                player = nullptr;
                typeChanged = true;
            }
        } else if (type == "random") {
            if (player == nullptr || player->name().contains("Random") == false) {
                delete player;
                player = new RandomAgent(isWhite, this);
                typeChanged = true;
            }
        } else if (type == "greedy") {
            if (player == nullptr || player->name().contains("Greedy") == false) {
                delete player;
                player = new GreedyAgent(isWhite, this);
                typeChanged = true;
            }
        } else if (type == "minimax") {
            if (player == nullptr || !player->name().contains("Minimax")) {
                delete player;
                player = new MinimaxAgent(isWhite, 5, this);
                typeChanged = true;
            }
        }
        
        if (typeChanged && player) {
            connect(dynamic_cast<QObject*>(player), SIGNAL(moveSelected(int)), this, SLOT(onAgentMoveSelected(int)));
        }
    };

    createAgent(m_blackPlayer, blackType, false);
    createAgent(m_whitePlayer, whiteType, true);

    // Trigger current agent if it's their turn
    IPlayer* currentPlayer = m_isWhiteTurn ? m_whitePlayer : m_blackPlayer;
    if (currentPlayer) {
        startAgentTurn();
    }
}

void MainWindow::handlePlayerTypeChanged() {
    // Optionally restart game or just update current players
    // For now, let's just update and see if it's the AI's turn
    setupPlayers();
}

void MainWindow::handleCellClicked(int index) {
    // Ignore click if it's an AI's turn
    IPlayer* currentPlayer = m_isWhiteTurn ? m_whitePlayer : m_blackPlayer;
    if (currentPlayer) return;

    uint64_t moves = m_board.getPossibleMoves(m_isWhiteTurn);
    uint64_t moveBit = 1ULL << index;

    if (moves & moveBit) {
        updateHistory(index, m_isWhiteTurn);
        m_board.makeMove(index, m_isWhiteTurn);
        m_isWhiteTurn = !m_isWhiteTurn;
        m_boardWidget->setBoard(m_board);
        updateStatusBar();
        
        checkGameOver();
    } else {
        statusBar()->showMessage("Coup invalide !", 2000);
    }
}

void MainWindow::onAgentMoveSelected(int index) {
    // Ensure it's still the correct turn and it's an AI
    IPlayer* currentPlayer = m_isWhiteTurn ? m_whitePlayer : m_blackPlayer;
    if (!currentPlayer) return;

    if (index != -1) {
        updateHistory(index, m_isWhiteTurn);
        m_board.makeMove(index, m_isWhiteTurn);
    }
    
    m_isWhiteTurn = !m_isWhiteTurn;
    m_boardWidget->setBoard(m_board);
    updateStatusBar();
    
    checkGameOver();
}

void MainWindow::startAgentTurn() {
    IPlayer* currentPlayer = m_isWhiteTurn ? m_whitePlayer : m_blackPlayer;
    if (currentPlayer) {
        currentPlayer->requestMove(m_board);
    }
}

void MainWindow::updateStatusBar() {
    QString turn = m_isWhiteTurn ? "BLANC" : "NOIR";
    IPlayer* p = m_isWhiteTurn ? m_whitePlayer : m_blackPlayer;
    QString type = p ? p->name() : "Humain";
    statusBar()->showMessage(QString("Tour : %1 (%2)").arg(turn).arg(type));
}

void MainWindow::checkGameOver() {
    if (m_board.getPossibleMoves(m_isWhiteTurn) == 0) {
        m_isWhiteTurn = !m_isWhiteTurn;
        if (m_board.getPossibleMoves(m_isWhiteTurn) == 0) {
            // Game Over
            int black = m_board.getPieceCount(false);
            int white = m_board.getPieceCount(true);
            QString winner = (black > white) ? "NOIR" : (white > black ? "BLANC" : "ÉGALITÉ");
            QMessageBox::information(this, "Fin de partie", 
                QString("Partie terminée !\nNoir: %1\nBlanc: %2\nGagnant: %3").arg(black).arg(white).arg(winner));
            return;
        } else {
            statusBar()->showMessage("Passe le tour. Tour : " + QString(m_isWhiteTurn ? "BLANC" : "NOIR"));
        }
    }
    
    // If next player is an agent, trigger it
    IPlayer* nextPlayer = m_isWhiteTurn ? m_whitePlayer : m_blackPlayer;
    if (nextPlayer) {
        startAgentTurn();
    }
}

void MainWindow::resetGame() {
    m_board.reset();
    m_isWhiteTurn = false;
    m_historyList->clear();
    m_boardWidget->setBoard(m_board);
    setupPlayers();
    updateStatusBar();
}

void MainWindow::updateHistory(int index, bool isWhite) {
    if (index == -1) return;
    
    char col = 'A' + (index % 8);
    int row = (index / 8) + 1;
    QString colorStr = isWhite ? "B" : "N";
    m_historyList->addItem(QString("%1: %2%3").arg(colorStr).arg(col).arg(row));
    m_historyList->scrollToBottom();
}
