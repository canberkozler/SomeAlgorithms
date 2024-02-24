#pragma once
#include <vector>
#include <limits>
#include <deque>
#include <cmath>
#include <iosfwd>

struct cell{
    static constexpr double dMax = std::numeric_limits<double>::max();

    int parent_i{-1}, parent_j{-1};
    double f{cell::dMax}, g{cell::dMax}, h{cell::dMax}; // f = g + h
};

class AStar{
    public:
        using ullPair = std::pair<std::size_t, std::size_t>;
        using pPair = std::pair<double, ullPair>;
        using Map = std::vector<std::vector<bool>>;
        using Cells = std::vector<std::vector<cell>>;

        AStar() = default;
        ~AStar() = default;
        
        AStar(const Map& mp): map{&mp}{}
        AStar(const ullPair& sc, const ullPair& ds): source{&sc}, destination{&ds} {}
        AStar(const Map& mp, const ullPair& sc, const ullPair& ds): map{&mp}, source{&sc}, destination{&ds}{}

        // To prevent copy and move object.
        AStar(const AStar&) = delete;
        AStar& operator=(const AStar&) = delete;

        void set_map(const Map& mp){
            map = &mp;
        }

        void set_source(const ullPair& sc){
            source = &sc;
        }

        void set_destination(const ullPair& mp){
            destination = &mp;
        }

        const Map& get_map()const&{
            return *map;
        }

        const ullPair& get_source()const&{
            return *source;
        }

        const ullPair& get_destination()const&{
            return *destination;
        }
        
        std::vector<ullPair> get_path()const{
            return {path.begin(), path.end()};
        }

        double get_length()const{
            return plength;
        }

        // Driver Code.
        void run_a_star();

        // Clear members.
        void reset();
    
    private:
        // Check whether given cell is a valid cell or not.
        bool is_valid(std::size_t row, std::size_t col) const;

        // Check whether the given cell is blocked or not. Return true when cell is unblocked.
        bool is_unblocked(const Map &grids, std::size_t row, std::size_t col) const;

        // Check whether destination cell has been reached or not.
        bool is_path_completed(std::size_t row, std::size_t col, const ullPair &dest) const;

        // Calculate the 'h' heuristics.
        double calculate_h_value(std::size_t row, std::size_t col, const ullPair &dest) const;

        // Trace the path from the source to destination.
        void trace_path(const Cells &cellDetails, const ullPair &dest);

        // Find the shortest path between a given source cell to a destination cell.
        void a_star_search(const Map& grids, const ullPair& src, const ullPair& dest);

        // Calculate length of the path.
        void calculate_length_of_path();

        // Calculate distance between 2 neighbours.
        inline double calculate_distance(const ullPair& u1, const ullPair& u2)const{
            return std::sqrt((static_cast<double>(u1.first)-static_cast<double>(u2.first))*(static_cast<double>(u1.first)-static_cast<double>(u2.first)) 
                            + (static_cast<double>(u1.second)-static_cast<double>(u2.second))*(static_cast<double>(u1.second)-static_cast<double>(u2.second)));
        }

        bool is_anything_null()const{
            return (!map) || (!source) || (!destination);
        }

        const Map* map{};

        const ullPair* source{};
        const ullPair* destination{};

        std::deque<ullPair> path;
        double plength{};
};

// ullPair printer.
std::ostream& operator<<(std::ostream& os, const AStar::ullPair& ullpair);

std::ostream& arrow(std::ostream& os);
