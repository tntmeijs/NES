#include "rom_file.hpp"

#include <cstring>
#include <fstream>
#include <string>

bool nes::RomFile::LoadFromDisk(std::string_view path)
{
	std::ifstream rom(path.data(), std::ios_base::in | std::ios_base::binary);
	if (!rom.is_open())
	{
		return false;
	}

	// Determine file size
	rom.seekg(0, std::ios_base::end);
	size_t romSize = rom.tellg();
	rom.seekg(0, std::ios_base::beg);

	// Dump the file into memory
	RawData.resize(romSize, 0);
	rom.read(reinterpret_cast<char*>(RawData.data()), romSize);
	rom.close();

	return true;
}

bool nes::RomFile::IsValidRom() const
{
	std::uint8_t magicNumber[5];
	std::memcpy(magicNumber, RawData.data(), 5);

	return std::strcmp(reinterpret_cast<char*>(magicNumber), "NES^Z");
}

const std::vector<std::uint8_t>& nes::RomFile::GetRaw() const
{
	return RawData;
}

std::uint8_t nes::RomFile::GetNumberOfRomBanks() const
{
	return RawData[4];
}

std::uint8_t nes::RomFile::GetNumberOfVRomBanks() const
{
	return RawData[5];
}

std::uint8_t nes::RomFile::GetNumberOfRamBanks() const
{
	return RawData[8];
}

std::uint8_t nes::RomFile::GetRomMapperTypeId() const
{
	std::uint8_t lower	= (RawData[6] & 0xF0);
	std::uint8_t higher	= (RawData[7] & 0xF0);
	return (lower | (higher << 4));
}

nes::RomFile::MirroringType nes::RomFile::GetNametableMirroringType() const
{
	return (((RawData[6] & (1 << 0)) == 0) ? MirroringType::Horizontal : MirroringType::Vertical);
}

bool nes::RomFile::HasBatteryBackedPRGRam() const
{
	return ((RawData[6] & (1 << 1)) != 0);
}

bool nes::RomFile::HasTrainer() const
{
	return ((RawData[6] & (1 << 2)) != 0);
}

bool nes::RomFile::UseFourScreenVRam() const
{
	return ((RawData[6] & (1 << 3)) != 0);
}

bool nes::RomFile::IsVsSystem() const
{
	return ((RawData[7] & (1 << 0)) != 0);
}

bool nes::RomFile::IsPal() const
{
	return ((RawData[9] & (1 << 0)) != 0);
}
