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
std::vector<int> pointsAlreadyTraveled{0};
std::vector<int> pointsAlreadyTraveledSorted{0}; // seperate vector so we can use binary search
int startingNumber = 0;
int currentStartingPoint  = 0;
 
 
 
 
int main() {
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
 const int sizeofPoints = rawPoints.size() * 7/5; // Reduces the amount of points calculated.
 float distance  = 0;
 std::vector<float> pointsToCheck;    
 std::vector<std::vector<float>>points{};

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
 int pointToStartAt = 1;
while (pointToStartAt != points.size()) {
    int startingpoint = 0;
    float smallestPoint = -1;
    float total = 0;
    int index = 0;
    while (startingpoint != points.size()){
        std::vector<int> pointsAlreadyUsed{};
        pointsAlreadyUsed = pointsAlreadyTraveledSorted;
        
        
        while (std::find(pointsAlreadyUsed.begin(),pointsAlreadyUsed.end(), startingpoint) != pointsAlreadyUsed.end() ) {
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
                if ( !std::binary_search(pointsAlreadyUsed.begin(),pointsAlreadyUsed.end(), points[currentPoint][i+1])){ // there is no need to check if it is the smallest  because it is already sorted
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
            total += sqrt( (rawPoints[0].x-rawPoints[currentPoint].x)*(rawPoints[0].x-rawPoints[currentPoint].x) + (rawPoints[0].y-rawPoints[currentPoint].y)*(rawPoints[0].y-rawPoints[currentPoint].y));
            }
        if ((smallestPoint > total || smallestPoint == -1) && total != -10){
            smallestPoint = total;
            currentStartingPoint = startingpoint;
            }
            startingpoint++;
    }
    totalTotal += sqrt( (rawPoints[currentStartingPoint].x-rawPoints[pointsAlreadyTraveled[pointsAlreadyTraveled.size()-1]].x)*(rawPoints[currentStartingPoint].x-rawPoints[pointsAlreadyTraveled[pointsAlreadyTraveled.size()-1]].x)+ (rawPoints[currentStartingPoint].y-rawPoints[pointsAlreadyTraveled[pointsAlreadyTraveled.size()-1]].y)*(rawPoints[currentStartingPoint].y-rawPoints[pointsAlreadyTraveled[pointsAlreadyTraveled.size()-1]].y) );
    pointToStartAt++;
    pointsAlreadyTraveled.push_back(currentStartingPoint);
    pointsAlreadyTraveledSorted.insert(std::upper_bound(pointsAlreadyTraveledSorted.begin(),pointsAlreadyTraveledSorted.end(),currentStartingPoint),currentStartingPoint);
    std::cout << currentStartingPoint << "\n";
}
 std::ofstream outo{"output.txt"};
 totalTotal += sqrt( (rawPoints[currentStartingPoint].x-rawPoints[0].x)*(rawPoints[currentStartingPoint].x-rawPoints[0].x)+ (rawPoints[currentStartingPoint].y-rawPoints[0].y)*(rawPoints[currentStartingPoint].y-rawPoints[0].y) );
 for (int i = 0; i < pointsAlreadyTraveled.size(); i++){
    outo << pointsAlreadyTraveled[i]+1 << " ";
 }
 outo<< "\nTotal length: " << totalTotal << "\n";
 outo.close();

 return 0;
}
