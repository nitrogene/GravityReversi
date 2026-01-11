#include <QApplication>
#include <QMainWindow>
#include <QLabel>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    QMainWindow window;
    window.setWindowTitle("Gravity Reversi");
    window.resize(800, 600);
    
    QLabel *label = new QLabel("🪐 Protocole Antigravity Initialisé", &window);
    label->setAlignment(Qt::AlignCenter);
    window.setCentralWidget(label);
    
    window.show();
    
    return app.exec();
}
