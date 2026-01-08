#include "node.hpp"
#include "edge.hpp"
#include <stdexcept>
#include <iostream>

using namespace std;

Node::Node(int id, string question, bool is_entry_node) : id(id), question(question), is_entry_node(is_entry_node)
{
}

int Node::getId()
{
    return id;
}

bool Node::addTarget(Node *target, string answer, vector<string> enable_tags, vector<string> disable_tags)
{
    //Validate input
    if(target == nullptr || target == this || answer == "")return false;
    for(Edge* edge : targets){
        if(edge->getSourceId() == target->getId()){
            return false;
        }
    }

    //Add target
    targets.push_back(new Edge(target->getId(), target, answer, enable_tags, disable_tags));
    return true;
}

bool Node::removeTarget(Node *target)
{
    //Validate input
    if(target == nullptr || target == this)return false;

    //Remove target
    for(int i = 0; i < targets.size(); i++){
        if(targets[i]->getSourceId() == target->getId()){
            Edge* edge_to_delete = targets[i];
            targets.erase(targets.begin() + i);
            delete edge_to_delete;
            return true;
        }
    }

    //If target to be removed not in target list inform the caller
    return false;
}

string Node::getQuestion()
{
    return question;
}


string Node::activate(vector<string>* state_tags, vector<Node *> *path)
{
    //Check for path loop or wrongful entry
    if(isPathLoop(path) || (path == nullptr && !is_entry_node)){
        throw runtime_error("Path loop detected or invalid path");
    }

    if(path == nullptr){
        path = new vector<Node*>();
    }
    if(state_tags == nullptr){
        state_tags = new vector<string>();
    }

    //Obtain the direction through the graph
    int answer = -1;
    while(answer < 0 || answer >= targets.size()){
        //Present options
        cout << question << endl;
        int i = 0;
        for(Edge* edge: targets){
            string potential_answer = edge->getAnswer(state_tags, path);
            if(potential_answer != ""){
                cout << i << ": " << potential_answer << endl;
            }
            i++;
        }

        //Get answer
        cout << "Answer: ";

        //Validate answer
        try{
            string answer_string;
            cin >> answer_string;
            answer = stoi(answer_string);
        } catch(const std::exception& e){
            answer = -1;
            cout << "Invalid input" << endl;
        }
        if(answer < 0 || answer >= targets.size()){
            cout << "Invalid answer" << endl;
        }
    }

    //Add self to path trace
    path->push_back(this);

    //Goto the next node
    return targets[answer]->tryActivate(state_tags, path);
}

bool Node::isPathLoop(vector<Node *> *path)
{
    if(path == nullptr){
        return false;
    }
    for(const auto node : *path){
        if(node == this){
            return true;
        }
    }
    return false;
}
