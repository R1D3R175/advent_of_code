#include <iostream>
#include <fstream>
#include <source_location>

class Solver
{
    private:
        std::ifstream& in;
        std::ofstream& out;
        bool enable_debug;

        void log(const std::string& message, const std::source_location& location = std::source_location::current());
        void solve();

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

void Solver::solve()
{
    // Your code here...
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