#include <iostream>

using namespace std;

bool is_number(const std::string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    return is_numeric;
}


int main()
{
    std::string expr;
    std::cout << "Input an expression in reverse Polish notation (end with #):" << std::endl;
    std::cout << "EXPR> ";
    getline(std::cin, expr);
    int stack[expr.length()];
    int iterator = 0;
    int current_amount = 0;
    int total_operands = 0;
    int total_operations = 0;
    bool failed = false;

    for (char c : expr)
    {
        std::string s = "";
        s += c;
        if (c == ' ')
        {
            continue;
        }
        else if (c == '#')
        {
            break;
        }
        else if (iterator == 0 and !is_number(s))
        {
            std::cout << "Error: Expression must start with a number" << std::endl;
            failed = true;
            break;
        }

        else if (c == '*')
        {
            int first = stack[current_amount-2];
            int second = stack[current_amount-1];
            int product = first * second;
            stack[current_amount-2] = product;
            stack[current_amount-1] = 0;
            ++total_operations;
            --current_amount;
        }
        else if (c == '/')
        {
            int first = stack[current_amount-2];
            int second = stack[current_amount-1];
            if (second == 0)
            {
                std::cout << "Error: Division by zero" << std::endl;
                failed = true;
                break;
            }
            else {
                int product = first / second;
                stack[current_amount-2] = product;
                stack[current_amount-1] = 0;
                ++total_operations;
                --current_amount;
            }

        }
        else if (c == '+')
        {
            int first = stack[current_amount-2];
            int second = stack[current_amount-1];
            int product = first + second;
            stack[current_amount-2] = product;
            stack[current_amount-1] = 0;
            ++total_operations;
            --current_amount;
        }
        else if (c == '-')
        {
            int first = stack[current_amount-2];
            int second = stack[current_amount-1];
            int product = first - second;
            stack[current_amount-2] = product;
            stack[current_amount-1] = 0;
            ++total_operations;
            --current_amount;
        }
        else if (!is_number(s))
        {
            std::cout << "Error: Unknown character" << std::endl;
            failed = true;
            break;
        }
        else
        {
            stack[current_amount] = stoi(s);
            ++current_amount;
            ++total_operands;
        }

        ++iterator;
    }

    if (!failed)
    {
        if (total_operations != total_operands - 1)
        {
            std::cout << "Error: Too few operators" << std::endl;
            return EXIT_FAILURE;
        }
        else if (total_operands <= total_operations)
        {
            std::cout << "Error: Too few operands" << std::endl;
            return EXIT_FAILURE;
        }
        else {
            std::cout << "Correct: " << stack[0] << " is the result" << std::endl;
        }
        return EXIT_SUCCESS;
    }



    return EXIT_FAILURE;
}
