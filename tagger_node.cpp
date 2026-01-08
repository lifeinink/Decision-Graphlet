#include <algorithm>
#include <string>
#include "edge.hpp"
#include "tagger_node.hpp"
#include <iostream>
#include <stdexcept>

using namespace std;

TagNode::TagNode(int id, vector<string> add_tags, vector<string> subtract_tags, bool is_entry_node) : Node(id, "", is_entry_node), add_tags(add_tags), subtract_tags(subtract_tags){

}

string TagNode::activate(vector<string>* state_tags, vector<Node *> *path){
    for(const auto tag : add_tags){
        if(find(state_tags->begin(), state_tags->end(), tag) == state_tags->end()){
            state_tags->push_back(tag);
        }
    }
    for(const auto tag : subtract_tags){
        state_tags->erase(remove(state_tags->begin(), state_tags->end(), tag), state_tags->end());
    }
    string result;
    for(Edge* edge : targets){
        result = edge->tryActivate(state_tags, path);
        if(result != ""){
            break;
        }
    }
    if(result == "")throw runtime_error("No valid path forward found");
    return result;
}

bool TagNode::addTarget(Node* target, vector<string> enable_tags, vector<string> disable_tags){
    if(Node::addTarget(target, "auto", enable_tags, disable_tags)){
        return true;
    }
    return false;
}