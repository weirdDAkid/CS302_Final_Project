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

int main(){

    //making graph
        DirectedGraph cityMap;

        int Reno = 1, SanFran = 2, SaltLake = 3, Seattle = 4, Vegas = 5;

        boost::add_edge(Reno, SanFran, 218, cityMap);
        boost::add_edge(Reno, SaltLake, 518, cityMap);
        boost::add_edge(Reno, Seattle, 704, cityMap);
        boost::add_edge(Reno, Vegas, 439, cityMap);

        boost::add_edge(SanFran, Reno, 218, cityMap);
        boost::add_edge(SanFran, Seattle, 811, cityMap);
        boost::add_edge(SanFran, Vegas, 564, cityMap);

        boost::add_edge(SaltLake, Reno, 518, cityMap);
        boost::add_edge(SaltLake, Seattle, 829, cityMap);
        boost::add_edge(SaltLake, Vegas, 421, cityMap);

        boost::add_edge(Seattle, Reno, 704, cityMap);
        boost::add_edge(Seattle, SanFran, 811, cityMap);
        boost::add_edge(Seattle, SaltLake, 829, cityMap);
        boost::add_edge(Seattle, Vegas, 1118, cityMap);

        boost::add_edge(Vegas, Reno, 439, cityMap);
        boost::add_edge(Vegas, SanFran, 564, cityMap);
        boost::add_edge(Vegas, SaltLake, 1118, cityMap);
        boost::add_edge(Vegas, Seattle, 421, cityMap);


    //making the list of lists
        List<List<Edge>> inProgress;
        List<List<Edge>> routes;
        List<int> lengths;
        std::pair<edge_iterator, edge_iterator> EI;
        for(EI = edges(cityMap); EI.first != EI.second; ++EI.first){
            if(source(EI.first) == Reno){
                List<Edge> newPath;
                newPath.insert(EI);
                inProgress.insert(newPath);
            }
        }
        for(i = 0; i < /*function zoya is making*/ ; i++){
            List<Edge> duplicate(-----);

        }


    return 0;
}