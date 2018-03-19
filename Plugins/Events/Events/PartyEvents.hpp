#pragma once

#include "API/Types.hpp"
//#include "API/Vector.hpp"
#include "API/CNWSFaction.hpp"
//#include "Common.hpp"
#include "Services/Hooks/Hooks.hpp"
#include "ViewPtr.hpp"

namespace Events {

class PartyEvents
{
public:
    PartyEvents(NWNXLib::ViewPtr<NWNXLib::Services::HooksProxy> hooker);

private:
        // For RequestSharedHook
        //static void InviteMemberHook
        // For ExclusiveHook
        //static int32_t InviteMemberHook
        static int32_t InviteMemberHook
        (
            // For RequestSharedHook
            //NWNXLib::Services::Hooks::CallType type, 
            NWNXLib::API::CNWSFaction* thisPtr, 
            NWNXLib::API::Types::ObjectID oidTarget, 
            NWNXLib::API::Types::ObjectID oidSender
        );
};

}
