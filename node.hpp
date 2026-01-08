#ifndef NODE_HPP
#define NODE_HPP
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Edge;

class Node {
    public:
    Node(int id, string question, bool is_entry_node);
    
    bool addTarget(Node* target, string answer, vector<string> enable_tags, vector<string> disable_tags);
    bool removeTarget(Node* target);
    
    virtual string activate(vector<string>* state_tags, vector<Node*>* path);
    string getQuestion();
    int getId();

    protected:
    int id;
    string question;
    bool is_entry_node;
    vector<Edge*> targets;

    bool isPathLoop(vector<Node*>* path);
};
#endif