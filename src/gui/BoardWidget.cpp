#include "BoardWidget.h"
#include <QDebug>

BoardWidget::BoardWidget(QWidget *parent) : QWidget(parent) {
    setMinimumSize(400, 400);
}

void BoardWidget::setBoard(const BitBoard& board) {
    m_board = board;
    update();
}

void BoardWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int side = qMin(width(), height());
    int cellSize = side / BOARD_SIZE;
    int xOffset = (width() - side) / 2;
    int yOffset = (height() - side) / 2;

    // Background
    painter.fillRect(rect(), QColor(50, 50, 50));
    painter.fillRect(xOffset, yOffset, side, side, colorBoard);

    // Grid lines
    painter.setPen(QPen(colorGrid, 2));
    for (int i = 0; i <= BOARD_SIZE; ++i) {
        painter.drawLine(xOffset + i * cellSize, yOffset, xOffset + i * cellSize, yOffset + side);
        painter.drawLine(xOffset, yOffset + i * cellSize, xOffset + side, yOffset + i * cellSize);
    }

    // Pieces
    for (int i = 0; i < 64; ++i) {
        uint64_t mask = 1ULL << i;
        int row = i / BOARD_SIZE;
        int col = i % BOARD_SIZE;
        
        QRectF cellRect(xOffset + col * cellSize + 5, yOffset + row * cellSize + 5, cellSize - 10, cellSize - 10);

        if (m_board.black & mask) {
            painter.setBrush(colorBlack);
            painter.setPen(Qt::NoPen);
            painter.drawEllipse(cellRect);
        } else if (m_board.white & mask) {
            painter.setBrush(colorWhite);
            painter.setPen(Qt::NoPen);
            painter.drawEllipse(cellRect);
        }
    }
}

void BoardWidget::mousePressEvent(QMouseEvent *event) {
    int side = qMin(width(), height());
    int cellSize = side / BOARD_SIZE;
    int xOffset = (width() - side) / 2;
    int yOffset = (height() - side) / 2;

    if (event->x() >= xOffset && event->x() < xOffset + side &&
        event->y() >= yOffset && event->y() < yOffset + side) {
        
        int col = (event->x() - xOffset) / cellSize;
        int row = (event->y() - yOffset) / cellSize;
        int index = row * BOARD_SIZE + col;
        
        emit cellClicked(index);
    }
}
