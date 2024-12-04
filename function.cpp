#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <filesystem>

#include "function.h"

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
            std::ifstream inp(pathToFile);
            if (inp)
            {
                while (not inp.eof())
                {
                    std::string temp;
                    inp >> temp;

                    fileContent.append(temp);
                }
            }

            std::transform(fileContent.begin(), fileContent.end(), fileContent.begin(), ::toupper);

            return fileContent;
        }
    }
    else
    {
        std::cout << pathToFile << " plik nie istnieje" << std::endl;
        exit(0);
    }
}

void writeToFile(const std::string &pathToFile, const std::string &fileContent)
{
    std::ofstream out(pathToFile);
    if (out)
    {
        out << fileContent;
    }
}

void adjustKey(std::string &key, const std::string &message)
{
    for (int i = key.length(), j = 0; i <= message.length(); i++, j++)
    {
        if (key.length() >= message.length())
        {
            return;
        }
        else
        {
            if (j == key.length())
            {
                j = 0;
            }

            key.push_back(key[j]);
        }
    }
}

void cryptonator(const std::string &inpFile, const std::string &outFile, const std::string &keyFile, const bool &encrypt)
{
    std::string message = readFile(inpFile),
                key = readFile(keyFile),
                processedMessage;

    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    adjustKey(key, message);

    int index = 0;
    for (int i = 0; i < message.length(); i++)
    {
        auto m = find(alphabet.begin(), alphabet.end(), message[i]);
        auto k = find(alphabet.begin(), alphabet.end(), key[i]);

        if (m != alphabet.end() && k != alphabet.end())
        {
            if (encrypt)
            {
                index = (distance(alphabet.begin(), m) + distance(alphabet.begin(), k)) % alphabet.length();
            }
            else
            {
                index = (distance(alphabet.begin(), m) - distance(alphabet.begin(), k) + alphabet.length()) % alphabet.length();
            }
            processedMessage.push_back(alphabet[index]);
        }
        else
        {
            processedMessage.push_back(message[i]);
        }
    }

    writeToFile(outFile, processedMessage);
}