#include <iostream>
#include <string>
#include <unordered_map>

#include "encodeDecode.h"
#include "crackCipher.h"

int main(int argc, char **argv)
{
    bool encrypt = false, crack = false, polskie = false;
    std::string inpFile, outFile, keyFile;
    if (argc <= 1)
    {
        std::cout << "Prosze zadeklarować paremetry: " << std::endl
                  << "--en szyfrowanie" << std::endl
                  << "--de odszyfrowanie" << std::endl
                  << "--br łamanie szyfru" << std::endl
                  << "--pl dla polskiego tekstu" << std::endl
                  << "-i plik tekstowy wejściowy" << std::endl
                  << "-o plik tekstowy wyjściowy" << std::endl
                  << "-k plik tekstowy z kluczem" << std::endl;
        exit(0);
    }
    for (int i = 1; i < argc; i++)
    {
        if (std::string(argv[i]) == "--en")
        {
            encrypt = true;
        }
        else if (std::string(argv[i]) == "--de")
        {
            encrypt = false;
        }
        else if (std::string(argv[i]) == "--br")
        {
            crack = true;
        }
        else if (std::string(argv[i]) == "--pl")
        {
            polskie = true;
        }
        else if (std::string(argv[i]) == "-i")
        {
            if (i + 1 < argc)
            {
                inpFile = argv[++i];
            }
            else
            {
                std::cout << "brak nazwy pliku wejściowego";
                exit(0);
            }
        }
        else if (std::string(argv[i]) == "-o")
        {
            if (i + 1 < argc)
            {
                outFile = argv[++i];
            }
            else
            {
                std::cout << "brak nazwy pliku wyjściowego";
                exit(0);
            }
        }
        else if (std::string(argv[i]) == "-k")
        {
            if (i + 1 < argc)
            {
                keyFile = argv[++i];
            }
            else
            {
                std::cout << "brak nazwy pliku z kluczem";
                exit(0);
            }
        }
        else
        {
            std::cout << "nieznany parametr \"" << argv[i] << "\"";
            exit(0);
        }
    }

    if (inpFile.empty())
    {
        std::cout << "brak pliku wejsciowego";
        exit(0);
    }
    if (outFile.empty())
    {
        std::cout << "brak pliku wyjsciowego";
        exit(0);
    }

    if (crack)
    {
        std::cout << "operacja łamania szyfru z pliku " << inpFile << " do pliku " << outFile << std::endl;
        cracker(inpFile, outFile, polskie);
    }
    else
    {
        if (keyFile.empty())
        {
            std::cout << "brak pliku klucza";
            exit(0);
        }
        if (encrypt)
        {
            std::cout << "operacja szyfrowania z pliku " << inpFile << " do pliku " << outFile << " z kluczem " << keyFile << std::endl;
        }
        else
        {
            std::cout << "operacja deszyfrowania z pliku " << inpFile << " do pliku " << outFile << " z kluczem " << keyFile << std::endl;
        }
        cryptonator(inpFile, outFile, keyFile, encrypt, polskie);
    }

    return 0;
}