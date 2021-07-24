#include <catch2/catch.hpp>
#include <ph_data_structures/data_structures.hpp>
#include <ph_concepts/concepts.hpp>
#include <ph_virtual_machine/virtual_machine.hpp>


#define EAT(...)
#define fwd(x) std::forward <decltype (x)> (x)




namespace ph::virtual_machine
{
    inline constexpr bool identifier (auto c) noexcept {
        return c >= 'a' and c <= 'z';
    }
    inline constexpr bool digit (auto c) noexcept {
        return c >= '0' and c <= '9';
    }
    inline constexpr bool whitespace (auto c) noexcept {
        return c == ' ' or c == '\t' or c == '\n';
    }
    inline constexpr bool period (auto c) noexcept {
        return c == '.';
    }
    inline constexpr bool comma (auto c) noexcept {
        return c == ',';
    }
    inline constexpr bool plus (auto c) noexcept {
        return c == '+';
    }
    inline constexpr bool minus (auto c) noexcept {
        return c == '-';
    }
    inline constexpr bool star (auto c) noexcept {
        return c == '*';
    }
    inline constexpr bool slash (auto c) noexcept {
        return c == '/';
    }
    inline constexpr bool operation (auto c) noexcept {
        return plus(c) or minus(c) or star(c) or slash(c);
    }
    
    using std::cout, std::endl;
    using namespace ph::concepts;
    
    
    
    
    
    
    
    
    
#define TOKEN_TYPES \
    X (NUMBER) \
    X (IDENTIFIER) \
    X (COMMA) \
    X (WHITESPACE) \
    X (PERIOD) \
    X (QUESTION_MARK) \
    X (BANG) \
    X (PLUS) \
    X (MINUS) \
    X (STAR) \
    X (SLASH) \
    X (SPACE)
    
    enum struct token_type
    {
#define X(t, ...) t,
TOKEN_TYPES
#undef X
    };
    
    std::ostream& operator << (std::ostream& os, token_type i)
    {
        
#define X(t, ...) \
    if (i == token_type::t) return os << #t;
        TOKEN_TYPES
#undef X
        
        return os << "";
    }
    
    

    

    

    
    auto execute = [] (Range auto && instructions, Range auto && stack)
    {
        auto pop_string = [&stack]()
        {
            
        };
        
        for (auto && i : instructions)
        {
            switch (i)
            {
//                case opcode::OP_PUSH:
//                {
//                    break;
//                }
//                case opcode::OP_POP:
//                {
//                    break;
//                }
                case opcode::OP_ADD:
                {
                    auto rhs = pop (stack);
                    auto lhs = pop (stack);
                    cout << "ADD " << lhs << " " << rhs << endl;
                    auto res = lhs + rhs;
                    
                    push (stack, res);
                    break;
                }
                case opcode::OP_MULT:
                {
                    auto rhs = pop (stack);
                    auto lhs = pop (stack);
                    cout << "MULT " << lhs << " " << rhs << endl;
                    auto res = lhs * rhs;
                    
                    push (stack, res);
                    break;
                }
                case opcode::OP_DIV:
                {
                    auto rhs = pop (stack);
                    auto lhs = pop (stack);
                    cout << "DIV " << lhs << " " << rhs << endl;
                    auto res = lhs / rhs;
                    
                    push (stack, res);
                    break;
                }
                case opcode::OP_SUB:
                {
                    auto rhs = pop (stack);
                    auto lhs = pop (stack);
                    cout << "SUB " << lhs << " " << rhs << endl;
                    auto res = lhs - rhs;
                    
                    push (stack, res);
                    break;
                }
//                case opcode::OP_REFERENCE:
//                {
//                    break;
//                }
//                case opcode::OP_LIST:
//                {
//                    break;
//                }
//                case opcode::OP_IDENTIFIER:
//                {
//                    auto length = pop (stack);
//                    break;
//                }
                    
                
                
                    
                    
                    
                default:
                {
                    break;
                }
            }
        }
    };
    
    auto disassemble (Range auto code, Range auto constants, String auto && name)
    {
        auto disassemble_instruction = [&code, &constants] (auto index)
        {
            auto instruction = code [index];
            
            switch (instruction)
            {
                case opcode::OP_ADD:
                    return std::make_tuple (index + 1, "adding");
                    
                case opcode::OP_CONSTANT:
                    return std::make_tuple (index + 1, "adding");
                    
                default:
                    return std::make_tuple (index + 1, "unknown");
            }
        };
        
        for (int i = 0; i < code.size (); ++i)
        {
            auto [j, msg] = disassemble_instruction (i);
            cout << "\t" << msg << endl;
            i = j;
        }
//        printf ("== %s ==\n", name);
    }
    
    
    
    
    template <auto...>
    constexpr auto push (auto & v, auto &&... values) noexcept -> void
    {
        ([&v] (auto value)
        {
            v.push_back (fwd (value));
        } (values), ...);
    }
    
    [[nodiscard]] constexpr auto pop (auto & in) noexcept -> auto &&
    {
        auto&& r = in.back ();
        in.pop_back ();
        return r;
    }
    
    [[nodiscard]] constexpr auto top (auto & in) noexcept -> auto &
    {
        return in.back ();
    }
    
    struct pusher {};
    struct popper {};
    
    template <size_t N>
    auto begin (char const (& c) [N]) -> char*
    {
        return c;
    }
    
    auto begin (auto c) -> auto&
    {
        return *c;
    }
    
    template <size_t N>
    constexpr auto string (char const (& c) [N])
    {
        return c;
    }
    
    TEST_CASE ("")
    {
        auto parse = [] (String auto && text) -> auto
        {
            auto code = std::vector <uint_fast8_t> {};
            auto constants = std::vector <value> {};
            
            enum state
            {
                BEGIN,
                NUMBER,
                WHITESPACE,
                IDENTIFIER,
//                ADD,
//                SUB,
//                MULT,
//                DIV,
                CONSTANT,
                OPERATION
            };
            
            Integer  auto e = 10;
            Floating auto number = double {0};
            
            auto current = state::BEGIN;
            
#define TRANSITION(x) current = state::x;
            
            
            // loop through source string
//            cout << whitespace('+') << endl;
            for (auto c : text)
            {
                if (whitespace (c)) // keep state
                {
                    cout << "whitespace(" << c << ")" << endl;
                    continue;
                }
    //            cout << c << endl;
                
                // check current state
                switch (current)
                {
                    case state::BEGIN:
                    {
//                        cout << "state: BEGIN" << endl;
                        
                        if (digit (c))
                        {
                            cout << "begin::digit(" <<  c << ")" << endl;
    //                        cout << "number" << endl;
                            // change current state
                            TRANSITION (NUMBER);
                            
                            push (code, opcode::OP_CONSTANT);
                            push (code, constants.size ());
                            push (constants, make_number (c - '0'));
                            
                        } else if (identifier (c))
                        {
                            cout << "begin::identifier(" <<  c << ")" << endl;

//                            cout << c << endl;
//                            push (code, opcode::OP_IDENTIFIER, constants.size());
//                            push (constants, c);
                            
                        } else if (operation (c))
                        {
                            cout << "begin::operation(" <<  c << ")" << endl;

                            switch (c)
                            {
                                case '+':
                                    push (code, opcode::OP_ADD);
                                    break;
                                    
                                case '-':
                                    push (code, opcode::OP_SUB);
                                    break;
                                    
                                case '*':
                                    push (code, opcode::OP_MULT);
                                    break;
                                    
                                case '/':
                                    push (code, opcode::OP_DIV);
                                    break;
    
                                default:
                                    break;
                            }
                        }
                        
                        break;
                    }
                        
                    case state::NUMBER:
                    {
                        if (digit (c))
                        {
                            auto index = top (code);
                            auto& nr = constants [index].as.number;

                            cout << "changed from " << nr;
                            nr *= 10;
                            nr += double (c - '0');
//                            cout << nr << endl;
                            cout << " to " << nr;
                            
                            cout << "number::digit(" <<  c << ")" << endl;

                            
//                            push (code, opcode::OP_CONSTANT, constants.size ());
//                            push (constants, c - '0');
                            
                        } else
                        {
                            auto index = pop (code);
                            auto instr = pop (code);
                            auto & number = constants [index].as.number;
//                            cout << number << endl;
//                            auto nr = constants []
                            
                            if (identifier (c))
                            {
                                cout << "number::identifier(" <<  c << ")" << endl;

    //                            cout << c << endl;
    //                            push (code, opcode::OP_IDENTIFIER, constants.size());
    //                            push (constants, c);
                                
                            } else if (operation (c))
                            {
                                switch (c)
                                {
                                    case '+':
                                        cout << "number::operation(" <<  c << ")" << endl;

//                                        push (code, opcode::OP_ADD, OP_CONSTANT, index);
                                        break;
                                        
                                    case '-':
                                        cout << "number::operation(" <<  c << ")" << endl;

//                                        push (code, opcode::OP_SUB, OP_CONSTANT, index);
                                        break;
                                        
                                    case '*':
                                        cout << "number::operation(" <<  c << ")" << endl;

//                                        push (code, opcode::OP_MULT, OP_CONSTANT, index);
                                        break;
                                        
                                    case '/':
                                        cout << "number::operation(" <<  c << ")" << endl;

//                                        push (code, opcode::OP_DIV, OP_CONSTANT, index);
                                        break;
        
                                    default:
                                        throw std::runtime_error ("whaaat");
                                        break;
                                }
                                
                                TRANSITION (OPERATION);
                            }
                        }
                        
                        
                        break;
                    }
                        
                    case state::CONSTANT:
                    {
                        if (digit (c)) // push value and keep state
                        {
                            cout << "constant::digit(" <<  c << " )" << endl;

//                            push (code, opcode::OP_ADD, constants.size());
//                            push (constants, c);
                            continue;
                            
                        } else
                        {
                            if (period (c)) // change e and keep state
                            {
                                cout << "constant::period(" <<  c << ")" << endl;

                                e = 0.1;
                                continue;
                                
                            } else if (c == '+') // push instruction and change state
                            {
                                cout << "constant::period(" <<  c << ")" << endl;

                                push (code, opcode::OP_ADD);
                                TRANSITION (OPERATION);
                                
                                e = 10;
                                continue;
                                
                            } else if (c == '-') // push instruction and change state
                            {
                                cout << "constant::period(" <<  c << ")" << endl;

                                push (code, opcode::OP_ADD);
                                TRANSITION (OPERATION);

                                e = 10;
                                continue;
                                
                            } else if (c == '*') // push instruction and change state
                            {
                                cout << "constant::period(" <<  c << ")" << endl;

                                push (code, opcode::OP_ADD);
                                TRANSITION (OPERATION);

                                e = 10;
                                continue;
                                
                            } else if (c == '/') // push instruction and change state
                            {
                                cout << "constant::period(" <<  c << ")" << endl;

                                push (code, opcode::OP_ADD);
                                TRANSITION (OPERATION);

                                e = 10;
                                continue;
                            }
                        }
                        
                        break;
                    }
                    
                    case state::IDENTIFIER:
                    {
//                        cout << "state: IDENTIFIER" << endl;
//
//                        if (identifier (c)) // keep state, change length
//                        {
//
//                            auto length = (uint_fast8_t) pop (code);
//                            ++length;
//                            auto index = top (code);
//                            push (code, length);
//                            push (constants, make_value (c));
//
//                        } else if (period (c))
//                        {
//
//                        }
//
//                        break;
                    }
                        
                    case state::OPERATION:
                    {
                        if (digit (c)) // change state and push value and instruction
                        {
                            auto index = constants.size();
                            push (constants, make_number (c - '0'));
                            push (code, opcode::OP_CONSTANT, index);
                            cout << "operation::digit(" << c << ")" << endl;

//                            push (code, opcode::OP_ADD, constants.size());
//                            push (constants, c - '0');
                            
                            TRANSITION (NUMBER);

                        } else if (identifier (c)) // change state and push identifier
                        {
                            cout << "operation::identifier(" << c << ")" << endl;

//                            push (code, opcode::OP_IDENTIFIER, constants.size (), /*length*/1);
//                            push (constants, c);

                            TRANSITION (IDENTIFIER);

                        } else if (operation (c))
                        {
                            cout << "operation::operation(" << c << ")" << endl;
                            TRANSITION (OPERATION);

                        }
                        
                        break;
                    }
                        
                    default:
                    {
                        cout << "state: default" << endl;
                        break;
                    }
                }
            }
            
            
//            cout << "tji" << endl;
    //        for (auto i : instructions)
    //            cout << i << endl;
            return std::make_tuple (code, constants);
        };
        
        
        cout << "in: " << "41 + 10" << endl;

        
        cout << "===lexing==============" << endl;
        auto [code, constants] = parse ("41 + 10");
        
        cout << "===execute==================" << endl;
        cout << code.size() << endl;
        auto execute = [](auto& code, auto& constants){
            for (int i = 0; i < code.size(); ++i)
            {
                switch (code [i])
                {
                    case opcode::OP_ADD:
                    {
                        cout << "OP_ADD" << endl;
                        break;
                    }
                    case opcode::OP_SUB:
                    {
                        cout << "OP_SUB" << endl;

                        break;
                    }
                    case opcode::OP_MULT:
                    {
                        cout << "OP_MULT" << endl;

                        break;
                    }
                    case opcode::OP_DIV:
                    {
                        cout << "OP_DIV" << endl;

                        break;
                    }
                    case opcode::OP_CONSTANT:
                    {
                        cout << "OP_CONSTANT" << endl;

                        break;
                    }

                    default:
                    {
                        cout << "unknown" << endl;
                        break;
                    }
                }


            }
        };
        
        execute (code, constants);
        

        
//        cout << code.size() << endl;
//        cout << constants.size() << endl;
//        cout << constants.size() << endl;
//        cout << constants[0] << endl;
        
//        auto*
        
        return;
     
//        for (int i = 0; i < code.size(); ++i)
//        {
//            switch (code [i])
//            {
//                case opcode::OP_CONSTANT:
//                {
//                    cout << "OP_CONSTANT" << endl;
////                    auto rhs = pop (constants).as.number;
////                    auto lhs = pop (constants).as.number;
//
////                    cout << "ADD " << lhs << " " << rhs << endl;
////                    push (constants, make_value (lhs + rhs));
//
////                    return i + 4;
//                    break;
//                }
//                case opcode::OP_ADD:
//                {
//                    auto rhs = pop (constants).as.number;
//                    auto lhs = pop (constants).as.number;
//
//                    cout << "ADD " << lhs << " " << rhs << endl;
////                    push (constants, make_value (lhs + rhs));
//                    i += 4;
//                    break;
//                }
//
//                case opcode::OP_SUB:
//                {
//                    auto rhs = pop (constants).as.number;
//                    auto lhs = pop (constants).as.number;
//
//                    cout << "SUB " << lhs << " " << rhs << endl;
////                    push (constants, make_value (lhs - rhs));
//                    i += 4;
//                    break;
//                }
//                case opcode::OP_MULT:
//                {
//                    auto rhs = pop (constants).as.number;
//                    auto lhs = pop (constants).as.number;
//
//                    cout << "MULT " << lhs << " " << rhs << endl;
////                    push (constants, make_value (lhs * rhs));
//                    i += 4;
//                    break;
//                }
//                case opcode::OP_DIV:
//                {
//                    auto rhs = pop (constants).as.number;
//                    auto lhs = pop (constants).as.number;
//
//                    cout << "DIV " << lhs << " " << rhs << endl;
////                    push (constants, make_value (lhs / rhs));
//                    i += 4;
//                    break;
//                }
//                case opcode::OP_PRINT:
//                {
//                    auto value = pop (constants).as.number;
//
//                    cout << "PRINT " << value << endl;
////                    push (constants, lhs / rhs);
//                    i += 4;
//                    break;
//                }
//
//
//
//                default:
//                {
//                    break;
//                }
//            }
//        }
        
        
    }
    
    
    TEST_CASE ("main")
    {
//        using constant = double;
//        using byte = uint8_t;
//
//        auto code = std::vector <byte> {};
//        auto constants = std::vector <constant> {};
//
//
//
//
//        const auto push_constants = [&code, &constants] (auto... values) constexpr noexcept -> void // push back value and return an index to it
//        {
//            ([&code, &constants] (auto value)
//            {
//                push (code, opcode::OP_CONSTANT, constants.size ());
////                push (code, constants.size ());
//                push (constants, value);
//            }
//             (values), ...);
//        };
//
//        const auto push_instructions = [&code] (auto... instructions) constexpr noexcept -> void // push back value and return an index to it
//        {
//            push (code, instructions...);
//        };
//
//
//        const auto run = [&code] (auto... executors) constexpr noexcept -> void
//        {
//            ([&code](auto executor){
//                for (int i = 0; i < code.size(); ++i)
//                {
//                    i = executor (i);
//                }
//            }(executors), ...);
//        };
        
    }

    TEST_CASE ("disassemble")
    {
//        return;
//        Range auto instructions = std::vector <opcode> {};
//        Range auto constants = std::vector <value> {};
//
//
        
//        disassemble (instructions, constants, "test chunk");
    }

    
}





    EAT
    ({
        $ [@var] = PUSH POP ADD SUB MULT DIV
        {
            auto $var = "$var"
        }
    })
    
    EAT
    ({
        inline constexpr bool operation (auto c) noexcept {
            $ [@fun @tecken] = {plus +} {minus -} {star *} {slash /}
            {
                if ($fun (c) or c == '@tecken') return true;
            }
            
            return false;
        }
    })
    
    EAT
    ({
        operations = {plus +} {minus -} {star *} {slash /}
        
        
        inline constexpr bool operation (auto c) noexcept {
            $ [@fun @tecken] = operations
            {
                if (fun (c) or c == '@tecken') return true;
            }
            
            return false;
        }
    })


#undef EAT
#undef fwd

