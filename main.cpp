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
bool containsEdge(DirectedGraph &cityMap,  std::list<Edge> &route, Edge &edgeInput);

//tells if a city has been visited
bool visited(DirectedGraph &cityMap, int city, std::list<Edge> &route);

//tells if all cities have been visited
bool visitedAll(DirectedGraph &cityMap, std::list<Edge> &route);

//prints the route
void printRoute(DirectedGraph &cityMap, std::list<Edge> &route, std::ostream &os);

int main(){

    //making graph
        std::cout << "Before we even make the graph" << std::endl;

        DirectedGraph cityMap;

        int Reno = 1, SanFran = 2, SaltLake = 3, Seattle = 4, Vegas = 5;

        std::cout << "Before we add edges" << std::endl;

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

        std::cout << "Before the list of lists" << std::endl;

        std::list<std::list<Edge>> inProgress;
        std::list<std::list<Edge>> routes;
        std::list<int> lengths;

    //Opening output file

        std::cout << "Opening a file" << std::endl;
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

                std::cout << "Before inProgress, inProgress length: " << inProgress.size() << std::endl;

                inProgress.push_back(newPath);
            }

        }
    //making the paths

        std::cout << "start of while loops" << std::endl;

        while (!inProgress.empty()){ 
            //sets size for only the original paths, not the new added ones
            int size = inProgress.size();

            std::cout << "before for statement (inside while loop)" << std::endl;
            //adds all other possible paths
            for(int i = 0; i < size; i++){

                std::cout << "Inside for statement, time #" << i << std::endl;
                
                std::list<std::list<Edge>>::iterator entryIt = inProgress.begin();
                for(int j = 0; j < i; j++){
                    entryIt ++;
                }
                std::list<Edge> Current_route = *entryIt;

                Edge last_edge = Current_route.back();

                int current_city = target(last_edge, cityMap);

                std::cout << "number of connections: " << numConnections(cityMap, current_city) << std::endl;

                for(int j = 1; j < numConnections(cityMap, current_city) ; j++){
                    Edge next_edge = connectionNum__(cityMap, current_city, j);
                    std::cout << "Next-Edge value: " << next_edge << std::endl;
                    //I am not allowing a path to go over the same edge twice, this checks that condition
                    std::cout << "before if statement which checks if an edge has been gone over" << std::endl;
                    if(!(containsEdge(cityMap, Current_route, next_edge))){
                        std::cout << "inside that ^^ if statement" << std::endl;
                        std::list<Edge> duplicate(Current_route);
                        duplicate.push_back(next_edge);
                        inProgress.push_back(duplicate);
                    }
                }
                Edge next_edge = connectionNum__(cityMap, current_city, 0);
                //same check case as earlier
                std::cout << "Before if statements about checking for duplicate case" << std::endl;
                if(!(containsEdge(cityMap, Current_route, next_edge))){
                    Current_route.push_back(next_edge);
                }
                else{
                    inProgress.remove(Current_route);
                }
                std::cout << "end of for for all possible paths loop" << std::endl;
            }
            std::cout << "outside of for loop" << std::endl;
            int index = 0;
            while(index != inProgress.size()){
                std::list<std::list<Edge>>::iterator entryIt = inProgress.begin();
                for(int j = 0; j < index; j++){
                    entryIt ++;
                }
                std::list<Edge> current = *entryIt;

                Edge most_recent = current.back();
                int city = target(most_recent, cityMap);
                if(city == Reno && visitedAll(cityMap, current)){
                    routes.push_back(current);
                    //calculate length and add that to that list
                    /*
                    int routeLength
                    for(int k = 0; k < current.getLength(); k++){
                        routeLength = routeLength + EdgeWeightMap[current.getEntry(k)]
                    }
                    lengths.insert(lengths.getLength(), routeLength);
                    */
                    //output route and length to file
                    /*
                    myFile << "Route " << index << ": ";
                    printRoute(cityMap, current, myFile);
                    myFile << "Length: " << routeLength << std::endl;
                    */

                    inProgress.remove(current);
                }
                else{
                    index++;
                }
            }
        }

    //looking for largest
    /*
        int smallest_val = lengths.front();
        int smallest_index = 0;
        */
    /*
        for(int i = 0; i < lengths.getLength(); i++){
            if(lengths.getEntry(i) < smallest_val){
                smallest_val = lengths.getEntry(i);
                smallest_index = i;
            }
        }
    */
   /*
   //Printing out shortest route to file
        myFile << "Shortest Route: ";
        printRoute(cityMap, routes.getEntry(smallest_index), myFile);
        myFile << "Length: " << smallest_val << " miles" << std::endl;

    //Printing out shortest route to screen
        std::cout << "Shortest Route: ";
        printRoute(cityMap, routes.getEntry(smallest_index), std::cout);
        std::cout << "Length: " << smallest_val << " miles" << std::endl;

   //Closing file
        myFile.close();
    */
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
    while( (i < num) || (EI.first != EI.second) ){
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
bool containsEdge(DirectedGraph &cityMap,  std::list<Edge> &route, Edge &edgeInput){
    bool edgeExists = 0;

    //Iterates through Route list and checks each edge for a match
    Edge temp;

    std::list<Edge>::iterator entryIt;

    for(entryIt = route.begin(); entryIt != route.end(); entryIt++){
        temp = *entryIt;

        if( temp == edgeInput ){

            std::cout << "containsEdge if statement" << std::endl;
            edgeExists = 1;
        }
    }

    return edgeExists;
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
                os << "Reno" << std::endl;
                break;
            case 2:
                os << "San Francisco" << std::endl;
                break;
            case 3:
                os << "Salt Lake City" << std::endl;
                break;
            case 4:
                os << "Seattle" << std::endl;
                break;
            case 5:
                os << "Las Vegas" << std::endl;
                break;
            default:
                os << "Oopsies" << std::endl;
        }
}