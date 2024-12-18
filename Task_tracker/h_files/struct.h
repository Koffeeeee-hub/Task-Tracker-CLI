#ifndef STRUCT_H
#define STRUCT_H

#include <iostream>

struct Task {
    int id = 1;
    std::string description = "Buy groceries";
    std::string status = "pending";
    std::string createdAt = "Monday";
    std::string updatedAt = "Tuesday";
};

#endif