#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <iostream>
#include <fstream>
#include <valarray>
#include <functional>

namespace SundayWork {
template<typename T>
void output2Console(const T& arr)
{
    for (auto ptr:arr)
        std::cout << ptr << " ";
}

template <typename Vector>
void output2File(std::fstream& file, Vector vecX, Vector vecY)
{
    // out array of i
    file << "i ";   std::cout << "i ";
    for (size_t i = 0; i < vecX.size(); i++) {
        file << std::to_string(i) << " ";
        std::cout << std::to_string(i) << " ";
    }
    file << std::endl;   std::cout << std::endl;
    // out array of X_i
    file << "x_i ";   std::cout << "x_i ";
    for (auto& ptr : vecX) {
        file << ptr << " ";
        std::cout << ptr << " ";
    }
    file << std::endl;   std::cout << std::endl;
    // out array of Y_i
    file << "y_i ";   std::cout << "y_i ";
    for (auto& ptr : vecY) {
        file << ptr << " ";
        std::cout << ptr << " ";
    }

    file.close();
}

template <typename Vector>
void output2File(std::fstream& file, Vector vecX, std::function<long double(long double)> func)
{
    // out array of i
    file << "i ";   std::cout << "i ";
    for (size_t i = 0; i < vecX.size(); i++) {
        file << std::to_string(i) << " ";
        std::cout << std::to_string(i) << " ";
    }
    file << std::endl;   std::cout << std::endl;
    // out array of X_i
    file << "x_i ";   std::cout << "x_i ";
    for (double& ptr : vecX) {
        file << ptr << " ";
        std::cout << ptr << " ";
    }
    file << std::endl;   std::cout << std::endl;
    // out array of Y_i
    file << "y_i ";   std::cout << "y_i ";
    for (double& ptr : vecX) {
        file << func(ptr) << " ";
        std::cout << func(ptr) << " ";
    }

    file.close();
}

}

#endif // OUTPUT_HPP
