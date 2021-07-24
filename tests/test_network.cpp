#include "test_network.hpp"
#include <ph_data_structures/stack.hpp>



namespace ph::network
{
    TEST_CASE("asio, connect to address and write string")
    {
        using namespace std;

        
        const auto te0 = [](auto ip_address, Signed auto port)
        {
            cout << "hi" << endl;
            
            auto error_code = boost::system::error_code {};
            auto context = boost::asio::io_context {};
            auto endpoint = boost::asio::ip::tcp::endpoint {boost::asio::ip::make_address (ip_address, error_code), static_cast<unsigned short>(port)};
            auto socket = boost::asio::ip::tcp::socket {context};
            
            socket.connect (endpoint, error_code);
            
            REQUIRE_FALSE (error_code);
            REQUIRE (socket.is_open ());
            
            auto text = "GET /index.html HTTP/1.1\r\n"
                        "Host: example.com\r\n"
                        "Connection: close\r\n\r\n";

            
            socket.write_some (boost::asio::buffer (text, strlen (text)), error_code);
            
        };
        
        
        te0 ("93.184.216.34", 80);
        
        
    }
}






TEST_CASE ("main")
{
    signed int a;
}

enum struct opcode
{
    MULTIPLY,
    DIVIDE,
    INCREMENT,
    DECREMENT,
    ADD,
    SUBTRACT,
    STOP,
    REPLAY
};

template <typename T>
struct stack
{
    
    std::vector <T> vec;
    
    
    
    auto top () -> auto&
    {
        return vec.back();
    }
    
    auto pop () -> auto&
    {
        vec.pop_back();
    }
    
    auto push (auto v)
    {
        vec.push_back(v);
    }
};

/**
 Number -> multiply, add, subtract, divide
 */

struct virtual_machine
{
    auto run (auto code, auto data)
    {
        for (auto c : code)
        {
            int a;
            int b;
            
            
            
            switch (c)
            {
                case opcode::MULTIPLY:
                {
                   
                    data.push (data.pop () * data.pop ());
                    
                    
                    break;
                }
                    
                case opcode::DIVIDE:
                {
                    std::cout << "what" << std::endl;
                    break;
                }
                    
                case opcode::INCREMENT:
                {
                    std::cout << "what" << std::endl;
                    break;
                }
                    
                case opcode::DECREMENT:
                {
                    std::cout << "what" << std::endl;
                    break;
                }
                    
                case opcode::ADD:
                {
                    std::cout << "what" << std::endl;
                    break;
                }
                    
                case opcode::SUBTRACT:
                {
                    std::cout << "what" << std::endl;
                    break;
                }
                    
                case opcode::STOP:
                {
                    std::cout << "what" << std::endl;
                    break;
                }
                    
                case opcode::REPLAY:
                {
                    std::cout << "what" << std::endl;
                    break;
                }
                    
                default:
                {
                    break;
                }
            }
        }
    }
};







TEST_CASE ("virtual machine")
{
    auto code =
    {
        opcode::MULTIPLY
    };
    
    auto data = ph::data_structures::stack
    {
        1,
        -70
    };
    
    auto vm = virtual_machine {};
    
//    vm.run ({opcode::MULTIPLY}, {1, -70});
    
    
    
}
