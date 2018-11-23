#pragma once

#include "Plugin.hpp"

namespace Tweaks {

class HideClassesOnCharList;
class PlayerDyingHitPointLimit;
class DisablePause;
class FixMasterServerDNS;
class CompareVarsForMerge;
class ParryAllAttacks;
class SneakAttackCritImmunity;
class PreserveDepletedItems;

class Tweaks : public NWNXLib::Plugin
{
public:
    Tweaks(const Plugin::CreateParams& params);
    virtual ~Tweaks();

private:
    std::unique_ptr<HideClassesOnCharList> m_HideClassesOnCharlist;
    std::unique_ptr<PlayerDyingHitPointLimit> m_PlayerDyingHitPointLimit;
    std::unique_ptr<DisablePause> m_DisablePause;
    std::unique_ptr<CompareVarsForMerge> m_CompareVarsForMerge;
    std::unique_ptr<ParryAllAttacks> m_ParryAllAttacks;
    std::unique_ptr<SneakAttackCritImmunity> m_SneakAttackCritImmunity;
    std::unique_ptr<PreserveDepletedItems> m_PreserveDepletedItems;
};

}
