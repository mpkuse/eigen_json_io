# Header-only JSON Serialization for Eigen 
This project give you tools to Serialize Eigen::Matrix to JSON
and also Deserialize JSON to Eigen::Matrix. 
For json parsing, we rely on the awesome `nlohmann/json` library. 
See [here](https://github.com/nlohmann/json). 


[Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page) is a C++ template library for linear algebra: matrices, vectors, numerical solvers, and related algorithms. It is quite widely used in 
computer vision / geometric vision / slam / 3d reconstruction 
community. 

## What can you do with this?

**Serialize Eigen (Eigen --> json )**
```
Eigen::MatrixXd D = Eigen::MatrixXd::Random( 2, 5 );
nlohmann::json D_json = EigenJSONSerialization::toJSON( D );
std::cout <<  "---Serialized D:\n" << D_json << std::endl;    
```


**Save json to file**
```
EigenFileHelpers::saveToFile( std::string( "/tmp/D.json"), D_json );
```

**Load .json file**
```
nlohmann::json loaded_combined_data = EigenFileHelpers::loadFromFile( 
    "/tmp/combined_data.json" );

```

**Deserialize JSON (json --> Eigen)**
```
Eigen::Matrix3d pose_loaded;
EigenJSONSerialization::fromJSON( loaded_combined_data.at("pose"), pose_loaded );
```


## Usage Samples 
Look at `test/`

## How to Install / Use in your own projects
Simply copy `include/json.hpp` and `include/EigenJSONSerialization.h`
to your project. Include both in places where you wish to 
do the Eigen <--> JSON file. 


## Author
Manohar Kuse <mpkuse@connect.ust.hk>