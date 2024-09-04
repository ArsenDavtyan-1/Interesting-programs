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

private:
    std::vector<T> data;
};




template<typename T>
auto createMatrixFromJsonObject(Json::Value& jsonObj) {
    std::vector<size_t> dims;
    while(jsonObj.isArray()){
        dims.push_back(static_cast<std::size_t>(jsonObj.size()));
        jsonObj = jsonObj[0];
    }
    if(dims.empty())
        std::cout << "Empty vector of dimensions" << std::endl;
    std::cout << "dimensions - " ;
    for(int i = 0; i < dims.size(); ++i){
        std::cout << dims[i] << (i < dims.size() - 1) ? "," : ".";
        std::cout << std::endl;
    } 
    auto tupleDims = std::apply([](auto... dims) {
        return std::make_tuple(dims...);
    }, dims);

    return std::apply([](auto... dims) {
        return NDimensionalMatrix<T, dims...>();
    }, tupleDims);
}
    
    


#endif      // !VARIADIC_H_ 




