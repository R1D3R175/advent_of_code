#include <fstream>
#include <string>
#include <array>
#include <numeric>

void update_array(std::array<size_t, 3>& elves, const size_t& elf) {
    if(elf > elves[0]) {
        elves[2] = elves[1];
        elves[1] = elves[0];
        elves[0] = elf;
    } else if(elf > elves[1]) {
        elves[2] = elves[1];
        elves[1] = elf;
    } else if(elf > elves[2]) {
        elves[2] = elf;
    }
}

int main(int argc, char** argv) {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    std::array<size_t, 3> elves = { 0 };

    std::string line;
    size_t tmp_elf = 0;
    while(std::getline(in, line)) {
        if(!line.length()) {
            update_array(elves, tmp_elf);

            tmp_elf = 0;
            continue;
        }

        tmp_elf += std::stoul(line);
    }

    out << std::accumulate(elves.begin(), elves.end(), 0) << std::endl;

    in.close();
    out.close();
    return 0;
}