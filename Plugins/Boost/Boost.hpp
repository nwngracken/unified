#pragma once

#include "Plugin.hpp"
#include "Services/Events/Events.hpp"

using ArgumentStack = NWNXLib::Services::Events::ArgumentStack;

namespace Boost {

class Boost : public NWNXLib::Plugin
{
public:
    Boost(const Plugin::CreateParams& params);
    virtual ~Boost();

private:
    ArgumentStack Hash (ArgumentStack&& args);

};

}
