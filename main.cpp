#pragma once
#include "pch.h"

#include "ds3runtime/ds3runtime.h"
#include "ds3runtime/hooks/game_frame_hook.h"
#include "ds3runtime/hooks/session_receive_hook.h"
#include "ds3runtime/hooks/session_send_hook.h"
#include "ds3runtime/scripts/animation_id_handler.h"
#include <ds3runtime/hooks/play_animation_hook.h>
#include <ds3runtime/hooks/throw_hook.h>
#include <ds3runtime/scripts/hotkey_manager.h>
#include <ds3runtime/scripts/fmod_system_handler.h>
#include <ds3runtime/scripts/param_patcher.h>
#include <ds3runtime/boss/build_copy.h>
#include <ds3runtime/scripts/king_crimson_protections.h>
#include <ds3runtime/hooks/has_speffect_visual.h>
#include <ds3runtime/hooks/sprj_chr_damage_module_hook.h>
#include <ds3runtime/hooks/jmp_table_status.h>
#include <ds3runtime/ds3_debug_variables.h>
#include <ds3runtime/scripts/mod_p2p_filter.h>
#include <ds3runtime/modules/network_roll_patch/ds3_iframe_patch.h>
#include <ds3runtime/modules/network_roll_patch/attacker_effect_hook.h>
#include <ds3runtime/modules/network_roll_patch/hit_uuid_hook.h>
#include <ds3runtime/modules/network_roll_patch/hit_uuid_identify.h>
#include <ds3runtime/modules/network_roll_patch/hit_sibling_hook.h>
#include <ds3runtime/modules/network_roll_patch/hit_reg_hook.h>
#include <ds3runtime/modules/network_roll_patch/hit_reg_hook_shockwave.h>
#include <ds3runtime/modules/network_roll_patch/hit_delete.h>
#include <ds3runtime/modules/network_roll_patch/no_player_iframes.h>
#include <ds3runtime/modules/network_roll_patch/durablity_cost_hook.h>
#include <ds3runtime/modules/network_roll_patch/bullet_chr_hit_vfx_hook.h>
#include <ds3runtime/modules/network_roll_patch/bullet_hit_hierarchy_hook.h>
#include <ds3runtime/modules/elden_ring/position_calculate_hook.h>
#include <ds3runtime/modules/elden_ring/elden_ring_jump.h>
#include <ds3runtime/modules/elden_ring/backstab_angle_check.h>
#include <ds3runtime/hooks/time_since_last_frame.h>
#include <ds3runtime/modules/run_frame_test/run_frame_test.h>

using namespace ds3runtime;

std::shared_ptr<DS3RuntimeScripting> ds3runtime::ds3runtime_global;

static std::shared_ptr<spdlog::logger> createLogger()
{
    auto logger = std::make_shared<spdlog::logger>("DS3RuntimeScripting");

    logger->sinks().push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("DS3RuntimeScripting.log"));
    logger->set_level(spdlog::level::info);
    logger->flush_on(spdlog::level::info);

//#ifdef _DEBUG
    AllocConsole();
    FILE* stream;
    freopen_s(&stream, "CONOUT$", "w", stdout);
    freopen_s(&stream, "CONIN$", "r", stdin);

    logger->sinks().push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    logger->set_level(spdlog::level::debug);
//#endif

    return logger;
}

static bool attach()
{
    ds3runtime_global.reset(new DS3RuntimeScripting);
    spdlog::set_default_logger(createLogger());
    //DS3DebugVariables().setDebugMovementMultiplier(true);
    //DS3DebugVariables().setDebugAnimSpeedPlayer(true);
    ds3runtime_global->addHook(std::make_unique<GameFrameHook>());
    ds3runtime_global->addHook(std::make_unique<PlayAnimationHook>());
    ds3runtime_global->addHook(std::make_unique<TimeSinceLastFrameHook>());
    ds3runtime_global->runScript(std::make_unique<AnimationIdHandler>());
    ds3runtime_global->runScript(std::make_unique<RunFrameTest>());

    /*
    ds3runtime_global->addHook(std::make_unique<ThrowHook>());
    ds3runtime_global->runScript(std::make_unique<ParamPatcher>());
    ds3runtime_global->runScript(std::make_unique<AnimationIdHandler>());
    //ds3runtime_global->runScript(std::make_unique<eldenring::BackstabAngleCheck>());
    ds3runtime_global->addHook(std::make_unique<SessionReceiveHook>());
    ds3runtime_global->addHook(std::make_unique<SessionSendHook>());
    ds3runtime_global->addHook(std::make_unique<SprjChrDamageModuleHook>());
    ds3runtime_global->addHook(std::make_unique<JmpTableStatus>());
    ds3runtime_global->addHook(std::make_unique<eldenring::PositionCalculateHook>());
    ds3runtime_global->addHook(std::make_unique<PlayAnimationHook>());
    ds3runtime_global->runScript(std::make_unique<eldenring::EldenRingJump>());
    */

    /*
    ds3runtime_global->addHook(std::make_unique<ds3IFramePatch::HitBoxUUIDHook>());
    ds3runtime_global->addHook(std::make_unique<ds3IFramePatch::HitUUIDIdentifyHook>());
    ds3runtime_global->addHook(std::make_unique<ds3IFramePatch::HitBoxHierarchyHook>());
    ds3runtime_global->addHook(std::make_unique<ds3IFramePatch::HitRegHook>());
    ds3runtime_global->addHook(std::make_unique<ds3IFramePatch::HitRegHookShockwave>());
    ds3runtime_global->addHook(std::make_unique<ds3IFramePatch::HitBoxDeleteHook>());
    ds3runtime_global->addHook(std::make_unique<ds3IFramePatch::FixDurablityCost>());
    ds3runtime_global->addHook(std::make_unique<ds3IFramePatch::NoPlayerIFrames>());
    ds3runtime_global->addHook(std::make_unique<ds3IFramePatch::BulletChrHitVfxHook>());
    ds3runtime_global->addHook(std::make_unique<ds3IFramePatch::BulletHierarchyHook>());
    */

    //ds3runtime_global->runScript(std::make_unique<ds3IFramePatch::DS3IFramePatch>());



    //ds3runtime_global->runScript(std::make_unique<HotkeyManager>());
    //ds3runtime_global->runScript(std::make_unique<RollReleaseTest>());

    /*
    ds3runtime_global->addHook(std::make_unique<SessionReceiveHook>());
    ds3runtime_global->addHook(std::make_unique<SessionSendHook>());
    ds3runtime_global->runScript(std::make_unique<ModP2PFilter>());
   
    */

    /*
    
    ds3runtime_global->runScript(std::make_unique<JmpTableStatusReset>());
    ds3runtime_global->addHook(std::make_unique<JmpTableStatus>());
    
    ds3runtime_global->addHook(std::make_unique<ThrowHook>());
    
    ds3runtime_global->addHook(std::make_unique<SprjChrDamageModuleHook>());
    ds3runtime_global->runScript(std::make_unique<ParamPatcher>());
    ds3runtime_global->runScript(std::make_unique<FMODSystemHandler>());
    ds3runtime_global->runScript(std::make_unique<AnimationIdHandler>());
    */
    
    //ds3runtime_global->runScript(std::make_unique<BuildCopy>());
    //ds3runtime_global->runScript(std::make_unique<KingCrimsonProtections>());
    //ds3runtime_global->addHook(std::make_unique<DS1Backstabs>());
    //ds3runtime_global->runScript(std::make_unique<DS1PassivePoise>());

    /*
    ds3runtime_global->runScript(std::make_unique<DS1PassivePoise>());
    ds3runtime_global->addHook(std::make_unique<GameFrameHook>());
    ds3runtime_global->addHook(std::make_unique<ThrowHook>());
    ds3runtime_global->addHook(std::make_unique<PlayAnimationHook>());
    ds3runtime_global->addHook(std::make_unique<DS1Backstabs>());
    ds3runtime_global->addHook(std::make_unique<DS1NoHyperArmor>());
    ds3runtime_global->runScript(std::make_unique<ParamPatcher>());
    ds3runtime_global->runScript(std::make_unique<FMODSystemHandler>());
    */

    ds3runtime_global->attach();
    spdlog::info("Sucessfully loaded!");
    return true;
}

static bool detach()
{
    const bool result = ds3runtime::ds3runtime_global->detach();
    if (result) spdlog::info("Sucessfully unloaded!");
    else spdlog::info("Unable to unload.");
    return result;
}

BOOL APIENTRY DllMain(HMODULE, DWORD dwReason, LPVOID)
{
    switch (dwReason) {
    case DLL_PROCESS_ATTACH:
        return attach();
        break;
    case DLL_PROCESS_DETACH:
        return detach();
        break;
    }

    return TRUE;
}

