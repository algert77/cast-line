#include "graph.h"

//define  static members:
Orders Graph::orders   (0);
std::vector <std::vector<int> > Graph::matrice(0);
//static std::vector<std::vector<int> >::iterator out (0);
//static std::vector<int>::iterator in (0);
std::vector<int>  Graph::inVec(0);
int Graph::reciter = 0;
int Graph::calc = 0;
int Graph::matr = 0;
int Graph::up = 1700;
int Graph::down = 1500; 
double Graph::dt = 0.3 ;  // (Kgramm / mm * hour)
//========================================

int Graph::setVariables(int x, int y, double z) {

    down = x;
    up = y;
    dt = z;
    return 1;
}


// ==================== cons ======================
Graph::Graph(const Orders ord ) {

    orders = ord;
    for_each1(orders.begin(), orders.end(), recIter);
}



int  Graph::calculate( Orders::iterator r, int index, int h) {

    calc  =  calc +1;
    if( h ==0) {
        return (orders.at(index).get<4>()  /  orders.at(index).get<3>()  - r->get<4>() /  r->get<3>()) ;

    }
    else
        return (orders.at(index).get<4>() / orders.at(index).get<3>());
}



// ==== 
//2  Vertices, timeline 



bool Graph::makeMatrice( Orders::iterator r, int index){

    int result;
    //index must be constant while recIter!
    matr = matr + 1;
    int n  = std::distance(orders.begin(),r);

    if(index == n) {
        result = calculate(r, index, 1);
        // std::cout << "the diagonal index is  - " <<result<< std::endl;
    }
    else if ((r->get<3>() + orders.at(index).get<3>() >= down) &&  (r->get<3>() + orders.at(index).get<3>()) <= up ) {

        result = calculate(r, index);
    }
    else result = 0;

    inVec.push_back(result);

    return false;
}



int Graph::recIter( Orders::iterator r) {

    //int p;
    // int result;
    reciter = reciter + 1;
    int index  = std::distance(orders.begin(),r);
    //
    find_if2(orders.begin(),orders.end(),index, makeMatrice);
    matrice.push_back(inVec);
    inVec.resize(0);

    return 1;
}



int Graph::getMatrice() {

    std::vector< std::vector<int> >::iterator out;
    std::vector<int>::iterator in;

    for (out = matrice.begin(); out != matrice.end(); ++out) {
        for(in  = out->begin(); in != out->end(); ++in){
            int index = std::distance(out->begin(), in);
            std::cout <<"||"<<index<< "|| "<< out->at(index)<<std::setw(7);
        }
    }

    std::cout << "reciter  - " <<reciter<<  std::endl;
    std::cout << "calc  - " <<calc<<  std::endl;
    std::cout << "matr  - " <<reciter<<  std::endl;
    std::cout << "And size of matrice is - "<<matrice.size()<<std::endl;
    return 1;
}



int Graph::calcIter() {
    // iter;
    std::cout<<" 100x100 elem is  - "<<matrice.at(1).at(14)<<std::endl;
    // int index  = std::distance(orders.begin(),iter);
    std::cout << "\n" << std::endl;
    //find_if100(vec.begin(),vec.end(),recIter);

    //for_each2(orders.begin(), orders.end(), index, recIter);
    return 1;
}



//make the routes through graphs
int Graph::getRoutes(){

    std::vector<int>::iterator in;
    std::cout << "size of orders is -  "<<orders.size() << std::endl;
    //int  = 0;
    //for(out = matrice.begin(); out != matrice.end(); ++out) {
    /// while cycle~~~~~~~~~~~~~~~~~~~~~~~~~
    out_index = 0;
    TIMETYPE temp = 0.0;

    while(out_index < orders.size()) {
        //int  i = 0;

        if(matrice.at(out_index).at(out_index) != 0) {
            std::cout << "in diagonal  index is - " <<matrice.at(out_index).at(out_index)<<"And index is  - "<<out_index<<std::endl;
            // temp = orders.at(out_index).get<3>() * orders.at(out_index).get<4>();
            temp =(TIMETYPE)  orders.at(out_index).get<4>() / ( orders.at(out_index).get<3>() );

            for(in_index = 0; in_index < orders.size(); ++in_index) {

                if ((matrice.at(out_index).at(in_index) == 0   && temp != 0) ) {

                    if(in_index == (orders.size() -1)) {
                        std::cout << "OUUUUUTTTT  - in_index is  " << in_index<< "and the out_index is "<<out_index << std::endl;
                        qDebug()<<"Not Pair    " << orders.at(out_index).get<1>();
                        //i = 0;
                        pairVec.push_back(std::pair<int,int>(out_index,-1));
                        tiraz(temp, 0 , temp, out_index, 0);
                        //vecChange.push_back
                        setZeroColStr(out_index);
                        temp = 0.0;
                        out_index = 0;
                        break;
                    }
                }

                else  if (in_index == out_index) {
                    std::cout << "Skip!! - " <<in_index << "And out_index - "<<out_index<< " and temp is  - "<<temp<<std::endl;
                    // ++i;

                    if(in_index == orders.size() - 1) {
                        tiraz(temp, 0 , temp, out_index, 0);
                        std::cout<<"Одиночный вывод!!!!!!: "<<std::endl;
                        qDebug() <<"The pair is  - "<<orders.at(in_index).get<1>();
                        pairVec.push_back(std::pair<int,int> (in_index,-1));
                        temp = 0.0;
                        setZeroColStr(in_index);
                        out_index = 0;
                        in_index  = 0;
                    }
                }

                else {

                    if(temp == 0.0 ){ break;}
                    temp = getNode(temp, out_index, in_index);
                    //in = out->begin();
                }
            } //inner for-cycle in columns
        } // endif

        else {
            ++out_index;
        }
    } //outer for-cycle in strings
    std::cout << "The algorithm is ended up!" << std::endl;
    return 1;
}



int Graph::makeGraph(const std::vector<Order> orders) {

    std::cout << "The make graph_function!!" << std::endl;
    qDebug()<< "And the meaning of second arrays  is  - " << orders.at(4).get<0>();
    return 0;
}



TIMETYPE Graph::getNode(TIMETYPE temp, int index_temp, int index_second) {

    qDebug() << "Pair is  - " << orders.at(index_temp).get<1>() << " and: "<<orders.at(index_second).get<1>();
    TIMETYPE  power =(TIMETYPE) orders.at(index_second).get<4>() /(  orders.at(index_second).get<3>() );

    if (temp  > power) {
        pairVec.push_back(std::pair<int, int> (index_temp, index_second));
        tiraz(temp, power,  temp - power, index_temp, index_second);
        setZeroColStr(index_second);
        //index_second = 0;
        in_index = 0;
        return (temp - power);
    }

    else if(power > temp) {
        pairVec.push_back(std::pair<int, int>(index_second, index_temp));
        tiraz(power , temp, power - temp,  index_second, index_temp);
        setZeroColStr(index_temp);
        out_index = index_second;
        in_index = 0;
        return (power - temp);
    }

    else {
        pairVec.push_back(std::pair <int, int>(index_second, index_temp));
        std::cout << "power of both orders equals ZERO!" << std::endl;
        out_index = 0;
        in_index = 0;
        return 0.0;
    }
}


 
int Graph::setZeroColStr(int index) {

    std::vector <std::vector <int> >::iterator outNull;
    for(outNull = matrice.begin(); outNull !=matrice.end(); ++outNull) {
        outNull->at(index) = 0;
    }
    
    for(unsigned int i = 0; i < orders.size(); i++){
        matrice.at(index).at(i) = 0;
        // for(out = matrice.at(index));
    }
    return 0;
}

/*

int Graph::matrIter(() {

    out = matrice.begin() && in = out->begin();
    ++out && ++in
      for (out = matrice.begin(); out != matrice.end(); ++out) {
        in.
*/

std::vector<std::pair <int, int> > Graph::getVector() {

    return pairVec;
}



//tempAfter - остаток tempOne - победитель (большее значение мб power ) , tempTwo  - проигравший  - меньшее значение
int Graph::tiraz(TIMETYPE tempOne, TIMETYPE tempTwo , TIMETYPE tempAfter, int master_index, int slave_index) {

    Node node;
    TIMETYPE mass_pair;
    //double dt = 0.3; //
    //производительность за час - коэффициент * ширину пары
    double product =(double) dt * ( orders.at(master_index).get<3>()  + orders.at(slave_index).get<3>()); //производительность за час  в Кграммах
    //tempAfter  - это  относительное время.
    TIMETYPE  dmPred  =  (double) tempAfter  *    orders.at(master_index).get<3>(); // остаток тиража, победившего в паре

    if( slave_index ==0){
        mass_pair = (double) tempOne *  orders.at(master_index).get<3>() ;
    }

    else {
        mass_pair =(double) tempOne *  orders.at(master_index).get<3>() + tempTwo *  orders.at(slave_index).get<3>() -  tempAfter *  orders.at(master_index).get<3>();
    }

    double timePred =  mass_pair / product; //  вычисление времени работы пары
    int minutes = (int) ( ( timePred - (int) timePred) * 100 ) * 60  /  100; //  (int) (  (ter  - (int) ter) * 100);
    QTime timeS((int)timePred, minutes);

    // if(slave_index == 0) {
    // node  =  std::make_pair( boost::make_tuple(orders.at(master_index).get<0>(),orders.at(master_index).get<1>(),orders.at(master_index).get<2>(),orders.at(master_index).get<3>(),(int)dmPred, timeS.toString()) , boost::make_tuple("----","-----","||||",NULL,NULL,""));
    // }

    //else  {
    node = std::make_pair(boost::make_tuple(orders.at(master_index).get<0>(), orders.at(master_index).get<1>(), orders.at(master_index).get<2>(), orders.at(master_index).get<3>(), dmPred, timeS.toString() ),  boost::make_tuple(orders.at(slave_index).get<0>(),orders.at(slave_index).get<1>(),orders.at(slave_index).get<2>(),orders.at(slave_index).get<3>(),0, "000") );
    //	}
    vecNode.push_back(node);
    //	qDebug()<<orders.at(master_index-1).get<3>();
    return 100;

}



Nodes Graph::getPairs() {

    return vecNode;
}
