#pragma once
#include <ph_concepts/concepts.hpp>

namespace ph::virtual_machine
{
#define OPCODES \
    X (OP_ADD) \
    X (OP_SUB) \
    X (OP_MULT) \
    X (OP_DIV) \
    X (OP_CONSTANT) \
    X (OP_PRINT)
    
    enum opcode : uint_fast8_t
    {
#define X(t, ...) t,
        OPCODES
#undef X
    };
    
    std::ostream& operator << (std::ostream& os, opcode i)
    {
#define X(t, ...) \
    if (i == opcode::t) return os << #t;
        OPCODES
#undef X
        
        return os << "";
    }
#undef OPCODES
}
