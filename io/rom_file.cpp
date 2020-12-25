#include "rom_file.hpp"
#include "editor/editor_logger.hpp"

#include <cstring>
#include <fstream>
#include <string>

bool nes::RomFile::LoadFromDisk(std::string_view path)
{
	std::size_t extensionStart = path.find_last_of('.');
	std::string_view extension = path.substr(extensionStart);

	if (extension != ".nes")
	{
		EditorLogger::GetInstance().LogError("Invalid file extension.");
		return false;
	}

	std::ifstream rom(path.data(), std::ios_base::in | std::ios_base::binary);
	if (!rom.is_open())
	{
		EditorLogger::GetInstance().LogError("Unable to open ROM");
		return false;
	}

	// Determine file size
	rom.seekg(0, std::ios_base::end);
	size_t romSize = rom.tellg();
	rom.seekg(0, std::ios_base::beg);

	// Dump the file into memory
	RawData.resize(romSize, Byte());
	rom.read(reinterpret_cast<char*>(RawData.data()), romSize);
	rom.close();

	EditorLogger::GetInstance().LogInformation("ROM banks dumped into RAM");

	return true;
}

bool nes::RomFile::IsValidRom() const
{
	if (RawData.empty())
	{
		return false;
	}

	std::uint8_t magicNumber[5];
	std::memcpy(magicNumber, RawData.data(), 5);

	return std::strcmp(reinterpret_cast<char*>(magicNumber), "NES^Z");
}

const std::vector<nes::Byte>& nes::RomFile::GetRaw() const
{
	return RawData;
}

std::uint8_t nes::RomFile::GetNumberOfRomBanks() const
{
	return RawData[4].value;
}

std::uint8_t nes::RomFile::GetNumberOfVRomBanks() const
{
	return RawData[5].value;
}

std::uint8_t nes::RomFile::GetNumberOfRamBanks() const
{
	return RawData[8].value;
}

std::uint8_t nes::RomFile::GetRomMapperTypeId() const
{
	std::uint8_t lower	= (RawData[6].value & 0xF0);
	std::uint8_t higher	= (RawData[7].value & 0xF0);
	return (lower | (higher << 4));
}

nes::RomFile::MirroringType nes::RomFile::GetNametableMirroringType() const
{
	return ((RawData[6].bit0 == 0) ? MirroringType::Horizontal : MirroringType::Vertical);
}

bool nes::RomFile::HasBatteryBackedPRGRam() const
{
	return (RawData[6].bit1 != 0);
}

bool nes::RomFile::HasTrainer() const
{
	return (RawData[6].bit2 != 0);
}

bool nes::RomFile::UseFourScreenVRam() const
{
	return (RawData[6].bit3 != 0);
}

bool nes::RomFile::IsVsSystem() const
{
	return (RawData[7].bit0 != 0);
}

bool nes::RomFile::IsPal() const
{
	return (RawData[9].bit0 != 0);
}

std::uint16_t nes::RomFile::GetFirstRomBankByteIndex() const
{
	// The first ROM bank starts at the 16th byte
	std::uint16_t startIndex = 16;

	if (HasTrainer())
	{
		// Skip the trainer
		startIndex += ROM_TRAINER_SIZE;

		EditorLogger::GetInstance().LogInformation("Trainer detected");
	}
	else
	{
		EditorLogger::GetInstance().LogInformation("No trainer detected");
	}

	return startIndex;
}

std::uint16_t nes::RomFile::GetSecondRomBankByteIndex() const
{
	// The second bank comes right after the first index
	std::uint16_t firstBankIndex = GetFirstRomBankByteIndex();
	return firstBankIndex + ROM_BANK_SIZE;
}
