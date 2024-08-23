#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/writer.h>
#include <jsoncpp/json/reader.h>



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

	

	// printing part
	


	Json::StreamWriterBuilder writer_builder;
	
	std::unique_ptr<Json::StreamWriter> writer(writer_builder.newStreamWriter());
	
	writer->write(jsonObject, &std::cout);
	std::cout << std::endl;

}
