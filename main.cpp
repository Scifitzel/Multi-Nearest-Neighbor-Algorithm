
// code attempts to find a path for the Traveling Salesman Problem (TSP) 
//  average difference is 1.08
// It works similarly to nearest neighbor, except that all nodes are considered as the next node Instead of just the nearest one. 

#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
struct Point {
    public:
        int x;
        int y;
    Point(int a, int b){
    x = a;
    y = b;  
    }
};
std::vector<Point> rawPoints{};
std::vector<int> pointsAlreadyTraveled{};
std::vector<int> firstPointsAlreadyTraveled{}; 
std::vector<int> pointsAlreadyTraveledSorted{}; // seperate vector so we can use binary search
int startingNumber = 0;
int currentStartingPoint  = 0;
 
 
 
 
int main() {
    float firstTotalTotal = 0;
 std::string input;
 std::ifstream into {"input.txt"};
 while (std::getline(into,input)) {
    rawPoints.push_back(Point(std::stoi(input.substr(0,input.find(','))),std::stoi(input.substr(input.find(',')+1)))); // algorithm expects a file called input.txt, which contains all the points 
 // Point are formatted like this:
 // 250,67
 //11,11
 //4554,422
  }
 into.close();
 float totalTotal = 0;
 const int sizeofPoints = 10/5 * rawPoints.size()-2; // Reduces the amount of points calculated.
 float distance  = 0;
 std::vector<float> pointsToCheck;    
 std::vector<std::vector<float>>points{};
float longestDistance = 0;
int firstPoint = 0;
int secondPoint = 0;
enum whichWay{UP,DOWN,LEFT,RIGHT};
whichWay way = UP;



 for (int i = 0; i < sizeofPoints; i++){
    pointsToCheck.push_back(-1);
    }

 for (int i = 0; i < rawPoints.size(); i++){
    for (int i = 0; i < sizeofPoints; i++){
        pointsToCheck[i] = -1;
        }
    points.push_back({});
    for (int n = 0; n < rawPoints.size(); n++){
        if (n == i) {
            n++;
            if (n == rawPoints.size()){
                break;
                    }
                }
        distance = sqrt( (rawPoints[i].x-rawPoints[n].x)*(rawPoints[i].x-rawPoints[n].x) + (rawPoints[i].y-rawPoints[n].y)*(rawPoints[i].y-rawPoints[n].y)); // distance formula
        if (distance > longestDistance) {
            longestDistance = distance;
            firstPoint = n;
            secondPoint = i;
        }
        for (int a = 0; a < sizeofPoints; a+=2){ 
            if (pointsToCheck[a] > distance || pointsToCheck[a] == -1){
                pointsToCheck.insert(pointsToCheck.begin()+a,distance);
                pointsToCheck.insert(pointsToCheck.begin()+a+1,n);
                pointsToCheck.erase(pointsToCheck.end()-2,pointsToCheck.end());
                break;
                            }
                }
        }
    points[i] = pointsToCheck;
 }

    pointsAlreadyTraveled.push_back(firstPoint);
    pointsAlreadyTraveledSorted.push_back(firstPoint);
    if (abs(rawPoints[firstPoint].x-rawPoints[secondPoint].x) < abs(rawPoints[firstPoint].y-rawPoints[secondPoint].y)){
        if (rawPoints[firstPoint].x > rawPoints[secondPoint].x){
            way = RIGHT;
        } else {
            way = LEFT;
        }
    } else {
        if (rawPoints[firstPoint].y < rawPoints[secondPoint].y) {
            way = DOWN;
        }
    }

    bool reachedSecondPoint = false;
 int pointToStartAt = 1;
while (pointToStartAt != points.size()) {
    int startingpoint = 0;
    float smallestPoint = -1;
    float total = 0;
    int index = 0;
    while (startingpoint != points.size()){
        std::vector<int> pointsAlreadyUsed{};
        pointsAlreadyUsed = pointsAlreadyTraveledSorted;
        
        
        while (startingpoint < points.size() && (std::binary_search(pointsAlreadyUsed.begin(),pointsAlreadyUsed.end(), startingpoint) ||  (( (way == UP &&  rawPoints[firstPoint].y-rawPoints[startingpoint].y < 0) ||   (way == DOWN &&  rawPoints[firstPoint].y-rawPoints[startingpoint].y > 0) || ((way == RIGHT &&  rawPoints[firstPoint].x-rawPoints[startingpoint].x < 0) || (way == LEFT && rawPoints[firstPoint].x-rawPoints[secondPoint].x > 0))) && (!reachedSecondPoint) ))) {     
            startingpoint++;
        }
        if (startingpoint == points.size()){
            break;
        }        
        int currentPoint  = startingpoint;
        total = sqrt( (rawPoints[pointsAlreadyTraveled[pointsAlreadyTraveled.size()-1]].x-rawPoints[currentPoint].x)*(rawPoints[pointsAlreadyTraveled[pointsAlreadyTraveled.size()-1]].x-rawPoints[currentPoint].x) + (rawPoints[pointsAlreadyTraveled[pointsAlreadyTraveled.size()-1]].y-rawPoints[currentPoint].y)*(rawPoints[pointsAlreadyTraveled[pointsAlreadyTraveled.size()-1]].y-rawPoints[currentPoint].y));
        pointsAlreadyUsed.insert(std::upper_bound(pointsAlreadyUsed.begin(),pointsAlreadyUsed.end(),currentPoint),currentPoint);
        while (pointsAlreadyUsed.size() != points.size()){
            index = -1;
            for (int i = 0; i <  points[currentPoint].size(); i+=2){
                if ( !std::binary_search(pointsAlreadyUsed.begin(),pointsAlreadyUsed.end(), points[currentPoint][i+1])   ){ // there is no need to check if it is the smallest  because it is already sorted
                    index = i+1;
                    break;
                    }
                }
            
            if (index != -1){
            total += points[currentPoint][index-1];
            currentPoint = points[currentPoint][index];
            pointsAlreadyUsed.insert(std::upper_bound(pointsAlreadyUsed.begin(),pointsAlreadyUsed.end(),currentPoint),currentPoint);
                } else{
            total = -10;
            break;
                }
        
        
        }
        
        if (total != -10){
            total += sqrt( (rawPoints[firstPoint].x-rawPoints[currentPoint].x)*(rawPoints[firstPoint].x-rawPoints[currentPoint].x) + (rawPoints[firstPoint].y-rawPoints[currentPoint].y)*(rawPoints[firstPoint].y-rawPoints[currentPoint].y));
            }
        if ((smallestPoint > total || smallestPoint == -1) && total != -10){
            smallestPoint = total;
            currentStartingPoint = startingpoint;
            }
            startingpoint++;
    }
    totalTotal += sqrt( (rawPoints[currentStartingPoint].x-rawPoints[pointsAlreadyTraveled[pointsAlreadyTraveled.size()-1]].x)*(rawPoints[currentStartingPoint].x-rawPoints[pointsAlreadyTraveled[pointsAlreadyTraveled.size()-1]].x)+ (rawPoints[currentStartingPoint].y-rawPoints[pointsAlreadyTraveled[pointsAlreadyTraveled.size()-1]].y)*(rawPoints[currentStartingPoint].y-rawPoints[pointsAlreadyTraveled[pointsAlreadyTraveled.size()-1]].y) );
    
    pointToStartAt++;
    if (currentStartingPoint == secondPoint) {
        reachedSecondPoint = true;
    }
    pointsAlreadyTraveled.push_back(currentStartingPoint);
    pointsAlreadyTraveledSorted.insert(std::upper_bound(pointsAlreadyTraveledSorted.begin(),pointsAlreadyTraveledSorted.end(),currentStartingPoint),currentStartingPoint);
    std::cout << pointsAlreadyTraveled.size() << "\n";
    if  (pointToStartAt == points.size()) {
         totalTotal += sqrt( (rawPoints[currentStartingPoint].x-rawPoints[firstPoint].x)*(rawPoints[currentStartingPoint].x-rawPoints[firstPoint].x)+ (rawPoints[currentStartingPoint].y-rawPoints[firstPoint].y)*(rawPoints[currentStartingPoint].y-rawPoints[firstPoint].y) );
    if (firstTotalTotal == 0) { // we reset the thing in case having the firstPoint and secondPoint being swapped leads to a shorter tour.
        firstTotalTotal = totalTotal;
        totalTotal = 0;
        reachedSecondPoint = false;
        pointToStartAt = 1;
        firstPointsAlreadyTraveled = pointsAlreadyTraveled;
        pointsAlreadyTraveled.clear();
        pointsAlreadyTraveledSorted.clear();
        pointsAlreadyTraveled.push_back(secondPoint);
        pointsAlreadyTraveledSorted.push_back(secondPoint);
        currentStartingPoint = firstPoint;
        firstPoint = secondPoint;
        secondPoint = currentStartingPoint;
    } else if (firstTotalTotal < totalTotal) {
        totalTotal = firstTotalTotal;
        pointsAlreadyTraveled = firstPointsAlreadyTraveled;
    }
    }
}


 std::ofstream outo{"output.txt"};
 for (int i = 0; i < pointsAlreadyTraveled.size(); i++){
    outo << pointsAlreadyTraveled[i]+1 << " ";
 }
 outo<< "\nTotal length: " << totalTotal << "\n";
 outo.close();

 return 0;
}
 
 
