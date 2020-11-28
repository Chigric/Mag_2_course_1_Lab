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
    static const size_t precision = 16;

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
        std::cout.setf(std::ios::fixed);
        std::cout.precision(precision);
        std::cout << data;
        outFile.setf(std::ios::fixed);
        outFile.precision(precision);
        outFile << data;
        return *this;
    }
    DoubleOutput& operator <<(const char* data)
    {
        std::cout << data;
        outFile << data;
        return *this;
    }
    DoubleOutput& operator <<(int data)
    {
        std::cout << data;
        outFile << data;
        return *this;
    }
    template<typename Arg>
    DoubleOutput& operator <<(Arg&& data)
    {
        std::cout.setf(std::ios::fixed);
        std::cout.precision(precision);
        std::cout << data;
        outFile.setf(std::ios::fixed);
        outFile.precision(precision);
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
    // сколько столбцов в строке && текущее полажение каретки
    size_t prettyOutput = 10, curSize = 0;
    // шаг вывода
    size_t stepOutput = 1;
    // my Loop =)
    auto myLoop = [&] (const char* str, Vector& vec) {
        out << str;
        for (size_t i = curSize; i < curSize+prettyOutput; i+=stepOutput) {
            if (i == curSize+prettyOutput - 1)
                out << vec[i];
            else
                out << vec[i] << " ";
        }
    };
    auto myLoopInt = [&] (const char* str, std::valarray<int>& vec) {
        out << str;
        for (size_t i = curSize; i < curSize+prettyOutput; i+=stepOutput) {
            if (i == curSize+prettyOutput - 1)
                out << vec[i];
            else
                out << vec[i] << " ";
        }
    };

    std::valarray<int> iVec(size);
    int count = 0;
    for (auto& ptr : iVec)
        ptr = count++;

    while (curSize < size) {
        // out array of i
        myLoopInt("i ", iVec);
        out << SundayWork::endl;
        // out array of x_i
        myLoop("X ", vecX);
        out << SundayWork::endl;
        // out array of Y_i
        myLoop("Y ", vecY);

        curSize += prettyOutput;
        if (curSize < size)
            out << SundayWork::endl;
        // output last row
        if (curSize >= size - prettyOutput)
            prettyOutput = size - curSize;
    }
}

template <typename Vector>
void output2File(std::fstream& file, Vector vecX, std::function<long double(long double)> func)
{
    Vector vecY(vecX.size());
    auto iterY = std::begin(vecY);
    for (auto ptr : vecX) {
        *iterY = func(ptr);
        ++iterY;
    }
    output2File(file, vecX, vecY);
}

}

#endif // OUTPUT_HPP
