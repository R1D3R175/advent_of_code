#include <fstream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    std::vector<std::vector<uint8_t>> trees;

    std::string line;
    while(std::getline(in, line)) {
        trees.push_back(std::vector<uint8_t>());
        
        for (const char& c : line) {
            trees.back().push_back(c - '0');
        }
    }

    const size_t R = trees.size();
    const size_t C = trees[0].size();
    size_t visible_trees = R * 2 + (C - 2) * 2;

    for(size_t i = 1; i < R - 1; i++) {
        for(size_t j = 1; j < C - 1; j++) {
            bool visible = false;

            bool entered = false;
            bool broke = false;
            for(int y = i - 1; y >= 0 && !visible; y--) {
                entered = true;

                if(trees[y][j] >= trees[i][j]) {
                    broke = true;
                    break;
                }
            }
            visible = (!broke && entered) || visible;
            
            broke = entered = false;
            for(int y = i + 1; y < R && !visible; y++) {
                entered = true;

                if(trees[y][j] >= trees[i][j]) {
                    broke = true;
                    break;
                }
            }
            visible = (!broke && entered) || visible;

            broke = entered = false;
            for(int x = j - 1; x >= 0 && !visible; x--) {
                entered = true;

                if(trees[i][x] >= trees[i][j]) {
                    broke = true;
                    break;
                }
            }
            visible = (!broke && entered) || visible;

            broke = entered = false;
            for(int x = j + 1; x < C && !visible; x++) {
                entered = true;

                if(trees[i][x] >= trees[i][j]) {
                    broke = true;
                    break;
                }
            }
            visible = (!broke && entered) || visible;

            visible_trees += visible;
        }
    }

    out << visible_trees << std::endl;

    in.close();
    out.close();
    return 0;
}