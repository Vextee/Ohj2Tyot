#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

bool palindrome_recursive(std::string s)
{
  RECURSIVE_FUNC
  // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
  // ------------

  if(s.length() <= 2)
  {
      if(s.at(0) != s.back())
      {
          return false;
      }
      else
      {
          return true;
      }
  }
  else if(s.at(0) != s.back())
  {
      return false;
  }
  else
  {
      return palindrome_recursive(s.substr(1, s.length()-2));
  }


  // Add your implementation here
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
#endif
