#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "excel.h"
#include  "graph.h"

#include <QMainWindow>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QLabel>
#include <QLineEdit>
#include <QAction>
#include <QVBoxLayout>
#include <QWidget>
#include <QTableView>
#include <QLineEdit>
#include <QDebug>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QSplitter>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QRect>

class MainWindow : public QMainWindow {

    Q_OBJECT
public:
    MainWindow();
    ~MainWindow();
    int createControls();
    int createMenu();
    int createActions();
    QStandardItemModel* createStandardModel(const Nodes, const Orders, const  std::vector<std::pair <int, int> >, const int);

public slots:
    int pushButton();
    int clck_emit();
    int fileDialog();
    int setVariables();
    int count_signal();
    int printOrders();

private:
    QAction* newAction;
    QAction* fileAction;
    QAction* setAction;
    QAction* countAction;
    QAction* printAction;

    QMenuBar* menuBar;
    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* countMenu;

    QSplitter* splitter;
    QTableView* tableView;

    QStringList listFiles;
    QWidget* wgt;
    QLineEdit* down_text;
    QLineEdit* up_text;
    QLineEdit* quant_text;
    int up;
    int down;

signals:
    void clck();
    void signal_to_count();
};


#endif //MAINWINDOW_H
