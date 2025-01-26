/**
 * @file encodeDecode.h
 *
 */
#ifndef ENCODEDECODE_H
#define ENCODEDECODE_H

#include <string>
#include <vector>

/**
 * @brief funkcja dopasowująca długość klucza
 * @param key zawartość pliku klucza
 * @param message zawartość pliku wejściowego
 * @returns klucz dopasowany do wiadomosci
 */
std::wstring adjustKey(std::wstring &key, const std::wstring &message);

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

#endif