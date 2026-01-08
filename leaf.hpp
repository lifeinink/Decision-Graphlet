#include "node.hpp"
#include <unordered_set>
#include <optional>
using namespace std;

class Leaf : public Node {
    public:
    Leaf(int id, string answer, optional<unordered_map<string,string>> tag_map);

    string activate(vector<string>* state_tags, vector<Node*>* path) override;

    protected:
    string answer;
    unordered_map<string,string> tag_map;


};
