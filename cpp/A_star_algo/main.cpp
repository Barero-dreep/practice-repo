#include <iostream>
#include <chrono>

#include "a_star.hpp"

int main() {
	Map map;
	Path path;

	map.changeValueAtPoint(Point(2, 1), Point(5, 9));
	map.changeValueAtPoint(Point(1, 2), Point(7, 40));
	map.changeValueAtPoint(Point(15, 15), Point(30, 30));

	std::cout << "Don\'t forget to make the console\'s text smaller, as there can be some artifacts \n" 
			  << "when you try to display \"big\" test cases (like current one)\n"
			  << "Start? (press ENTER to continue)\n";

	while (std::cin.get() != '\n')
		;

	// Calculating the path and measuring the time
	auto start = std::chrono::high_resolution_clock::now();
	path.aStarAlgo(map, Point(1, 1), Point(30, 31));
	auto end = std::chrono::high_resolution_clock::now();

	displayPathOnMap(map, path);
	// display current map
	// map.displayMap();

	std::cout << "Elapsed for " << std::chrono::duration<double> (end - start).count() << "s" << std::endl;

	return 0;
}