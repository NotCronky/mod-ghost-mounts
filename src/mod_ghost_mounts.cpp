#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Log.h"

#define RemoveMount NULL

namespace mod_ghost_mounts
{
    constexpr uint32 DEFAULT_ALLIANCE_GROUND = 2404;
    constexpr uint32 DEFAULT_ALLIANCE_FLYING = 17697;
    constexpr uint32 DEFAULT_HORDE_GROUND = 2327;
    constexpr uint32 DEFAULT_HORDE_FLYING = 17699;

    constexpr float DEFAULT_SPEED_20_39 = 1.6f;
    constexpr float DEFAULT_SPEED_40_59 = 2.0f;
    constexpr float DEFAULT_SPEED_60_69 = 2.5f;
    constexpr float DEFAULT_SPEED_70_80 = 4.1f;

    constexpr float DEFAULT_FLY_SPEED_60_69 = 2.5f;
    constexpr float DEFAULT_FLY_SPEED_70_80 = 3.1f;

    bool IsFlyingAllowedMap(uint32 mapId)
    {
        return (mapId == 530 || mapId == 571);
    }

    struct GhostMountPlayerScript : public PlayerScript
    {
        GhostMountPlayerScript() : PlayerScript("GhostMountPlayerScript"), m_normalFlySpeed(2.5f) {}

        float m_normalFlySpeed;

        void OnPlayerReleasedGhost(Player* player) override
        {
            uint8 level = player->GetLevel();
            uint32 mapId = player->GetMapId();
            bool canFly = IsFlyingAllowedMap(mapId);

            uint32 displayId = 0;

            if (player->GetTeamId() == TEAM_ALLIANCE)
            {
                displayId = canFly ? sConfigMgr->GetOption<uint32>("GhostMount.Alliance.Flying", DEFAULT_ALLIANCE_FLYING)
                    : sConfigMgr->GetOption<uint32>("GhostMount.Alliance.Ground", DEFAULT_ALLIANCE_GROUND);
            }
            else
            {
                displayId = canFly ? sConfigMgr->GetOption<uint32>("GhostMount.Horde.Flying", DEFAULT_HORDE_FLYING)
                    : sConfigMgr->GetOption<uint32>("GhostMount.Horde.Ground", DEFAULT_HORDE_GROUND);
            }


            float speed = 1.0f;
            if (level >= 20 && level <= 39)
                speed = sConfigMgr->GetOption<float>("GhostMount.Speed.20-39", DEFAULT_SPEED_20_39);
            else if (level >= 40 && level <= 59)
                speed = sConfigMgr->GetOption<float>("GhostMount.Speed.40-59", DEFAULT_SPEED_40_59);
            else if (level >= 60 && level <= 69)
                speed = sConfigMgr->GetOption<float>("GhostMount.Speed.60-69", DEFAULT_SPEED_60_69);
            else if (level >= 70)
                speed = sConfigMgr->GetOption<float>("GhostMount.Speed.70-80", DEFAULT_SPEED_70_80);

            float flySpeed = 1.0f;
            if (level >= 60 && level <= 69)
                flySpeed = sConfigMgr->GetOption<float>("GhostMount.FlySpeed.60-69", DEFAULT_FLY_SPEED_60_69);
            else if (level >= 70)
                flySpeed = sConfigMgr->GetOption<float>("GhostMount.FlySpeed.70-80", DEFAULT_FLY_SPEED_70_80);

            if (level < 20)
                return;

            if (player->IsAlive())
            {
                m_normalFlySpeed = player->GetSpeed(MOVE_FLIGHT);
            }

            player->SetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID, displayId);
            player->SetUInt32Value(UNIT_FIELD_DISPLAYID, RemoveMount);

            if (canFly)
            {
                player->SetCanFly(true);
                player->SetSpeed(MOVE_FLIGHT, flySpeed, true);
            }
            player->SetSpeed(MOVE_RUN, speed, true);
        }

        void OnPlayerResurrect(Player* player, float /*restore_percent*/, bool /*applySickness*/) override
        {
            player->SetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID, RemoveMount);
            player->SetUInt32Value(UNIT_FIELD_DISPLAYID, RemoveMount);

            player->InitDisplayIds();

            player->SetCanFly(false);
            player->SetSpeed(MOVE_FLIGHT, m_normalFlySpeed, true);
            player->SetSpeed(MOVE_RUN, 1.0f, true);
        }
    };
}

void Addmod_ghost_mountsScripts()
{
    new mod_ghost_mounts::GhostMountPlayerScript();
}
