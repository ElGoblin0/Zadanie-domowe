#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>

#include <hwd.h>

#include "common.h"



int main(int argc, char * argv[])
try
{
    std::vector<char> data;
    std::vector<char> data2;
    std::vector<char> temp;
    std::vector<char> end_of_file;
    end_of_file.push_back('e');
    end_of_file.push_back('o');
    end_of_file.push_back('f');
    end_of_file.push_back('\n');

    
    if (argc > 1)
    {
        auto input = safely_open_file(argv[1]);
        data = read_entire_stream(input);

        if(argv[2] != nullptr)
        {
            auto input2 = safely_open_file(argv[2]);
            data2 = read_entire_stream(input2);
        
            temp.reserve(data.size() + data2.size() + end_of_file.size());
            temp.insert(temp.end(), data.begin(), data.end());
            temp.insert(temp.end(), end_of_file.begin(), end_of_file.end());
            temp.insert(temp.end(), data2.begin(), data2.end());
        }
        else
        {
            temp = data;
        }          
    }
    else
    {
        temp = read_entire_stream(std::cin);
    }   

    if(temp.empty())
    {
        throw std::runtime_error("nothing to write");
    }

    bool ok = hwd::memory::write(temp, 0);

    if(!ok)
    {
        throw std::runtime_error("could not write");
    }
}
catch (const std::runtime_error & err)
{
    std::cerr << err.what() << std::endl;
    return EXIT_FAILURE;
}
