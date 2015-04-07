#include "mainwindow.h"


MainWindow::MainWindow() {

    createMenu();
    createControls();

    setWindowTitle("Рассчет загрузки каст-линии");
    resize(800,400);
    show();
}


MainWindow::~MainWindow() {

}



int MainWindow::createMenu() {

    menuBar = new QMenuBar();
    fileMenu = new QMenu(tr("Файл"));
    editMenu = new QMenu(tr("Правка"));
    countMenu = new QMenu(tr("Расчет"));

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(editMenu);
    menuBar->addMenu(countMenu);
    setMenuBar(menuBar);

    createActions();
    return 1;
}



int MainWindow::createActions() {

    newAction = new QAction("Создать", this);
    setAction = new QAction("Изменить граничные значения", this);
    countAction = new QAction("Расчитать заказы", this);
    printAction = new QAction("Печать",this);

    fileMenu->addAction(newAction);
    fileMenu->addAction(printAction);
    editMenu->addAction(setAction);
    countMenu->addAction(countAction);
    connect(newAction, SIGNAL(triggered()), this, SLOT(fileDialog()));
    connect(setAction, SIGNAL(triggered()), this, SLOT(setVariables()));
    connect(countAction, SIGNAL(triggered()), this, SLOT(count_signal()));
    connect(printAction, SIGNAL(triggered()), this, SLOT(printOrders()));
    return 1;
}


int MainWindow::createControls() {

    return 1;
}


int MainWindow::clck_emit() {

    qDebug()<<"The clck signal from  the main window";
    return 1;
}



int MainWindow::fileDialog() {

    QFileDialog dialog(this);
    dialog.setNameFilter(tr("XLSX Files (*.xlsx)"));

    if ( dialog.exec()) {
        listFiles = dialog.selectedFiles();
        qDebug()<<"File name is "<<listFiles.at(0);
    }

    return 1;

}


// установка  граничных переменных
int MainWindow::setVariables() {

    QVBoxLayout* vert  = new QVBoxLayout();
    QHBoxLayout* hor1 = new QHBoxLayout();
    QHBoxLayout* hor2 = new QHBoxLayout();
    QHBoxLayout* hor3 = new QHBoxLayout();
    QHBoxLayout* hor4 = new QHBoxLayout();
    wgt = new QWidget();
    QLabel* label1 = new QLabel("Нижняя граница: ");
    QLabel* label2 = new QLabel("Верхняя граница:");
    down_text = new QLineEdit("1500");
    up_text  = new QLineEdit("1700");
    quant_text = new QLineEdit("0.3");
    QLabel* label5 = new QLabel("Изменение коэффициента времени: ");
    QLabel* label3 = new QLabel("    ");
    QPushButton* send  = new QPushButton("Ввести!");
    QLabel* label4 = new QLabel("  ");

    hor1->addWidget(label1);
    hor1->addWidget(down_text);
    hor2->addWidget(label2);
    hor2->addWidget(up_text);
    hor3->addWidget(label5);
    hor3->addWidget(quant_text);
    hor4->addWidget(label3);
    hor4->addWidget(send);
    hor4->addWidget(label4);
    
    vert->addLayout(hor1);
    vert->addLayout(hor2);
    vert->addLayout(hor3);
    vert->addLayout(hor4);
    connect(send, SIGNAL(clicked()), this, SLOT(pushButton()));
    wgt->setLayout(vert);
    wgt->show();
    return 1;
}


int MainWindow::pushButton() {

    int x = down_text->text().toInt();
    int y = up_text->text().toInt();
    double z = quant_text->text().toDouble();
    Graph::setVariables(x,y,z);

    QMessageBox message (QMessageBox::Warning, down_text->text(), up_text->text());
    message.exec();

    wgt->close();
    return 1;
}




QStandardItemModel* MainWindow::createStandardModel( const Nodes nodes , const Orders orders, const std::vector<std::pair <int, int> >  vec, const int modelIndex)  {

    int cols =  2;
    int rows = vec.size();
    qDebug()<<"the ----------- rows  ----- and cols "<<rows;
    std::cout<<modelIndex<<std::endl;
    QObject* parent = 0;
    QStandardItemModel* model = new QStandardItemModel(rows, cols, parent);

    int mod = 0;
    for(int i = 0; i < rows; ++i) {
        QStandardItem* item = new QStandardItem (nodes.at(i).first.get<0>() + "|  Номер карты:  " + nodes.at(i).first.get<1>() + " | Название:  " + nodes.at(i).first.get<2>() + " |  Ширина: "  + QString::number(nodes.at(i).first.get<3>()) + " мм   | Иcходный тираж:  " + QString::number( orders.at(vec.at(i).first).get<4>()) +  " кг    | Остаток тиража: " + QString::number(nodes.at(i).first.get<4>())  + " кг    | Время работы  пары:  " + nodes.at(i).first.get<5>());
        model->setItem(mod,0,item);
        ++mod;

        if(vec.at(i).second  ==  -1) {
            QStandardItem* item2 = new QStandardItem("Одиночный вывод!!!");
            model->setItem(mod,0,item2);
            ++mod;
        }

        else {

            QStandardItem* item2 = new QStandardItem (nodes.at(i).second.get<0>() + " | Номер карты: " + nodes.at(i).second.get<1>() + " | Название: " + nodes.at(i).second.get<2>() + "      |  Ширина:  " + QString::number(nodes.at(i).second.get<3>()) +  "мм  | Иcходный тираж: " + QString::number( orders.at(vec.at(i).second).get<4>()) +  "кг   | Остаток тиража: закончился "/* + QString::number(nodes.at(i).second.get<4>())   + "   | Время: " +  nodes.at(i).second.get<5>() */);
            model->setItem(mod,0,item2);
            ++mod;

        }


        QStandardItem* item3 = new QStandardItem(" ==============================");
        model->setItem(mod,0,item3);
        ++mod;
    }
    model->setHorizontalHeaderItem(0, new QStandardItem("Вывод!"));

    return model;
}



int MainWindow::count_signal() {


    if(listFiles.size() == 0 ) {

        QMessageBox message(QMessageBox::Warning,"The ","test");
        message.exec();
        return 0;
    }

    QMessageBox message(QMessageBox::Warning,listFiles.at(0),"CastList!");
    message.exec();

    Excel excel(listFiles.at(0));
    //   typedef boost::tuple<int,double> order;
    Graph* gr = new Graph(excel.getOrders());
    gr->getMatrice();
    //gr->makeGraph(excel.getOrders());
    gr->getRoutes();

    QStandardItemModel* modelS = createStandardModel(gr->getPairs(), excel.getOrders(),gr->getVector(),0);
    splitter = new QSplitter();
    tableView = new QTableView();
    tableView->setModel(modelS);
    tableView->resizeColumnToContents(0);
    splitter->resize(900,600);
    splitter->addWidget(tableView);
    setCentralWidget(splitter);

    return 1;
}



int MainWindow::printOrders() {

    QPrinter printer(QPrinter::HighResolution);

    qDebug()<<tableView->model()->rowCount();
    QMessageBox message (QMessageBox::Warning, QString(tableView->model()->rowCount()), QString(tableView->model()->columnCount()));
    message.exec();
    QPrintDialog* printDialog = new QPrintDialog(&printer, this);
    printDialog->setWindowTitle(tr("Печать карт"));

    if( printDialog->exec() == QDialog::Accepted)  {

        QPainter painter(&printer);
        QPixmap pixmap(600,800);
        QAbstractItemModel* model = tableView->model();
        for(int i = 0; i< 100; i++) {

            QModelIndex currentIndex = model->index(i, 0, tableView->rootIndex());
            painter.drawText(QPointF(0,i*300),currentIndex.data(Qt::TextAlignmentRole).toString());
        }
        painter.end();
    }
    return 1;
}
