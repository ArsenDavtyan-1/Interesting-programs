#ifndef VARIADIC_H_
#define VARIADIC_H_
#include <iostream>
#include <vector>
#include <utility>
#include <tuple>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>
#include <jsoncpp/json/reader.h>

template <typename T, size_t... Dims>   // Dims short for dimensions
class NDimensionalMatrix;


template <typename T, size_t First, size_t... Rest>
class NDimensionalMatrix<T,First, Rest...>
{
public:
    using SubMatrix = NDimensionalMatrix<T,Rest...>;

    NDimensionalMatrix() : data(First) {}

    SubMatrix& operator[](const size_t index)
    {
        return data[index];
    }

    const SubMatrix& operator[](const size_t index) const
    {
        return data[index];
    }

    void print(size_t level = 0) const
    {
        for(const auto& submatrix : data){
            submatrix.print(level + 1);
            std::cout << std::endl;
        }
        if(level == 0)
            std::cout << std::endl;
    }

    void fillMatrixFromJson(Json::Value jsonObject)
    {
        //std::cout << "Opened fill function" << std::endl;
        int i = 0;
        for(auto& submatrix : data){
            submatrix.fillMatrixFromJson(jsonObject[i]);
            //std::cout << "i = " << i << std::endl;
            ++i;
        }
        //std::cout << "Closed fill function" << std::endl;
    }
private:
    std::vector<SubMatrix> data;
};



template <typename T,size_t Last>
class NDimensionalMatrix<T,Last>
{

public:
    NDimensionalMatrix() : data(Last){}

    T& operator[](const size_t index)
    {
        return data[index];
    }
    const T& operator[](const size_t index) const
    {
        return data[index];
    }

    void print(size_t level = 0) const
    {
        for(const T& elem : data)
            std::cout << elem << "  ";
    }

    void fillMatrixFromJson(Json::Value jsonObject)
    {
        //std::cout << "Opened base fill function" << std::endl;
        int i = 0;
        for(auto& elem : data){
            //std::cout << "data[" << i << "] = " << (jsonObject[i]) << ", ";
            elem = (jsonObject[i]).asInt();
            ++i;
        }
        //std::cout << "exit from base case" << std::endl;   
    }

private:
    std::vector<T> data;
};




    
    


#endif      // !VARIADIC_H_ 




