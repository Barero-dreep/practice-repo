#include "a_star.h"

std::ostream& Map::displayMap(std::ostream& os) {
    for (size_t i = 0; i < getHeight(); i++) {
        for (size_t j = 0l; j < getWidth(); j++)
            os << m_map[i][j] << " ";
        os << std::endl;
        for (size_t j = 0u; j < getWidth(); j++)
            os << "  ";
        os << std::endl;
    }

    return os;
}

std::ostream& Map::displayPathOnMap(Path& path, std::ostream& os) {
    // TODO: insert return statement here
}

bool Map::isValid(const Point& p) {
    return p.row > 0 && p.row < getHeight() && p.column > 0 && p.column < getWidth();
}

Path& Map::findPath(const Point& start, const Point& dest) {
    return aStarAlgo(*this, start, dest);
}

float heuristics(Point& p1, Point& p2) {
    return sqrt(pow(p2.row - p1.row, 2)
        +
        pow(p2.column - p1.column, 2));
}

bool isDestination(const int row, const int column, const Point& dest) {
    return dest.row == row && dest.column == column;
}

Path& aStarAlgo(Map& map, const Point& start, const Point& dest) {
    Path finalPath{};

    if(!map.isValid(start) || !map.isValid(dest)) return finalPath;

    // if(!map.isUnblocked(start) || !map.isUnBlocked(dest)) return finalPath;

    if(start == dest) return finalPath;

    bool closedList[MAP_ROWS][MAP_COLS]{ false };
    Cell cells[MAP_ROWS][MAP_COLS];
    std::set<std::pair<double, Point>> openList;
    bool foundDest = false;
    int i = start.row, j = start.column;

    cells[i][j].f = 0.0;
    cells[i][j].g = 0.0;
    cells[i][j].h = 0.0;
    cells[i][j].parent.row = i;
    cells[i][j].parent.column = j;

    openList.insert(std::make_pair(0.0, Point(i,j)));


    while (!openList.empty()) {
        std::pair<double, Point> p = *openList.begin();
        openList.erase(openList.begin());

        i = p.second.row;
        j = p.second.column;
        closedList[i][j] = true;

        double gNew, hNew, fNew;

        for (int row = -1; row <= 1; row++) {
            for (int col = -1; col <= 1; col++) {
                // remove that if we want to look in all directions
                // better to put here some kind of bool?
                if ((row == 0 && col == 0) || (row != 0 && col != 0))
                    continue;

                int iNew = i + row;
                int jNew = j + col;

                if (iNew >= 0 && iNew < MAP_ROWS && jNew >= 0 && jNew < MAP_COLS) {
                    if (Point(iNew, jNew) == dest) {
                        cells[iNew][jNew].parent.row = i;
                        cells[iNew][jNew].parent.column = j;
                        foundDest = true;

                        return tracePath(cells, start, dest);
                    }
                    else if (closedList[iNew][jNew] == false &&
                             map.isUnBlocked(Point(iNew, jNew))) {
                        // put isUnblocked here
                        gNew = cells[iNew][jNew].g + 1.0;
                        hNew = heuristics(Point(iNew, jNew), dest);
                        fNew = gNew + hNew;

                        if (cells[iNew][jNew].f == FLT_MAX ||
                            cells[iNew][jNew].f > fNew) {
                            openList.insert(std::make_pair(fNew, Point(iNew, jNew)));

                            cells[iNew][jNew].g = gNew;
                            cells[iNew][jNew].h = hNew;
                            cells[iNew][jNew].f = fNew;
                            cells[iNew][jNew].parent.row = i;
                            cells[iNew][jNew].parent.column = j;
                        }
                    }
                }
            }
        }

    }


    return finalPath;
}