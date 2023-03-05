#ifndef LAB_0_1_PROJ_STUDENTINFO_H
#define LAB_0_1_PROJ_STUDENTINFO_H

#include <string>

class StudentInfo {
private:
    unsigned int faculty;
    unsigned int group;
    unsigned int course;
    std::string name;
public:

public:
    StudentInfo(int faculty, int group, int course, const std::string &name);

public:
    [[nodiscard]]  int getFaculty() const;

    [[nodiscard]]  int getGroup() const;

    [[nodiscard]]  int getCourse() const;

    [[nodiscard]] const std::string &getName() const;
};


#endif //LAB_0_1_PROJ_STUDENTINFO_H
