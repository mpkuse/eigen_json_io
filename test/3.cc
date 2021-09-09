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
    // Input data 
    Eigen::MatrixXd objectPts = Eigen::MatrixXd::Random( 4, 10 );
    Eigen::MatrixXd imagePts = Eigen::MatrixXd::Random( 3, 10 );
    Eigen::Matrix3d K = Eigen::Matrix3d::Random(); 
    Eigen::Matrix4d cam_pose0 = Eigen::Matrix4d::Random(); 
    Eigen::VectorXd wt = Eigen::VectorXd::Ones(5); 
    Eigen::VectorXi idx = Eigen::VectorXi::Random(8); 

    std::cout << "---Input Data:\n";
    std::cout << "objectPts:\n" << objectPts << std::endl;
    std::cout << "imagePts:\n" << imagePts << std::endl;
    std::cout << "K:\n" << K << std::endl;
    std::cout << "cam_pose0:\n" << cam_pose0 << std::endl;
    std::cout << "wt:\n" << wt << std::endl;
    std::cout << "idx:\n" << idx << std::endl;



    // Serialization
    std::cout << "=====\nEigen --> JSON\n=====\n";
    nlohmann::json j; 
    j["K"] = EigenJSONSerialization::toJSON( K );
    j["objectPts"] = EigenJSONSerialization::toJSON( objectPts );
    j["imagePts"] = EigenJSONSerialization::toJSON( imagePts );
    j["cam_pose0"] = EigenJSONSerialization::toJSON( cam_pose0 );
    j["wt"] = EigenJSONSerialization::toJSON( wt );
    j["idx"] = EigenJSONSerialization::toJSON( idx );
    std::cout <<  "---Serialized :\n" << j.dump(4) << std::endl;


    // Deserialized output vars
    Eigen::MatrixXd objectPts_d;
    Eigen::MatrixXd imagePts_d;
    Eigen::Matrix3d K_d;
    Eigen::Matrix4d cam_pose0_d;
    Eigen::VectorXd wt_d;
    Eigen::VectorXi idx_d;


    // Deserialization
    std::cout << "=====\nJSON --> Eigen\n=====\n";
    if( ! EigenJSONSerialization::fromJSON( j["K"], K_d ) )  return false; 
    if( ! EigenJSONSerialization::fromJSON( j["cam_pose0"], cam_pose0_d ) ) return false; 
    if( ! EigenJSONSerialization::fromJSON( j["objectPts"], objectPts_d ) ) return false; 
    if( ! EigenJSONSerialization::fromJSON( j["imagePts"], imagePts_d ) ) return false; 
    if( ! EigenJSONSerialization::fromJSON( j["wt"], wt_d ) ) return false; 
    if( ! EigenJSONSerialization::fromJSON( j["idx"], idx_d ) ) return false; 

    


    std::cout << "---Deserialized Data:\n";
    std::cout << "objectPts_d:\n" << objectPts_d << std::endl;
    std::cout << "imagePts_d:\n" << imagePts_d << std::endl;
    std::cout << "K_d:\n" << K << std::endl;
    std::cout << "cam_pose0_d:\n" << cam_pose0_d << std::endl;
    std::cout << "wt_d:\n" << wt_d << std::endl;
    std::cout << "idx_d:\n" << idx_d << std::endl;

    std::cout << "========________=========\n";
    std::cout << "========SUCCESS =========\n";
    std::cout << "========________=========\n";
}