#include <iostream>
#include "genTree.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "Parsing.hpp"
#include "getData.hpp"

int main(int argc, char const *argv[])
{
    // Parsing parser;
    // genTree tree;

    // tree.init();
    // tree.run();
    try 
    {
        genTree tree;
        CovidInfo info;
        Parsing parser;
        
        std::vector<std::string> colNames;
        info.download_daily_report(07, 01, 2020);
        auto resultParser = parser.run(readBuffer, colNames);
        tree.init(resultParser, colNames);
        tree.run();
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception Occured" << std::endl;
        std::cerr << e.what() << '\n';
    }

    return 0;
}
