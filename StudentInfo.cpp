//
// Created by Иван Березуцкий on 05.03.2023.
//

#include "StudentInfo.h"

int StudentInfo::getFaculty() const {
    return faculty;
}

int StudentInfo::getGroup() const {
    return group;
}

int StudentInfo::getCourse() const {
    return course;
}

const std::string &StudentInfo::getName() const {
    return name;
}

StudentInfo::StudentInfo(int faculty, int group, int course, const std::string &name)
        : faculty(faculty), group(group), course(course), name(name) {}

