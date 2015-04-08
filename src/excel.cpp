#include "excel.h"

Excel::Excel(QString str) {

    int i = 1;
    dateCell  = "A%1";
    cardCell  = "B%1";
    nameCell  = "C%1";
    widthCell = "L%1";
    massCell  = "M%1";

    QXlsx::Document xlsx(str);

    while(!xlsx.read(dateCell.arg(i)).toString().isEmpty()) {
        orders.push_back(boost::make_tuple(xlsx.read(dateCell.arg(i)).toString(),
                                           xlsx.read(cardCell.arg(i)).toString(),
                                           xlsx.read(nameCell.arg(i)).toString(),
                                           xlsx.read(widthCell.arg(i)).toInt(),
                                           xlsx.read(massCell.arg(i)).toInt()));

        ++i;
    }

    //qDebug()<<QLocale("C").toDate(orders.at(0).get<0>(), QLatin1String("dd.MMM.yyyy"));
}

// = ==================================================================

std::vector<Order> Excel::getOrders() {

    return this->orders;
}


// ===================================================
