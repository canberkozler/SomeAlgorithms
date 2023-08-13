#include <iostream>
#include "union_implementation.hpp"
#include "MyClass.h"

#include <vector>
#include <string>

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
    std::cout<<"\n";
    { // MyClass
        std::vector<MyClass*> myvec;

        for(std::size_t i{}; i<MyClass::max_no_of_dynamic_object; ++i){
            myvec.push_back(new MyClass);
        }

        try{
            myvec.push_back(new MyClass);
        }catch(const std::exception& ex){
            std::cerr<<ex.what()<<"\n";
        }

        delete myvec[16];
        delete myvec.back();

        try{
            auto pt = new MyClass;
            std::cout<<"1) All good.\n";
        }catch(const std::exception& ex){
            std::cerr<<ex.what()<<"\n";
        }

        try{
            myvec.push_back(new MyClass);
            std::cout<<"2) All good.\n";
        }catch(const std::exception& ex){
            std::cerr<<ex.what()<<"\n";
        }

        try{
            auto pt = new MyClass;
            std::cout<<"3) All good.\n";
        }catch(const std::exception& ex){
            std::cerr<<ex.what()<<"\n";
        }
    }
}