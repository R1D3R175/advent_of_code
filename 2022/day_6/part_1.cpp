#include <fstream>
#include <string>
#include <set>

int main(int argc, char** argv) {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    std::string line;
    std::getline(in, line);

    std::set<char> packet_marker;
    for(size_t i = 0; i < line.length() - 4; i++) {
        packet_marker.clear();

        bool broke = false;

        for(const char& c : line.substr(i, 4)) {
            auto ret = packet_marker.insert(c);

            if(!ret.second) {
                broke = true;
                break;
            }
        }

        if(!broke) {
            out << i + 4 << std::endl;
            break;
        }
    }

    in.close();
    out.close();
    return 0;
}
