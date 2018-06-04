#include "nwnx"

int NWNX_Boost_Hash(string str);

int NWNX_Boost_Hash(string str)
{
    string sFunc = "Hash";

    NWNX_PushArgumentString("NWNX_Boost", "Hash", str);
    NWNX_CallFunction("NWNX_Boost", "Hash");
    return NWNX_GetReturnValueInt("NWNX_Boost", "Hash");
}
