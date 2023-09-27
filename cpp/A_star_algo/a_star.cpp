// Done by Vladyslav Savchyn
// on 2023-06-06

#include "a_star.h"

std::ostream& Map::displayMap(std::ostream& os) {
    size_t rows = getHeight();
    size_t cols = getWidth();

    for (size_t i = 0; i < rows; i++) {
        // Printing columns
        for (size_t j = 0u; j < cols; j++) {
            
            switch (m_map[i][j]) 
            {
            default:
                os << "W";
                break;
            case Constraints::nothing:
                os << " ";
                break;
            case Constraints::wall:
                os << static_cast<char>(219);
                break;
            case Constraints::path:
                os << "\033[38;2;255;211;0mP\033[0m";
                break;
            case Constraints::start:
                os << "\033[38;2;11;218;81mS\033[0m";
                break;
            case Constraints::destination:
                os << "\033[38;2;245;00mD\033[0m";
            }

            os << ((j != cols - 1) ? "|" : "\n");
        }

        // Printing row border
        if (i != rows - 1) {
            for (size_t j = 0u; j < cols; j++)
                os << "- ";
            os << '\n';
        }
    }
    return os;
}

size_t Map::getHeight() const{
    return height;
}

size_t Map::getWidth() const {
    return width;
}

Map& Map::changeValueAtPoint(const Point& point, int value) {
    if (isValid(point)) {
        m_map[point.row][point.column] = value;
    }
    return *this;
}

Map& Map::changeValueAtPoint(const Point& from, const Point& to, int value) {
    int row = from.row;
    int col = from.column;
    int height = abs(to.row - row) + 1;
    int width = abs(to.column - col) + 1;

    if (isValid(from) && isValid(to)) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                m_map[row + i][col + j] = value;
            }
        }
    }
    return *this;
}

bool Map::isValid(const Point& p) const {
    return p.row >= 0 && (size_t)p.row < getHeight() && p.column >= 0 && (size_t)p.column < getWidth();
}

bool Map::isUnBlocked(const Point& p) const {
    return m_map[p.row][p.column] != 1;
}

Path& Path::addPoint(const Point& tmp_point) { 
    points.push_back(tmp_point);
    return *this;
}

Point Path::operator[](size_t i) const{
    return i < points.size() ? points[i] : Point();
}

size_t Path::getSize() const {
    return points.size();
}

void Path::reverse() {
    std::reverse(points.begin(), points.end());
}

bool Path::isDestination(const int row, const int column, const Point& dest) const {
    return dest.row == row && dest.column == column;
}

double Path::heuristics(const Point& p1, const Point& p2) {
    return sqrt(pow(p2.row - p1.row, 2)
                +
                pow(p2.column - p1.column, 2));
}


Path& Path::tracePath(Cell cells[][MAP_COLS], const Point& start, const Point& end) {
    Point p = end;

    while (cells[p.row][p.column].parent != p) {
        this->addPoint(p);

        p = cells[p.row][p.column].parent;
    }

    this->addPoint(start);
    this->reverse();

    return *this;
}

Path& Path::aStarAlgo(const Map& map, const Point& start, const Point& dest, bool allowAllDirs) {
    // Base cases
    if (!map.isValid(start)) {
        std::cout << "Start point is not a valid point\n";
        return *this;
    }

    if (!map.isValid(dest)) {
        std::cout << "Destenation point is not a valid point\n";
        return *this;
    }

    if (!map.isUnBlocked(start)) {
        std::cout << "Start point is blocked\n";
        return *this;
    }

    if (!map.isUnBlocked(dest)) {
        std::cout << "Destenation point is blocked\n";
        return *this;
    }

    if (start == dest) {
        std::cout << "We are already at destenation\n";
        return *this;
    }
    
    // curr version needs constants to run.
    bool closedList[MAP_ROWS][MAP_COLS]{false};
    Cell cells[MAP_ROWS][MAP_COLS];
    
    std::vector<std::pair<double, Point>> openList;
    
    double moveCost = 0.0;
    size_t steps = 0;
    int i = start.row, j = start.column;

    cells[i][j].f = 0.0;
    cells[i][j].g = 0.0;
    cells[i][j].h = 0.0;
    cells[i][j].parent.row = i;
    cells[i][j].parent.column = j;

    openList.emplace_back(std::make_pair(0.0, Point(i,j)));

    while (!openList.empty()) {
        if (steps++ >= max_num_points) {
            std::cout << "Reached max num of steps\n";
            return *this;
        }

        std::pair<double, Point> p = *openList.begin();
        openList.erase(openList.begin());

        i = p.second.row;
        j = p.second.column;
        closedList[i][j] = true;

        double gNew, hNew, fNew;

        for (int row = -1; row <= 1; row++) {
            for (int col = -1; col <= 1; col++) {
                // Check if we can move vertically and horizontaly
                if (!allowAllDirs && ((row == 0 && col == 0) || (row != 0 && col != 0)))
                    continue;

                moveCost = (row != 0 && col != 0) ? DIAGONAL_MOVE_COST : VERTICAL_MOVE_COST;

                int iNew = i + row;
                int jNew = j + col;

                if (map.isValid(Point(iNew, jNew))) {
                    if (Point(iNew, jNew) == dest) {
                        cells[iNew][jNew].parent.row = i;
                        cells[iNew][jNew].parent.column = j;
                        
                        // std::cout << "Path was found!\n";
                        
                        return this->tracePath(cells, start, dest);
                    }
                    else if (closedList[iNew][jNew] == false && map.isUnBlocked(Point(iNew, jNew)))  {
                        gNew = cells[i][j].g + moveCost;
                        hNew = Path::heuristics(Point(iNew, jNew), dest);
                        fNew = gNew + hNew;

                        if (cells[iNew][jNew].f == FLT_MAX || cells[iNew][jNew].f > fNew) {
                            openList.emplace_back(std::make_pair(fNew, Point(iNew, jNew)));

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

    return *this;
}

void displayPathOnMap(const Map& map, const Path& path) {
    Map newMap(map);
    size_t sizeOfPath = path.getSize();

    // Looking if the path is valid in terms of our map
    for (size_t i = 0; i < sizeOfPath; i++)
        if (!map.isValid(path[i])) {
            std::cout << "Path is invalid" << std::endl;
            return;
        }

    // Writting a path into newMap
    newMap.changeValueAtPoint(path[0], Constraints::start);
    for (size_t i = 1; i < sizeOfPath - 1; i++)
        newMap.changeValueAtPoint(path[i], Constraints::path);
    newMap.changeValueAtPoint(path[sizeOfPath - 1], Constraints::destination);

    // Displaying actual map
    newMap.displayMap() << std::endl;
}
