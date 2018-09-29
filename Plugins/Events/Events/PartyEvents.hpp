#pragma once

#include "API/Types.hpp"
#include "API/CNWSFaction.hpp"
#include "Services/Hooks/Hooks.hpp"
#include "ViewPtr.hpp"

namespace Events {

class PartyEvents
{
public:
    PartyEvents(NWNXLib::ViewPtr<NWNXLib::Services::HooksProxy> hooker);

private:
        static int32_t InviteMemberHook
        (
            NWNXLib::API::CNWSFaction* thisPtr, 
            NWNXLib::API::Types::ObjectID oidTarget, 
            NWNXLib::API::Types::ObjectID oidSender
        );
};

}
