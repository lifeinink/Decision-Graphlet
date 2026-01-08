#include "node.hpp"
#include <vector>
#include <string>
using namespace std;

class TagNode : public Node{
    public:
    TagNode(int id, vector<string> add_tags, vector<string> subtract_tags, bool is_entry_node);

    bool addTarget(Node* target, vector<string> enable_tags, vector<string> disable_tags);

    string activate(vector<string>* state_tags, vector<Node*>* path) override;

    protected:
    vector<string> add_tags;
    vector<string> subtract_tags;
};