#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <locale.h>
#include <unordered_map>
#include <cwctype>

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
                 key = toWStringConverter(readFile(keyFile)),
                 processedMessage,
                 alphabet;

    if (polskie)
    {
        alphabet = L"AĄBCĆDEĘFGHIJKLŁMNŃOÓPQRSŚTUVWXYZŹŻ";
    }
    else
    {
        alphabet = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        characterReplacer(message);
    }

    deleteSpecialCharacters(message);
    deleteSpecialCharacters(key);
    adjustKey(key, fromWStringConverter(message));

    int index = 0;
    for (int i = 0; i < message.length(); i++)
    {
        auto m = find(alphabet.begin(), alphabet.end(), message[i]);
        auto k = find(alphabet.begin(), alphabet.end(), key[i]);

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

    writeToFile(outFile, fromWStringConverter(processedMessage));
}

std::unordered_map<wchar_t, double> calcFrequency(const std::wstring &inp)
{
    std::unordered_map<wchar_t, double> freq;
    int sum = 0;

    for (const auto &letter : inp)
    {
        if (iswalpha(letter))
        {
            freq[letter]++;
            sum++;
        }
    }

    for (auto &bucket : freq)
    {
        bucket.second = (bucket.second / sum) * 100;
    }

    return freq;
}

int messageLength(const std::wstring &inp)
{
    int sum = 0;

    for (const auto &letter : inp)
    {
        if (iswalpha(letter))
        {
            sum++;
        }
    }

    return sum;
}

double chiSquared(const std::unordered_map<wchar_t, double> &inp, const int &textLength)
{
    std::unordered_map<wchar_t, double> polishFrequency = {{L'A', 8.96245}, {L'I', 8.28964}, {L'E', 7.92385}, {L'O', 7.58735}, {L'Z', 5.66797}, {L'N', 5.60146}, {L'W', 4.56461}, {L'R', 4.53273}, {L'S', 4.25198}, {L'C', 3.97801}, {L'T', 3.96688}, {L'Y', 3.88081}, {L'K', 3.39007}, {L'D', 3.31361}, {L'P', 3.10022}, {L'M', 2.89518}, {L'J', 2.36613}, {L'U', 2.33865}, {L'L', 2.10044}, {L'Ł', 1.76535}, {L'B', 1.47574}, {L'G', 1.36726}, {L'Ę', 1.14961}, {L'H', 1.05652}, {L'Ą', 1.03303}, {L'Ż', 0.90111}, {L'Ó', 0.83236}, {L'Ś', 0.68938}, {L'Ć', 0.45459}, {L'F', 0.30361}, {L'Ń', 0.18380}, {L'Ź', 0.06140}, {L'V', 0.00848}, {L'X', 0.00486}, {L'Q', 0.00085}};
    std::unordered_map<wchar_t, double> englishFrequency = {{L'E', 12.702}, {L'T', 9.056}, {L'A', 8.167}, {L'O', 7.507}, {L'I', 6.966}, {L'N', 6.749}, {L'S', 6.327}, {L'H', 6.094}, {L'R', 5.987}, {L'D', 4.253}, {L'I', 4.025}, {L'C', 2.782}, {L'U', 2.758}, {L'M', 2.406}, {L'W', 2.361}, {L'F', 2.228}, {L'G', 2.015}, {L'Y', 1.974}, {L'P', 1.929}, {L'B', 1.492}, {L'V', 0.978}, {L'K', 0.772}, {L'J', 0.153}, {L'X', 0.150}, {L'A', 0.095}, {L'Z', 0.074}};

    double chiSqr = 0;

    for (const auto &bucket : polishFrequency)
    {
        double observed = 0;
        auto finder = inp.find(bucket.first);
        if (finder != inp.end())
        {
            observed = finder->second;
        }
        double expected = bucket.second * textLength / 100;

        chiSqr += ((observed - expected) * (observed - expected)) / expected;
    }

    return chiSqr;
}

double calcIC(const std::wstring &inp)
{
    std::unordered_map<wchar_t, int> letterCounter;

    double sum = 0,
           textIC = 0;

    int textLength = messageLength(inp);

    for (const auto &letter : inp)
    {
        if (iswalpha(letter))
        {
            letterCounter[letter]++;
        }
    }

    for (const auto &bucket : letterCounter)
    {
        sum += bucket.second * (bucket.second - 1);
    }

    textIC = sum / (textLength * (textLength - 1));

    return textIC;
}

void deleteSpecialCharacters(std::wstring &inp)
{
    std::wstring out;
    for (const auto &letter : inp)
    {
        if (iswalpha(letter))
        {
            out += letter;
        }
    }
    inp = out;
}

int findKeyLength(std::wstring &inp)
{
    /*
    ICEnglish = 0.0667
    ICPolish = 0.0607
    ICRandom = 0.0385
    */
    deleteSpecialCharacters(inp);

    bool lengthFound = false;
    int n = 0;

    std::vector<double> keyIC;

    while (!lengthFound)
    {
        n++;
        std::vector<std::wstring> slices;
        for (int i = 0; i < n; i++)
        {
            std::wstring tempSlice;
            for (int j = i; j < inp.size(); j += n)
            {
                tempSlice += inp[j];
            }
            slices.push_back(tempSlice);
        }

        double ICsum = 0;
        for (int i = 0; i < n; i++)
        {
            ICsum += calcIC(slices[i]);
        }

        keyIC.push_back(ICsum / n);
        if (n == inp.size() / 2)
        {
            lengthFound = true;
        }
    }

    double sum = 0,
           average = 0,
           threshold = 0;
    for (const auto &value : keyIC)
    {
        sum += value;
    }
    average = sum / keyIC.size();
    threshold = average * 1.3;
    for (int i = 0; i < keyIC.size(); i++)
    {
        if (keyIC[i] > threshold)
        {
            return i + 1;
        }
    }
    return 0;
}

void cracker(const std::string &inpFile, const std::string &outFile)
{
}