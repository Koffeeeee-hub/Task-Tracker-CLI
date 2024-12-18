#include "../h_files/struct.h"
#include "json.cpp"
#include "utils.cpp"
#include "cli.cpp"


int main(int argc, char** argv) {

    if (argc < 2) {
        std::cout << "Too few arguments";
        exit(1);
    } else {
        if (std::string(argv[1]) == "add") {CLI::add_task(argv[2]);}
        else if (std::string(argv[1]) == "delete") {CLI::delete_task(std::stoi(argv[2]));}
        else if (std::string(argv[1]) == "update") {CLI::update_task(std::stoi(argv[2]), argv[3]);}
        else if (std::string(argv[1]) == "mark-in-progress") {CLI::mark_task(std::string(argv[1]), std::stoi(argv[2]));}
        else if (std::string(argv[1]) == "mark-done") {CLI::mark_task(std::string(argv[1]), std::stoi(argv[2]));}
        else if (std::string(argv[1]) == "list") {
            if (argv[2] == 0) {CLI::list_task();}
            else if (std::string(argv[2]) == "done") {CLI::list_task(std::string(argv[2]));}
            else if (std::string(argv[2]) == "in-progress") {CLI::list_task(std::string(argv[2]));}
            else if (std::string(argv[2]) == "todo") {CLI::list_task(std::string(argv[2]));}
        }
    }
    return 0;
}