#ifndef MYJSON_H__
#define MYJSON_H__

#include <string>

namespace myjson{
    enum Vtype{_NULL, _FALSE, _TRUE, _NUMBER, _STRING, _ARRAY, _OBJECT};
    enum {PARSE_OK = 0, PARSE_EXPECT_VALUE, PARSE_INVALID_VALUE, PARSE_ROOT_NOT_SINGULAR};
    class Item{
        public:
            Vtype type;
            Item(){type = _NULL;}
    };

    int parse(Item v, const std::string json);
    Vtype get_type(const Item v);
}


#endif