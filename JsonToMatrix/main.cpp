#include <iostream>
#include "newvariadic.h"
#include <fstream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>




int main()
{
    std::ifstream file("matrix.json",std::ifstream::binary);

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


    auto matrix = createMatrixFromJsonObject<int>(jsonObject);

    std::cout << "Compiled successfuly" << std::endl;
    return 0;
}
