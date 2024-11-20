#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "mapping.h"

#define MAX_CARGO_WEIGHT 2000
#define MAX_CARGO_VOLUME 20.0

typedef struct {
    int weight;          // Weight of the shipment
    double volume;       // Size of the box in cubic meters
    Point destination;   // Delivery destination point
} Package;

typedef struct {
    Route route;          // Route assigned to the truck
    int currentWeight;    // Current weight of cargo
    double currentVolume; // Current volume of cargo
    char lineColor;       // Color identifier for the truck route
} Truck;

// Define routes for each truck
Route blueRoute, greenRoute, yellowRoute;

void initializeRoutes() {
    blueRoute = getBlueRoute();
    greenRoute = getGreenRoute();
    yellowRoute = getYellowRoute();
}

// Calculate Euclidean distance between two points
double calculateDistance(const Point* p1, const Point* p2) {
    return sqrt(pow(p2->row - p1->row, 2) + pow(p2->col - p1->col, 2));
}

// Find the nearest point on a route to the destination
int findNearestPointOnRoute(const Route* route, const Point* destination) {
    int closestPointIndex = -1;
    double shortestDistance = INFINITY;
    for (int i = 0; i < route->numPoints; i++) {
        double distanceToDestination = calculateDistance(&route->points[i], destination);
        if (distanceToDestination < shortestDistance) {
            shortestDistance = distanceToDestination;
            closestPointIndex = i;
        }
    }
    return closestPointIndex;
}

// Determine which truck should carry the package based on capacity and proximity
int assignPackageToTruck(Package package, Truck trucks[], int numTrucks) {
    int bestTruck = -1;
    double minDistance = INFINITY;

    for (int i = 0; i < numTrucks; i++) {
        Truck* truck = &trucks[i];

        // Check if truck has enough capacity
        if (truck->currentWeight + package.weight > MAX_CARGO_WEIGHT ||
            truck->currentVolume + package.volume > MAX_CARGO_VOLUME) {
            continue; // Truck is already full
        }

        // Calculate nearest distance from truck route to package destination
        int closestPointIndex = findNearestPointOnRoute(&truck->route, &package.destination);
        double distanceToDestination = calculateDistance(&truck->route.points[closestPointIndex], &package.destination);

        // Find truck with minimum distance to destination
        if (distanceToDestination < minDistance || (distanceToDestination == minDistance && 
            (truck->currentWeight + truck->currentVolume) < 
            (trucks[bestTruck].currentWeight + trucks[bestTruck].currentVolume))) {
            minDistance = distanceToDestination;
            bestTruck = i;
        }
    }
    return bestTruck;
}

// Update truck cargo details after adding a package
void updateTruckCargo(Truck* truck, Package package) {
    truck->currentWeight += package.weight;
    truck->currentVolume += package.volume;
}

// Main function for testing
int main(void) {
    Map baseMap = populateMap();

    // Initialize trucks with routes and zero cargo
    Truck trucks[3] = {
        { getBlueRoute(), 0, 0.0, 'B' },
        { getGreenRoute(), 0, 0.0, 'G' },
        { getYellowRoute(), 0, 0.0, 'Y' }
    };

    Package package1 = { 500, 1.0, {8, 'Y' - 'A'} }; // Example package

    int assignedTruckIndex = assignPackageToTruck(package1, trucks, 3);
    if (assignedTruckIndex != -1) {
        printf("Package assigned to %c truck.\n", trucks[assignedTruckIndex].lineColor);
        updateTruckCargo(&trucks[assignedTruckIndex], package1);
    } else {
        printf("Ships tomorrow\n");
    }

    printMap(&baseMap, 1, 1);
    return 0;
}
