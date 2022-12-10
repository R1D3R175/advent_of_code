#include <fstream>
#include <string>

class CPU {
    private:
        long x_reg;
    public:
        long cycles;
        std::string crt[6];
        CPU() : x_reg(1), cycles(0) {
            for(size_t i = 0; i < 6; i++)
                crt[i] = "........................................";
        }

        void noop() {
            if(abs((cycles % 40) - x_reg) <= 1) {
                crt[cycles / 40][cycles % 40] = '#';
            }

            cycles++;

        }

        void addx(const long& how_much) {
            noop();
            noop();
            x_reg += how_much;
        }
};

int main(int argc, char** argv) {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    CPU cpu;

    std::string line;
    while(std::getline(in, line)) {
        std::string instruction = line.substr(0, 4);
        if (line == "noop") {
            cpu.noop();
        } else {
            long how_much = std::stol(line.substr(5, std::string::npos));
            cpu.addx(how_much);
        }
    }

    for(size_t i = 0; i < 6; i++)
        out << cpu.crt[i] << std::endl;

    in.close();
    out.close();
    return 0;
}