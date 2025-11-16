# UNTS
United Template Structures which unite opportunities from STL structures in few. 
# C++
Project was written on `C++` and based on `C++17` standard.
# All structures from UNTS
You can see the list of the structures, which were united from `STL structures`.
1. std::set + std::array → `unique_array`
2. std::set + std::priority_queue → `unique_priority_queue`
3. std::array + std::list → `static_list`
4. std::array + std::map → `static_map`
5. std::array + std::deque → `static_deque`
6. std::array + std::valarray → `static_valarray`
7. std::set + std::valarray → `unique_valarray`
# Example of structure in code for working with UNTS
```
#include <iostream>
#include "unts.h" // header file of the UNTS project

int main() {
    unts::unique_array<int,10> example_array; // created object of unique_array class 
    example_array.add(0,1);                   // with static size
    example_array.add(1,2);
    example_array.add(2,3); // emplace elements by index
    example_array.add(3,4);
    example_array.add(4,4);    // dublicated element. He'll not be inserted in structure.
    example_array.for_each(); // for_each() displays sorted and unique elements
    // output will be: 1 2 3 4
    std::cout << example_array[0] << std::endl; // get elements by index. At 0 index is 1
    example_array.clear(); // for cleaning elements in structure
    return 0 ;
}
```
# CMake
Project was configured and generated with `CMake`.
# Contacts 
If you want to offer the improvements for this project, you can find me in: 
- [@fr1zb3e](@fr1zb3e) →  Telegram nickname
- [Habr](https://habr.com/ru/users/fr1zb3e/) →  WebSite
# How can you download this project
1. Click on the button '<> code' and download the project in ZIP format. There is the button 'Download ZIP'.
2. Yoo can copy the link to git of repository and clone to your machine: ``
# License 
This project works under `MIT` license
