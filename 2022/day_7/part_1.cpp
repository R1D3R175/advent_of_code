#include <fstream>
#include <string>
#include <vector>

static inline size_t ul_till_whitespace(const std::string& str) {
    return std::stoul(str.substr(0, str.find(' ')));
}

class Node {
    public:
        Node* parent;
        std::vector<Node*> children;
        size_t dir_size;
        Node(Node* parent) : parent(parent), dir_size(0) {}

        Node* add_child(Node* child) {
            this->children.push_back(child);
            return child;
        }
};

void increment_dir_sizes(Node* node, const size_t& size) {
    while(node != nullptr) {
        node->dir_size += size;
        node = node->parent;
    }
}

size_t sum_dirs_at_most_100000(Node* node) {
    size_t sum = 0;
    if(node->dir_size <= 100000) sum += node->dir_size;

    for(Node* child : node->children)
        sum += sum_dirs_at_most_100000(child);

    return sum;
}

int main(int argc, char** argv) {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    
    Node* root = new Node(nullptr);

    std::string line;
    std::getline(in, line);

    Node* curr_node = root;

    while(std::getline(in, line)) {
        if(line[0] != '$') {
            if(line.substr(0, 3) != "dir")
                increment_dir_sizes(curr_node, ul_till_whitespace(line));

            continue;
        }
        std::string cmd = line.substr(2, 2);
        if(cmd == "cd") {
            std::string dir = line.substr(5, std::string::npos);

            curr_node = (dir != "..") ? 
                        curr_node->add_child(new Node(curr_node)) : 
                        curr_node->parent;
        }
    }

    out << sum_dirs_at_most_100000(root) << std::endl;

    in.close();
    out.close();
    return 0;
}