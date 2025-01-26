/**
 * @file fileOperations.h
 *
 */
#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H

#include <string>

/**
 * @brief funkcja odczytująca zawartość pliku i zamienia na wielkie litery
 * @param pathToFile ścieżka do pliku
 * @returns zawartość pliku zamieniona na wielkie litery
 */
std::string readFile(const std::string &pathToFile);

/**
 * @brief funcja zamieniająca na wielkie linery z uwzględnieniem znaków unicode
 *
 * @param inp text do zamiany
 */
void toUpperCase(std::string &inp);

/**
 * @brief funkcja zamieniajaca stringa na wstringa
 *
 * @param inp zmienna do zamiany
 * @return std::wstring
 */
std::wstring toWStringConverter(const std::string &inp);

/**
 * @brief funkcja zamienijaca wstringa na stringa
 *
 * @param inp zmienna do zamiany
 * @return std::string
 */
std::string fromWStringConverter(const std::wstring &inp);

/**
 * @brief funcja zapisujaca do pliku
 * @param pathToFile ścieżka do pliku
 * @param fileContent zawartość do zapisania
 */
void writeToFile(const std::string &pathToFile, const std::string &fileContent);
#endif