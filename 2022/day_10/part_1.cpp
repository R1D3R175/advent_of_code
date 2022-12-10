#include <fstream>
#include <string>

class CPU {
    private:
        long x_reg;
    public:
        long cycles;
        long signal_strength_sum;
        CPU() : x_reg(1), cycles(0), signal_strength_sum(0) {}

        void noop() {
            cycles++;

            if((cycles - 20) % 40 == 0) 
                signal_strength_sum += x_reg * cycles;
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

    out << cpu.signal_strength_sum << std::endl;

    in.close();
    out.close();
    return 0;
}