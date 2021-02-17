#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

std::vector<std::string> split(const std::string& line, char sep, bool empty = false)
{
    std::vector<std::string> parts;

    std::string::size_type left = 0;
    std::string::size_type right = 0;

    while(right != std::string::npos)
    {
        right = line.find(sep, left);

        std::string part = line.substr(left, right - left);

        if (part == "" and empty == true)
        {
            left = right + 1;
            continue;
        }

        parts.push_back(part);

        left = right + 1;
    }



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
    std::map<string, int> results;

    while(std::getline(file, line))
    {
        std::vector<std::string> parts = split(line, ':', true);
        if(results.find(parts.at(0)) != results.end())
        {
            results.at(parts.at(0)) += stoi(parts.at(1));
        }
        results.insert({parts.at(0), stoi(parts.at(1))});
    }
    std::cout << "Final scores: " << std::endl;

    std::map<string, int>::iterator iter;
    iter = results.begin();
    while (iter != results.end())
    {
        std::cout << iter->first << ": " << iter->second << std::endl;
                ++iter;
    }

    return EXIT_SUCCESS;
}
