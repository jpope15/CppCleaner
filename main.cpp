#include <iostream>
#include <filesystem>
#include <fstream>
#include <boost/regex.hpp>

static const boost::regex delim_regex(".*\\/\\/\\s*!CPP_CLEAN!");

int main(int argc, char* argv[])
{
    if (argc != 2U)
    {
        std::cerr << "Error: no input file specified\n";
        return 0U;
    }

    // opening the listed file
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        std::cerr << "Couldn't open file " << argv[1] << '\n';
        return 0U;
    }

    // parsing the file
    std::string temp;
    while (std::getline(inputFile, temp))
    {
        if (boost::regex_match(temp, delim_regex))
        {
            std::cout << "found a match\n";
        }
        else
        {
            std::cout << temp << "\n";
        }
    }    
    inputFile.close();

    // delete input file...
     
    // open input file as new output file...

    // write to output file
    return 0U;
}