#include <fstream>
#include <array>
#include <string>
#include <algorithm>

int main(int argc, char** argv) {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    size_t priorities_sum = 0;

    std::array<std::string, 3> rucksacks;
    while(in >> rucksacks[0] >> rucksacks[1] >> rucksacks[2]) {
        std::sort(rucksacks[0].begin(), rucksacks[0].end());
        std::sort(rucksacks[1].begin(), rucksacks[1].end());
        std::sort(rucksacks[2].begin(), rucksacks[2].end());

        std::string intersection;

        std::set_intersection(
            rucksacks[0].begin(), rucksacks[0].end(),
            rucksacks[1].begin(), rucksacks[1].end(),
            std::back_inserter(intersection)
        );

        std::set_intersection(
            intersection.begin(), intersection.end(),
            rucksacks[2].begin(), rucksacks[2].end(),
            intersection.begin()
        );

        priorities_sum += (size_t)(intersection[0]) - (islower(intersection[0]) ? 'a' : 'A' - 26) + 1;
    }

    out << priorities_sum << std::endl;

    in.close();
    out.close();
    return 0;
}