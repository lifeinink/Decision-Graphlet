#include "leaf.hpp"
#include <iostream>
using namespace std;

Leaf::Leaf(int id, string answer, optional<unordered_map<string,string>> tag_map) : Node(id, "", false), answer(answer)
{
    if(tag_map.has_value()){
        this->tag_map = tag_map.value();
    }
}

string Leaf::activate(vector<string>* state_tags, vector<Node *> *path)
{
    unordered_map<string,string> inclusives = unordered_map<string,string>();
    for(const auto tag : *state_tags){
        if(tag_map.find(tag) != tag_map.end()){
            string insert_sequence = tag_map[tag];
            inclusives.insert(make_pair(insert_sequence, tag));
        }
    }
    for(const auto pair : inclusives){
        string replace_var = "${"+pair.first+"}";
        answer = answer.replace(answer.find(replace_var), replace_var.length(), pair.second);
    }
    return answer;
}