#include <iostream>                  // for std::cout
#include <utility>                   // for std::pair
#include <algorithm>                 // for std::for_each
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#include "Node.h"
#include "ListInterface.h"
#include "List.h"

typedef boost::property<boost::edge_weight_t, int> EdgeWeightProperty;
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, boost::no_property, EdgeWeightProperty > DirectedGraph;
typedef boost::graph_traits<DirectedGraph>::edge_iterator edge_iterator;
typedef std::pair<int, int> Edge;

/* List of Cities:
    City 1 = Reno
    City 2 = San Francisco
    City 3 = Salt Lake City
    City 4 = Seattle
    City 5 = Las Vegas
*/

int main(){

    //making graph
        DirectedGraph cityMap;

        boost::add_edge(1, 2, 218, cityMap);
        boost::add_edge(1, 3, 518, cityMap);
        boost::add_edge(1, 4, 704, cityMap);
        boost::add_edge(1, 5, 439, cityMap);

        boost::add_edge(2, 1, 218, cityMap);
        boost::add_edge(2, 4, 811, cityMap);
        boost::add_edge(2, 5, 564, cityMap);

        boost::add_edge(3, 1, 518, cityMap);
        boost::add_edge(3, 4, 829, cityMap);
        boost::add_edge(3, 5, 421, cityMap);

        boost::add_edge(4, 1, 704, cityMap);
        boost::add_edge(4, 2, 811, cityMap);
        boost::add_edge(4, 3, 829, cityMap);
        boost::add_edge(4, 5, 1118, cityMap);

        boost::add_edge(5, 1, 439, cityMap);
        boost::add_edge(5, 2, 564, cityMap);
        boost::add_edge(5, 3, 1118, cityMap);
        boost::add_edge(5, 4, 421, cityMap);


    //makeing the list of lists
        List<List<Edge>> inProgress;
        List<List<Edge>> routes;
        List<int> lengths;
        std::pair<edge_iterator, edge_iterator> EI;
        for(EI = edges(cityMap); EI.first != EI.second; ++EI.first){
            if(EI.first == Reno)
        }



    return 0;
}