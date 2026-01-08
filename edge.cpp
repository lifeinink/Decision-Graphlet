#include "edge.hpp"
#include "node.hpp"


using namespace std;

Edge::Edge(int source_id,Node* destination, string answer, optional<vector<string>> enable_tags, optional<vector<string>> disable_tags) : destination(destination), answer(answer)
{
    if(enable_tags.has_value()){
        this->enable_tags = enable_tags.value();
    }
    if(disable_tags.has_value()){
        this->disable_tags = disable_tags.value();
    }
}

bool Edge::isAnswerValid(vector<string>* state_tags, vector<Node*>* path){
        bool will_activate = true;
    if(enable_tags.size() > 0){
        will_activate = false;
        for(const auto tag : enable_tags){
            for(const auto state_tag : *state_tags){
                if(tag == state_tag){
                    will_activate = true;
                    break;
                }
            }
        }
    }
    if(disable_tags.size() > 0){
        for(const auto tag : disable_tags){
            for(const auto state_tag : *state_tags){
                if(tag == state_tag){
                    will_activate = false;
                    break;
                }
            }
        }
    }
    return will_activate;
}

string Edge::getAnswer(vector<string>* state_tags, vector<Node*>* path)
{
    if (this->isAnswerValid(state_tags, path))return answer;
    return "";
}

string Edge::tryActivate(vector<string>* state_tags, vector<Node*>* path){
    if(this->isAnswerValid(state_tags, path)){
        return destination->activate(state_tags, path);
    }
    return "";
}

int Edge::getSourceId(){
    return source_id;
}