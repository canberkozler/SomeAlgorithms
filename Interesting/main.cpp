#include <iostream>
#include "union_implementation.hpp"


int main(){
    { // union_implementation.hpp - Value
        Value val1{};

        val1.set_number(5);

        try{
            std::cout << "number: " << val1.number()<<"\n";
        }catch(const Value::Bad_entry& be){
            std::cerr<<"Invalid Call.\n";
        }

        val1.set_text("Subarashii desu ne。");

        try{
            std::cout << val1.number()<<"\n";
        }catch(const Value::Bad_entry& be){
            std::cerr<<"Invalid Call.\n";
        }

        try{
            std::cout << val1.text()<<"\n";
        }catch(const Value::Bad_entry& be){
            std::cerr<<"Invalid Call.\n";
        }

        val1.set_text("Hi Github!");
        auto vrt = val1.get_variant();

        try{
            std::cout << std::get<int>(vrt)<<"\n";
        }catch(const std::exception& ex){
            std::cerr<<ex.what()<<"\n";
        }

        try{
            std::cout << std::get<std::string>(vrt)<<"\n";
        }catch(const std::exception& ex){
            std::cerr<<ex.what()<<"\n";
        }
    }

    std::cout<<std::endl;

    { // union_implementation.hpp - Immutable_string
        Immutable_string short_string{"Canberk"};
        Immutable_string longer_string{"Just a longer string."};

        std::cout << "Main (longer_string): " << longer_string.get_str() << "\n";

        short_string.set_string("ali");

        std::cout << "Main (short_string): " << short_string.get_str() << "\n";

        longer_string = std::move(short_string);

        std::cout << "After Move (short_string): " << short_string.get_str() << " Size: " << short_string.capacity() <<  "\n";
        std::cout << "After Move (longer_string): " << longer_string.get_str() << " Size: " << longer_string.capacity() << "\n";
    }
}