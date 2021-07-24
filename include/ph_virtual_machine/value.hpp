#pragma once
#include <ph_concepts/concepts.hpp>

using namespace ph::concepts;

namespace ph::virtual_machine
{

    
    struct value
    {
        enum {VAL_BOOL, VAL_NUMBER, VAL_NIL, VAL_CHAR} type;
        union {bool boolean; double number; char chaar;} as;
//        char name [100];
//        std::variant <std::string, >
        
        friend std::ostream& operator<< (std::ostream& os, value const& v)
        {
            switch (v.type)
            {
                case value::VAL_NIL:
                {
                    return os << "nil";
                }
                    
                case value::VAL_BOOL:
                {
                    return os << v.as.boolean;
                }
                    
                case value::VAL_NUMBER:
                {
                    return os << v.as.number;
                }
                    
                case value::VAL_CHAR:
                {
                    return os << v.as.chaar;
                }
                    
                default:
                {
                    return os << "unknown";
                }
            }
        }
    };
    
    constexpr auto make_value (Bool auto b) noexcept -> value
    {
        return {value::VAL_BOOL, .as.boolean = b};
    }
    
    constexpr auto make_value (Char auto n) noexcept -> value
    {
        return {value::VAL_CHAR, .as.chaar = n};
    }
    
    constexpr auto make_value (Number auto n) noexcept -> value
    {
        return {value::VAL_NUMBER, .as.number = n};
    }
    
    
    
    constexpr auto make_value (auto* b) noexcept -> value
    {
        return {value::VAL_NIL};
    }
    
    
    auto make_vm_value ()
    {
        
    }
}
