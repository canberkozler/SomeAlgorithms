#include <iostream>
#include <set>
#include "astar.hpp"

constexpr std::size_t ROW {9};
constexpr std::size_t COL {10};

std::ostream& operator<<(std::ostream& os, const AStar::ullPair& ullpair){
    return os << "(" << ullpair.first <<", " << ullpair.second<< ") ";
}

std::ostream& arrow(std::ostream& os){
    return os << "-> ";
}

bool AStar::is_valid(std::size_t row, std::size_t col) const{
    return (row < ROW) && (col < COL);
}
 
bool AStar::is_unblocked(const Map& grids, std::size_t row, std::size_t col) const{
    if (grids[row][col]) return true;
    return false;
}

bool AStar::is_path_completed(std::size_t row, std::size_t col, const ullPair& dest) const{
    if (row == dest.first && col == dest.second) return true;
    return false;
}
 
double AStar::calculate_h_value(std::size_t row, std::size_t col, const ullPair& dest) const{
    // Returns distance formula
    return sqrt((row-dest.first)*(row-dest.first) + (col-dest.second)*(col-dest.second));
}
 
void AStar::trace_path(const Cells& cellDetails, const ullPair& dest){
    std::cout << "\nThe Path is ";
    auto row = dest.first;
    auto col = dest.second;
 
    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)){
        path.emplace_front(row, col);
        auto temp_row = cellDetails[row][col].parent_i;
        auto temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }
    path.emplace_front(row, col);
}

void AStar::a_star_search(const Map& grids, const ullPair& src, const ullPair& dest){
    if (!is_valid(src.first, src.second)){
        std::cout <<"Source is invalid\n";
        return;
    }

    if (!is_valid(dest.first, dest.second)){
        std::cout <<"Destination is invalid\n";
        return;
    }

    if (!(is_unblocked(grids, src.first, src.second) && is_unblocked(grids, dest.first, dest.second))){
        std::cout <<"Source or the destination is blocked\n";
        return;
    }

    if (is_path_completed(src.first, src.second, dest)){
        std::cout <<"Already at the destination\n";
        return;
    }
 
    // Create a closed list and initialise it to false which means that no cell has been included yet
    Map closedList(ROW, std::vector<bool>(COL));

    // Declare a 2D array of structure to hold the details of that cell
    Cells cellDetails(ROW, std::vector<cell>(COL));
 
    cellDetails[src.first][src.second].parent_i = src.first;
    cellDetails[src.first][src.second].parent_j = src.second;
 
    /*
     * Create an set having information as- <f, <i, j>>
     * where f = g + h, and i is row, j is column index of that cell.
     */
    std::set<pPair> open_list;

    // f is 0.0 on initial state.
    open_list.emplace(0.0, std::make_pair(src.first, src.second));
 
    // Flag holding to reach to destination.
    bool is_dest_found{};
 
    while(!open_list.empty()){
        auto i = (*open_list.begin()).second.first;
        auto j = (*open_list.begin()).second.second;
 
        // Remove this vertex from the open list
        open_list.erase(open_list.begin());
    
        closedList[i][j] = true;

        double gNew, hNew, fNew;

        // North
        if (is_valid(i-1, j)){

            if (is_path_completed(i-1, j, dest)){
                cellDetails[i-1][j].parent_i = i;
                cellDetails[i-1][j].parent_j = j;

                std::cout<<"The destination cell is found\n";
                trace_path (cellDetails, dest);
                is_dest_found = true;
                return;
            }
            else if ((!closedList[i-1][j]) && is_unblocked(grids, i-1, j)){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculate_h_value(i-1, j, dest);
                fNew = gNew + hNew;
 
                // If it isn’t on the open list, add it to
                // the open list. Make the current square
                // the parent of this square. Record the
                // f, g, and h costs of the square cell
                //                OR
                // If it is on the open list already, check
                // to see if this path to that square is better,
                // using 'f' cost as the measure.
                if ((cellDetails[i-1][j].f == cell::dMax) || (cellDetails[i-1][j].f > fNew)){
                    open_list.emplace(fNew, std::make_pair(i-1, j));
 

                    cellDetails[i-1][j].f = fNew;
                    cellDetails[i-1][j].g = gNew;
                    cellDetails[i-1][j].h = hNew;
                    cellDetails[i-1][j].parent_i = i;
                    cellDetails[i-1][j].parent_j = j;
                }
            }
        }
 
        // South
        if (is_valid(i+1, j)){
            if (is_path_completed(i+1, j, dest)){
                cellDetails[i+1][j].parent_i = i;
                cellDetails[i+1][j].parent_j = j;

                std::cout<<"The destination cell is found\n";
                trace_path(cellDetails, dest);
                is_dest_found = true;
                return;
            }
            else if ((!closedList[i+1][j]) && is_unblocked(grids, i+1, j)){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculate_h_value(i+1, j, dest);
                fNew = gNew + hNew;

                if ((cellDetails[i+1][j].f == cell::dMax) || (cellDetails[i+1][j].f > fNew)){
                    open_list.emplace(fNew, std::make_pair(i+1, j));

                    cellDetails[i+1][j].f = fNew;
                    cellDetails[i+1][j].g = gNew;
                    cellDetails[i+1][j].h = hNew;
                    cellDetails[i+1][j].parent_i = i;
                    cellDetails[i+1][j].parent_j = j;
                }
            }
        }
 
        // East
        if(is_valid (i, j+1)){
            if(is_path_completed(i, j+1, dest)){
                cellDetails[i][j+1].parent_i = i;
                cellDetails[i][j+1].parent_j = j;

                std::cout<<"The destination cell is found\n";
                trace_path(cellDetails, dest);
                is_dest_found = true;
                return;
            }
            else if((!closedList[i][j+1]) && is_unblocked (grids, i, j+1)){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculate_h_value (i, j+1, dest);
                fNew = gNew + hNew;

                if ((cellDetails[i][j+1].f == cell::dMax) || (cellDetails[i][j+1].f > fNew)){
                    open_list.emplace(fNew, std::make_pair(i, j+1));

                    cellDetails[i][j+1].f = fNew;
                    cellDetails[i][j+1].g = gNew;
                    cellDetails[i][j+1].h = hNew;
                    cellDetails[i][j+1].parent_i = i;
                    cellDetails[i][j+1].parent_j = j;
                }
            }
        }
 
        // West
        if (is_valid(i, j-1)){
            if (is_path_completed(i, j-1, dest)){
                cellDetails[i][j-1].parent_i = i;
                cellDetails[i][j-1].parent_j = j;

                std::cout<<"The destination cell is found\n";
                trace_path(cellDetails, dest);
                is_dest_found = true;
                return;
            }
            else if ((!closedList[i][j-1]) && is_unblocked(grids, i, j-1)){
                gNew = cellDetails[i][j].g + 1.0;
                hNew = calculate_h_value(i, j-1, dest);
                fNew = gNew + hNew;
 
                if ((cellDetails[i][j-1].f == cell::dMax) || (cellDetails[i][j-1].f > fNew))
                {
                    open_list.emplace(fNew, std::make_pair(i, j-1));

                    cellDetails[i][j-1].f = fNew;
                    cellDetails[i][j-1].g = gNew;
                    cellDetails[i][j-1].h = hNew;
                    cellDetails[i][j-1].parent_i = i;
                    cellDetails[i][j-1].parent_j = j;
                }
            }
        }
 
        // North-East
        if (is_valid(i-1, j+1)){
            if (is_path_completed(i-1, j+1, dest)){
                cellDetails[i-1][j+1].parent_i = i;
                cellDetails[i-1][j+1].parent_j = j;

                std::cout<<"The destination cell is found\n";
                trace_path (cellDetails, dest);
                is_dest_found = true;
                return;
            }
            else if ((!closedList[i-1][j+1]) && is_unblocked(grids, i-1, j+1)){
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculate_h_value(i-1, j+1, dest);
                fNew = gNew + hNew;
 
                if ((cellDetails[i-1][j+1].f == cell::dMax) || (cellDetails[i-1][j+1].f > fNew)){
                    open_list.emplace(fNew, std::make_pair(i-1, j+1));
 
                    cellDetails[i-1][j+1].f = fNew;
                    cellDetails[i-1][j+1].g = gNew;
                    cellDetails[i-1][j+1].h = hNew;
                    cellDetails[i-1][j+1].parent_i = i;
                    cellDetails[i-1][j+1].parent_j = j;
                }
            }
        }
 
        // North-West
        if (is_valid (i-1, j-1)){
            if (is_path_completed (i-1, j-1, dest)){
                cellDetails[i-1][j-1].parent_i = i;
                cellDetails[i-1][j-1].parent_j = j;

                std::cout<<"The destination cell is found\n";
                trace_path (cellDetails, dest);
                is_dest_found = true;
                return;
            }
            else if ((!closedList[i-1][j-1]) && is_unblocked(grids, i-1, j-1)){
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculate_h_value(i-1, j-1, dest);
                fNew = gNew + hNew;
 
                if ((cellDetails[i-1][j-1].f == cell::dMax) || (cellDetails[i-1][j-1].f > fNew)){
                    open_list.emplace(fNew, std::make_pair(i-1, j-1));

                    cellDetails[i-1][j-1].f = fNew;
                    cellDetails[i-1][j-1].g = gNew;
                    cellDetails[i-1][j-1].h = hNew;
                    cellDetails[i-1][j-1].parent_i = i;
                    cellDetails[i-1][j-1].parent_j = j;
                }
            }
        }
 
        // South-East
        if (is_valid(i+1, j+1)){
            if (is_path_completed(i+1, j+1, dest)){
                cellDetails[i+1][j+1].parent_i = i;
                cellDetails[i+1][j+1].parent_j = j;
                std::cout<<"The destination cell is found\n";
                trace_path (cellDetails, dest);
                is_dest_found = true;
                return;
            }
            else if ((!closedList[i+1][j+1]) && is_unblocked(grids, i+1, j+1)) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculate_h_value(i+1, j+1, dest);
                fNew = gNew + hNew;
 
                if ((cellDetails[i+1][j+1].f == cell::dMax) || (cellDetails[i+1][j+1].f > fNew))
                {
                    open_list.emplace(fNew, std::make_pair(i+1, j+1));
 
                    cellDetails[i+1][j+1].f = fNew;
                    cellDetails[i+1][j+1].g = gNew;
                    cellDetails[i+1][j+1].h = hNew;
                    cellDetails[i+1][j+1].parent_i = i;
                    cellDetails[i+1][j+1].parent_j = j;
                }
            }
        }
 
        // South-West
        if (is_valid (i+1, j-1)){
            if (is_path_completed(i+1, j-1, dest)){
                cellDetails[i+1][j-1].parent_i = i;
                cellDetails[i+1][j-1].parent_j = j;

                std::cout<<"The destination cell is found\n";
                trace_path(cellDetails, dest);
                is_dest_found = true;
                return;
            }
            else if ((!closedList[i+1][j-1]) && is_unblocked(grids, i+1, j-1)) {
                gNew = cellDetails[i][j].g + 1.414;
                hNew = calculate_h_value(i+1, j-1, dest);
                fNew = gNew + hNew;
 
                if ((cellDetails[i+1][j-1].f == cell::dMax) || (cellDetails[i+1][j-1].f > fNew))
                {
                    open_list.emplace(fNew, std::make_pair(i+1, j-1));

                    cellDetails[i+1][j-1].f = fNew;
                    cellDetails[i+1][j-1].g = gNew;
                    cellDetails[i+1][j-1].h = hNew;
                    cellDetails[i+1][j-1].parent_i = i;
                    cellDetails[i+1][j-1].parent_j = j;
                }
            }
        }
    }
 
    if (is_dest_found == false)
        std::cout<<"Failed to find the destination\n";
}

void AStar::calculate_length_of_path(){
    if(path.size() == 2){
        plength = calculate_distance(*path.cbegin(), *next(path.cbegin()));
        return;
    }

    for(auto it = path.cbegin(); it != prev(path.cend()); ++it){
        plength+= calculate_distance(*it, *next(it));
    }
}

void AStar::run_a_star(){
    if(is_anything_null()){
        std::cout << "Null Input/Inputs!!\nMake sure, all inputs are setted.\n";
        return;
    }
    path.clear();
    plength = .0;

    a_star_search(*map, *source, *destination);

    path.shrink_to_fit();

    if(path.size()>1)
        calculate_length_of_path();
}

void AStar::reset(){
    map = nullptr;
    source = nullptr;
    destination = nullptr;

    path.clear();
    path.shrink_to_fit();
    plength = .0;
}

/*
 N.W   N   N.E
   \   |   /
    \  |  /
 W----Cell----E
      / | \
    /   |  \
 S.W    S   S.E
*/
int main()
{
    /* 
     * 1--> The cell is not blocked
     * 0--> The cell is blocked    
     */
    AStar::Map grids{
        { 1, 0, 1, 1, 1, 1, 0, 1, 0, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 0, 0 },
        { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
        { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
        { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
    };
    AStar::ullPair src = std::make_pair(8, 0);
    AStar::ullPair dest = std::make_pair(8, 9);

    AStar aStarSearch{grids, src, dest};

    aStarSearch.run_a_star();

    auto path = aStarSearch.get_path();

    for(auto&& pr: path){
        std::cout << arrow << pr;
    }

    std::cout <<"\nLength of path: " << aStarSearch.get_length();
}