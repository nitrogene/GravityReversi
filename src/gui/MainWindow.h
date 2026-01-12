#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QPushButton>
#include <QListWidget>
#include "BoardWidget.h"
#include "../core/BitBoard.h"
#include "../agents/IPlayer.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleCellClicked(int index);
    void handlePlayerTypeChanged();
    void onAgentMoveSelected(int index);
    void resetGame();

private:
    void updateStatusBar();
    void checkGameOver();
    void startAgentTurn();
    void setupPlayers();
    void updateHistory(int index, bool isWhite);


    BoardWidget *m_boardWidget;
    BitBoard m_board;
    bool m_isWhiteTurn = false;

    IPlayer* m_blackPlayer = nullptr;
    IPlayer* m_whitePlayer = nullptr;

    QComboBox* m_blackTypeCombo;
    QComboBox* m_whiteTypeCombo;
    QPushButton* m_newGameButton;
    QListWidget* m_historyList;
};

#endif // MAINWINDOW_H
