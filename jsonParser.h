#ifndef JSONPARSER_H__
#define JSONPARSER_H__

#include <string>
#include "jsonValue.h"

using std::string;

namespace myjson{
    enum ParseResult{PARSE_FAIL = -1, PARSE_OK};

    class Parser{
        public:
            const string json;
            size_t position;
            
            Parser(const string json):json(json), position(0), __val(){}

            const BaseValue getValue(){return __val;}

            inline bool isEnd(){return position >= json.length();}
            int parse();
            void parse_whitespace();
            void parse_value();
            void parse_literal(const string literal, Vtype type);
            void parse_number();
        
        private:
            BaseValue __val;
            
    };

    

}


#endif