/*
Rasse 2

Kuvaus:
Käynnistyessään ohjelma aluksi tulostaa

*/

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

using Tramlines = std::map<std::string, std::map<double, std::string>>;

std::vector<std::string> split(const std::string& s, const char delimiter){
    std::vector<std::string> result = {""};
    std::string tmp = s;
    bool found = false;

    for (char c : s)
    {
        if (c == '"')
        {
            found = !found;
        }
        else if (c == delimiter and found == false)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(c);
        }
    }

    if (result.back() == "")
    {
        result.pop_back();
    }

    return result;
}


std::string read_file_name()
{
    std::string file_name;
    std::cout << "Give a name for input file: ";
    getline(std::cin, file_name);
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

void save_data(Tramlines& tramlines, std::string file_name)
{
    std::ifstream file(file_name);
    std::string line;

    while (getline(file, line))
    {
        std::vector<std::string> parts = split(line, ';');


        if(parts.size() < 3)
        {
            parts.push_back("0.0");
        }
        else if(parts.at(2) == "")
        {
            parts.at(2) = "0.0";
        }

        double distance = stod(parts.at(2));
        std::pair<double, std::string> stop_and_dis = {distance, parts.at(1)};

        if (tramlines.find(parts.at(0)) == tramlines.end())
        {
            tramlines[parts.at(0)] = {};
        }

        for (std::pair<double, std::string> stops : tramlines.at(parts.at(0)))
        {
            if (stops.first == distance or stops.second == parts.at(1))
            {
                std::cout << "Error: Stop/line already exists." << std::endl;
                return;
            }
        }
        tramlines[parts.at(0)].insert(stop_and_dis);
    }
    file.close();
    return;
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


void print_lines(const Tramlines& tramlines)
{
    std::cout << "All tramlines in alphabetical order:" << std::endl;
    std::vector<std::string> line_names = {};
    for (std::pair<std::string, std::map<double, std::string>> lines : tramlines)
    {
        line_names.push_back(lines.first);
    }
    sort(line_names.begin(), line_names.end());
    for (std::string s : line_names)
    {
        std::cout << s << std::endl;
    }

    return;
}

void print_line_stops(const Tramlines& tramlines, const std::string& line)
{
    bool line_found = false;

    for (std::pair<std::string, std::map<double, std::string>> lines : tramlines)
    {
        if (lines.first == line)
        {
            line_found = true;
        }
    }

    if (!line_found)
    {
        std::cout << "Error: Line could not be found." << std::endl;
        return;
    }

    std::cout << "Line " << line << " goes through these stops in the order they are listed:" << std::endl;
    for (std::pair<double, std::string> stops : tramlines.at(line))
    {
        std::cout << " - " << stops.second << " : " << stops.first << std::endl;
    }
    return;
}

void print_stops(const Tramlines& tramlines)
{ 
    std::cout << "All stops in alphabetical order:" << std::endl;
    std::vector<std::string> stops = {};
    for (std::pair<std::string, std::map<double, std::string>> lines : tramlines)
    {
        for (std::pair<double, std::string> stop : lines.second)
        {
            if (std::find(stops.begin(), stops.end(), stop.second) == stops.end())
            {
                stops.push_back(stop.second);
            }
        }

    }
    sort(stops.begin(), stops.end());
    for (std::string s : stops)
    {
        std::cout << s << std::endl;
    }
    return;
}

void print_stop_lines(const Tramlines& tramlines, const std::string& stop)
{
    std::vector<std::string> line_names = {};;

    for (std::pair<std::string, std::map<double, std::string>> lines : tramlines)
    {
        for (std::pair<double, std::string> s : lines.second)
        {
            if (s.second == stop)
            {
                line_names.push_back(lines.first);
            }
        }
    }
    sort(line_names.begin(), line_names.end());
    if (line_names.size() == 0)
    {
        std::cout << "Error: Stop could not be found." << std::endl;
    }
    else
    {
        std::cout << "Stop " << stop << " can be found on the following lines:" << std::endl;
        for (std::string l : line_names)
        {
            std::cout << " - " << l << std::endl;
        }
    }

    return;
}

void print_distance_between_stops(const Tramlines& tramlines, const std::string& line, const std::string& stop1, const std::string& stop2)
{
    double dis1 = -1;
    double dis2 = -1;
    double dis_between = 0;

    bool line_found = false;

    for (std::pair<std::string, std::map<double, std::string>> lines : tramlines)
    {
        if (lines.first == line)
        {
            line_found = true;
        }
    }

    if (!line_found)
    {
        std::cout << "Error: Line could not be found." << std::endl;
        return;
    }

    for (std::pair<double, std::string> stops : tramlines.at(line))
    {
        if (stops.second == stop1)
        {
            dis1 = stops.first;
        }
        else if (stops.second == stop2)
        {
            dis2 = stops.first;
        }
    }

    if (dis1 == -1 or dis2 == -1)
    {
        std::cout << "Error: Stop could not be found." << std::endl;
        return;
    }
    else
    {
        if (dis1 > dis2)
        {
            dis_between = dis1 - dis2;
        }
        else
        {
            dis_between = dis2 - dis1;
        }
    }
    std::cout << "Distance between " << stop1 << " and " << stop2 << " is " << dis_between << std::endl;

    return;
}

void add_line(Tramlines& tramlines, const std::string& line)
{
    bool line_found = false;

    for (std::pair<std::string, std::map<double, std::string>> lines : tramlines)
    {
        if (lines.first == line)
        {
            line_found = true;
        }
    }
    if (line_found)
    {
        std::cout << "Error: Stop/line already exists." << std::endl;
        return;
    }

    tramlines[line] = {};

    return;
}

void add_stop(Tramlines& tramlines, const std::string& line, const std::string& new_stop, const double& distance)
{
    bool line_found = false;

    for (std::pair<std::string, std::map<double, std::string>> lines : tramlines)
    {
        if (lines.first == line)
        {
            line_found = true;
        }
    }
    if (!line_found)
    {
        std::cout << "Error: Line could not be found." << std::endl;
        return;
    }

    for (std::pair<double, std::string> s : tramlines.at(line))
    {
        if (s.second == new_stop or s.first == distance)
        {
            std::cout << "Error: Stop/line already exists." << std::endl;
            return;
        }
    }

    std::pair<double, std::string> stop_and_dis = {distance, new_stop};
    tramlines[line].insert(stop_and_dis);
    std::cout << "Stop was added." << std::endl;
    return;
}

void remove_stop(Tramlines& tramlines, const std::string& stop)
{
    bool stop_found = false;
    for (std::pair<std::string, std::map<double, std::string>> lines : tramlines)
    {
        for (std::pair<double, std::string> s : lines.second)
        {
            if (s.second == stop)
            {
                stop_found = true;
            }
        }
    }

    if (!stop_found)
    {
        std::cout << "Error: Stop could not be found." << std::endl;
        return;
    }

    for (std::pair<std::string, std::map<double, std::string>> lines : tramlines)
    {
        for (std::pair<double, std::string> s : lines.second)
        {
            if (s.second == stop)
            {
                tramlines.at(lines.first).erase(s.first);
            }
        }
    }
    std::cout << "Stop was removed from all lines." << std::endl;
    return;
}

bool interface(std::string file_name)
{
    std::map <std::string, std::map<double, std::string>> tramlines;

    save_data(tramlines, file_name);
    while(true)
    {
        std::string full_command;
        std::cout << "tramway> ";
        getline(std::cin, full_command);
        std::vector<std::string> command_parts = split(full_command, ' ');
        if (command_parts.size() == 0)
        {
            continue;
        }
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
