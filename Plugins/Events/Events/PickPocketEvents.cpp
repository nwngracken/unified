#include "Events/PickPocketEvents.hpp"
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


PickPocketEvents::PickPocketEvents(ViewPtr<Services::HooksProxy> hooker)
{
    hooker->RequestExclusiveHook<
        NWNXLib::API::Functions::CNWSCreature__AddPickPocketActions,
        int32_t,
        NWNXLib::API::CNWSFaction*,
        NWNXLib::API::Types::ObjectID
    >(PickPocketEvents::AddPickPocketActionsHook);
}

int32_t PickPocketEvents::InviteMemberHook
(
    NWNXLib::API::CNWSFaction* thisPtr,
    NWNXLib::API::Types::ObjectID oidTarget
)
{
    Events::PushEventData("TARGET_OBJECT_ID", NWNXLib::Utils::ObjectIDToString(oidTarget));

    Events::SignalEvent("NWNX_ON_ADD_PICK_POCKET_ACTIONS", thisPtr->m_nFactionId);
    return 0;
}

}
