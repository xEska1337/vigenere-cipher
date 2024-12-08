/**
 * @file function.h
 *
 */
#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>

/**
 * @brief funkcja odczytująca zawartość pliku i zamienia na wielkie litery
 * @param pathToFile ścieżka do pliku
 * @returns zawartość pliku zamieniona na wielkie litery
 */
std::string readFile(const std::string &pathToFile);

/**
 * @brief funcja zapisujaca do pliku
 * @param pathToFile ścieżka do pliku
 * @param fileContent zawartość do zapisania
 */
void writeToFile(const std::string &pathToFile, const std::string &fileContent);

/**
 * @brief funkcja dopasowująca długość klucza
 * @param key zawartość pliku klucza
 * @param message zawartość pliku wejściowego
 */
void adjustKey(std::wstring &key, const std::string &message);

/**
 * @brief funcja zamieniająca na wielkie linery z uwzględnieniem znaków unicode
 * 
 * @param inp text do zamiany
 */
void toUpperCase(std::string & inp);

/**
 * @brief funkcja szyfrująca/deszyfrująca
 * 
 * @param inpFile ścieżka do pliku wejściowego
 * @param outFile ścieżka do pliku wyjściowego
 * @param keyFile ścieżka do pliku klucza
 * @param encrypt wybór między szyfrowaniem a odszyfrowaniem
 */
void cryptonator(const std::string &inpFile, const std::string &outFile, const std::string &keyFile, const bool &encrypt);
#endif