#include <iostream>
#include <vector>
#include <bitset>
#include <utility>
#include <fstream>

#include "bitap.hpp"

void PatternFinder::find_pattern()const{
    int pos = bitap_search();

    if (pos == -1) std::cout << "\nNo Match\n";
    else std::cout << "\nPattern found at position : " << pos << '\n';
}

int PatternFinder::bitap_search()const{
    if (m_pattern.empty()) return -1;
    

    if (m_pattern.size() >= PatternFinder::MaxLength){
        std::cout << "Pattern is too long!";
        return -1;
    }

    std::vector<bitmask> pattern_mask(256);
    
    for (std::size_t i{}; i < pattern_mask.size(); ++i) pattern_mask[i].flip();

    for (std::size_t i{}; i < m_pattern.size(); ++i) pattern_mask[m_pattern[i]].set(i, false);

    bitmask R = ~1;
    for (int i{}; i < m_text.length(); ++i){
        R |= pattern_mask[m_text[i]];
        R <<= 1;

        if (!R.test(m_pattern.size()))
            return i - static_cast<int>(m_pattern.size()) + 1;
    }

    return -1;
}

void PatternFinder::set_text(const std::string& s){
    m_text = s;
}

void PatternFinder::set_text(std::string&& s){
    m_text = std::move(s);
}

const std::string& PatternFinder::get_text()const& {
    return m_text;
}

void PatternFinder::set_pattern(const std::string& s){
    m_pattern = s;
}

void PatternFinder::set_pattern(std::string&& s){
    m_pattern = std::move(s);
}

const std::string& PatternFinder::get_pattern()const&{
    return m_pattern;
}

void PatternFinder::set_params_from_txt(){
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cout << "\nError while opening input file.\n";
        return;
    }
    std::cout << "\nSet text and pattern from txt file.";

    getline(inputFile, m_text);         // ADL
    getline(inputFile, m_pattern);      // ADL
    
    inputFile.close();
}

int main(){
    std::cout << "Enter text:\n";
    std::string text;
    std::cin >> text;
    PatternFinder::get_instance().set_text(text);

    std::cout << "Enter pattern:\n";

    std::string pattern;
    std::cin >> pattern;

    PatternFinder::get_instance().set_pattern(pattern);

    PatternFinder::get_instance().find_pattern();

    PatternFinder::get_instance().set_params_from_txt();
    PatternFinder::get_instance().find_pattern();

}