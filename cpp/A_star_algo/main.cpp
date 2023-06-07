#include <iostream>

#include "a_star.h"

int main() {
	Map map;
	Path path;

	map.changeValueAtPoint(Point(2,1), Point(5,9));
	displayPathOnMap(map, path.aStarAlgo(map,Point(1,1),Point(6,6)));

	return 0;
}