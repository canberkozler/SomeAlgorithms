#pragma once
#include <string>

class PatternFinder{
public:
    static constexpr std::size_t MaxLength = 64;
    using bitmask = std::bitset<PatternFinder::MaxLength>;

    static PatternFinder& get_instance();

    void find_pattern()const;

    void set_text(const std::string&);
    void set_text(std::string&&);

    const std::string& get_text()const&;

    void set_pattern(const std::string&);
    void set_pattern(std::string&&);

    const std::string& get_pattern()const&;

    void set_params_from_txt();

private:
    PatternFinder() = default;
    ~PatternFinder() = default;

    int bitap_search()const;

    std::string m_text;
    std::string m_pattern;

    mutable std::size_t cntr{};
};

PatternFinder& PatternFinder::get_instance(){
    static PatternFinder s;
    return s;
}