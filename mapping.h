#pragma once
#ifndef MAPPING_H
#define MAPPING_H

#define MAP_ROWS 25
#define MAP_COLS 25
#define MAX_ROUTE 100
#define BLUE 2
#define GREEN 4
#define YELLOW 8
#define DIVERSION 16
#define MAX_CARGO_WEIGHT 2000
#define MAX_CARGO_VOLUME 20.0

// Structures
struct Map {
    int squares[MAP_ROWS][MAP_COLS];
    int numRows;
    int numCols;
};

struct Point {
    char row;
    char col;
};

struct Route {
    struct Point points[MAX_ROUTE];
    int numPoints;
    char routeSymbol;
};

typedef struct {
    int weight;
    double volume;
    struct Point destination;
} Package;

typedef struct {
    struct Route route;
    int currentWeight;
    double currentVolume;
    char lineColor;
} Truck;

// Function Prototypes
struct Map populateMap();
int getNumRows(const struct Map* map);
int getNumCols(const struct Map* map);
void printMap(const struct Map* map, const int base1, const int alphaCols);
struct Map addRoute(const struct Map* map, const struct Route* route);
void addPtToRoute(struct Route* route, struct Point pt);
void addPointToRouteIfNot(struct Route* route, const int row, const int col, const struct Point notThis);
void addPointToRoute(struct Route* route, const int row, const int col);

struct Route getBlueRoute();
struct Route getGreenRoute();
struct Route getYellowRoute();

double calculateDistance(const struct Point* p1, const struct Point* p2);
struct Route shortestPath(const struct Map* map, const struct Point start, const struct Point dest);
struct Route getPossibleMoves(const struct Map* map, const struct Point p1, const struct Point backpath);
int eqPt(const struct Point p1, const struct Point p2);
int getClosestPoint(const struct Route* route, const struct Point pt);

int assignPackageToTruck(Package package, Truck trucks[], int numTrucks);
void updateTruckCargo(Truck* truck, Package package);

#endif // MAPPING_H
