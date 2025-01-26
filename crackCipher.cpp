#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <locale.h>
#include <unordered_map>
#include <cwctype>

#include "encodeDecode.h"
#include "fileOperations.h"
#include "crackCipher.h"

const std::wstring polishAlphabet = L"AĄBCĆDEĘFGHIJKLŁMNŃOÓPQRSŚTUVWXYZŹŻ";
const std::wstring englishAlphabet = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";

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

double chiSquared(const std::unordered_map<wchar_t, double> &inp, const int &textLength, const bool &polskie)
{
    std::unordered_map<wchar_t, double> polishFrequency = {{L'A', 8.96245}, {L'I', 8.28964}, {L'E', 7.92385}, {L'O', 7.58735}, {L'Z', 5.66797}, {L'N', 5.60146}, {L'W', 4.56461}, {L'R', 4.53273}, {L'S', 4.25198}, {L'C', 3.97801}, {L'T', 3.96688}, {L'Y', 3.88081}, {L'K', 3.39007}, {L'D', 3.31361}, {L'P', 3.10022}, {L'M', 2.89518}, {L'J', 2.36613}, {L'U', 2.33865}, {L'L', 2.10044}, {L'Ł', 1.76535}, {L'B', 1.47574}, {L'G', 1.36726}, {L'Ę', 1.14961}, {L'H', 1.05652}, {L'Ą', 1.03303}, {L'Ż', 0.90111}, {L'Ó', 0.83236}, {L'Ś', 0.68938}, {L'Ć', 0.45459}, {L'F', 0.30361}, {L'Ń', 0.18380}, {L'Ź', 0.06140}, {L'V', 0.00848}, {L'X', 0.00486}, {L'Q', 0.00085}};
    std::unordered_map<wchar_t, double> englishFrequency = {{L'E', 12.702}, {L'T', 9.056}, {L'A', 8.167}, {L'O', 7.507}, {L'I', 6.966}, {L'N', 6.749}, {L'S', 6.327}, {L'H', 6.094}, {L'R', 5.987}, {L'D', 4.253}, {L'I', 4.025}, {L'C', 2.782}, {L'U', 2.758}, {L'M', 2.406}, {L'W', 2.361}, {L'F', 2.228}, {L'G', 2.015}, {L'Y', 1.974}, {L'P', 1.929}, {L'B', 1.492}, {L'V', 0.978}, {L'K', 0.772}, {L'J', 0.153}, {L'X', 0.150}, {L'A', 0.095}, {L'Z', 0.074}};
    std::unordered_map<wchar_t, double> frequency;
    double chiSqr = 0;

    if (polskie)
    {
        frequency = polishFrequency;
    }
    else
    {
        frequency = englishFrequency;
    }

    for (const auto &bucket : frequency)
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

std::vector<std::wstring> makeSlices(const std::wstring &inp, const int &sliceLenght)
{
    std::vector<std::wstring> slices;
    for (int i = 0; i < sliceLenght; i++)
    {
        std::wstring tempSlice;
        for (int j = i; j < inp.size(); j += sliceLenght)
        {
            tempSlice += inp[j];
        }
        slices.push_back(tempSlice);
    }
    return slices;
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
        std::vector<std::wstring> slices = makeSlices(inp, n);

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

std::wstring caesarCipher(const std::wstring &inp, const int &shift, const bool &polskie)
{
    std::wstring outputText,
        alphabet;

    if (polskie)
    {
        alphabet = polishAlphabet;
    }
    else
    {
        alphabet = englishAlphabet;
    }

    for (auto &letter : inp)
    {
        auto letterIndex = find(alphabet.begin(), alphabet.end(), letter);
        int newIndex = (distance(alphabet.begin(), letterIndex) + shift) % alphabet.length();
        if (newIndex < 0)
        {
            newIndex += alphabet.length();
        }
        outputText.push_back(alphabet[newIndex]);
    }
    return outputText;
}

std::wstring findKey(const std::wstring &inp, const int &keyLength, const bool &polskie)
{
    std::wstring outputKey,
        alphabet;
    std::vector<std::wstring> slices = makeSlices(inp, keyLength);

    if (polskie)
    {
        alphabet = polishAlphabet;
    }
    else
    {
        alphabet = englishAlphabet;
    }

    for (auto &slice : slices)
    {
        std::vector<double> chiSqTable;
        int n = alphabet.length();

        for (int i = n; n >= 1; n--)
        {
            std::wstring temp = caesarCipher(slice, n, polskie);
            chiSqTable.push_back(chiSquared(calcFrequency(temp), temp.length(), polskie));
        }
        auto keyLetterIndex = std::min_element(chiSqTable.begin(), chiSqTable.end());
        outputKey.push_back(alphabet[std::distance(chiSqTable.begin(), keyLetterIndex)]);
    }
    return outputKey;
}

void cracker(const std::string &inpFile, const std::string &outFile, const bool &polskie)
{
    std::wstring message = toWStringConverter(readFile(inpFile));
    int keyLength = findKeyLength(message);
    std::wstring key = findKey(message, keyLength, polskie);
    writeToFile("foundKey.txt", fromWStringConverter(key));
    cryptonator(inpFile, outFile, "foundKey.txt", false, polskie);
}