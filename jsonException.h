#include <exception>
#include <string>
namespace myjson
{
    class JsonException : public std::exception
    {
        std::string __msg;

        public:
            JsonException(const std::string &msg):__msg(msg){}
            const char * what () const throw (){return __msg.c_str();}
    };
}