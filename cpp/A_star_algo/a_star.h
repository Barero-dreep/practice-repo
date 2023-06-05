#ifndef A_STAR_H
#define A_STAR_H

#define TWO_DIMENTION_ALGO 2
// #define THREE_DIMENTION_ALGO 3

#define MOWMENT_COST 1

#define MAP_ROWS 25
#define MAP_COLS 25

#include <iostream>
#include <iomanip>

#include <vector>
#include <set>

#include <cmath>
#include <cfloat>
#include <algorithm>

struct Point {
	int row;
	int column;
//#ifdef THREE_DIMENTIONS
//	size_t z;
//#endif
	Point() = default;
	Point(int i, int j) : row(i), column(j){}

	bool operator==(const Point& other) const {
		return this->row == other.row && this->column == other.column;
	};
};

struct Cell {
	Point parent;

	double f, g, h;

	Cell() : parent(-1,-1) {
		f = g = h = FLT_MAX;
	}
};

using Path = std::vector<Point>;
// TODO: write a route class:
// Should have:
//		array of points
//		finite number of points ??
//		method addPoint
//		operator[] overload to get points
//		reverse method to reverse array, possible usage of STL's reverse
//		trace path, to trace the path ??
//


class Map {
	size_t height = 25;
	size_t width = 25;

	int m_map[25][25]{ 0 };
public:
	std::ostream& displayMap(std::ostream& os = std::cout);
	std::ostream& displayPathOnMap(Path& path, std::ostream& os = std::cout);
	int getHeight() const { return height; };
	int getWidth()  const { return width;  };

	bool isValid(const Point& p);
	//bool isUnBlocked(const Point& p);

	Path& findPath(const Point& start, const Point& dest);
};

float heuristics(Point p1, Point p2);

bool isDestination(const int row, const int col, const Point& dest);

Path& aStarAlgo(Map& map, const Point& start, const Point& dest);

#endif