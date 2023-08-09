#pragma once
#include <string>
#include <variant>
#include <cstring>
#include <cstddef>

// Value
class Value{
public:
    struct Bad_entry{}; 

    Value() : i{}, type{Tag::number}{} // Default init is for int.
    Value(int i_) : i{i_}, type{Tag::number}{}

    Value(const std::string& ss){
        new (&s) std::string(ss);

        type = Tag::text;
    }

    Value(const Value & val){
        switch (val.type){
            case Tag::number:
                i = val.i;
                break;
            case Tag::text:
                new (&s) std::string(val.s); // placement new: explicit construct
        }
        type = val.type;
    }

    Value &operator=(const Value &e) // necessary because of the string variant
    {
        if (type == Tag::text && e.type == Tag::text){
            s = e.s; // usual string assignment
            return *this;
        }

        if (type == Tag::text)
            s.~basic_string(); // explicit destroy
        
        switch (e.type){
            case Tag::number:
                i = e.i;
                break;
            case Tag::text:
                new (&s) std::string(e.s); // placement new: explicit construct
        }
        type = e.type;
        return *this;
    }

    ~Value(){
        if (type == Tag::text)
            s.~basic_string(); // explicit destroy
    }


    int number() const
    {
        if (type != Tag::number)
            throw Bad_entry{};
        return i;
    }
    std::string text() const
    {
        if (type != Tag::text)
            throw Bad_entry{};
        return s;
    }

    std::variant<int, std::string> get_variant()const{
        if (type == Tag::number)
            return std::variant<int, std::string>{i};
        
        return std::variant<int, std::string>{s};
    }

    void set_number(int n)
    {
        if (type == Tag::text)
        {
            s.~basic_string(); // explicitly destroy string
            type = Tag::number;
        }
        i = n;
    }
    void set_text(const std::string &ss)
    {
        if (type == Tag::text)
            s = ss;
        else
        {
            new (&s) std::string{ss}; // placement new: explicitly construct string
            type = Tag::text;
        }
    }
private:
    enum class Tag { number, text };
    Tag type;
    union { // representation (note: anonymous union)
        int i;
        std::string s; // string has default constructor, copy operations, and destructor
        // using std::string = std::basic_string<char>;. Thats why call ~basic_string() for destruction.
    };
};

// Immutable_string

class Immutable_string {
public:
    Immutable_string(const char* str) :
        size(strlen(str))
    {
        if (size < Immutable_string::buffer_size){
            strcpy_s(string_buffer, Immutable_string::buffer_size, str); //strcpy_s is a function from the C11 standard (and later) that provides a safer alternative to strcpy for copying strings.
            puts("Short-string optimization. For");
            puts(string_buffer);
        }
        else {
            string_ptr = new char[size + 1];
            strcpy_s(string_ptr, size + 1, str);
        }
    }

    Immutable_string(const Immutable_string &other) : size(other.size){
        if (size < Immutable_string::buffer_size) {
            strcpy_s(string_buffer, Immutable_string::buffer_size, other.get_str());
        }
        else{
            string_ptr = new char[size + 1];
            strcpy_s(string_ptr, size + 1, other.get_str());
        }
    }

    Immutable_string& operator=(const Immutable_string &other){
        if (this == &other){
            return *this;
        }

        if (size >= Immutable_string::buffer_size){
            delete[] string_ptr;
        }

        size = other.size;
        if (size < Immutable_string::buffer_size){
            strcpy_s(string_buffer, Immutable_string::buffer_size, other.get_str());
        }
        else{
            string_ptr = new char[size + 1];
            strcpy_s(string_ptr, size + 1, other.get_str());
        }

        return *this;
    }

    Immutable_string(Immutable_string&& other) noexcept
        : size(other.size) {
        if (size < Immutable_string::buffer_size) {
            std::memmove(string_buffer, other.string_buffer, size + 1);
            other.string_buffer[0] = '\0';
        } else {
            string_ptr = other.string_ptr;
            other.string_ptr = nullptr;
        }
        other.size = 0;
    }

    Immutable_string& operator=(Immutable_string&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        if (size >= Immutable_string::buffer_size) {
            delete[] string_ptr;
        } 
        size = other.size;
        if (size < Immutable_string::buffer_size) {
            std::memmove(string_buffer, other.string_buffer, size + 1);
            other.string_buffer[0] = '\0';
        } else {
            string_ptr = other.string_ptr;
            other.string_ptr = nullptr;
        }
        other.size = 0;

        return *this;
    }
    
    ~Immutable_string()
    {
        if (size >= Immutable_string::buffer_size)
            delete[] string_ptr;
    }

    const char* get_str() const
    {
        return (size < Immutable_string::buffer_size) ? string_buffer : string_ptr;
    }

    void set_string(const char* str){
        if(size >= Immutable_string::buffer_size){
            delete[] string_ptr;
        }

        size = strlen(str);
        if (size < Immutable_string::buffer_size)
        {
            strcpy_s(string_buffer, Immutable_string::buffer_size, str);
        }
        else
        {
            string_ptr = new char[size + 1];
            strcpy_s(string_ptr, size + 1, str);
        }
    }

    std::size_t capacity() const{
        return size;
    }

    static constexpr size_t buffer_size = 16; // Slightly larger than the size of a pointer
private:
    // If the string is short enough, we store the string itself
    // instead of a pointer to the string.
    std::size_t size;
    union {
        char* string_ptr;
        char string_buffer[Immutable_string::buffer_size];
    };

};



