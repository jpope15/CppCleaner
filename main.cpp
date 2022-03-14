#include <iostream>
#include <filesystem>
#include <fstream>

int main(int argc, char* argv[])
{
    if (argc != 2U)
    {
        std::cerr << "Error: no input file specified";
        return 0U;
    }

    // opening the listed file
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open())
    {
        std::cerr << "Couldn't open file " << argv[1];
        return 0U;
    }

    // check if its a valid file extension...

    // parse the file...

    // close input file...
    inputFile.close();

    // delete input file...
     
    // open input file as new output file...

    // write to output file
    return 0U;
}