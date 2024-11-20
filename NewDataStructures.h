// NewDataStructures.h
#ifndef NEW_DATA_STRUCTURES_H
#define NEW_DATA_STRUCTURES_H

#define MAP_ROWS 25
#define MAP_COLS 25
#define MAX_ROUTE 100
#define BLUE 2
#define GREEN 4
#define YELLOW 8
#define DIVERSION 16
#define MAX_CARGO_WEIGHT 2000
#define MAX_CARGO_VOLUME 20.0

typedef struct {
    int squares[MAP_ROWS][MAP_COLS];
    int numRows;
    int numCols;
} Map;

typedef struct {
    char row;
    char col;
} Point;

typedef struct {
    Point points[MAX_ROUTE];
    int numPoints;
    char routeSymbol;
} Route;

typedef struct {
    int weight;
    double volume;
    Point destination;
} Package;

typedef struct {
    Route route;
    int currentWeight;
    double currentVolume;
    char lineColor;
} Truck;

#endif // NEW_DATA_STRUCTURES_H
