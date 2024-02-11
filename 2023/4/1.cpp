#include <iostream>
#include <fstream>
#include <source_location>
#include <unordered_set>

typedef unsigned char byte;

class Solver
{
    private:
        std::ifstream& in;
        std::ofstream& out;
        bool enable_debug;

        size_t answer = 0;

        void log(const std::string& message, const std::source_location& location = std::source_location::current());
        void solve();

        std::unordered_set<byte> parse_winning_numbers(const std::string& line);
        size_t count_winning_numbers(const std::string& line, const std::unordered_set<byte>& winning_numbers);

    public:
        Solver(std::ifstream& in, std::ofstream& out) : in(in), out(out), enable_debug(false) { this->solve(); }
        Solver(std::ifstream& in, std::ofstream& out, bool enable_debug) : in(in), out(out), enable_debug(enable_debug) { this->solve(); }
        ~Solver();
};

Solver::~Solver()
{
    in.close();
    out.close();
}

void Solver::log(const std::string& message, const std::source_location& location)
{
    if(this->enable_debug)
    {
        std::cout << "DEBUG [" << location.function_name() << "] -> " << message << std::endl;
    }
}

std::unordered_set<byte> Solver::parse_winning_numbers(const std::string& line)
{
    std::unordered_set<byte> winning_numbers;
    const size_t colon = line.find(':'), pipe = line.find('|');
    const std::string winning_numbers_str = line.substr(colon + 2, pipe - colon - 3);
    this->log("Winning numbers: " + winning_numbers_str);
    
    for(size_t i = 0; i < winning_numbers_str.size(); i += 3)
    {
        const std::string number_str = winning_numbers_str.substr(i, 2);
        winning_numbers.insert(std::stoul(number_str) & 0xFF);
    }

    return winning_numbers;
}

size_t Solver::count_winning_numbers(const std::string& line, const std::unordered_set<byte>& winning_numbers)
{
    size_t count = 0;

    const size_t pipe = line.find('|');
    const std::string extracted_numbers_str = line.substr(pipe + 2);
    this->log("Extracted numbers: " + extracted_numbers_str);

    for(size_t i = 0; i < extracted_numbers_str.size(); i += 3)
    {
        const std::string number_str = extracted_numbers_str.substr(i, 2);

        byte number = std::stoul(number_str) & 0xFF;

        count += winning_numbers.count(number);
    }

    return count;
}

void Solver::solve()
{
    while(!in.eof())
    {
        std::string line;
        std::getline(in, line);

        const std::unordered_set<byte> winning_numbers = this->parse_winning_numbers(line);
        const size_t found_numbers_count = this->count_winning_numbers(line, winning_numbers); 
        this->log("Found numbers count: " + std::to_string(found_numbers_count));

        this->answer += (1 << (found_numbers_count - 1)) * (found_numbers_count > 0);
    }

    this->out << this->answer << std::endl;
}

int main(int argc, char** argv)
{
    if(argc < 3 || argc > 4)
    {
        std::cout << "Usage: " << argv[0] << " <input file> <output file> [debug, write anything to enable it]" << std::endl;
        return -1;
    }
    bool debug = argc == 4;

    std::ifstream in(argv[1]);
    if(!in.is_open())
    {
        std::cout << "File " << argv[1] << " does not exist." << std::endl;
        return -1;
    }

    std::ofstream out(argv[2]);
    if(!out.is_open())
    {
        std::cout << "File " << argv[2] << " could not be created." << std::endl;
        return -1;
    }

    Solver(in, out, debug);
}