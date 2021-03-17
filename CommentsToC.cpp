// CommentsToC.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

int main()
{
  while (1)
  {
    fstream input, output;
    std::string filename, filename_orig;
    std::string line;
    std::cout << "Input filename: ";

    std::cin >> filename;
    filename_orig = filename + ".orig";
    std::rename(filename.c_str(), filename_orig.c_str());

    input.open(filename_orig, ios::in);
    output.open(filename, ios::out);

    if (input.is_open() && output.is_open())
    {
      while (getline(input, line))
      {
        std::size_t found = line.find("//");
        if (found != std::string::npos) // found "//"
        {
          std::string substring;
          std::string newstring;

          substring = line.substr(found);
          newstring.assign(line.substr(0, line.length() - substring.length()));

          // search vor unneccessary /* ... */ sequences
          while (found != std::string::npos)
          {
            found = substring.find("/*");
            if (found != std::string::npos) // found "/*"
              substring.erase(found, 2);
          }
          while (found != std::string::npos)
          {
            found = substring.find("*/");
            if (found != std::string::npos) // found "*/"
              substring.erase(found, 2);
          }

          newstring.append("/* ");
          newstring.append(substring.substr(2));
          newstring.append(" */");

          output << newstring << '\n';
        }
        else
          output << line << '\n';
      }
      input.close();
      output.close();
    }
    else
      cout << "Unable to open file" << std::endl;
  }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
