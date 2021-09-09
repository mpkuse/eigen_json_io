#pragma once 
#include <iostream>
#include <sstream>

#include "json.hpp"

#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Geometry>
// using namespace Eigen;




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
        
        Eigen::IOFormat CleanFmt( Eigen::FullPrecision,  Eigen::DontAlign, ",", ";", "", "");
        std::stringstream ss; 
        ss << a.format(CleanFmt) ;
        j["data"] = ss.str(); 

        return j; 
    }


    static bool fromJSON( const nlohmann::json str, Eigen::MatrixXd&  output )
    {
        int ncols = str["cols"];
        int nrows = str["rows"];
        std::string data = str["data"];
        if( ncols > 0 && ncols > 0 )
            output = Eigen::MatrixXd::Zero(nrows, ncols );
        else {
            std::cout << __FUNCTION__ << " ERROR, nrows and cols should be positive\n";
            return false;
        }


        // split( data, ';')
        std::vector<std::string> all_rows = split( data, ';' );
        if( nrows != all_rows.size() )
        {
            std::cout << __FUNCTION__ << " ERROR, requested " << nrows << " but actually are " << all_rows.size() << std::endl;
            return false;
        }
        for( int r=0 ; r<all_rows.size() ; r++ )
        {
            std::vector<std::string> all_cols_for_this_row = split( all_rows[r], ',' );
            if( ncols != all_cols_for_this_row.size() )
            {
                std::cout << __FUNCTION__ << " ERROR, requested " << ncols << " but actually are " << all_cols_for_this_row.size() << " for row=" << r << std::endl;
                return false;
            }

            for( int c=0 ; c<all_cols_for_this_row.size() ; c++ )
            {
                output(r, c) = std::stod( all_cols_for_this_row[c] );
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
};