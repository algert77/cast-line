#ifndef  EXCEL_H
#define  EXCEL_H
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


class Excel {

private:
    Orders orders;

public:
    Excel(QString string);
    std::vector<Order> getOrders();
};

#endif //EXCEL_H






