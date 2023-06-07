// Done by Vladyslav Savchyn
// 2023-06-06

#ifndef A_STAR_H
#define A_STAR_H

#define MAP_ROWS 10u
#define MAP_COLS 10u

#define VERTICAL_MOVE_COST 1.0
#define DIAGONAL_MOVE_COST 1.41

enum Constraints
{
	nothing,
	wall,
	path,
	start,
	destination
};

#define WALL 1
#define PATH 2
#define START 3
#define DEST 4

#include <iostream>

#include <vector>

#include <cmath>
#include <float.h>

#include <algorithm>

struct Point {
	int row;
	int column;

	Point() : row(-1), column(-1){}
	Point(int i, int j) : row(i), column(j){}

	bool operator==(const Point& other) const {
		return this->row == other.row && this->column == other.column;
	}
};

struct Cell {
	Point parent;

	double f, g, h;

	Cell() : parent(-1,-1) {
		f = g = h = FLT_MAX;
	}
};

class Map {
	size_t height = MAP_ROWS;
	size_t width = MAP_COLS;

	char m_map[MAP_ROWS][MAP_COLS] = { '\0' };
public:
	Map() = default;
	Map(const Map& other) = default;
	Map(Map&& other) = default;

	std::ostream& displayMap(std::ostream& os = std::cout);

	size_t getHeight() const { return height; };
	size_t getWidth()  const { return width;  };

	Map& changeValueAtPoint(const Point& point, int value = 1);
	Map& changeValueAtPoint(const Point& from, const Point& to, int value = 1);

	bool isValid(const Point& p) const;
	bool isUnBlocked(const Point& p) const;	
};

class Path {
	std::vector<Point> points;
	size_t max_num_points = MAP_ROWS * MAP_COLS;
public:
	Path() = default;
	Path(const Path& other) = default;
	Path(Path&& other) = default;

	void reverse();
	bool isDestination(const int row, const int col, const Point& dest) const;

	Path& addPoint(const Point& tmp_point);
	Point operator[] (size_t i) const;
	size_t getSize() const;

	double heuristics(const Point& p1, const Point& p2);
	Path& tracePath(Cell cells[][MAP_COLS], const Point& start, const Point& end);
	Path& aStarAlgo(const Map& map, const Point& start, const Point& dest, bool allowAllDirs = true);
};

void displayPathOnMap(const Map& map, const Path& path);

#endif
