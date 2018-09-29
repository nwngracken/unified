#include "Events/PartyEvents.hpp"
#include "API/CNWSFaction.hpp"
#include "API/Functions.hpp"
#include "API/Globals.hpp"
#include "Events.hpp"
#include "Utils.hpp"
#include "ViewPtr.hpp"

namespace Events {

using namespace NWNXLib;
using namespace NWNXLib::API;
using namespace NWNXLib::Services;


PartyEvents::PartyEvents(ViewPtr<Services::HooksProxy> hooker)
{
    hooker->RequestExclusiveHook<
        NWNXLib::API::Functions::CNWSFaction__InviteMember,
        int32_t,
        NWNXLib::API::CNWSFaction*,
        NWNXLib::API::Types::ObjectID,
        NWNXLib::API::Types::ObjectID
    >(PartyEvents::InviteMemberHook);
}

int32_t PartyEvents::InviteMemberHook
(
    NWNXLib::API::CNWSFaction* thisPtr,
    NWNXLib::API::Types::ObjectID oidTarget,
    NWNXLib::API::Types::ObjectID oidSender
)
{
    Events::PushEventData("TARGET_OBJECT_ID", NWNXLib::Utils::ObjectIDToString(oidTarget));
    Events::PushEventData("SENDER_OBJECT_ID", NWNXLib::Utils::ObjectIDToString(oidSender));

    Events::SignalEvent("NWNX_ON_INVITE_MEMBER", thisPtr->m_nFactionId);
    return 0;
}

}
