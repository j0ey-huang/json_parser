#include "jsonParser.h"
#include "jsonValue.h"
#include <iostream>

inline bool isWhiteSpace(char c){return c == ' ' || c == '\r' || c == '\n' || c == '\t';}
inline bool isDigit(char c){return c >= '0' && c <= '9';}

namespace myjson
{
    int Parser::parse()
    {
        try
        {
            parse_whitespace();
            parse_value();
            parse_whitespace();
            if(!isEnd()) throw JsonException("Parse root is not singular!");
            return PARSE_OK;
        }
        catch( JsonException e )
        {
            std::cerr << "Fail: " << e.what() << std::endl;
            return PARSE_FAIL;
        }
    }

    void Parser::parse_whitespace()
    {
        char c;
        while(!isEnd() && isWhiteSpace(c = json[position])) position++;
    }

    void Parser::parse_value()
    {
        if(isEnd()){
            throw JsonException("Parse expect value");
            return;
        } 
        switch (json[position])
        {
            case 'n': parse_literal("null", _NULL); return;
            case 't': parse_literal("true", _TRUE); return;
            case 'f': parse_literal("false", _FALSE); return;
            case '\0': throw JsonException("Parse expect value"); return;
            default: parse_number(); return;
        }
    }

    void Parser::parse_literal(const string literal, Vtype type)
    {
        if( literal == json.substr(position, literal.length()) && \
        (position+literal.length() == json.length() || isWhiteSpace(json[position+literal.length()])))
        {
            position += literal.length();
            __val.type = type;
        }
        else throw JsonException("Parse invalid value!");
    }

    void Parser::parse_number()
    {
        size_t* idx = &position;
        if(json[position] == '-' || isDigit(json[position])){
            try
            {
                __val.num = std::stod(json.substr(position), idx);
                __val.type = _NUMBER;
            }
            catch(const std::exception& e)
            {
                throw JsonException("Parse invalid value!");
            }
        }
        else throw JsonException("Parse invalid value!");
    }
}

