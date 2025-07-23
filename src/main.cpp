#include "UI/MainWindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <QPalette>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("HabitLoom");
    app.setApplicationDisplayName("HabitLoom - Si Pelacak Kebiasaan Sarkastik");

    // Set dark palette as base
    app.setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    app.setPalette(darkPalette);

    MainWindow window;
    window.resize(800, 600);
    window.show();

    return app.exec();
}