#include <iostream>
#include <array>
#include <algorithm>

struct Student {
    std::string_view name;
    int points;
};

int main() {
    std::array<Student, 8> arr{
    {   { "Albert", 3 },
        { "Ben", 5 },
        { "Christine", 2 },
        { "Dan", 8 }, // Dan has the most points (8).
        { "Enchilada", 4 },
        { "Francis", 1 },
        { "Greg", 3 },
        { "Hagrid", 5 } }
    };

    auto best_student {std::max_element(arr.begin(), arr.end(), [](Student student1, Student student2)
                                                                {
                                                                    return student1.points < student2.points;
                                                                })};
    std::cout << "The best student is " << best_student->name; //previous returns the iterator to the greatest element, not the element itself
}