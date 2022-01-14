/*
	* DS3RuntimeScripting
	* Contributers: Amir
*/

#pragma once
#include "pch.h"
#include "hit_uuid_hook.h"
#include "ds3runtime/ds3runtime.h"
#include "ds3_iframe_patch.h"
#include "ds3runtime/world_chr_man.h"
#include "ds3runtime/player_ins.h"

namespace ds3runtime::ds3IFramePatch {

HitBoxUUIDHook::HitBoxUUIDHook()
	: Hook(0x140832500, (uintptr_t)onHitBoxStructCreate, { "ds3_iframe_patch" })
{
	instance = this;
}

bool HitBoxUUIDHook::onHitBoxStructCreate(uintptr_t hitBoxAddress, uintptr_t unk0, uintptr_t unk1, uintptr_t hitBoxOwnerIns, uintptr_t unk2, uintptr_t unk3, uintptr_t unk4, uintptr_t unk5, uintptr_t unk6)
{
	bool (*originalFunction)(...);
	*(uintptr_t*)&originalFunction = *instance->original;
	
	//Check if hitbox owner is the local player or bullet of the hitbox is owned by the local player
	if (WorldChrMan::hasInstance() && PlayerIns::isMainChrLoaded() && hitBoxOwnerIns == PlayerIns::getMainChrAddress()) {
		DS3IFramePatch* ds3IFramePatch = (DS3IFramePatch*)ds3runtime_global->accessScript("ds3_iframe_patch");
		ds3IFramePatch->registerOutgoingHitBox(hitBoxAddress, static_cast<uint32_t>(PlayerIns::Handle::MainChr));
	} else if (WorldChrMan::hasInstance() && PlayerIns::isMainChrLoaded()
		&& *(uintptr_t*)hitBoxOwnerIns == 0x14287AC18 
		&& *(uint32_t*)(hitBoxOwnerIns + 0xB98) == (uint32_t)PlayerIns::Handle::MainChr) {
		DS3IFramePatch* ds3IFramePatch = (DS3IFramePatch*)ds3runtime_global->accessScript("ds3_iframe_patch");
		ds3IFramePatch->registerOutgoingHitBox(hitBoxAddress, *accessMultilevelPointer<int32_t>(hitBoxOwnerIns + 8));
	}

	return originalFunction(hitBoxAddress, unk0, unk1, hitBoxOwnerIns, unk2, unk3, unk4, unk5, unk6);
}

HitBoxUUIDHook* HitBoxUUIDHook::instance = nullptr;

}