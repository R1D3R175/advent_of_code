#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>

static inline bool is_data(const std::string& str) {
    return (str.find_first_not_of(str[0]) != std::string::npos);
}

static inline size_t substr_to_ul(const std::string& str,
                                  const size_t& start_whitespace,
                                  const size_t& end_whitespace)
{
    return std::stoul(str.substr(start_whitespace + 1, end_whitespace - start_whitespace - 1));
}

int main(int argc, char** argv) {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    std::vector<std::deque<char>> crates;

    std::string line, tmp;
    size_t pos;

    while(std::getline(in, line)) {
        if(line.find('1') != std::string::npos) {
            std::getline(in, line);
            break;
        }

        size_t tmp_size = (size_t)(ceil(line.length() / 4.0));
        if(tmp_size > crates.size())
            crates.resize(tmp_size);

        if(line[line.length() - 1] == '\r' || line[line.length() - 1] == '\n')
            line.pop_back();

        for(pos = 0; pos < tmp_size; pos++) {
            tmp = line.substr(pos * 4, 4);
            if(!is_data(tmp)) continue;

            crates[pos].push_back(tmp[1]);
        }
    }

    while(std::getline(in, line)) {
        size_t how_much_start = 4;
        size_t how_much_end = line.find(' ', how_much_start + 1);
        size_t how_much = substr_to_ul(line, how_much_start, how_much_end);

        size_t source_start = how_much_end + 5;
        size_t source_end = line.find(' ', source_start + 1);
        size_t source = substr_to_ul(line, source_start, source_end) - 1;

        size_t dest_start = source_end + 3;
        size_t dest_end = std::string::npos;
        size_t dest = substr_to_ul(line, dest_start, dest_end) - 1;

        for(size_t i = 0; i < how_much; i++) {
            if(crates[source].empty()) break;

            crates[dest].push_front(crates[source].front());
            crates[source].pop_front();
        }
    }

    for(const auto& crate : crates) {
        if(crate.empty()) continue;

        out << crate.front();
    }

    in.close();
    out.close();
    return 0;
}
