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
    std::cout << "---Input Matrix D (shape=" << EigenFileHelpers::matrixShape(D) << "):\n" << D << std::endl;



    nlohmann::json D_json = EigenJSONSerialization::toJSON( D );
    std::cout <<  "---Serialized D:\n" << D_json << std::endl;
    


    Eigen::Matrix3d pose = Eigen::Matrix3d::Identity();
    nlohmann::json pose_json = EigenJSONSerialization::toJSON( pose );
    std::cout <<  "---Serialized po:\n" << pose_json << std::endl;


    
    // save to file 
    std::cout << "---Save to JSON file\n";
    EigenFileHelpers::saveToFile( std::string( "/tmp/j.json"), D_json );
    EigenFileHelpers::saveToFile( std::string( "/tmp/j_mat3d.json"), pose_json );


    // combine and save to file 
    std::cout << "---Save combined to JSON file\n";
    nlohmann::json combined_data; 
    combined_data["D"] = D_json; 
    combined_data["pose"] = pose_json; 
    EigenFileHelpers::saveToFile( std::string( "/tmp/combined_data.json"), combined_data );


    // load json 
    std::cout << "---Load combined JSON file\n";
    auto loaded_combined_data = EigenFileHelpers::loadFromFile( "/tmp/combined_data.json" );
    std::cout << loaded_combined_data << std::endl; 


    // deserialize pose 
    Eigen::Matrix3d pose_loaded;
    EigenJSONSerialization::fromJSON( loaded_combined_data.at("pose"), pose_loaded );
    std::cout << "pose_loaded:\n" << pose_loaded << std::endl;

    // deserialze D
    Eigen::MatrixXd D_loaded; 
    EigenJSONSerialization::fromJSON( loaded_combined_data.at("D"), D_loaded );
    std::cout << "D_loaded:\n" << D_loaded << std::endl;


}