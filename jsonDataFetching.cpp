#include <iostream> 
#include <vector>
#include <jsoncpp/json/json.h>
#include <map>
#include <string>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>
#include <fstream>




// for holding values of json object
std::map<std::string, int> for_ints;
std::map<std::string, bool> for_bools;
std::map<std::string, std::string> for_strings;


void sort_values(Json::Value& obj,std::string name = ""); // sorting values by it type
void Print_maps();



int main()
{


   std::ifstream file("jsonexamp.json", std::ifstream::binary);

	if(!file.is_open())
	{
		std::cerr << "Failed to open file" << std::endl;
		return 1;
	}

	
	Json::Value jsonObject;
	
	Json::CharReaderBuilder reader_builder;
	
	std::string errs;	
	bool parsingSuccessful = Json::parseFromStream(reader_builder,file,&jsonObject,&errs);
	if(!parsingSuccessful)
	{
		std::cout << "Failed to parse json file to json object" << std::endl;
		std::cout << errs << std::endl;
		return 1;
	}


    sort_values(jsonObject); 
    Print_maps();


    return 0;    

}



void sort_values(Json::Value& obj,std::string name)
{
    for(Json::Value::iterator it = obj.begin(); it != obj.end(); ++it)
    {
        if((*it).isInt())
        {
            if(name.empty())
                 for_ints[it.key().asString()] = (*it).asInt();
            else
                for_ints[name + it.key().asString()] = (*it).asInt();
        }
        else if((*it).isString())
        {
            if(name.empty())
                for_strings[it.key().asString()] = (*it).asString();
            else
                for_strings[name + it.key().asString()] = (*it).asString();
        }
        else if((*it).isBool())
        {
            if(name.empty())
                for_bools[it.key().asString()] = (*it).asBool();
            else
                 for_bools[name + it.key().asString()] = (*it).asBool();
        }
        else if((*it).isArray())
        {
            for(int i = 0;i < (*it).size(); ++i)
            {
                Json::Value element = (*it)[i];
                sort_values(element,std::to_string(i));
            }
        }
        else if((*it).isObject())
        {
            sort_values(*it,std::string(it.key().asString() + "->"));
        }
        
    }

    //std::cout << "Sort is over" << std::endl;
}



void Print_maps()
{
    std::cout << "Printing ints" << std::endl << std::endl;
    for(std::map<std::string,int>::iterator iter = for_ints.begin(); iter != for_ints.end(); ++iter)
    {
        std::cout << "Key: " << (*iter).first << " | Type: int | Value: " << (*iter).second << std::endl; 
    }
    std::cout << std::endl << "------------------------------------------" << std::endl;

    std::cout << "Printing bools" << std::endl << std::endl;
    for(std::map<std::string,bool>::iterator iter = for_bools.begin(); iter != for_bools.end(); ++iter)
    {
        std::cout << "Key: " <<(*iter).first << " | Type: bool | Value: " << (*iter).second << std::endl; 
    }
    std::cout << std::endl << "------------------------------------------" << std::endl;


    std::cout << "Printing strings" << std::endl << std::endl;
    for(auto iter = for_strings.begin(); iter != for_strings.end(); ++iter)
    {
        std::cout << "Key: " <<(*iter).first << " | Type: string | Value:  " << (*iter).second << std::endl; 
    }
    std::cout << std::endl << "------------------------------------------" << std::endl;


}

