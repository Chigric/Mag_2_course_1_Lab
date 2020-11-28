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


enum Specifiers
{
    endl = 0x01
};

class DoubleOutput
{
private:
    // уже открытый файл (opened file)
    std::fstream outFile;

public:
    DoubleOutput(std::fstream& file)
    {
        outFile = std::move(file);
    }
    ~DoubleOutput()
    {
        outFile.close();
    }

    template<typename Arg>
    DoubleOutput& operator <<(Arg& data)
    {
        std::cout << data;
        outFile << data;
        return *this;
    }

    template<typename Arg>
    DoubleOutput& operator <<(Arg&& data)
    {
        std::cout << data;
        outFile << data;
        return *this;
    }

    // I'm so lazy for write this through funcs (like std::endl)
    DoubleOutput& operator <<(Specifiers specifier)
    {
        if (specifier == SundayWork::endl)
            *this << "\n";
        return *this;
    }
};

template <typename Vector>
void output2File(std::fstream& file, Vector vecX, Vector vecY)
{
    DoubleOutput out(file);
    size_t size = vecX.size();
    const size_t prettyOutput = 10;
    auto myLoop = [&out, &prettyOutput] (const char* str, Vector& vec) {
        out << str;
        for (size_t i = 0; i < prettyOutput; i++)
            out << vec[i] << " ";
    };

    size_t tmpSize = 0;
    while (tmpSize < size) {
        // out array of i
        out << "i ";
        for (size_t i = 0; i < prettyOutput; i++)
            out << i << " ";
        out << SundayWork::endl;
        // out array of x_i
        myLoop("x_i ", vecX);
        out << SundayWork::endl;
        // out array of Y_i
        myLoop("y_i ", vecY);

        if ((tmpSize += prettyOutput) < size)
            out << SundayWork::endl;
    }
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
