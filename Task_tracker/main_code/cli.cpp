#ifndef CLI_CPP
#define CLI_CPP

#include "../h_files/struct.h"
#include "json.cpp"
#include "utils.cpp"

class CLI {
public:
    // Adds a task

    static void add_task(const std::string &description) {

        Task new_task;

        std::ifstream file(filename);
        std::string filecontent((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();

        if (filecontent.empty()) {
            new_task.id = 1;
        } else {
            size_t starting = filecontent.rfind("id") + 6;
            size_t final = filecontent.find("\"", starting);
            new_task.id = std::stoi(filecontent.substr(starting, final - starting)) + 1;
        }

        new_task.description = description;
        new_task.status = "todo";
        new_task.createdAt = get_current_time();
        new_task.updatedAt = get_current_time();

        Writetojson(new_task);
        std::cout << "Task added successfully (ID: " << new_task.id << ")" << std::endl;
    }

    // Deletes a Task
    static void delete_task(const int &targetid) {
        std::vector<Task> updatedtasks;
        std::vector<Task> outdatedtasks= parsejsonfile();

        std::ofstream file(filename);
        file << "";
        file.close();

        for (int i = 0; i < outdatedtasks.size(); ++i) {
            if (outdatedtasks[i].id != targetid) {
                if (outdatedtasks[i].id > targetid) {
                    outdatedtasks[i].id -= 1;
                }
                Writetojson(outdatedtasks[i]);
            }
        }
    }

    // Updates a task
    static void update_task(const int &targetid, const std::string &newdescription) {
        std::vector<Task> outdatedtasks= parsejsonfile();

        std::ofstream file(filename);
        file << "";
        file.close();

        for (int i = 0; i < outdatedtasks.size(); ++i) {
            if (outdatedtasks[i].id == targetid) {
                outdatedtasks[i].description = newdescription;
                outdatedtasks[i].updatedAt = get_current_time();
            }
            Writetojson(outdatedtasks[i]);
        }
    }

    // Marks the progress of a task
    static void mark_task(const std::string &mark, const int &targetid) {
        if (mark == "mark-in-progress") {
            std::vector<Task> outdatedtasks= parsejsonfile();

            std::ofstream file(filename);
            file << "";
            file.close();

            for (int i = 0; i < outdatedtasks.size(); ++i) {
                if (outdatedtasks[i].id == targetid) {
                    outdatedtasks[i].status = "in-progress";
                    outdatedtasks[i].updatedAt = get_current_time();
                }
            Writetojson(outdatedtasks[i]);
            }
        } else if (mark == "mark-done") {
            std::vector<Task> outdatedtasks= parsejsonfile();

            std::ofstream file(filename);
            file << "";
            file.close();

            for (int i = 0; i < outdatedtasks.size(); ++i) {
                if (outdatedtasks[i].id == targetid) {
                    outdatedtasks[i].status = "done";
                    outdatedtasks[i].updatedAt = get_current_time();
                }
                Writetojson(outdatedtasks[i]);
            }
        }
    }

    // Returns the list of specified tasks from json file
    static void list_task(const std::string type = "None") {
        std::vector<Task> all_tasks = parsejsonfile();

        if (type == "None") {
            std::cout << "\nList of all tasks:\n" << std::endl;
            for (int i = 0; i < all_tasks.size(); ++i) {
                std::cout << "\tID: " << std::to_string(all_tasks[i].id) << std::endl;
                std::cout << "\tDescription: " << all_tasks[i].description << std::endl;
                std::cout << "\tStatus: " << all_tasks[i].status << std::endl;
                std::cout << "\tUpdatedAt: " << all_tasks[i].createdAt << std::endl;
                std::cout << "\tCreatedAt: " << all_tasks[i].updatedAt << "\n" << std::endl;
            }
        } else {
            std::cout << "\nList of all " << type << " tasks:\n" << std::endl;
            for (int i = 0; i < all_tasks.size(); ++i) {
                if (all_tasks[i].status == type) {
                    std::cout << "\tID: " << std::to_string(all_tasks[i].id) << std::endl;
                    std::cout << "\tDescription: " << all_tasks[i].description << std::endl;
                    std::cout << "\tStatus: " << all_tasks[i].status << std::endl;
                    std::cout << "\tUpdatedAt: " << all_tasks[i].createdAt << std::endl;
                    std::cout << "\tCreatedAt: " << all_tasks[i].updatedAt << "\n" << std::endl;
                }
            }
        }
    }
};

#endif