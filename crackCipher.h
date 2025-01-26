/**
 * @file crackCipher.h
 *
 */
#ifndef CRACKCIPHER_H
#define CRACKCIPHER_H

#include <string>
#include <vector>
#include <unordered_map>

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