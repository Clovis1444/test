#include <qscreen.h>

#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a{argc, argv};
    MainWindow w;
    w.setWindowTitle("Program");

    QRect s_rect{QApplication::primaryScreen()->geometry()};
    QRect w_rect{w.frameGeometry()};

    // Center application window
    w.setGeometry((s_rect.width() / 2) - (w_rect.width() / 2),
                  (s_rect.height() / 2) - (w.height() / 2), w.width(),
                  w.height());

    w.show();

    return QApplication::exec();
}
