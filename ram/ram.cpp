#include "ram.hpp"
#include "io/rom_file.hpp"

#include <algorithm>	// std::copy
#include <cstring>
#include <vector>

nes::RAM::RAM() :
	FIRST_ROM_BANK_ADDRESS(0x8000),
	SECOND_ROM_BANK_ADDRESS(FIRST_ROM_BANK_ADDRESS + RomFile::ROM_BANK_SIZE),
	STACK_START_ADDRESS(0x01FF)
{
	// Initialize the memory to a default known state of zero
	for (std::size_t i = 0; i < Memory.size(); ++i)
	{
		Memory[i].value = 0;
	}
}

nes::Byte nes::RAM::ReadByte(std::uint16_t address) const
{
	return Memory[address];
}

void nes::RAM::WriteByte(std::uint16_t address, Byte value)
{
	Memory[address] = value;
}

void nes::RAM::ClearByte(std::uint16_t address)
{
	Memory[address].value = 0;
}

void nes::RAM::StoreRomData(const RomFile& romFile)
{
	std::uint8_t numRomBanks = romFile.GetNumberOfRomBanks();

	// Retrieve the entire ROM as a byte array
	const std::vector<Byte>& romDataRef = romFile.GetRaw();

	auto firstBankStart = romFile.GetFirstRomBankByteIndex();
	auto firstBankStop = firstBankStart + RomFile::ROM_BANK_SIZE;

	// Always copy the first ROM bank to the memory array
	auto firstBankBegin = romDataRef.begin() + firstBankStart;
	auto firstBankEnd = romDataRef.begin() + firstBankStop;
	std::copy(firstBankBegin, firstBankEnd, &Memory[0] + FIRST_ROM_BANK_ADDRESS);

	if (numRomBanks == 1)
	{
		// If the game only uses one ROM bank, mirror the existing bank
		std::copy(firstBankBegin, firstBankEnd, &Memory[0] + SECOND_ROM_BANK_ADDRESS);
	}
	else
	{
		auto secondBankStart = romFile.GetSecondRomBankByteIndex();
		auto secondBankEnd = secondBankStart + RomFile::ROM_BANK_SIZE;

		// Copy the second ROM bank into memory
		std::copy(romDataRef.begin() + secondBankStart, romDataRef.begin() + secondBankEnd, &Memory[0] + SECOND_ROM_BANK_ADDRESS);
	}
}

std::size_t nes::RAM::GetSize() const
{
	return Memory.size();
}
