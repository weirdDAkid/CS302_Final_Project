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
typedef graph_traits<Graph>::edge_iterator Edge;

//returns number of edges that depart from iputted city
int numConnections(DirectedGraph &cityMap, int city);

//returns the __'th edge that starts from the inputted city
Edge connectionNum__(DirectedGraph &cityMap, int city, int num);

//tells if graph contians a certain edge
bool containsEdge(DirectedGraph &cityMap, Edge edgeInput);

//tells if a city has been visited
bool visited(DirectedGraph &cityMap, int city, List<EdgeW> route);

//tells if all cities have been visited
bool visitedAll(DirectedGraph &cityMap, List<Edge> route);

//prints the route
void printRoute(DirectedGraph &cityMap, List<Edge> route);

int main(){

    //making graph
        DirectedGraph cityMap;

        int Reno = 1, SanFran = 2, SaltLake = 3, Seattle = 4, Vegas = 5;

        //edges will be different going in the different directions

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
    //the beginning of the routes
        std::pair<edge_iterator, edge_iterator> EI;
        int ind = 0;
        for(EI = edges(cityMap); EI.first != EI.second; ++EI.first){
            if(source(*EI.first) == Reno){
                List<Edge> newPath;
                newPath.insert(0, *EI);
                inProgress.insert(ind, newPath);
            }
        }
    //making the paths
        while (!inProgress.isEmpty()){ 
            //sets size for only the original paths, not the new added ones
            int size = inProgress.getLength();
            //adds all other possible paths
            for(int i = 0; i < size; i++){
                List<Edge> Current_route = inProgress.getEntry(i);
                Edge last_edge = Current_route.getEntry(Current_route.getLength());
                int current_city = target(last_edge, cityMap);
                for(j = 1; j < numConnections(cityMap, current_city) ; j++){
                    Edge next_edge = connectionNum__(cityMap, current_city, j);
                    //I am not allowing a path to go over the same edge twice, this checks that condition
                    if(!(containsEdge(cityMap, next_edge)){
                        List<Edge> duplicate(Current_route);
                        duplicate.insert(duplicate.getLength(), next_edge);
                        inProgress.insert(inProgress.getLength(), duplicate);
                    }
                }
                Edge next_edge = connectionNum__(cityMap, current_city, 0);
                //same check case as earlier
                if(!(containsEdge(cityMap, next_edge)){
                    Current_route.insert(Current_route.getLength(), next_edge);
                }
                else{
                    inProgress.remove(i);
                }
            }
            int index = 0;
            while(index != inProgress.getLength()){
                List<Edge> current = inProgress.getEntry(index);
                Edge most_recent = current.getEntry(current.getLength() - 1);
                int city = target(most_recent, cityMap);
                if(city == Reno && visitedAll(cityMap, current)){
                    routes.insert((routes.getLength()), current);
                    //calculate length and add that to that list
                    /*
                    int weight
                    for(int k = 0; k < current.getLength(); k++){
                        weight = weight + EdgeWeightMap[current.getEntry(k)]
                    }
                    lengths.insert(lengths.getLength(), weight);
                    */
                    //output route and length to file

                    inProgress.remove(index);
                }
                else{
                    index++;
                }
            }
        }
        //looking for largest
        int smallest_val = lengths.getEntry(0);
        int smallest_index = 0;
    /*
        for(int i = 0; i < lengths.getLength(); i++){
            if(lengths.getEntry(i) < smallest_val){
                smallest_val = lengths.getEntry(i);
                smallest_index = i;
            }
        }
    */

    return 0;
}

//Function which returns the  number of connections a city has
int numConnections(DirectedGraph &cityMap, int city){
    int count = 0;
    std::pair<edge_iterator, edge_iterator> EI;

    for(EI = edges(cityMap); EI.first != EI.second; ++EI.first){
        if(source(*EI.first) == city){
            count++;
        }
    }

    return count;
}

//returns the __'th edge that starts from the inputted city
Edge connectionNum__(DirectedGraph &cityMap, int city, int num){
    std::pair<edge_iterator, edge_iterator> EI;
    EI = edges(cityMap);

    //checks for conditional case where num = 0
    if(num == 0){
        while( (source(*EI.first) != city) ){
            ++EI.first
        }
        
        return *EI.first
    }

    //if num > 1, iterates through the edges, incrementing when it hits edges belonging to city
    //once it reaches the __'th edge it will return that edge
    int i = 0;
    while( (i < num) || (EI.first != EI.second) ){}
        if(source(*EI.first) == city){
            ++i;

            if( i == num ){
                return *EI.first;
            }
        }

        ++EI.first;
    }

    //if it reaches that point, there are < "num" number of edges corresponding to the city
    return NULL;
}

//tells if graph contians a certain edge
bool containsEdge(DirectedGraph &cityMap, Edge edgeInput){
    bool edgeExists = 0;

    std::pair<edge_iterator, edge_iterator> EI;

    for(EI = edges(cityMap); EI.first != EI.second; ++EI.first){
        if(source(*EI.first) == edgeInput){
            edgeExists = 1;
        }
    }

    return edgeExists;
}

//tells if a city has been visited
bool visited(DirectedGraph &cityMap, int city, List<EdgeW> route){

}

//tells if all cities have been visited
bool visitedAll(DirectedGraph &cityMap, List<Edge> route);

//prints the route
void printRoute(DirectedGraph &cityMap, List<Edge> route);