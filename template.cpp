#include <fstream>

int main(int argc, char** argv)
{
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    // Your code here...

    in.close();
    out.close();
}