#include <iostream>
#include <string>
#include <algorithm>
#include <filesystem>
#include <unordered_map>

#include "encodeDecode.h"
#include "fileOperations.h"
#include "crackCipher.h"

const std::wstring polishAlphabet = L"AĄBCĆDEĘFGHIJKLŁMNŃOÓPQRSŚTUVWXYZŹŻ";
const std::wstring englishAlphabet = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

std::wstring adjustKey(std::wstring &key, const std::wstring &message)
{
    std::wstring keyOut;
    int j = 0;
    for (int i = 0; i <= message.length(); i++)
    {
        if (keyOut.length() >= message.length())
        {
            return keyOut;
        }

        if (iswalpha(message[i]))
        {
            keyOut.push_back(key[j]);
            j = (j + 1) % key.length();
        }
        else
        {
            keyOut.push_back(message[i]);
        }
    }

    return keyOut;
}

void characterReplacer(std::wstring &inp)
{
    std::unordered_map<wchar_t, char> characterToReplace = {{L'ą', 'a'}, {L'Ą', 'A'}, {L'ć', 'c'}, {L'Ć', 'C'}, {L'ę', 'e'}, {L'Ę', 'E'}, {L'ł', 'l'}, {L'Ł', 'L'}, {L'ń', 'n'}, {L'Ń', 'N'}, {L'ó', 'o'}, {L'Ó', 'O'}, {L'ś', 's'}, {L'Ś', 'S'}, {L'ż', 'z'}, {L'Ż', 'Z'}, {L'ź', 'z'}, {L'Ź', 'Z'}};
    for (int i = 0; i < inp.size(); i++)
    {
        auto finder = characterToReplace.find(inp[i]);
        if (finder != characterToReplace.end())
        {
            inp[i] = finder->second;
        }
    }
}

void cryptonator(const std::string &inpFile, const std::string &outFile, const std::string &keyFile, const bool &encrypt, const bool &polskie)
{
    std::wstring message = toWStringConverter(readFile(inpFile)),
                 keyToProcess = toWStringConverter(readFile(keyFile)),
                 key,
                 processedMessage,
                 alphabet;

    if (polskie)
    {
        alphabet = polishAlphabet;
    }
    else
    {
        alphabet = englishAlphabet;
        characterReplacer(message);
    }

    // deleteSpecialCharacters(message);
    deleteSpecialCharacters(key);
    key = adjustKey(keyToProcess, message);

    int index = 0;
    for (int i = 0; i < message.length(); i++)
    {
        auto m = find(alphabet.begin(), alphabet.end(), message[i]);
        auto k = find(alphabet.begin(), alphabet.end(), key[i]);

        if (m != alphabet.end())
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
