#include <iostream>
#include <map>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>

// The most magnificent function in this whole program.
// Prints a RASSE
void print_rasse()
{
    std::cout <<
                 "=====//==================//===\n"
                 "  __<<__________________<<__   \n"
                 " | ____ ____ ____ ____ ____ |  \n"
                 " | |  | |  | |  | |  | |  | |  \n"
                 " |_|__|_|__|_|__|_|__|_|__|_|  \n"
                 ".|                  RASSE   |. \n"
                 ":|__________________________|: \n"
                 "___(o)(o)___(o)(o)___(o)(o)____\n"
                 "-------------------------------" << std::endl;
}

std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}


std::string read_file_name()
{
    std::string file_name;
    std::cout << "Give a name for input file: ";
    std::cin >> file_name;
    return file_name;
}

bool check_data(std::string file_name)
{
    std::ifstream file(file_name);
    if (!file)
    {
        std::cout << "Error: File could not be read." << std::endl;
        file.close();
        return false;
    }
    else
    {
        std::string line;
        while (getline(file, line))
        {
           std::vector<std::string> parts = split(line, ';');
           if (parts.size() > 3 or parts.size() < 2 or parts.at(0) == "" or parts.at(1) == "")
           {
               std::cout << "Error: Invalid format in file." << std::endl;
               file.close();
               return false;
           }
        }
    }
    file.close();
    return true;
}

bool same_command(std::string real_command, std::string given_command)
{
    std::transform(given_command.begin(), given_command.end(), given_command.begin(), ::toupper);
    if (given_command == real_command)
    {
        return true;
    }
    else
    {
        return false;
    }

}

using Tramlines = std::map<std::string, std::map<std::string, double>>;

void print_lines(Tramlines tramlines)
{
    return;
}

void print_line_stops(Tramlines tramlines, std::string lines)
{
    return;
}

void print_stops(Tramlines tramlines)
{
    return;
}

void print_stop_lines(Tramlines tramlines, std::string stop)
{
    return;
}

void print_distance_between_stops(Tramlines tramlines, std::string line, std::string stop1, std::string stop2)
{
    return;
}

void add_line(Tramlines& tramlines, std::string line)
{
    return;
}

void add_stop(Tramlines& tramlines, std::string line, std::string new_stop, double distance)
{
    return;
}

void remove_stop(Tramlines& tramlines, std::string stop)
{
    return;
}

bool interface(std::string file_name)
{
    std::map <std::string, std::map<std::string, double>> tramlines;
    std::ifstream file(file_name);
    std::string line;

    /*while (getline(file, line))
    {
        std::vector<std::string> parts = split(line, ';');
        if(parts.at(2) == "")
        {
            parts.at(2) = "0";
        }
        if (tramlines.find(parts.at(0)) != tramlines.end())
        {

        }
    }*/


    while(true)
    {
        std::string full_command;
        std::cout << "tramway> ";
        getline(std::cin, full_command);
        std::vector<std::string> command_parts = split(full_command, ' ');
        std::string command = command_parts.at(0);

        if (same_command("QUIT", command))
        {
            break;
        }
        else if (same_command("LINES", command))
        {
            print_lines(tramlines);
        }
        else if (same_command("LINE", command))
        {
            if (command_parts.size() < 2)
            {
                std::cout << "Error: Invalid input." << std::endl;
            }
            else
            {
                std::string line = command_parts.at(1);
                print_line_stops(tramlines, line);
            }
        }
        else if (same_command("STOPS", command))
        {
            print_stops(tramlines);
        }
        else if (same_command("STOP", command))
        {
            if (command_parts.size() < 2)
            {
                std::cout << "Error: Invalid input." << std::endl;
            }
            else
            {
                std::string stop = command_parts.at(1);
                print_stop_lines(tramlines, stop);
            }
        }
        else if (same_command("DISTANCE", command))
        {
            if (command_parts.size() < 4)
            {
                std::cout << "Error: Invalid input." << std::endl;
            }
            else
            {
                std::string line = command_parts.at(1);
                std::string stop1 = command_parts.at(2);
                std::string stop2 = command_parts.at(3);
                print_distance_between_stops(tramlines, line, stop1, stop2);
            }

        }
        else if (same_command("ADDLINE", command))
        {
            if (command_parts.size() < 2)
            {
                std::cout << "Error: Invalid input." << std::endl;
            }
            else
            {
                std::string line = command_parts.at(1);
                add_line(tramlines, line);
            }
        }
        else if (same_command("ADDSTOP", command))
        {
            if (command_parts.size() < 4)
            {
                std::cout << "Error: Invalid input." << std::endl;
            }
            else
            {
                std::string line = command_parts.at(1);
                std::string new_stop = command_parts.at(2);
                double distance = stod(command_parts.at(3));
                add_stop(tramlines, line, new_stop, distance);
            }

        }
        else if (same_command("REMOVE", command))
        {
            if (command_parts.size() < 2)
            {
                std::cout << "Error: Invalid input." << std::endl;
            }
            else
            {
                std::string stop = command_parts.at(1);
                remove_stop(tramlines, stop);
            }
        }
        else
        {
            std::cout << "Error: Invalid input.1" << std::endl;
        }
    }
    return true;
}

// Short and sweet main.
int main()
{
    print_rasse();
    std::string file_name = read_file_name();

    if (check_data(file_name))
    {
        if (interface(file_name))
        {
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;

}
