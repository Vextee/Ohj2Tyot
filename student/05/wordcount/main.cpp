#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

std::vector<std::string> split(const std::string& line, char sep, bool empty = false)
{
    std::vector<std::string> parts;

    std::string::size_type left = 0;
    std::string::size_type right = line.find(sep, left);

    while(right != std::string::npos)
    {
        std::string part = line.substr(left, right-left);


        if (part != "" or !empty)
        {
            parts.push_back(part);
        }

        left = right + 1;
        right = line.find(sep, left);
    }

    std::string final_part = line.substr(left, std::string::npos);
    parts.push_back(final_part);

    return parts;
}

int main()
{
    std::string file_name;
    cout << "Input file: ";
    std::cin >> file_name;
    std::ifstream file;
    file.open(file_name);
    if (!file.is_open())
    {
        std::cout << "Error! The file " << file_name <<  " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<std::string> lines;
    std::string line;

    while(std::getline(file, line))
    {
        lines.push_back(line);
    }
    file.close();

    std::map<std::string, std::set<int>> lines_by_word;
    for (size_t row_index = 0; row_index < lines.size(); row_index++)
    {
        line = lines.at(row_index);
        std::vector<std::string> words = split(line, ' ', true);
        for ( size_t word_index = 0; word_index < words.size(); word_index++)
        {
            std::string word = words.at(word_index);
            if (lines_by_word.count(word) == 0)
            {
                lines_by_word[word] = std::set<int>();
            }
            lines_by_word[word].insert(static_cast<int>(row_index) + 1);
        }
    }

    for (std::pair<std::string, std::set<int>> key_value_pair : lines_by_word)
    {
        std::string word = key_value_pair.first;
        std::set<int> lines = key_value_pair.second;

        std::cout << word << " " << lines.size() << ": ";

        for (std::set<int>::iterator current_line = lines.begin(); current_line != lines.end(); ++current_line)
        {
            std::cout << *current_line;
            if (current_line != --lines.end())
            {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }


    return 0;
}
