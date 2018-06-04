#include "Events/PartyEvents.hpp"
#include "API/CNWSFaction.hpp"
#include "API/Functions.hpp"
#include "API/Globals.hpp"
#include "Events.hpp"
#include "Utils.hpp"
#include "ViewPtr.hpp"
//#include "API/Vector.hpp"

namespace Events {

using namespace NWNXLib;
using namespace NWNXLib::API;
using namespace NWNXLib::Services;


PartyEvents::PartyEvents(ViewPtr<Services::HooksProxy> hooker)
{
    //hooker->RequestSharedHook<
    //hooker->RequestExclusiveHook<
    hooker->RequestExclusiveHook<
        NWNXLib::API::Functions::CNWSFaction__InviteMember,
        int32_t,
        NWNXLib::API::CNWSFaction*,
        NWNXLib::API::Types::ObjectID,
        NWNXLib::API::Types::ObjectID
    >(PartyEvents::InviteMemberHook);
}

// For RequestSharedHook
//void PartyEvents::InviteMemberHook
// For RequestExclusiveHook
//int32_t PartyEvents::InviteMemberHook
int32_t PartyEvents::InviteMemberHook
(
    //Services::Hooks::CallType type,
    NWNXLib::API::CNWSFaction* thisPtr,
    NWNXLib::API::Types::ObjectID oidTarget,
    NWNXLib::API::Types::ObjectID oidSender
)
{
    // For RequestSharedHook
    //const bool before = type == Services::Hooks::CallType::BEFORE_ORIGINAL;
    Events::PushEventData("TARGET_OBJECT_ID", NWNXLib::Utils::ObjectIDToString(oidTarget));
    Events::PushEventData("SENDER_OBJECT_ID", NWNXLib::Utils::ObjectIDToString(oidSender));

    // For RequestSharedHook
    //Events::SignalEvent(before ? "NWNX_ON_INVITE_MEMBER_BEFORE" : "NWNX_ON_INVITE_MEMBER_AFTER", thisPtr->m_nFactionId);
    // For RequestExclusive Hook
    //Events::SignalEvent("NWNX_ON_INVITE_MEMBER", thisPtr->m_nFactionId);
    //return 0;
    Events::SignalEvent("NWNX_ON_INVITE_MEMBER", thisPtr->m_nFactionId);
    return 0;
}

}
