#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

#include "function.h"

std::string readFile(const std::string &pathToFile)
{
    std::string fileContent;
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
        if (encrypt)
        {
            index = (alphabet.find(message[i]) + alphabet.find(key[i])) % alphabet.length();
        }
        else
        {
            index = (alphabet.find(message[i]) - alphabet.find(key[i]) + 26) % alphabet.length();
        }

        processedMessage.push_back(alphabet[index]);
    }

    writeToFile(outFile, processedMessage);
}