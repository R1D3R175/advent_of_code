#include <fstream>
#include <string>
#include <algorithm>

int main(int argc, char** argv) {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    size_t priorities_sum = 0;

    std::string rucksack;
    while(in >> rucksack) {
        std::string first_compartment, second_compartment, intersection;
        first_compartment = rucksack.substr(0, rucksack.length() / 2);
        second_compartment = rucksack.substr(rucksack.length() / 2, rucksack.length() / 2);

        std::sort(first_compartment.begin(), first_compartment.end());
        std::sort(second_compartment.begin(), second_compartment.end());

        std::set_intersection(
            first_compartment.begin(), first_compartment.end(),
            second_compartment.begin(), second_compartment.end(),
            std::back_inserter(intersection)
        );

        priorities_sum += (size_t)(intersection[0]) - (islower(intersection[0]) ? 'a' : 'A' - 26) + 1;
    }

    out << priorities_sum << std::endl;

    in.close();
    out.close();
    return 0;
}