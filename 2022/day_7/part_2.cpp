#include <fstream>
#include <string>
#include <vector>
#include <limits>

static constexpr size_t MAX_SIZE      = 70000000;
static constexpr size_t DESIRED_SPACE = 30000000;

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

size_t best_to_delete(Node* node, const size_t& free_space) {
    size_t best = (node->dir_size + free_space >= DESIRED_SPACE) ? 
                  (node->dir_size) : 
                  (std::numeric_limits<size_t>::max());

    for(Node* child : node->children) {
        size_t child_best = best_to_delete(child, free_space);
        if(child_best < best && child_best + free_space >= DESIRED_SPACE)
            best = child_best;
    }

    return best;
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

    out << best_to_delete(root, MAX_SIZE - root->dir_size) << std::endl;

    in.close();
    out.close();
    return 0;
}