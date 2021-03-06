#include <iostream>                  // for std::cout
#include <utility>                   // for std::pair
#include <algorithm>                 // for std::for_each
#include <fstream>                   // for std::ofstream
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::property<boost::edge_weight_t, int> EdgeWeightProperty;
typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, boost::no_property, EdgeWeightProperty > DirectedGraph;
typedef boost::graph_traits<DirectedGraph>::edge_iterator edge_iterator;
//typedef std::pair<int, int> Edge;
typedef boost::graph_traits<DirectedGraph>::edge_descriptor Edge;

//returns number of edges that depart from iputted city
int numConnections(DirectedGraph &cityMap, int city);

//returns the __'th edge that starts from the inputted city
Edge connectionNum__(DirectedGraph &cityMap, int city, int num);

//tells if graph contians a certain edge
bool containsEdge(DirectedGraph &cityMap,  std::list<Edge> &route, Edge edgeInput);

//tells if a city has been visited
bool visited(DirectedGraph &cityMap, int city, std::list<Edge> &route);

//tells if all cities have been visited
bool visitedAll(DirectedGraph &cityMap, std::list<Edge> &route);

//prints the route
void printRoute(DirectedGraph &cityMap, std::list<Edge> &route, std::ostream &os);

int main(){

    //making graph

        DirectedGraph cityMap;

        int Reno = 1, SanFran = 2, SaltLake = 3, Seattle = 4, Vegas = 5;

        boost::add_edge(Reno, SanFran, EdgeWeightProperty(218), cityMap);
        boost::add_edge(Reno, SaltLake, EdgeWeightProperty(518), cityMap);
        boost::add_edge(Reno, Seattle, EdgeWeightProperty(704), cityMap);
        boost::add_edge(Reno, Vegas, EdgeWeightProperty(439), cityMap);

        boost::add_edge(SanFran, Reno, EdgeWeightProperty(218), cityMap);
        boost::add_edge(SanFran, Seattle, EdgeWeightProperty(811), cityMap);
        boost::add_edge(SanFran, Vegas, EdgeWeightProperty(564), cityMap);

        boost::add_edge(SaltLake, Reno, EdgeWeightProperty(518), cityMap);
        boost::add_edge(SaltLake, Seattle, EdgeWeightProperty(829), cityMap);
        boost::add_edge(SaltLake, Vegas, EdgeWeightProperty(421), cityMap);

        boost::add_edge(Seattle, Reno, EdgeWeightProperty(704), cityMap);
        boost::add_edge(Seattle, SanFran, EdgeWeightProperty(811), cityMap);
        boost::add_edge(Seattle, SaltLake, EdgeWeightProperty(829), cityMap);
        boost::add_edge(Seattle, Vegas, EdgeWeightProperty(1118), cityMap);

        boost::add_edge(Vegas, Reno, EdgeWeightProperty(439), cityMap);
        boost::add_edge(Vegas, SanFran, EdgeWeightProperty(564), cityMap);
        boost::add_edge(Vegas, SaltLake, EdgeWeightProperty(1118), cityMap);
        boost::add_edge(Vegas, Seattle, EdgeWeightProperty(421), cityMap);

        boost::property_map<DirectedGraph, boost::edge_weight_t>::type EdgeWeightMap = get(boost::edge_weight, cityMap);


    //making the list of lists

        std::list<std::list<Edge>> inProgress;
        std::list<std::list<Edge>> routes;
        std::list<int> lengths;

    //Opening output file

        std::ofstream myFile;
        myFile.open("ListOfAllRoutes.txt");

    //the beginning of the routes

        std::pair<edge_iterator, edge_iterator> EI;


        for(EI = edges(cityMap); EI.first != EI.second; ++EI.first){

            edge_iterator first_EI = EI.first; 
            Edge newEdge = *first_EI;

            if(source(*first_EI, cityMap) == Reno){
                std::list<Edge> newPath;
                
                newPath.push_front(newEdge);

                //std::cout << "Before inProgress, inProgress length: " << inProgress.size() << std::endl;

                inProgress.push_back(newPath);
            }

        }
    //making the paths

        int max = 0;
        while (!inProgress.empty() && max < 120){ 
            //sets size for only the original paths, not the new added ones
            int size = inProgress.size();
            

            //std::cout << "before for statement (inside while loop)" << std::endl;
            //adds all other possible paths
            for(int i = 0; i < size; i++){
                
                std::list<std::list<Edge>>::iterator entryIt = inProgress.begin();
                for(int j = 0; j < i; j++){
                    entryIt++;
                }
                std::list<Edge> Current_route = *entryIt;
                

                Edge last_edge = Current_route.back();

                int current_city = target(last_edge, cityMap);

                int numberOfConnections = numConnections(cityMap, current_city);

                for(int j = 2; j <= numberOfConnections ; j++){

                    Edge next_edge = connectionNum__(cityMap, current_city, j);
                    //I am not allowing a path to go over the same edge twice, this checks that condition
                    //std::cout << "before if statement which checks if an edge has been gone over" << std::endl;
                    if(!(containsEdge(cityMap, Current_route, next_edge))){
                        std::list<Edge> duplicate(Current_route);
                        duplicate.push_back(next_edge);
                        duplicate.unique();
                        inProgress.push_back(duplicate);
                        inProgress.unique();
                    }
                }
                Edge next_edge = connectionNum__(cityMap, current_city, 1);
                //same check case as earlier
                if(containsEdge(cityMap, Current_route, next_edge)){
                    inProgress.remove(Current_route);
                }
                else{
                    Current_route.push_back(next_edge);
                    
                }
                max++;
            }

            int index = 0;
            while(index != inProgress.size()){
                std::list<std::list<Edge>>::iterator entryIt = inProgress.begin();
                for(int j = 0; j < index; j++){
                    entryIt ++;
                }
                std::list<Edge> current = *entryIt;

                Edge most_recent = current.back();
                int city = target(most_recent, cityMap);
                int backToReno = 0;
                if(visitedAll(cityMap, current)){

                    routes.push_back(current);
                    //calculate length and add that to that list
                    

                    int currentWeight = 0;
                    int routeLength = 0;
                    for(int k = 0; k < current.size(); k++){

                        std::list<Edge>::iterator entryIt = current.begin();
                        for(int j = 0; j < k; j++){
                            entryIt++;
                        }
                        Edge Current_route = *entryIt;

                        currentWeight = EdgeWeightMap(Current_route);

                        switch(city){
                            case 1:
                                std::cout << "oopsies Reno" << std::endl;
                            case 2:
                                backToReno = 218;
                                break;
                            case 3:
                                backToReno = 518;
                                break;
                            case 4:
                                backToReno = 704;
                                break;
                            case 5:
                                backToReno = 439;
                                break;
                            default:
                                std::cout << "Oopsies" << std::endl;
                        }

                        routeLength = routeLength + currentWeight + backToReno;
                    }

                    lengths.push_back(routeLength);
                    //output route and length to file
                    
                    myFile << "Route " << index << ": ";
                    printRoute(cityMap, current, myFile);
                    myFile << "Length: " << routeLength << std::endl;

                    inProgress.remove(current);
                }
                else{
                    index++;
                }
            }
        }

    //looking for largest
    
        int smallest_val = lengths.front();
        int smallest_index = 0;

        for(int i = 0; i < lengths.size(); i++){

            std::list<int>::iterator entryIt = lengths.begin();
            for(int j = 0; j < i; j++){
                entryIt++;
            }
            int curr_entry = *entryIt;

            if(curr_entry < smallest_val){
                smallest_val = curr_entry;
                smallest_index = i;
            }
        }

   
   //Printing out shortest route to file
        myFile << "Shortest Route: ";

        std::list<std::list<Edge>>::iterator entryIt = routes.begin();
        for(int j = 0; j < smallest_index; j++){
            entryIt++;
        }
        std::list<Edge> curr_route = *entryIt;

        printRoute(cityMap, curr_route, myFile);
        myFile << "Length: " << smallest_val << " miles" << std::endl;

    //Printing out shortest route to screen
        std::cout << "Shortest Route: ";
        printRoute(cityMap, curr_route, std::cout);
        std::cout << "Length: " << smallest_val << " miles" << std::endl;

   //Closing file
        myFile.close();
    
    return 0;
}

//Function which returns the  number of connections a city has
int numConnections(DirectedGraph &cityMap, int city){
    int count = 0;
    std::pair<edge_iterator, edge_iterator> EI;

    for(EI = edges(cityMap); EI.first != EI.second; ++EI.first){
        edge_iterator first_EI = EI.first; 
        if(source(*first_EI, cityMap) == city){
            count++;
        }
    }

    return count;
}

//returns the __'th edge that starts from the inputted city
Edge connectionNum__(DirectedGraph &cityMap, int city, int num){

    std::pair<edge_iterator, edge_iterator> EI;
    EI = edges(cityMap);

    //if num > 1, iterates through the edges, incrementing when it hits edges belonging to city
    //once it reaches the __'th edge it will return that edge

    int i = 0;
    while( (i < num) && (EI.first != EI.second) ){
        //std::cout << "inside while loop in connectionNum" << std::endl;
        edge_iterator first_EI = EI.first; 
        if(source(*first_EI, cityMap) == city){
            ++i;

            if( i == num ){
                return *first_EI;
            }
        }

        ++EI.first;
    }
    
    //if it reaches that point, there are < "num" number of edges corresponding to the city
    return *EI.first;
}

//tells if list contians a certain edge
bool containsEdge(DirectedGraph &cityMap,  std::list<Edge> &route, Edge edgeInput){

    //Iterates through Route list and checks each edge for a match

    std::list<Edge>::iterator theIt;
    
    theIt = find(route.begin(), route.end(), edgeInput);
    if(theIt != route.end()){
        return 1;
    }
    else{
        return 0;
    }
}

//tells if a city has been visited
bool visited(DirectedGraph &cityMap, int city, std::list<Edge> &route){
    bool visitedCity = 0;

    //Iterates through Route list and checks the first value of each edge for match to city
    Edge temp;
    for(int i = 0; i < route.size(); ++i){
        std::list<Edge>::iterator entryIt = route.begin();
        for(int j = 0; j < i; j++){
            entryIt ++;
        }
        temp = *entryIt;

        //If the city is found, sets visitedCity to true
        if( source(temp, cityMap) == city ){
            visitedCity = 1;
        }
    }

    //Checks the second value of the last edge for match to city
    if(target(temp, cityMap) == city){
        visitedCity = 1;
    }

    return visitedCity;
}

//tells if all cities have been visited
bool visitedAll(DirectedGraph &cityMap, std::list<Edge> &route){
    bool visitedAllCities = 1;

    //Checks if visited all 5 cities
    for(int i = 1; i <= 5; ++i){
        if( !visited(cityMap, i, route) ){
            visitedAllCities = 0;
        }
    }

    return visitedAllCities;
}

//prints the route
void printRoute(DirectedGraph &cityMap, std::list<Edge> &route, std::ostream &os){
    Edge temp;
    //Prints out first cities on route
    for(int i = 0; i < route.size(); ++i){
        std::list<Edge>::iterator entryIt = route.begin();
        for(int j = 0; j < i; j++){
            entryIt ++;
        }
        temp = *entryIt;

        switch( source(temp, cityMap) ){
            case 1:
                os << "Reno, ";
                break;
            case 2:
                os << "San Francisco, ";
                break;
            case 3:
                os << "Salt Lake City, ";
                break;
            case 4:
                os << "Seattle, ";
                break;
            case 5:
                os << "Las Vegas, ";
                break;
            default:
                os << "Oopsies";
        }
    }

    //Prints out final city on route
    switch( target(temp, cityMap) ){
        case 1:
            os << "Oopsies? reno" << std::endl;
            break;
        case 2:
            os << "San Francisco";
            break;
        case 3:
            os << "Salt Lake City";
            break;
        case 4:
            os << "Seattle";
            break;
        case 5:
            os << "Las Vegas";
            break;
        default:
            os << "Oopsies" << std::endl;
    }

    os << ", Reno" << std::endl;
}