#include "leaf.hpp"
#include "tagger_node.hpp"
#include <optional>
#include <iostream>


using namespace std;

int main(int argc, char const *argv[])
{
    //This is an harcoded example of how to use decision graphlet
    Node* start = new Node(0, "Are you in a chore crunch?", true);
    Node* ext_obs = new Node(1,"Are you about to be bound by external obligations?", false);
    Node* prod_window = new Node(2,"Are you in a production window?", false);
    Node* in_break = new Node(3,"Are you in a break?", false);
    Node* break_need = new Node(4,"What is the most pressing concern of the break?", false);
    Node* chores = new Node(5,"Do you have chores you could do?", false);
    Node* sleep = new Node(6,"Approaching sleep?", false);
    Node* nutrition = new Node(7,"Nutrition dose overdue?",false);
    Node* cognitive_level = new Node(8,"High or low cognitive readiness",false);
    Node* motivation = new Node(9,"High or low motivation",false);

    Node* obligation = new Leaf(10,"Obligation",nullopt);
    Node* wander_mind = new Leaf(11,"Let your mind wander",nullopt);
    Node* do_chores = new Leaf(12,"Do chores",nullopt);
    Node* movement_snack = new Leaf(13,"Exercise snack",nullopt);
    Node* sensory_deprivation = new Leaf(14,"Sensory deprivation",nullopt);
    Node* dose_nutrients = new Leaf(15,"Dose nutrients",nullopt);
    Node* leisure_or_reflection = new Leaf(16,"Leisure or reflection",nullopt);
    Node* do_sleep = new Leaf(16,"Sleep",nullopt);



    vector<string> manual_task_tags = vector<string>();
    manual_task_tags.push_back("manual domain task");
    vector<string> project_task_tags = vector<string>();
    project_task_tags.push_back("project task");
    TagNode* manual_task = new TagNode(19, manual_task_tags, vector<string>(), false);
    TagNode* project_task = new TagNode(20, project_task_tags, vector<string>(), false);
    vector<string> break_tags = vector<string>();
    break_tags.push_back("break");
    TagNode* breaking = new TagNode(21, break_tags, vector<string>(), false);
    

    unordered_map<string,string> task_type = unordered_map<string,string>();
    task_type["manual domain task"] = "thing";
    task_type["project task"] = "thing";

    Node* most_appealing_x = new Leaf(17,"Most appealing ${thing}", task_type);
    Node* most_needed_or_neglected_x = new Leaf(18,"Most needed or neglected ${thing}", task_type);

    start->addTarget(ext_obs, "No", vector<string>(), vector<string>());
    start->addTarget(do_chores, "Yes", vector<string>(), vector<string>());

    ext_obs->addTarget(prod_window, "No", vector<string>(), vector<string>());
    ext_obs->addTarget(obligation, "Yes", vector<string>(), vector<string>());

    prod_window->addTarget(in_break, "Yes", vector<string>(), vector<string>());
    prod_window->addTarget(chores, "No", vector<string>(), vector<string>());

    in_break->addTarget(breaking,"Yes", vector<string>(), vector<string>());
    in_break->addTarget(cognitive_level, "No", vector<string>(), vector<string>());
    breaking->addTarget(break_need, vector<string>(), vector<string>());

    break_need->addTarget(movement_snack, "Move Itch", vector<string>(), vector<string>());
    break_need->addTarget(sensory_deprivation, "Sensory Stress", vector<string>(), vector<string>());
    break_need->addTarget(dose_nutrients, "Hunger", vector<string>(), vector<string>());
    break_need->addTarget(chores,"Focus problems", vector<string>(), vector<string>());

    chores->addTarget(sleep, "No", vector<string>(), break_tags);
    chores->addTarget(wander_mind, "No", break_tags, vector<string>());
    chores->addTarget(do_chores, "Yes", vector<string>(), vector<string>());

    sleep->addTarget(do_sleep, "Yes", vector<string>(), vector<string>());
    sleep->addTarget(nutrition, "No", vector<string>(), vector<string>());

    nutrition->addTarget(dose_nutrients, "Yes", vector<string>(), vector<string>());
    nutrition->addTarget(leisure_or_reflection, "No", vector<string>(), vector<string>());

    cognitive_level->addTarget(project_task,"High",vector<string>(),vector<string>());
    cognitive_level->addTarget(manual_task,"Low",vector<string>(),vector<string>());

    project_task->addTarget(motivation,vector<string>(),vector<string>());
    manual_task->addTarget(motivation,vector<string>(),vector<string>());

    motivation->addTarget(most_needed_or_neglected_x,"High",vector<string>(),vector<string>());
    motivation->addTarget(most_appealing_x,"Low",vector<string>(),vector<string>());

    cout << start->activate(nullptr, nullptr);   
    return 0;
}