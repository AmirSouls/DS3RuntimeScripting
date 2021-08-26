#pragma once
#include "pch.h"
#include "player_game_data.h"
#include "databaseaddress.h"
#include "memory_util.h"

namespace ds3runtime {

PlayerGameData::PlayerGameData(uintptr_t address)
{
	this->address = address;
}

int32_t PlayerGameData::getPlayerNo() const
{
	return *accessMultilevelPointer<int32_t>(address + 0x10);
}

PlayerGameData::Voice PlayerGameData::getVoice() const
{
	return static_cast<Voice>(*accessMultilevelPointer<uint8_t>(address + 0xAB));
}

void PlayerGameData::setVoice(const Voice& voice)
{
	*accessMultilevelPointer<uint8_t>(address + 0xAB) = static_cast<uint8_t>(voice);
}

PlayerGameData::Class PlayerGameData::getClass() const
{
	return static_cast<Class>(*accessMultilevelPointer<uint8_t>(address + 0xAE));
}

void PlayerGameData::setClass(const Class& chrClass)
{
	*accessMultilevelPointer<uint8_t>(address + 0xAE) = static_cast<uint8_t>(chrClass);
}

PlayerGameData::Gender PlayerGameData::getGender() const
{
	return (Gender)*accessMultilevelPointer<uint8_t>(address + 0xAA);
}

void PlayerGameData::setGender(const Gender& gender)
{
	*accessMultilevelPointer<uint8_t>(address + 0xAA) = static_cast<uint8_t>(gender);
}

PlayerGameData::Age PlayerGameData::getAge() const
{
	return static_cast<Age>(*accessMultilevelPointer<uint8_t>(address + 0x6B8));
}

void PlayerGameData::setAge(const Age& age)
{
	*accessMultilevelPointer<uint8_t>(address + 0x6B8) = static_cast<uint8_t>(age);
}

Attributes PlayerGameData::getAttributes() const
{
	return *reinterpret_cast<Attributes*>(accessMultilevelPointer<uintptr_t>(address + 0x44));
}

void PlayerGameData::setAttributes(const Attributes& attributes)
{
	*reinterpret_cast<Attributes*>(accessMultilevelPointer<uintptr_t>(address + 0x44)) = attributes;
}

std::wstring PlayerGameData::getName() const
{
	return std::wstring(accessMultilevelPointer<wchar_t>(address + 0x88));
}

void PlayerGameData::setName(const std::wstring& name)
{
	wchar_t* namePointer = accessMultilevelPointer<wchar_t>(address + 0x88);
	memset(namePointer, 0, 16);
	memcpy(namePointer, name.c_str(), name.length() * 2);
}

PlayerGameData::Covenant PlayerGameData::getCovenant() const
{
	return static_cast<Covenant>(*accessMultilevelPointer<uint32_t>(address + 0xF7));
}

void PlayerGameData::setCovenant(const Covenant& covenant)
{
	*accessMultilevelPointer<uint32_t>(address + 0xF7) = static_cast<uint32_t>(covenant);
}

PlayerGameData::InvadeType PlayerGameData::getInvadeType() const
{
	return static_cast<InvadeType>(*accessMultilevelPointer<uint32_t>(address + 0xFC));
}

void PlayerGameData::setInvadeType(const PlayerGameData::InvadeType& invadeType)
{
	*accessMultilevelPointer<uint32_t>(address + 0xFC) = (uint32_t)invadeType;
}

uintptr_t PlayerGameData::getEquipGameData()
{
	return address + 0x228;
}

uint16_t PlayerGameData::getWeaponSheathData() const
{
	uint16_t(*function)(uintptr_t);
	*reinterpret_cast<uintptr_t*>(&function) = 0x1409EBA70;
	return function(address + 0x2B8);
}

int32_t PlayerGameData::getRightHandSlot() const
{
	return *accessMultilevelPointer<int32_t>(address + 0x2BC);
}

void PlayerGameData::setRightHandSlot(const int32_t& slot)
{
	*accessMultilevelPointer<int32_t>(address + 0x2BC) = slot;
}

int32_t PlayerGameData::getLeftHandSlot() const
{
	return *accessMultilevelPointer<int32_t>(address + 0x2C0);
}

void PlayerGameData::setLeftHandSlot(const int32_t& slot)
{
	*accessMultilevelPointer<int32_t>(address + 0x2C0) = slot;
}

int32_t PlayerGameData::getWeaponSheathState() const
{
	return *accessMultilevelPointer<int32_t>(address + 0x2B8);
}

void PlayerGameData::setWeaponSheathState(const int32_t& slot)
{
	*accessMultilevelPointer<int32_t>(address + 0x2B8) = slot;
}

}
