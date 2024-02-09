#include <iostream>
#include <fstream>
#include <source_location>
#include <vector>
#include <cctype>
#include <utility>

typedef std::pair<size_t, size_t> index;
typedef std::pair<size_t, index> range;

class Solver
{
    private:
        std::ifstream& in;
        std::ofstream& out;
        bool enable_debug;

        std::vector<std::string> matrix;
        std::vector<range> ranges;
        size_t answer = 0;

        void log(const std::string& message, const std::source_location& location = std::source_location::current());
        void solve();

        void read_matrix();
        std::vector<index> get_valid_adjacent_indexes(const size_t& i, const size_t& j);
        void add_found_range(const size_t& row_index, const size_t& start_index, const size_t& end_index);
        bool was_already_counted(const size_t& i, const size_t& j);
        size_t extract_number(const size_t& i, const size_t& j);
        void sum_adjacent_numbers(const size_t& i, const size_t& j);
        void find_symbols_and_sum_them();

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

void Solver::read_matrix()
{
    while(!in.eof())
    {
        std::string line;
        std::getline(in, line);
        this->log("Read line: " + line);

        this->matrix.push_back(line);
    }
}

std::vector<index> Solver::get_valid_adjacent_indexes(const size_t& i, const size_t& j)
{
    std::vector<index> indexes;

    // Clockwise check starting from the top-left corner
    if(i > 0 && j > 0) indexes.emplace_back(i - 1, j - 1);
    if(i > 0) indexes.emplace_back(i - 1, j);
    if(i > 0 && j < this->matrix[i].size() - 1) indexes.emplace_back(i - 1, j + 1);
    if(j < this->matrix[i].size() - 1) indexes.emplace_back(i, j + 1);
    if(i < this->matrix.size() - 1 && j < this->matrix[i].size() - 1) indexes.emplace_back(i + 1, j + 1);
    if(i < this->matrix.size() - 1) indexes.emplace_back(i + 1, j);
    if(i < this->matrix.size() - 1 && j > 0) indexes.emplace_back(i + 1, j - 1);
    if(j > 0) indexes.emplace_back(i, j - 1);

    return indexes;
}

size_t Solver::extract_number(const size_t& i, const size_t& j)
{
    size_t start_index = 0, end_index = 0;
    for(size_t k = j; k < this->matrix[i].size(); k++)
    {
        if(isdigit(this->matrix[i][k])) end_index = k;
        else break;
    }

    for(size_t k = j + 1; k-- > 0; )
    {
        if(isdigit(this->matrix[i][k])) start_index = k;
        else break;
    }

    const std::string number = this->matrix[i].substr(start_index, end_index - start_index + 1);
    const size_t extracted_number = std::stoul(number);
    this->add_found_range(i, start_index, end_index);
    this->log("Extracted number: " + number);

    return extracted_number;
}

void Solver::add_found_range(const size_t& row_index, const size_t& start_index, const size_t& end_index)
{
    this->log("Adding range containing number: matrix[" + std::to_string(row_index) + "][" + std::to_string(start_index) + " : " + std::to_string(end_index) + "]");
    this->ranges.emplace_back(row_index, std::make_pair(start_index, end_index));
}

bool Solver::was_already_counted(const size_t& i, const size_t& j)
{
    // Binary search based on row (i) to find the closest row containing the number (allowed difference of <= 2)
    size_t left = 0, right = this->ranges.size() - 1;
    while(left <= right && left < this->ranges.size() && right < this->ranges.size())
    {
        const size_t mid = (left + right) / 2;
        const size_t row = this->ranges[mid].first;

        if( ((i > row) ? (i - row) : (3)) < 3 )
        {
            this->log("Found starting point to search for the number: " + std::to_string(row));
            left = right = mid;
            break;
        }

        if(row < i) left = mid + 1;
        else right = mid - 1;
    }

    for(size_t k = left; k < this->ranges.size() - 1; k++)
    {
        auto[row, range] = this->ranges[k];
        if( ((row > i) ? (row - i) : (2)) > 2)
        {
            this->log("No more rows to search for the number");
            break;
        }

        if(row != i) continue;

        auto[start, end] = range;
        if(j >= start && j <= end)
        {
            this->log("Number at (" + std::to_string(i) + ", " + std::to_string(j) + ") was already counted. I iterated " + std::to_string(k - left + 1) + " times to find it");
            return true;
        }
    }

    this->log("Number at (" + std::to_string(i) + ", " + std::to_string(j) + ") was not already counted");
    return false;
}

void Solver::sum_adjacent_numbers(const size_t& i, const size_t& j)
{
    std::vector<std::pair<size_t, size_t> > indexes = this->get_valid_adjacent_indexes(i, j);

    for(const std::pair<size_t, size_t>& index : indexes)
    {
        if(!isdigit(this->matrix[index.first][index.second])) continue;
        this->log("Found adjacent number at (" + std::to_string(index.first) + ", " + std::to_string(index.second) + "): " + this->matrix[index.first][index.second]);
        
        const size_t extracted_number = this->extract_number(index.first, index.second);
        if(was_already_counted(index.first, index.second))
        {
            this->log("Preventing sum of the same number: " + std::to_string(extracted_number));
            this->ranges.pop_back(); // Remove the last range to not have duplicate ranges
            continue;
        }
        
        this->log("Summing " + std::to_string(extracted_number) + " to the answer");
        this->answer += extracted_number;
    }
}

void Solver::find_symbols_and_sum_them()
{
    for(size_t i = 0; i < this->matrix.size(); i++)
    {
        for(size_t j = 0; j < this->matrix[i].size(); j++)
        {
            if(this->matrix[i][j] == '.' || !ispunct(this->matrix[i][j])) continue;
            
            this->log("Found symbol at (" + std::to_string(i) + ", " + std::to_string(j) + "): " + this->matrix[i][j]);
            this->sum_adjacent_numbers(i, j);
        }
    }
}

void Solver::solve()
{
    this->read_matrix();
    this->find_symbols_and_sum_them();
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