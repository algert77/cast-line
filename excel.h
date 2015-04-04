#ifndef  TERWE_H
#define  TERWE_H 
#include <QtGui>
#include <QtXlsx>
#include <QString>
#include <QVariant>
#include <QDateTime>
#include <QLocale>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <utility>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <functional>

typedef QString DATE_STRING ; //дата окончания заказа
typedef QString NAME_STRING; //наименование заказа
typedef QString CARD_STRING; // Номер карты
typedef QString TIME_STRING; // время работы пары
typedef double TIMETYPE;

typedef boost::tuple<DATE_STRING,NAME_STRING,CARD_STRING,int,int> Order;
typedef std::vector<Order> Orders;

typedef boost::tuple<DATE_STRING,NAME_STRING,CARD_STRING, int, int, TIME_STRING> NodeOrder;
typedef std::pair<NodeOrder, NodeOrder> Node;
typedef std::vector<Node> Nodes;


typedef struct {
    QString name;
    QString card;
    QString date;
    int width;
    double quant;
} orders_s;



class Excel {
private:
    int testmain;

    // typedef boost::tuple<QString ,QString,QString,int,double> order;
    Orders orders;


public:
    Excel(QString string);
    std::vector<Order> getOrders();
};







#endif






