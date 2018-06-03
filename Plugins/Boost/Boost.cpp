#include "Boost.hpp"
#include <boost/functional/hash.hpp>

using namespace NWNXLib;

static ViewPtr<Boost::Boost> g_plugin;

NWNX_PLUGIN_ENTRY Plugin::Info* PluginInfo()
{
    return new Plugin::Info
    {
        "Boost",
        "Provides Boost C++ library functionality",
        "gracken",
        "nwngracken@gmail.com",
        1,
        true
    };
}

NWNX_PLUGIN_ENTRY Plugin* PluginLoad(Plugin::CreateParams params)
{
    g_plugin = new Boost::Boost(params);
    return g_plugin;
}

//using namespace NWNXLib::API;
//using namespace NWNXLib::Services;

namespace Boost {

Boost::Boost(const Plugin::CreateParams& params)
    : Plugin(params)
{

#define REGISTER(func) \
    GetServices()->m_events->RegisterEvent(#func, std::bind(&Boost::func, this, std::placeholders::_1))

    REGISTER(Hash);

#undef REGISTER
}

Boost::~Boost()
{
}

ArgumentStack Boost::Hash(ArgumentStack&& args)
{
    ArgumentStack stack;
    const auto str = Services::Events::ExtractArgument<std::string>(args);

    boost::hash<std::string> string_hash;
    std::uint32_t iOut = string_hash(str);

    Services::Events::InsertArgument(stack, iOut);
    return stack;
}

}
