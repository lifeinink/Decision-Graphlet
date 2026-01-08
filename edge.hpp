#include <string>
#include <vector>
#include <optional>
using namespace std;

//Placeholder preventing cyclical reference
class Node;


class Edge{
    public:
    Edge(int source_id,Node* destination, string answer, optional<vector<string>> enable_tags, optional<vector<string>> disable_tags);

    string getAnswer(vector<string>* state_tags, vector<Node*>* path);
    string tryActivate(vector<string>* state_tags, vector<Node*>* path);
    int getSourceId();


    protected:
    Node* destination;
    string answer;
    vector<string> enable_tags;
    vector<string> disable_tags;
    int source_id;
    bool isAnswerValid(vector<string>* state_tags, vector<Node*>* path);


};