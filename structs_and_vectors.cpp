#include <algorithm> // std::shuffle
#include <array>
#include <ctime>
#include <iostream>
#include <numeric> // std::reduce
#include <random>

struct student {
    std::string name;
    int grade;
};

bool studentComparator(student s1, student s2) {
    return s1.grade > s2.grade;
}

int promptForStudentCount() {
    std::cout << "How many students?";
    int ret;
    std::cin >> ret;
    return ret;
}

std::string promptForStudentName()
{
    std::cout << "What is the name of the student?";
    std::string ret;
    std::cin >> ret;
    return ret;
}

int promptForStudentGrade()
{
    std::cout << "What is the grade of the student?";
    int ret;
    std::cin >> ret;
    return ret;
}

void printStudents(const std::vector<student>& students) {
    for(auto student: students) {
        std::cout << student.name << " has a grade of " << student.grade << "\n";
    }
}

int main() {
    int studentCount {promptForStudentCount()};
    std::vector<student> studentVector(studentCount);

    for(std::size_t i = 0; i < studentVector.size(); i++) {
        student newStudent {promptForStudentName(), promptForStudentGrade()};
        studentVector[i] = newStudent;
    }

    std::sort(studentVector.begin(), studentVector.end(), studentComparator);

    printStudents(studentVector);
}