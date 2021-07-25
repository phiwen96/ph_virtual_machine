#include <catch2/catch.hpp>
//#include <ph_data_structures/data_structures.hpp>
#include <ph_concepts/concepts.hpp>
#include <ph_virtual_machine/virtual_machine.hpp>


#define EAT(...)
#define fwd(x) std::forward <decltype (x)> (x)


namespace A
{
    inline namespace a {auto print(){}};
    namespace B
    {
        namespace current
        {
            struct KUK {static auto print(){std::cout<<"current"<<std::endl;}};
        }
        
        inline namespace old
        {
            struct KUK {static auto print(){std::cout<<"old"<<std::endl;}};
        }
        
        
    }
}
namespace A{
    inline namespace a{auto print2(){}};
}

TEST_CASE("")
{
    A::print2();
    A::print();
    A::B::KUK::print();
    A::B::current::KUK::print();
    A::B::old::KUK::print();

}

namespace ph {
    template <typename T>
    concept Stack = Range <T> and requires ()
    {
        true;
    };
}

namespace ph::virtual_machine
{
//    using namespace ph::concepts;
    /**
     låt varje opcode definiera ett par funktioner som den skickar med som argument till register_instruction
     */
    
    
    
    
    
    
    
    
    template <typename operation_code>
    consteval auto register_instruction (auto&& executor, Stack auto&& code, Stack auto&& stack) noexcept
    requires requires (int i)
    {
        {executor (i)} noexcept -> /*next instruction*/Integer;
    }
    {
        return [&](){
            for (auto i = ph::begin (code); i < ph::end (code); ++i)
            {
                i = executor (i);
            }
        };
    }
    
    TEST_CASE ("lol")
    {
//        auto
    }
    
    
    
    template <uint_fast8_t>
    struct Code
    {
        
        auto push (auto&& v) -> auto&
        {
            _code.push_back (fwd (v));
            return _code.back();
        }
        
        friend std::ostream& operator << (std::ostream& os, Code const& c)
        {
            for (int i = 0; i < c._code.size(); ++i)
            {
                switch (c._code [i])
                {
                        
                }
            }
            return os;
        }
        
    private:
        std::vector <opcode> _code;
    };
    
    
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
    constexpr auto push (auto & v, auto val) noexcept -> auto&
    {
//        ([&v] (auto value)
//        {
            v.push_back (fwd (val));
//        } (val), ...);
        return v.back ();
        
//#ifdef DEBUG
//        cout << "stack {";
//        for (auto& i : v)
//            cout << i << " ";
//        cout << "}";
//#endif
    }
    
    [[nodiscard]] constexpr auto pop (auto & in) noexcept -> auto
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
//                WHITESPACE,
//                IDENTIFIER,
//                ADD,
//                SUB,
//                MULT,
//                DIV,
//                CONSTANT,
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
#ifdef DEBUG
                    cout << "whitespace(" << c << ")" << endl;
#endif
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
#ifdef DEBUG
                            cout << "begin::digit(" <<  c << ")" << endl;
#endif


    //                        cout << "number" << endl;
                            // change current state
                            TRANSITION (NUMBER);
                            
                            push (code, opcode::OP_CONSTANT);
                            push (code, constants.size ());
                            push (constants, make_number (c - '0'));
                            
                        } else if (identifier (c))
                        {
#ifdef DEBUG
                            cout << "begin::identifier(" <<  c << ")" << endl;
#endif

//                            cout << c << endl;
//                            push (code, opcode::OP_IDENTIFIER, constants.size());
//                            push (constants, c);
                            
                        } else if (operation (c))
                        {
#ifdef DEBUG
                            cout << "begin::operation(" <<  c << ")" << endl;
#endif

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
#ifdef DEBUG
                            cout << "number::digit(" <<  c << ")" << endl;

                            cout << "changed from " << nr;
#endif
                            nr *= 10;
                            nr += double (c - '0');
//                            cout << nr << endl;
#ifdef DEBUG
                            cout << " to " << nr << endl;
#endif
                            
                        

                            
//                            push (code, opcode::OP_CONSTANT, constants.size ());
//                            push (constants, c - '0');
                            
                        } else
                        {
                            auto index = pop (code);
                            auto op_code = pop (code);
                            auto & number = constants [index].as.number;
//                            cout << number << endl;
//                            auto nr = constants []
                            
                            if (identifier (c))
                            {
                                
#ifdef DEBUG
                                        cout << "number::identifier(" <<  c << ")" << endl;
#endif
    //                            cout << c << endl;
    //                            push (code, opcode::OP_IDENTIFIER, constants.size());
    //                            push (constants, c);
                                
                            } else if (operation (c))
                            {
                                switch (c)
                                {
                                    case '+':
                                    {
                                        const auto index = pop (code);
                                        const auto op_type = pop (code);
                                        
                                        
#ifdef DEBUG
//                                        assert(code.size() == 0);
                                        cout << "number::operation(" <<  c << ")" << endl;
                                        
                                        cout << "lhs = " << constants [index] << endl;
#endif
                                        
                                        
                                        push (code, opcode::OP_ADD);
                                        push (code, opcode::OP_CONSTANT);
                                        push (code, index);


//                                        push (code, opcode::OP_ADD, OP_CONSTANT, index);
                                        break;
                                    }
                                        
                                    case '-':
#ifdef DEBUG
                                        cout << "number::operation(" <<  c << ")" << endl;
#endif
                                        push (code, opcode::OP_SUB);

//                                        push (code, opcode::OP_SUB, OP_CONSTANT, index);
                                        break;
                                        
                                    case '*':
#ifdef DEBUG
                                        cout << "number::operation(" <<  c << ")" << endl;
#endif
                                        push (code, opcode::OP_MULT);

//                                        push (code, opcode::OP_MULT, OP_CONSTANT, index);
                                        break;
                                        
                                    case '/':
#ifdef DEBUG
                                        cout << "number::operation(" <<  c << ")" << endl;
#endif
                                        push (code, opcode::OP_DIV);

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
 
                    case state::OPERATION:
                    {
                        auto& lhs = constants [pop (code)];
                        auto&& lhs_opcode = pop (code);
                        
                        auto& op_code = push (code, opcode::OP_GEN_ERROR);
                        
                        if (digit (c)) // change state and push value and instruction
                        {
                            op_code = opcode::OP_ADD;
                            
                            push (code, opcode::OP_CONSTANT);
                            push (code, constants.size());
                            push (constants, make_number (c - '0'));
                            
                            const auto index = constants.size();
                            const auto nr = make_number (c - '0');
                            cout << ":" << nr << endl;
                            push (constants, nr);
                            push (code, opcode::OP_CONSTANT);
                            push (code, index);

                            
                            
#ifdef DEBUG
                            cout << "operation::digit(" << c << ")" << endl;
                            cout << "index = " << index << endl;
                            cout << "pushed = " << top (constants) << endl;

#endif

//                            push (code, opcode::OP_ADD, constants.size());
//                            push (constants, c - '0');
                            
                            TRANSITION (NUMBER);

                        } else if (identifier (c)) // change state and push identifier
                        {
                            cout << "operation::identifier(" << c << ")" << endl;

//                            push (code, opcode::OP_IDENTIFIER, constants.size (), /*length*/1);
//                            push (constants, c);

//                            TRANSITION (IDENTIFIER);

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
        
        
        

        
#ifdef DEBUG
#define INPUT "1 + 2"

        cout << "in: " << INPUT << endl;
        cout << "===lexing==============" << endl;
#endif

        
        auto [code, constants] = parse (INPUT);
        
        cout << "===execute==================" << endl;
        cout << "code size = " << code.size() << endl;
        auto execute = [](auto& code, auto& constants){
            for (int i = 0; i < code.size(); ++i)
            {
                switch (code [i])
                {
                    case opcode::OP_ADD:
                    {
                        auto lhs = constants [code [i + 2]].as.number;
                        auto rhs = constants [code [i + 4]].as.number;
#ifdef DEBUG
                        cout << "OP_ADD" << endl;
                        cout << lhs << endl;
                        cout << rhs << endl;
#endif
                        break;
                    }
                    case opcode::OP_SUB:
                    {
#ifdef DEBUG
                        cout << "OP_SUB" << endl;

#endif

                        break;
                    }
                    case opcode::OP_MULT:
                    {
#ifdef DEBUG
                        cout << "OP_MULT" << endl;

#endif

                        break;
                    }
                    case opcode::OP_DIV:
                    {
#ifdef DEBUG
                        cout << "OP_DIV" << endl;

#endif

                        break;
                    }
                    case opcode::OP_CONSTANT:
                    {
#ifdef DEBUG
                        cout << "OP_CONSTANT" << endl;

#endif

                        break;
                    }

                    default:
                    {
#ifdef DEBUG
                        cout << "unknown" << endl;

#endif
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

