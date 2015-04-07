#include "excel.h"
#include "graph.h"
#include "mainwindow.h"
#include <QtGui>
#include <QApplication>
#include <QTableView>
#include <QStandardItemModel>
#include <QSplitter>



int main(int argc, char* argv[]) {

    QApplication app(argc, argv);
    MainWindow wnd ;//= new MainWindow();

    return app.exec();
}
