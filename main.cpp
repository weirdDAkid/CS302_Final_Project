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

/* List of Cities:
    City 'A' = Reno
    City 'B' = San Francisco
    City 'C' = Salt Lake City
    City 'D' = Seattle
    City 'E' = Las Vegas
*/

int main(){

    DirectedGraph cityMap;

    boost::add_edge('A', 'B', 218, cityMap);
    boost::add_edge('A','C', 518, cityMap);
    boost::add_edge('A','D', 704, cityMap);
    boost::add_edge('A','E', 439, cityMap);

    boost::add_edge('B','A', 218, cityMap);
    boost::add_edge('B','D', 811, cityMap);
    boost::add_edge('B','E', 564, cityMap);

    boost::add_edge('C','A', 518, cityMap);
    boost::add_edge('C','D', 829, cityMap);
    boost::add_edge('C','E', 421, cityMap);

    boost::add_edge('D','A', 704, cityMap);
    boost::add_edge('D','B', 811, cityMap);
    boost::add_edge('D','C', 829, cityMap);
    boost::add_edge('D','E', 1118, cityMap);

    boost::add_edge('E','A', 439, cityMap);
    boost::add_edge('E','B', 564, cityMap);
    boost::add_edge('E','C', 1118, cityMap);
    boost::add_edge('E','D', 421, cityMap);

    return 0;
}