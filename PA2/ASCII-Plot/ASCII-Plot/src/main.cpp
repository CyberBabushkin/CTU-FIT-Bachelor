//
//  main.cpp
//  ASCII-Plot
//
//  Created by Andrey Babushkin on 18/05/16.
//  Copyright © 2016 Mannannlegur. All rights reserved.
//

/*! \mainpage Welcome to ASCII-Plots Documentation!
 *
 * \section intro_sec This program was created to help you visualise
 * your data with the fabulous ASCII graphics. 
 *
 * - Firstly, build the project. Instructions can be found here: \ref install_sec.
 * - Secondly, run the program! That's it. If you don't know how to use it follow this link: \ref using_sec.
 *
 *
 * \section install_sec Installation
 * In the main directory from the terminal you can use these commands:
 * - make all
 * \par This command will create the binary file and the documentation.
 * - make compile
 * \par Creates only the binary file.
 * - make doc
 * \par Creates only the documentation (like this one that you're reading now).
 * - make run
 * \par Runs the program with default parameters.
 * - make clean
 * \par Deletes the binary file and the documentation.
 *
 * \section using_sec How to use
 * The syntax is:
 *
 * \par asciiplots [--conf config_file] [--hist histogram_data_path] [--pie pie_data_path] [--bar bar_data_path] [--line line_data_path] data_path<br>
 * \par asciiplots [--conf config_file] --hist histogram_data_path --pie pie_data_path --bar bar_data_path --line line_data_path
 *
 * As you can see, there are two possibilities. You should specify a data file for all 4 plots
 * but you can specify only one data file for all plots. As an example, the default run will be shown.
 * 
 * You want to set a data file for a histogram called data.csv, for a bar chart bar.csv and for pie and line plots
 * a file data1.csv. Just run the program with these parameters:
 *
 * \par asciiplots --hist ./data.csv --bar ./bar.csv ./data1.csv
 *
 * The defaulf path (the last argument) will be used for all unconfigured plots. 
 *
 * Or you want to set for every plot a separated data file:
 *
 * \par asciiplots --conf ./conf.conf --bar ./bar.csv --hist ./hist.csv --pie ./pie.csv --line ./line.csv
 *
 * That's it!
 *
 * All available flags are:
 * - --hist Sets the path to a data file for a histogram plot.
 * - --line Sets the path to a data file for a line plot.
 * - --pie Sets the path to a data file for a pie chart.
 * - --bar Sets the path to a data file for a bar chart.
 * - --conf Sets the path to a configuration file.
 */

#include <iostream>

#include "CInterlocutor.h"

using namespace std;

/*!
 * \brief A main function of a program.
 *
 * Reads arguments, parses them and then creates an instance of CInterlocutor.
 */
int main(int argc, const char * argv[])
{
    try
    {
        string howToUse = "asciiplots [--conf config_file] [--hist histogram_data_path] [--pie pie_data_path] "
                          "[--bar bar_data_path] [--line line_data_path] data_path\n\n"
                          "asciiplots [--conf config_file] --hist histogram_data_path --pie pie_data_path --bar bar_data_path"
                          " --line line_data_path";
        if ( argc == 1 )
        {
            cout << howToUse << endl;
            return 1;
        }
        
        map<string, string> flags = {
                                      { "--hist", "" },
                                      { "--line", "" },
                                      { "--pie" , "" },
                                      { "--bar" , "" },
                                      { "--conf", "../../examples/config.conf" }
                                    };
        
        for ( int i = 1; i < argc; i++ )
        {
            string arg( argv[i] );
            
            if ( arg.empty() )
            {
                cout << "An empty parameter found." << endl;
                
                cout << howToUse << endl;
                return 1;
            }
            
            map<string, string>::iterator it = flags.find( arg );
            
            if ( it == flags.end() &&
                 arg[0] == '-' )
            {
                cout << "Unknown parameter: \"" + arg + "\"." << endl;
                
                cout << howToUse << endl;
                return 1;
            }
            
            if ( it == flags.end() )
            {
                if ( i+1 < argc )
                {
                    cout << "Error! Found arguments after the non-key value." << endl;
                    
                    cout << howToUse << endl;
                    return 1;
                }
                
                for ( map<string, string>::iterator it = flags.begin();
                      it != flags.end();
                      it ++ )
                    if ( it->second . empty() )
                        it->second = arg;
                continue;
            }
            
            if ( i + 1 == argc )
            {
                cout << "No values found for the argument \"" + arg + "\"." << endl;
                
                cout << howToUse << endl;
                return 1;
            }
            
            i ++;
            it -> second = argv[i];
            
        }
        
        for ( map<string, string>::iterator it = flags.begin();
              it != flags.end();
              it ++ )
            if ( it->second . empty() )
            {
                cout << "Error!\n";
                cout << "No data file(s) were specified.\n"
                        "Please, either specify for every plot a path to its data or "
                        "just use generalised syntax to set a general data file for all unset paths.";
                cout << endl << endl;
                
                cout << howToUse << endl;
                return 1;
            }
                    
        try
        {
            CInterlocutor interloc( flags );
        }
        catch ( CException & ex )
        {
            cout << "Error: ";
            cout << ex.toString() << endl;
            cout << "Exiting..." << endl;
            return 1;
        }
    }
    catch (...)
    {
        cout << "An unknown error occurred." << endl;
        return 1;
    }
    
    
}
