#include <fstream>
#include <string>
#include <set>
#include <array>
#include <utility>
#include <cmath>

class Rope {
    constexpr static size_t SQRT_5 = 2;

    private:
        std::array<std::pair<long, long>, 10> knots;
        std::set<std::pair<long, long>> visited;
    public:
        Rope() {
            const std::pair<long, long> null_pair = std::make_pair(0, 0);
            for(size_t i = 0; i < 10; i++)
                knots[i] = null_pair;

            visited.insert(null_pair);
        }

        inline size_t get_distance(const std::pair<long, long>& head, const std::pair<long, long>& tail) {
            return (size_t)(floor(sqrt(pow(head.first - tail.first, 2) + pow(head.second - tail.second, 2))));
        }

        void adjust_tail(std::pair<long, long>& head, std::pair<long, long>& tail) {
            if(head.first == tail.first && abs(head.second - tail.second) > 1) {
                tail.second += (head.second > tail.second) ? (1) : (-1);
            } else if(head.second == tail.second && abs(head.first - tail.first) > 1) {
                tail.first += (head.first > tail.first) ? (1) : (-1);
            } else if(get_distance(head, tail) == SQRT_5) {
                long x_diff = head.first - tail.first;
                long y_diff = head.second - tail.second;

                if(x_diff >= 1) {
                    tail.first++;
                    tail.second += (y_diff >= 1) ? (1) : (-1);
                } else if(x_diff <= -1) {
                    tail.first--;
                    tail.second += (y_diff >= 1) ? (1) : (-1);
                }
            }
        }

        void adjust_tails() {
            for(size_t i = 0; i < 9; i++)
                adjust_tail(knots[i], knots[i + 1]);

            visited.insert(knots[9]);
        }

        void go_up(const size_t& how_much) {
            for(size_t i = 0; i < how_much; i++) {
                knots[0].second++;
                adjust_tails();
            }
        }

        void go_right(const size_t& how_much) {
            for(size_t i = 0; i < how_much; i++) {
                knots[0].first++;
                adjust_tails();
            }
        }

        void go_down(const size_t& how_much) {
            for(size_t i = 0; i < how_much; i++) {
                knots[0].second--;
                adjust_tails();
            }
        }

        void go_left(const size_t& how_much) {
            for(size_t i = 0; i < how_much; i++) {
                knots[0].first--;
                adjust_tails();
            }
        }

        size_t get_visited() {
            return visited.size();
        }
};

int main(int argc, char** argv) {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    Rope rope;

    std::string line;
    while(std::getline(in, line)) {
        char direction = line[0];
        size_t how_much = std::stoul(line.substr(2, std::string::npos));

        switch(direction) {
            case 'U':
                rope.go_up(how_much);
                break;
            case 'R':
                rope.go_right(how_much);
                break;
            case 'D':
                rope.go_down(how_much);
                break;
            case 'L':
                rope.go_left(how_much);
                break;
        }
    }

    out << rope.get_visited() << std::endl;

    in.close();
    out.close();
    return 0;
}