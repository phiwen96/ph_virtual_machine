#pragma once

namespace ph::virtual_machine
{
    enum struct value_type
    {
        STRING,
        NUMBER,
        STRUCT
    };
    
    struct value
    {
        enum {STRING, NUMBER, STRUCT} type;
        union
        {
            
        } as;
        char name [100];
//        std::variant <std::string, >
    };
}
