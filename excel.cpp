#include "excel.h"

Excel::Excel(QString str) {

    int i = 1;
    QXlsx::Document xlsx(str);
    qDebug()<<QString("A%1").arg(1);

    while(!xlsx.read(QString("A%1").arg(i)).toString().isEmpty()) {
        orders.push_back(boost::make_tuple(xlsx.read(QString("A%1").arg(i)).toString(),
                                           xlsx.read(QString("B%1").arg(i)).toString(),
                                           xlsx.read(QString("C%1").arg(i)).toString(),
                                           xlsx.read(QString("L%1").arg(i)).toInt(),
                                           xlsx.read(QString("M%1").arg(i)).toInt()));

        ++i;
    }

 
    qDebug()<<QLocale("C").toDate(orders.at(0).get<0>(), QLatin1String("dd.MMM.yyyy"));
  
}

// = ==================================================================

std::vector<Order> Excel::getOrders() {

    return this->orders;

}


// ===================================================
