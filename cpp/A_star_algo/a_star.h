// Done by Vladyslav Savchyn
// 2023-09-26

#ifndef A_STAR_H
#define A_STAR_H

// Current demo will only work with the values up to 150u
// If we give more, the compiler gives stack overflow error
constexpr unsigned int MAP_ROWS = 50;
constexpr unsigned int MAP_COLS = 50;

constexpr double VERTICAL_MOVE_COST = 1.0;
constexpr double DIAGONAL_MOVE_COST = 1.41;

enum Constraints
{
	nothing,
	wall,
	path,
	start,
	destination
};

#include <iostream>

#include <vector>

#include <cmath>
#include <float.h>

#include <algorithm>

// Point in space that can hold in which row and column it is
struct Point {
	int row;
	int column;

	Point() : row(-1), column(-1){}
	Point(int i, int j) : row(i), column(j){}

	bool operator==(const Point& other) const {
		return this->row == other.row && this->column == other.column;
	}

	bool operator!=(const Point& other) const {
		return !(operator==(other));
	}
};

// Cell that holds a values to be calculated
struct Cell {
	Point parent;

	double f, g, h;

	Cell() : parent(-1,-1) {
		f = g = h = FLT_MAX;
	}
};

// 2D map that holds the info
// about what type of cell it has
class Map {
	size_t height = MAP_ROWS;
	size_t width  = MAP_COLS;

	char m_map[MAP_ROWS][MAP_COLS] = { '\0' };
public:
	Map()                 = default;
	Map(const Map& other) = default;
	Map(Map&& other)      = default;

	// Display 2D map into ostream
	std::ostream& displayMap(std::ostream& os = std::cout);

	// Accessor method for height
	size_t getHeight() const;
	// Accessor method for width
	size_t getWidth()  const;

	// Changes one point to specified value (uses Constraints enumeration)
	Map& changeValueAtPoint(const Point& point, int value = Constraints::wall);
	// Changes sqare of points to specified value (uses Constraints enumeration)
	Map& changeValueAtPoint(const Point& from, const Point& to, int value = Constraints::wall);

	// Checks if point is valid
	bool isValid(const Point& p) const;
	// Checks if the point is unblocked
	bool isUnBlocked(const Point& p) const;	
};

class Path {
	std::vector<Point> points;
	size_t max_num_points = MAP_ROWS * MAP_COLS;
public:
	Path() = default;
	Path(const Path& other) = default;
	Path(Path&& other) = default;

	// Reverse the path
	void reverse();
	// Checks if the row & col is a destenation
	bool isDestination(const int row, const int col, const Point& dest) const;

	// Adds the point to the path
	Path& addPoint(const Point& tmp_point);
	// Accessor method for the point at possition specified postion
	Point operator[] (size_t i) const;
	// Accessor for the size of the path
	size_t getSize() const;

	// Heuristics functions for calculating distance
	double heuristics(const Point& p1, const Point& p2);
	// Traces the path from end to the beginning of cells arr, and then
	// reverses the points vector
	Path& tracePath(Cell cells[][MAP_COLS], const Point& start, const Point& end);
	// Main Algorithm
	Path& aStarAlgo(const Map& map, const Point& start, const Point& dest, bool allowAllDirs = true);
};

// Displays the path using map to the ostream
void displayPathOnMap(const Map& map, const Path& path);

#endif
