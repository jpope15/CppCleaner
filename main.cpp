#include <iostream>
#include <filesystem>
#include <fstream>
#include <queue>
#include <boost/regex.hpp>

const boost::regex single_line_regex(".*\\/\\/.*DEBUG_REMOVE.*");
const boost::regex block_comment_start_regex(".*\\/\\*.*DEBUG_REMOVE.*");
const boost::regex block_comment_end_regex(".*\\*\\/.*");

bool is_single_line_comment(const std::string& line);
bool is_block_comment_start(const std::string& line);
bool is_block_comment_end(const std::string& line);

void handle_block_comment(std::string& line, std::ifstream& input_file, std::ofstream& output_file, int& lines_removed);

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
        std::cerr << "Couldn't open file " << argv[1] << "\nCheck your spelling and try again\n";
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
        if (is_block_comment_start(temp))
            handle_block_comment(temp, inputFile, outputFile, lines_removed);

        if (!is_single_line_comment(temp))
            outputFile << temp << '\n';        
        else
            lines_removed++;
    }
    inputFile.close();
    outputFile.close();

    // delete input file...
    if (std::remove(argv[1]))
        std::cerr << "Couldn't delete file " << argv[1] << '\n';

    std::rename("temp.txt", argv[1]);

    // writing to stdout
    std::cout << "Debug Cleaner\n"
            << "Ran on " << argv[1] << '\n'
            << "Removed " << std::to_string(lines_removed) << " lines\n";
    return 0U;
}

bool is_single_line_comment(const std::string& line)
{
    return boost::regex_match(line, single_line_regex);
}

bool is_block_comment_start(const std::string& line)
{
    return boost::regex_match(line, block_comment_start_regex);
}

bool is_block_comment_end(const std::string& line)
{
    return boost::regex_match(line, block_comment_end_regex);
}

void handle_block_comment(std::string& line, std::ifstream& input_file, std::ofstream& output_file, int& lines_removed)
{
    std::streampos old_pos = input_file.tellg();
    bool ok = false;
    int pos_lines_removed = 0;
    do
    {
        pos_lines_removed++;
        if (is_block_comment_end(line))
        {
            ok = true;
            break;
        }
    } while (std::getline(input_file, line));

    if (ok)
    { 
        lines_removed += pos_lines_removed;
        std::getline(input_file, line);         // advancing to the next line
    }
    else
    {
        input_file.seekg(old_pos);
    }
}
