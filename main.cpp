#include <iostream>
#include <string>
#include <unordered_map>

#include "function.h"

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
                  << "--pl załączenie obsługi polskich znaków" << std::endl
                  << "-i plik tekstowy wejściowy" << std::endl
                  << "-o plik tekstowy wyjściowy" << std::endl
                  << "-k plik tekstowy z kluczem" << std::endl;
    }
    for (int i = 1; i < argc; i++)
    {
        if (std::string(argv[i]) == "--en")
        {
            encrypt = true;
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
            inpFile = argv[++i];
        }
        else if (std::string(argv[i]) == "-o")
        {
            outFile = argv[++i];
        }
        else if (std::string(argv[i]) == "-k")
        {
            keyFile = argv[++i];
        }
    }

    /*
    if (crack)
    {
        cracker(inpFile,outFile,polskie);
    }
    else
    {
        cryptonator(inpFile,outFile,keyFile,encrypt,polskie);
    }
    */

    cryptonator(inpFile,outFile,keyFile,encrypt,polskie);

    return 0;
}