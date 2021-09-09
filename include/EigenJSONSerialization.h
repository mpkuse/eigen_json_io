#pragma once 
#include <iostream>
#include <sstream>
#include <fstream>

#include "json.hpp"

#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>
// using namespace Eigen;


class EigenFileHelpers
{
    public:
    static bool saveToFile( const std::string output_fname, const nlohmann::json& j, bool save_pretty=true )
    {
        std::ofstream ofile( output_fname );
        if( ! ofile.good() ) {
            std::cout << __FUNCTION__ << " ERROR, cannot save json to file=" << output_fname  << std::endl;
            return false; 
        }
        
        ofile << j.dump(2) << std::endl;
        return true; 

    }

    static bool loadFromFile( const std::string output_fname, nlohmann::json& j )
    {
        std::ifstream inpfile(output_fname);
        if( ! inpfile.good() ) {
            std::cout << __FUNCTION__ << " ERROR, cannot load json from file=" << output_fname  << std::endl;
            return false; 
        }
        
        inpfile >> j;
        return true; 
    }

    static nlohmann::json loadFromFile( const std::string output_fname )
    {
        nlohmann::json j;

        std::ifstream inpfile(output_fname);
        if( ! inpfile.good() ) {
            std::cout << __FUNCTION__ << " ERROR, cannot load json from file=" << output_fname  << std::endl;
            return j; 
        }
        
        
        inpfile >> j;
        return j; 
    }

    template <typename Derived>
    static std::string matrixShape( const Eigen::MatrixBase<Derived>& a )
    {
        std::stringstream ss; 
        ss << a.rows() << "x" << a.cols() ;
        return ss.str(); 
    }
};


class EigenJSONSerialization 
{
    /**
    //  [ 0.2857131543876468, -0.2530077727001951, 0.9243132912401226, -0.02953755668229465   ]
    //  [-0.9566719337894203, -0.01884313243445668, 0.2905576491157474, 0.2114882406102183,   ]
    //  [-0.05609638588601445, -0.9672807262182707, -0.2474291659792429, 0.04534835279466286, ]
    //  [0, 0, 0, 1                                                                           ]           
    //                      |
    //                      |
    //                      v
    //{
    //            "cols": 4,
    //            "rows": 4,
    //            "data": "0.2857131543876468, -0.2530077727001951, 0.9243132912401226, -0.02953755668229465 ; -0.9566719337894203, -0.01884313243445668, 0.2905576491157474, 0.2114882406102183, ; -0.05609638588601445, -0.9672807262182707, -0.2474291659792429, 0.04534835279466286 ;0, 0, 0, 1"
    //            "type": "Eigen"
    // }
    */
    public: 
    template <typename Derived>
    static nlohmann::json toJSON( const Eigen::MatrixBase<Derived>& a)
    {
        if( a.size() == 0 ) {
            nlohmann::json j_empty; 
            return j_empty; 
        }

        nlohmann::json j; 
        j["cols"] = a.cols(); 
        j["rows"] = a.rows();
        j["type"] = "Eigen"; 
        
        Eigen::IOFormat CleanFmt( Eigen::FullPrecision,  Eigen::DontAlign, ",", ";", "", "");
        std::stringstream ss; 
        ss << a.format(CleanFmt) ;
        j["data"] = ss.str(); 

        return j; 
    }

    static bool fromJSON( const nlohmann::json& str, Eigen::MatrixXd&  output )
    {
        if( is_valid_eigen_serialization( str ) == false ) 
            return false;
        

        const int nrows = str.at("rows");
        const int ncols = str.at("cols");
        const std::string data = str.at("data");
        if( ncols > 0 && nrows > 0 )
            output = Eigen::MatrixXd::Zero(nrows, ncols );
        else {
            std::cout << __FUNCTION__ << " ERROR, nrows and cols should be positive\n";
            return false;
        }


        // split( data, ';')
        std::vector<std::string> all_rows = split( data, ';' );
        for( int r=0 ; r<all_rows.size() ; r++ )
        {
            std::vector<std::string> all_cols_for_this_row = split( all_rows[r], ',' );
            
            for( int c=0 ; c<all_cols_for_this_row.size() ; c++ )
            {
                output(r, c) = std::stod( all_cols_for_this_row[c] );
            }
        }
        return true;

    }

    static bool fromJSON( const nlohmann::json& str, Eigen::Matrix4d&  output )
    {
        if( is_valid_eigen_serialization( str ) == false ) 
            return false;
        

        const int nrows = str.at("rows");
        const int ncols = str.at("cols");
        const std::string data = str.at("data");
        if( nrows == 4 && ncols ==4  )
            output = Eigen::Matrix4d::Zero( );
        else {
            std::cout << __FUNCTION__ << " ERROR, nrows and cols should be 4 and 4\n";
            return false;
        }


        // split( data, ';')
        std::vector<std::string> all_rows = split( data, ';' );
        for( int r=0 ; r<all_rows.size() ; r++ )
        {
            std::vector<std::string> all_cols_for_this_row = split( all_rows[r], ',' );
            
            for( int c=0 ; c<all_cols_for_this_row.size() ; c++ )
            {
                output(r, c) = std::stod( all_cols_for_this_row[c] );
            }
        }
        return true;
    }

    static bool fromJSON( const nlohmann::json& str, Eigen::Matrix3d&  output )
    {
        if( is_valid_eigen_serialization( str ) == false ) 
            return false;
        

        const int nrows = str.at("rows");
        const int ncols = str.at("cols");
        const std::string data = str.at("data");
        if( nrows == 3 && ncols == 3  )
            output = Eigen::Matrix3d::Zero( );
        else {
            std::cout << __FUNCTION__ << " ERROR, nrows and cols should be 3 and 3\n";
            return false;
        }


        // split( data, ';')
        std::vector<std::string> all_rows = split( data, ';' );
        for( int r=0 ; r<all_rows.size() ; r++ )
        {
            std::vector<std::string> all_cols_for_this_row = split( all_rows[r], ',' );
            
            for( int c=0 ; c<all_cols_for_this_row.size() ; c++ )
            {
                output(r, c) = std::stod( all_cols_for_this_row[c] );
            }
        }
        return true;
    }

    static bool fromJSON( const nlohmann::json& str, Eigen::VectorXd&  output )
    {
        if( is_valid_eigen_serialization( str ) == false ) 
            return false;
        

        const int nrows = str.at("rows");
        const int ncols = str.at("cols");
        const std::string data = str.at("data");
        if( nrows > 0 && ncols == 1  )
            output = Eigen::VectorXd::Zero(nrows );
        else {
            std::cout << __FUNCTION__ << " ERROR, nrows and cols should be 4 and 1\n";
            return false;
        }


        // split( data, ';')
        std::vector<std::string> all_rows = split( data, ';' );
        for( int r=0 ; r<all_rows.size() ; r++ )
        {
            std::vector<std::string> all_cols_for_this_row = split( all_rows[r], ',' );
            
            for( int c=0 ; c<all_cols_for_this_row.size() ; c++ )
            {
                output(r, c) = std::stod( all_cols_for_this_row[c] );
            }
        }
        return true;
    }

    static bool fromJSON( const nlohmann::json& str, Eigen::VectorXi&  output )
    {
        if( is_valid_eigen_serialization( str ) == false ) 
            return false;
        

        const int nrows = str.at("rows");
        const int ncols = str.at("cols");
        const std::string data = str.at("data");
        if( nrows > 0 && ncols ==1  )
            output = Eigen::VectorXi::Zero(nrows );
        else {
            std::cout << __FUNCTION__ << " ERROR, nrows and cols should be 4 and 4\n";
            return false;
        }


        // split( data, ';')
        std::vector<std::string> all_rows = split( data, ';' );
        for( int r=0 ; r<all_rows.size() ; r++ )
        {
            std::vector<std::string> all_cols_for_this_row = split( all_rows[r], ',' );
            
            for( int c=0 ; c<all_cols_for_this_row.size() ; c++ )
            {
                output(r, c) = std::stoi( all_cols_for_this_row[c] );
            }
        }
        return true;
    }

    private:
    static std::vector<std::string>
    split( std::string const& original, char separator )
    {
        std::vector<std::string> results;
        std::string::const_iterator start = original.begin();
        std::string::const_iterator end = original.end();
        std::string::const_iterator next = std::find( start, end, separator );
        while ( next != end ) {
            results.push_back( std::string( start, next ) );
            start = next + 1;
            next = std::find( start, end, separator );
        }
        results.push_back( std::string( start, next ) );
        return results;
    }    

    static bool is_valid_eigen_serialization( const nlohmann::json& j )
    {
        // make sure it contains 'rows', 'cols', 'data'
        if( !( j.contains( "rows") && j.contains("cols") && j.contains( "data") && j.contains("type") ) )
        {
            std::cout << __FUNCTION__ << "The input json does not look like an eigen serialization. It needs to contain the keys: `rows`, `cols`, `data`, `type`" << std::endl;
            std::cout << "Input json:\n>>>>>" << j.dump(4) << "<<<<<\n";
            return false; 
        }

        if(  !( j.at( "rows").is_number_integer()  && j.at( "cols" ).is_number_integer() && j.at( "data").is_string() && j.at( "type").is_string() ) )
        {
            std::cout << __FUNCTION__ << "The input json does not look like an eigen serialization. It needs to contain the keys: `rows` (type=int), `cols` (type=int), `data` (string), `type`" << std::endl;
            std::cout << "Input json:\n>>>>>" << j.dump(4) << "<<<<<\n";
            return false; 
        }


        if( j.at("type") != "Eigen" )
        {
            std::cout << __FUNCTION__ << "The input jsons type has to be Eigen, json_d[type]=" << j.at("type" );
            std::cout << "Input json:\n>>>>>" << j.dump(4) << "<<<<<\n";
            return false; 
        }

        if( j.at( "rows") <= 0 || j.at( "cols") <= 0 )
        {
            std::cout << __FUNCTION__ << "The input json need to have +ve integers for json_d[rows] and for json_d[cols]\n"; 
            std::cout << "Input json:\n>>>>>" << j.dump(4) << "<<<<<\n";
            return false; 
        }


        std::vector<std::string> all_rows = split( j.at("data"), ';' );
        if( j.at( "rows") != all_rows.size() )
        {
            std::cout << __FUNCTION__ << " ERROR, requested " << j.at( "rows") << " but actually are " << all_rows.size() << std::endl;
            return false;
        }
        
        for( int r=0 ; r<all_rows.size() ; r++ )
        {
            std::vector<std::string> all_cols_for_this_row = split( all_rows[r], ',' );
            if( j.at( "cols") != all_cols_for_this_row.size() )
            {
                std::cout << __FUNCTION__ << " ERROR, requested " << j.at( "cols") << " but actually are " << all_cols_for_this_row.size() << " for row=" << r << std::endl;
                return false;
            }
        }

        return true; 

    }
};