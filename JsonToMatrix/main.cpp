#include <iostream>
#include "newvariadic.h"
#include <fstream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>




int main()
{
    std::ifstream file("matrix2.json",std::ifstream::binary);

    if(!file.is_open()){
        std::cerr << "Failed to open file" << std::endl;
        return 1;
    }

    Json::CharReaderBuilder builder;
    Json::Value jsonObject;
    std::string errs;

    bool parsingSuccessful = Json::parseFromStream(builder,file,&jsonObject,&errs);
    if(!parsingSuccessful){
        std::cerr << "Failed to parse file" << std::endl;
        std::cerr << errs<< std::endl;
        return 1;
    }

    Json::Value jso = jsonObject;
    int l = 0;
    /*while(jso.isArray())
    {
        std::cout << "size" << l << " - " << jso.size() << std::endl;
        ++l;
        jso = jso[0];
    }*/
    
    
    NDimensionalMatrix<int,4,1,1,4> Matrix;
    Matrix.print();


    Matrix.fillMatrixFromJson(jsonObject);
    std::cout << "After filling" << std::endl << std::endl << std::endl;

    Matrix.print();
    std::cout <<  "Matrix[2][0][0][1] = " << Matrix[2][0][0][1] << std::endl;
    std::cout <<  "Matrix[0][0][0][1] = " << Matrix[0][0][0][1] << std::endl;


    return 0;
}
