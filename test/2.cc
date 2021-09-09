#include <iostream>

// nlohmann::json
#include <json.hpp>


// Eigen
#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>

// Eigen to JSON 
#include <EigenJSONSerialization.h>

int main()
{
    std::cout << "Eigen --> JSON\n";
    Eigen::MatrixXd D = Eigen::MatrixXd::Random( 2, 5 );
    std::cout << "---Input Matrix D:\n" << D << std::endl;



    nlohmann::json j = EigenJSONSerialization::toJSON( D );
    std::cout <<  "---Serialized :\n" << j << std::endl;
    

    Eigen::MatrixXd U;
    EigenJSONSerialization::fromJSON( j, U );
    std::cout << "---Deserialized matrix U:\n" << U << std::endl;





}