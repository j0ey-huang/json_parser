#ifndef JSONVALUE_H__
#define JSONVALUE_H__

#include <string>
#include "jsonException.h"

using std::string;

namespace myjson{

    enum Vtype{_NULL, _FALSE, _TRUE, _NUMBER, _STRING, _ARRAY, _OBJECT};

    class BaseValue{
            public:
                Vtype type;
                BaseValue(){type = _NULL;}
        };

        class NumberValue : public BaseValue{
            public:
                double num;
        };

        class StringValue : public BaseValue{
            public:
                string str;
        };
}

#endif