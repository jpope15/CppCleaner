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
    std::ofstream outputFile("temp.txt");

    if (!inputFile.is_open())
    {
        std::cerr << "Couldn't open file " << argv[1] << '\n';

        return 0U;
    }
    if (!outputFile.is_open())
    {
        std::cerr << "Couldn't open file temp.txt";
        return 0U;
    }

    // parsing the file
    std::string temp;
    int lines_removed = 0;
    while (std::getline(inputFile, temp))
    {
        if (!boost::regex_match(temp, delim_regex))
        {
            outputFile << temp << '\n';
        }
        else
        {
            lines_removed++;
        }
    }
    inputFile.close();
    outputFile.close();

    // delete input file...
    if (std::remove(argv[1]))
    {
        std::cerr << "Couldn't delete file " << argv[1] << '\n';
    }

    std::rename("temp.txt", argv[1]);

    // writing to stdout
    std::cout << "CPP_CLEANER\n"
            << "Ran on " << argv[1] << '\n'
            << "Removed " << std::to_string(lines_removed) << " lines\n";
    return 0U;
}