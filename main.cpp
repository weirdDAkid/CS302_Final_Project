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
typedef boost::property_traits<DirectedGraph>::read_write_property_map_tag WeightPropertyType;
typedef boost::property_map<DirectedGraph, boost::edge_weight_t>::WeightPropertyType EdgeWeight;

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

                //std::cout << "Before inProgress, inProgress length: " << inProgress.size() << std::endl;

                inProgress.push_back(newPath);
            }

        }
    //making the paths

        std::cout << "start of while loops" << std::endl;
        int max = 0;
        while (!inProgress.empty() && max < 120){ 
            //sets size for only the original paths, not the new added ones
            int size = inProgress.size();
            

            //std::cout << "before for statement (inside while loop)" << std::endl;
            //adds all other possible paths
            for(int i = 0; i < size; i++){

                std::cout << "inProgress.size() original: " << size << std::endl;
                std::cout << "updating inProgres.size(): " << inProgress.size() << std::endl;
                std::cout << "max: " << max << std::endl;    

                std::cout << "Inside for statement, time #" << i << std::endl;
                
                std::list<std::list<Edge>>::iterator entryIt = inProgress.begin();
                for(int j = 0; j < i; j++){
                    entryIt++;
                }
                std::list<Edge> Current_route = *entryIt;
                

                Edge last_edge = Current_route.back();

                int current_city = target(last_edge, cityMap);

                std::cout << "number of connections: " << numConnections(cityMap, current_city) << std::endl;

                int numberOfConnections = numConnections(cityMap, current_city);

                for(int j = 2; j <= numberOfConnections ; j++){

                    std::cout << "numConnections for loop time #" << j << std::endl;
                    Edge next_edge = connectionNum__(cityMap, current_city, j);
                    std::cout << "Next-Edge value: " << next_edge << std::endl;
                    //I am not allowing a path to go over the same edge twice, this checks that condition
                    //std::cout << "before if statement which checks if an edge has been gone over" << std::endl;
                    if(!(containsEdge(cityMap, Current_route, next_edge))){
                        std::cout << "inside that ^^ if statement" << std::endl;
                        std::list<Edge> duplicate(Current_route);
                        duplicate.push_back(next_edge);
                        duplicate.unique();
                        inProgress.push_back(duplicate);
                        inProgress.unique();

                        std::cout << "end of ^^ if statement" << std::endl;
                    }
                    else{
                        std::cout << "does not add" << std::endl;
                    }
                    
                    std::cout << "end of numConnections for loop" << std::endl;
                }
                Edge next_edge = connectionNum__(cityMap, current_city, 1);
                //same check case as earlier
                std::cout << "Before if statements about checking for duplicate case" << std::endl;
                if(containsEdge(cityMap, Current_route, next_edge)){
                    std::cout << "removing items from inProgress" << std::endl;
                    inProgress.remove(Current_route);
                }
                else{
                    Current_route.push_back(next_edge);
                    
                }
                std::cout << "end of for for all possible paths loop" << std::endl;
                max++;
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
                    

                    EdgeWeight currentWeight = 0;
                    int routeLength = 0;
                    for(int k = 0; k < current.size(); k++){

                        std::list<std::list<Edge>>::iterator entryIt = inProgress.begin();
                        for(int j = 0; j < k; j++){
                            entryIt++;
                        }
                        std::list<Edge> Current_route = *entryIt;

                        currentWeight = get(currentWeight, cityMap, Current_route);

                        routeLength = routeLength + currentWeight;

                        std::cout << "currentWeight: " << currentWeight << " , routeLength: " << routeLength << std::endl;
                    }

                    std::cout << "Final route length: " << routeLength << std::endl;
                    lengths.push_back(routeLength);
                    //output route and length to file
                    /*
                    myFile << "Route " << index << ": ";
                    printRoute(cityMap, current, myFile);
                    myFile << "Length: " << routeLength << std::endl;
                    */
                   std::cout << "removing items after adding them to the final list" << std::endl;

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
    std::cout << "inside connectionNum" << std::endl;
    std::cout << "city: " << city << ", num: " << num << std::endl;

    std::pair<edge_iterator, edge_iterator> EI;
    EI = edges(cityMap);

    //if num > 1, iterates through the edges, incrementing when it hits edges belonging to city
    //once it reaches the __'th edge it will return that edge
    if(num <= 0){
        std::cout << "inserting num <= 0 into connectionNum" << std::endl;
    }
    std::cout << "before while loop in connectionNum" << std::endl;
    int i = 0;
    while( (i < num) && (EI.first != EI.second) ){
        //std::cout << "inside while loop in connectionNum" << std::endl;
        edge_iterator first_EI = EI.first; 
        if(source(*first_EI, cityMap) == city){
            ++i;

            if( i == num ){
                std::cout << "found 'num' in connectionNum" << std::endl;
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