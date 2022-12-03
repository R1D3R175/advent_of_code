#include <fstream>
#include <string>

int main(int argc, char** argv) {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    std::string line;
    size_t biggest_elf = 0, tmp_elf = 0;
    while(std::getline(in, line)) {
        if(!line.length()) {
            if(tmp_elf > biggest_elf) 
                biggest_elf = tmp_elf;
            
            tmp_elf = 0;
            continue;
        }

        tmp_elf += std::stoul(line);
    }

    out << biggest_elf << std::endl;

    in.close();
    out.close();
    return 0;
}