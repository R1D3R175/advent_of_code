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

    size_t max_scenic_score = 0;

    const size_t R = trees.size();
    const size_t C = trees[0].size();

    for(size_t i = 1; i < R - 1; i++) {
        for(size_t j = 1; j < C - 1; j++) {
            size_t top    = 1,
                   right  = 1,
                   bottom = 1,
                   left   = 1;

            for(size_t y = i - 1; y > 0; y--) {
                if (trees[y][j] >= trees[i][j]) break;

                top++;
            }
            
            for(size_t y = i + 1; y < R - 1; y++) {
                if (trees[y][j] >= trees[i][j]) break;

                bottom++;
            }

            for(size_t x = j - 1; x > 0; x--) {
                if (trees[i][x] >= trees[i][j]) break;

                left++;
            }

            for(size_t x = j + 1; x < C - 1; x++) {
                if (trees[i][x] >= trees[i][j]) break;

                right++;
            }

            max_scenic_score = std::max(max_scenic_score, top * right * bottom * left);
        }
    }

    out << max_scenic_score << std::endl;

    in.close();
    out.close();
    return 0;
}