#include <algorithm> // std::shuffle
#include <array>
#include <ctime>
#include <iostream>
#include <numeric> // std::reduce
#include <random>

enum itemType 
{
    potion,
    torch,
    arrow,
    itemCount
};

template <typename T> 
int countTotalItems(std::array<T, itemCount>& items) {
    auto totalItems = std::reduce(items.begin(), items.end());
    return totalItems;
}

template <typename T>
void printItems(std::array<T, itemCount>& items) {
    std::cout << "The player has " << countTotalItems(items) << " total items in their inventory.\n";
}

template <typename T>
void printItem(std::array<T, itemCount>& items, int itemType) {
    std::cout << "The user has " << items[itemType] << " of itemType " << itemType << " in their inventory.\n";
}


int main() 
{
    std::array items {2, 5, 10};


    printItems(items);
    printItem(items, torch);
}