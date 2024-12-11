#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <locale.h>
#include <unordered_map>

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

            // std::transform(fileContent.begin(), fileContent.end(), fileContent.begin(), ::toupper);
            toUpperCase(fileContent);
            // characterReplacer(fileContent);

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

void adjustKey(std::wstring &key, const std::string &message)
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

void characterReplacer(std::string &inp)
{
    std::wstring winp = toWStringConverter(inp);
    std::unordered_map<wchar_t, char> characterToReplace = {{L'ą', 'a'}, {L'Ą', 'A'}, {L'ć', 'c'}, {L'Ć', 'C'}, {L'ę', 'e'}, {L'Ę', 'E'}, {L'ł', 'l'}, {L'Ł', 'L'}, {L'ń', 'n'}, {L'Ń', 'N'}, {L'ó', 'o'}, {L'Ó', 'O'}, {L'ś', 's'}, {L'Ś', 'S'}, {L'ż', 'z'}, {L'Ż', 'Z'}, {L'ź', 'z'}, {L'Ź', 'Z'}};
    for (int i = 0; i < winp.size(); i++)
    {
        auto finder = characterToReplace.find(winp[i]);
        if (finder != characterToReplace.end())
        {
            winp[i] = finder->second;
        }
    }
    inp = fromWStringConverter(winp);
}

void cryptonator(const std::string &inpFile, const std::string &outFile, const std::string &keyFile, const bool &encrypt)
{
    std::wstring message = toWStringConverter(readFile(inpFile)),
                 key = toWStringConverter(readFile(keyFile)),
                 processedMessage;

    // const std::wstring alphabet = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::wstring alphabet = L"AĄBCĆDEĘFGHIJKLŁMNŃOÓPQRSŚTUVWXYZŹŻ";

    adjustKey(key, fromWStringConverter(message));

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

    writeToFile(outFile, fromWStringConverter(processedMessage));
}