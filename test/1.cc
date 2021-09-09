#include <iostream>

#include <json.hpp>


int main()
{
    std::cout << "Hello\n";
    nlohmann::json j; 

    j["pi"] = 3.14;
    std::cout << j << std::endl;

    // More examples on how to use the nlohmann::json 
    //      https://github.com/nlohmann/json#json-as-first-class-data-type

}