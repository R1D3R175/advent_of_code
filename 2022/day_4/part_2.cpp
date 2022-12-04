#include <fstream>
#include <string>

static inline bool does_overlap(const size_t& first_start,
                                const size_t& first_end, 
                                const size_t& second_start, 
                                const size_t& second_end)  
{
    return (first_start <= second_start && first_end >= second_start) || 
           (second_start <= first_start && second_end >= first_start);
}

int main(int argc, char** argv) {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    size_t overlapped_ranges = 0;

    std::string first_elf;
    size_t first_elf_start, first_elf_end;

    std::string second_elf;
    size_t second_elf_start, second_elf_end;

    size_t pos;
    while(std::getline(in, first_elf, ',')) {
        std::getline(in, second_elf);
        
        pos = first_elf.find('-');
        first_elf_start = std::stoul(first_elf.substr(0, pos));
        first_elf_end = std::stoul(first_elf.substr(pos + 1));

        pos = second_elf.find('-');
        second_elf_start = std::stoul(second_elf.substr(0, pos));
        second_elf_end = std::stoul(second_elf.substr(pos + 1));

        overlapped_ranges += does_overlap(first_elf_start, first_elf_end, second_elf_start, second_elf_end);
    }

    out << overlapped_ranges << std::endl;

    in.close();
    out.close();
    return 0;
}