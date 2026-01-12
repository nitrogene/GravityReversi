#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include "../core/BitBoard.h"

/**
 * @brief The BoardWidget class renders the Reversi board and handles clicks.
 */
class BoardWidget : public QWidget {
    Q_OBJECT
public:
    explicit BoardWidget(QWidget *parent = nullptr);

    void setBoard(const BitBoard& board);

signals:
    void cellClicked(int index);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    BitBoard m_board;
    static constexpr int BOARD_SIZE = 8;
    
    // Aesthetic constants
    const QColor colorBoard = QColor(34, 139, 34); // Forest Green
    const QColor colorGrid = QColor(0, 100, 0);   // Dark Green
    const QColor colorBlack = QColor(20, 20, 20);
    const QColor colorWhite = QColor(240, 240, 240);
};

#endif // BOARDWIDGET_H
