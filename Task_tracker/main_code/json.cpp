#ifndef JSON_CPP
#define JSON_CPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../h_files/struct.h"

std::string filename = "list.json";

// Writes or overwrites to the json file
void Writetojson(const Task& task) {
    std::string newtask;
    newtask =
    "\t{"
    "\n\t\t\"id\": \"" + std::to_string(task.id) + "\","
    "\n\t\t\"description\": \"" + task.description + "\","
    "\n\t\t\"status\": \"" + task.status + "\","
    "\n\t\t\"createdAt\": \"" + task.createdAt + "\","
    "\n\t\t\"updatedAt\": \"" + task.updatedAt + "\""
    "\n\t}";

    // Reads file into a string
    std::ifstream file(filename);
    std::string jsoncontent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    size_t start_pos = jsoncontent.find('[');
    size_t end_pos = jsoncontent.find_last_of(']');

    if (!jsoncontent.empty() && jsoncontent[end_pos-2] != ',') {
        jsoncontent.insert(end_pos-1, ",\n" + newtask);
    } else {
        jsoncontent = "[\n" + newtask + "\n]";
    }
    std::ofstream updatedfile(filename);
    updatedfile << jsoncontent;
    updatedfile.close();
}

// Returns a vector of task objects from json file
std::vector<Task> parsejsonfile() {
    std::vector<Task> all_tasks;

    std::ifstream file(filename);
    std::string jsoncontent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    size_t start_pos = jsoncontent.find("[") + 3;
    size_t end_pos = jsoncontent.find_last_of("]");

    if (start_pos != std::string::npos && end_pos != std::string::npos) {
        std::string jsontask = jsoncontent.substr(start_pos, end_pos - 3);

        size_t taskStartpos = 0;
        size_t taskEndpos = jsontask.find_first_of('}');

        while (taskStartpos != std::string::npos && taskEndpos != std::string::npos) {

            Task task;
            size_t idStartpos = jsontask.find("id", taskStartpos) + 6;
            size_t idEndpos = jsontask.find("\"", idStartpos);
            task.id = std::stoi(jsontask.substr(idStartpos, idEndpos - idStartpos));

            size_t descStartpos = jsontask.find("description", taskStartpos) + 15;
            size_t descEndpos = jsontask.find("\"", descStartpos);
            task.description = jsontask.substr(descStartpos, descEndpos - descStartpos);

            size_t statusStartpos = jsontask.find("status", taskStartpos) + 10;
            size_t statusEndpos = jsontask.find("\"", statusStartpos);
            task.status = jsontask.substr(statusStartpos, statusEndpos - statusStartpos);

            size_t createdStartpos = jsontask.find("createdAt", taskStartpos) + 13;
            size_t createdEndpos = jsontask.find("\"", createdStartpos);
            task.createdAt = jsontask.substr(createdStartpos, createdEndpos - createdStartpos);

            size_t updatedStartpos = jsontask.find("updatedAt", taskStartpos) + 13;
            size_t updatedEndpos = jsontask.find("\"", updatedStartpos);
            task.updatedAt = jsontask.substr(updatedStartpos, updatedEndpos - updatedStartpos);

            all_tasks.push_back(task);
            taskStartpos = taskEndpos + 2;
            taskEndpos = jsontask.find('}', taskStartpos);
        }
        return all_tasks;
    }
    return all_tasks;
}

#endif