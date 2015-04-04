#ifndef GRAPH_H
#define GRAPH_H
#include "excel.h"
#include "stl.h"
#include <iomanip>
/*
int recIter( Orders , Orders::iterator, int);
//int calcIter(Orders::iterator, int);
int makeMatrice(Orders, Orders::iterator, int);
*/

/*typedef int (Graph::*recIter)(int, Orders::iterator);
typedef int (Graph::*calcIter)(Orders::iterator, int);
typedef double (Graph::*calculate) (Order );
*/


class Graph {

    static Order vertice;
    static Orders orders ;
    static std::vector<std::vector<int> > matrice;
    std::vector<std::vector<int> >::iterator out;
    static std::vector<int>  inVec;
    //Edges edges;
    //std::bitset bitArray; //make decision about empty arr
    //static const int up = 1700 ;
    //  static const  int down = 1500 ;
    static int up  ;
    static int down  ;
    static int reciter ;
    static int calc;
    static int matr;
    unsigned int in_index;
    unsigned int out_index;
    static double dt;
    //std::pair<Order, Order> pair_temp;
    //std::pair<int, int> index_temp;
    std::vector<std::pair <int, int> >  pairVec;
    std::vector<boost::tuple <int, QDate> > vecChange;
    Nodes vecNode;

public:
    explicit Graph (const Orders) ;  //empty graph
    int makeGraph(const Orders);
    static int recIter( Orders::iterator);
    static int calcIter();
    static int calculate (Orders::iterator, int,  int h = 0 );
    static bool makeMatrice(Orders::iterator, int);
    static int setVariables(int, int, double);
    int getMatrice();
    int getRoutes();
    TIMETYPE getNode(double, int , int); //about template methods in calsses
    int setZeroColStr(int);
    std::vector<std::pair <int, int> > getVector();
    int tiraz(TIMETYPE, TIMETYPE, TIMETYPE, int, int) ;
    //int matrIter();
    Nodes getPairs();
};


typedef int (Graph::*REF)(Orders::iterator ,int );
typedef int (Graph::*REF1)(Orders::iterator ,int );
typedef int (Graph::*CALC)(Orders::iterator,int, int);



#endif
