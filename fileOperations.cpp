#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>

#include "fileOperations.h"

std::string readFile(const std::string &pathToFile)
{
    std::string fileContent;
    if (std::filesystem::exists(pathToFile))
    {
        if (std::filesystem::is_empty(pathToFile))
        {
            std::cout << pathToFile << " jest pusty, wprowadz poprawna wartosc" << std::endl;
            exit(0);
        }
        else
        {
            std::ifstream inp(pathToFile, std::ios_base::binary);
            if (inp)
            {
                inp.seekg(0, std::ios_base::end);
                int size = inp.tellg();
                inp.seekg(0, std::ios_base::beg);

                fileContent.reserve(size);

                fileContent.assign((std::istreambuf_iterator<char>(inp)),
                                   std::istreambuf_iterator<char>());
            }
            toUpperCase(fileContent);

            return fileContent;
        }
    }
    else
    {
        std::cout << pathToFile << " plik nie istnieje" << std::endl;
        exit(0);
    }
}

void toUpperCase(std::string &inp)
{
    std::locale::global(std::locale(""));

    std::wstring toConvet = toWStringConverter(inp);

    std::transform(toConvet.begin(), toConvet.end(), toConvet.begin(), ::towupper);

    inp = fromWStringConverter(toConvet);
}

std::wstring toWStringConverter(const std::string &inp)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> wsconverter;
    return wsconverter.from_bytes(inp);
}

std::string fromWStringConverter(const std::wstring &inp)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> wsconverter;
    return wsconverter.to_bytes(inp);
}

void writeToFile(const std::string &pathToFile, const std::string &fileContent)
{
    std::ofstream out(pathToFile);
    if (out)
    {
        out << fileContent;
    }
}