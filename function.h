/**
 * @file function.h
 *
 */
#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>
#include <unordered_map>
#include <vector>

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
 * @brief funkcja zamieniajaca polskie znaki na ich odpowiedniki bez ogonków
 *
 * @param inp text do zamiany
 * @note funkcja do użycia jeżeli nie chcemy polskich znaków w zaszyfrowanym tekscie
 */
void characterReplacer(std::wstring &inp);

/**
 * @brief funkcja szyfrująca/deszyfrująca
 *
 * @param inpFile ścieżka do pliku wejściowego
 * @param outFile ścieżka do pliku wyjściowego
 * @param keyFile ścieżka do pliku klucza
 * @param encrypt wybór między szyfrowaniem a odszyfrowaniem
 * @param polskie czy maja zostac polskie znaki czy nie
 */
void cryptonator(const std::string &inpFile, const std::string &outFile, const std::string &keyFile, const bool &encrypt, const bool &polskie);

/**
 * @brief funkcja obliczająca częstotliwość występowania litter w zaszyfrowanym tekście
 *
 * @param inp text do obliczenia
 * @return std::unordered_map<wchar_t, double> tabela częstotliwości
 */
std::unordered_map<wchar_t, double> calcFrequency(const std::wstring &inp);

/**
 * @brief funkcja obliczająca długość tekstu bez znaków specjalnych
 *
 * @param inp text do obliczenia
 * @return int długość tekstu
 */
int messageLength(const std::wstring &inp);

/**
 * @brief funkcja porównująca tabele częstotliwości ze sobą
 *
 * @param inp tabela do porównania
 * @param polskie czy było szyfrowane z polskimi znakami czy bez
 * @return double różnica miedzy tabelami
 */
double chiSquared(const std::unordered_map<wchar_t, double> &inp, const int &textLength, const bool &polskie);

/**
 * @brief funkcja obliczająca Index of Coincidence
 *
 * @param inp text do obliczenia
 * @return double
 */
double calcIC(const std::wstring &inp);

/**
 * @brief funkcja usuwa wszystkie znaki które nie są literami
 *
 * @param inp text do korekcji
 */
void deleteSpecialCharacters(std::wstring &inp);

/**
 * @brief funkcja dzielaca tekst na mniejszcze cześci co n litere
 *
 * @param inp text do podzielienia
 * @param sliceLenght co która litere
 * @return std::vector<std::wstring>
 */
std::vector<std::wstring> makeSlices(const std::wstring &inp, const int &sliceLenght);

/**
 * @brief funkcja obliczająca długość klucza
 *
 * @param inp text do obliczenia
 * @return int długość klucza
 */
int findKeyLength(std::wstring &inp);

/**
 * @brief funkcja robiąca szyfr cezara o zadanym przesunięciu
 *
 * @param inp text do szyfru
 * @param shift przesunięcie
 * @param polskie czy było szyfrowane z polskimi znakami czy bez
 * @return std::wstring
 */
std::wstring caesarCipher(const std::wstring &inp, const int &shift, const bool &polskie);

/**
 * @brief funkcja szukajaca klucza na podstawie tabeli czestotliwosci
 *
 * @param inp text zaszyfrowany
 * @param keyLength długość klucza
 * @param polskie czy było szyfrowane z polskimi znakami czy bez
 * @return std::wstring
 */
std::wstring findKey(const std::wstring &inp, const int &keyLength, const bool &polskie);

/**
 * @brief funkcja próbująca złamać szyfr
 *
 * @param inpFile ścieżka do pliku wejściowego
 * @param outFile ścieżka do pliku wyjściowego
 * @param polskie czy było szyfrowane z polskimi znakami czy bez
 */
void cracker(const std::string &inpFile, const std::string &outFile, const bool &polskie);
#endif