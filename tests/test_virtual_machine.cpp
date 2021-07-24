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
        
        
        return false;
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
    
    
#define INSTRUCTION_TYPES \
    X (PUSH, 0) \
    X (POP, 0) \
    X (ADD, 2) \
    X (MULT, 2) \
    X (DIV, 2) \
    X (SUB, 2) \
    X (REFERENCE, 0) \
    X (LIST, 0) \
    X (IDENTIFIER, 0) \
    X (CONSTANT, 1) \
    X (PRINT, 0) \
    X (TAIL, 0)
    
    enum instruction_type : uint8_t
    {
#define X(t, ...) t,
INSTRUCTION_TYPES
#undef X
    };
    
    std::ostream& operator << (std::ostream& os, instruction_type i)
    {
#define X(t, ...) \
    if (i == instruction_type::t) return os << #t;
        INSTRUCTION_TYPES
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
                case instruction_type::PUSH:
                {
                    break;
                }
                case instruction_type::POP:
                {
                    break;
                }
                case instruction_type::ADD:
                {
                    auto rhs = pop (stack);
                    auto lhs = pop (stack);
                    cout << "ADD " << lhs << " " << rhs << endl;
                    auto res = lhs + rhs;
                    
                    push (stack, res);
                    break;
                }
                case instruction_type::MULT:
                {
                    auto rhs = pop (stack);
                    auto lhs = pop (stack);
                    cout << "MULT " << lhs << " " << rhs << endl;
                    auto res = lhs * rhs;
                    
                    push (stack, res);
                    break;
                }
                case instruction_type::DIV:
                {
                    auto rhs = pop (stack);
                    auto lhs = pop (stack);
                    cout << "DIV " << lhs << " " << rhs << endl;
                    auto res = lhs / rhs;
                    
                    push (stack, res);
                    break;
                }
                case instruction_type::SUB:
                {
                    auto rhs = pop (stack);
                    auto lhs = pop (stack);
                    cout << "SUB " << lhs << " " << rhs << endl;
                    auto res = lhs - rhs;
                    
                    push (stack, res);
                    break;
                }
                case instruction_type::REFERENCE:
                {
                    break;
                }
                case instruction_type::LIST:
                {
                    break;
                }
                case instruction_type::IDENTIFIER:
                {
                    auto length = pop (stack);
                    break;
                }
                    
                
                
                    
                    
                    
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
                case instruction_type::ADD:
                    return std::make_tuple (index + 1, "adding");
                    
                case instruction_type::CONSTANT:
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
    
    
    constexpr auto push (auto & v, auto &&... value) noexcept -> void
    {
        ([&v] (auto value)
        {
            v.push_back (fwd (value));
        } (value), ...);
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
    
    
    
    
    
    TEST_CASE ("main")
    {
        using constant = double;
        using byte = uint8_t;
        
        auto code = std::vector <byte> {};
        auto constants = std::vector <constant> {};
        
        

        
        const auto push_constants = [&code, &constants] (auto... values) constexpr noexcept -> void // push back value and return an index to it
        {
            ([&code, &constants] (auto value)
            {
                push (code, instruction_type::CONSTANT, constants.size ());
//                push (code, constants.size ());
                push (constants, value);
            }
             (values), ...);
        };
        
        const auto push_instructions = [&code] (auto... instructions) constexpr noexcept -> void // push back value and return an index to it
        {
            push (code, instructions...);
        };
    
        
        const auto run = [&code] (auto... executors) constexpr noexcept -> void
        {
            ([&code](auto executor){
                for (int i = 0; i < code.size(); ++i)
                {
                    i = executor (i);
                }
            }(executors), ...);
        };
        
    }
    
    
    
    
    
    TEST_CASE ("disassemble")
    {
        return;
        Range auto instructions = std::vector <instruction_type> {};
        Range auto constants = std::vector <int> {};
        
        
        
//        disassemble (instructions, constants, "test chunk");
    }
    

    
    TEST_CASE ("")
    {
        using constant = double;
        using byte = uint8_t;
        
        
        
//        return;
        auto lex = [] (String auto && text) -> auto
        {
            auto code = std::vector <byte> {};
            auto constants = std::vector <constant> {};
            
            enum state
            {
                BEGIN,
                NUMBER,
                WHITESPACE,
                IDENTIFIER,
                ADD,
                SUB,
                MULT,
                DIV,
                CONSTANT
            };
            
            Integer  auto e = 10;
            Floating auto number = double {0};
            
            auto current = BEGIN;
            
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
                            current = state::NUMBER;
                            
                            push (code, instruction_type::CONSTANT, constants.size ());
                            push (constants, c - '0');
                            
                        } else if (identifier (c))
                        {
                            cout << "begin::identifier(" <<  c << ")" << endl;

//                            cout << c << endl;
                            push (code, instruction_type::IDENTIFIER, constants.size());
                            push (constants, c);
                            
                        } else if (operation (c))
                        {
                            cout << "begin::operation(" <<  c << ")" << endl;

                            switch (c)
                            {
                                case '+':
                                    push (code, instruction_type::ADD);
                                    break;
                                    
                                case '-':
                                    push (code, instruction_type::SUB);
                                    break;
                                    
                                case '*':
                                    push (code, instruction_type::MULT);
                                    break;
                                    
                                case '/':
                                    push (code, instruction_type::DIV);
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
                            cout << "number::digit(" <<  c << ")" << endl;
    //                        cout << "number" << endl;
                            // change current state
                            current = state::NUMBER;
                            
                            push (code, instruction_type::CONSTANT, constants.size ());
                            push (constants, c - '0');
                            
                        } else if (identifier (c))
                        {
                            cout << "number::identifier(" <<  c << ")" << endl;

//                            cout << c << endl;
                            push (code, instruction_type::IDENTIFIER, constants.size());
                            push (constants, c);
                            
                        } else if (operation (c))
                        {
                            cout << "number::operation(" <<  c << ")" << endl;

                            switch (c)
                            {
                                case '+':
                                    push (code, instruction_type::ADD);
                                    break;
                                    
                                case '-':
                                    push (code, instruction_type::SUB);
                                    break;
                                    
                                case '*':
                                    push (code, instruction_type::MULT);
                                    break;
                                    
                                case '/':
                                    push (code, instruction_type::DIV);
                                    break;
    
                                default:
                                    break;
                            }
                        }
                        break;
                    }
                        
                    case state::CONSTANT:
                    {
                        if (digit (c)) // push value and keep state
                        {
                            cout << "constant::digit(" <<  c << " )" << endl;

                            push (code, instruction_type::ADD, constants.size());
                            push (constants, c);
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
                                push (code, instruction_type::ADD);
                                current = state::ADD;
                                
                                current = state::ADD;
                                e = 10;
                                continue;
                                
                            } else if (c == '-') // push instruction and change state
                            {
                                push (code, instruction_type::ADD);
                                current = state::ADD;
                                
                                e = 10;
                                continue;
                                
                            } else if (c == '*') // push instruction and change state
                            {
                                push (code, instruction_type::ADD);
                                current = state::ADD;
                                
                                e = 10;
                                continue;
                                
                            } else if (c == '/') // push instruction and change state
                            {
                                push (code, instruction_type::ADD);
                                current = state::ADD;
                                
                                current = state::ADD;
                                e = 10;
                                continue;
                            }
                        }
                        
                        break;
                    }
                        
                    case state::ADD:
                    {
                        cout << "state: ADD" << endl;
                        
                        if (digit (c)) // change state and push value and instruction
                        {
                            push (code, instruction_type::ADD, constants.size());
                            push (constants, c - '0');
                            
                            current = state::NUMBER;
                            
                        } else if (identifier (c)) // change state and push identifier
                        {
                            push (code, instruction_type::IDENTIFIER, constants.size (), /*length*/1);
                            push (constants, c);
//                            push (constants, c);

                            current = state::IDENTIFIER;
                        }
                        
                        break;
                    }
                    
                    case state::IDENTIFIER:
                    {
                        cout << "state: IDENTIFIER" << endl;
                        
                        if (identifier (c)) // keep state, change length
                        {
                            
                            auto length = pop (code);
                            ++length;
                            auto index = top (code);
                            push (code, length);
                            push (constants, c);
                        
                        } else if (period (c))
                        {
                            
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

        
//        cout << endl;
//        code = lex ("---");
        
//        return 0;
        
        
        auto [code, constants] = lex ("41 + 10");
        
        cout << code.size() << endl;
//        cout << constants.size() << endl;
        
        for (int i = 0; i < code.size(); ++i)
        {
            switch (code [i])
            {
                case instruction_type::ADD:
                {
                    auto rhs = pop (constants);
                    auto lhs = pop (constants);
                    
                    cout << "ADD " << lhs << " " << rhs << endl;
                    push (constants, lhs + rhs);
                    return i + 4;
                }
                    
                case instruction_type::SUB:
                {
                    auto rhs = pop (constants);
                    auto lhs = pop (constants);
                    
                    cout << "SUB " << lhs << " " << rhs << endl;
                    push (constants, lhs - rhs);
                    return i + 4;
                }
                case instruction_type::MULT:
                {
                    auto rhs = pop (constants);
                    auto lhs = pop (constants);
                    
                    cout << "MULT " << lhs << " " << rhs << endl;
                    push (constants, lhs * rhs);
                    return i + 4;
                }
                case instruction_type::DIV:
                {
                    auto rhs = pop (constants);
                    auto lhs = pop (constants);
                    
                    cout << "DIV " << lhs << " " << rhs << endl;
                    push (constants, lhs / rhs);
                    return i + 4;
                }
                case instruction_type::PRINT:
                {
                    auto value = pop (constants);
                    
                    cout << "PRINT " << value << endl;
//                    push (constants, lhs / rhs);
                    return i + 4;
                }
                    
                    
                    
                default:
                {
                    return i + 1;
                }
            }
        }
        
       
     
        
        return;
        
        auto aa = {instruction_type::ADD, instruction_type::SUB};
        for (auto i : aa)
        {
//            cout << i << endl;
        }
//        execute (instructions, stack);
        
//        1 + 2 * 3 + 4 = 11
//        int stack [] = {1, 2, 3, 4};
        
        
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

