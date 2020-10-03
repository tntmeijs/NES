#include "ram.hpp"
#include "io/rom_file.hpp"

#include <algorithm>	// std::copy
#include <cstring>
#include <vector>

nes::RAM::RAM() :
	FIRST_ROM_BANK_ADDRESS(0x8000),
	SECOND_ROM_BANK_ADDRESS(FIRST_ROM_BANK_ADDRESS + RomFile::ROM_BANK_SIZE),
	STACK_START_ADDRESS(0x01FF),
	Memory(nullptr),
	Size(0)
{}

void nes::RAM::Initialize(std::uint32_t size)
{
	Size = size;

	Memory = new std::uint8_t[Size];
	std::memset(Memory, 0, Size);
}

void nes::RAM::Delete()
{
	if (Memory)
	{
		delete[] Memory;
		Memory = nullptr;
	}
}

void nes::RAM::Clear()
{
	Delete();
	Initialize(Size);
}

const std::uint8_t nes::RAM::ReadByte(std::uint16_t address) const
{
	return Memory[address];
}

void nes::RAM::WriteByte(std::uint16_t address, std::uint8_t value)
{
	Memory[address] = value;
}

std::uint8_t* const nes::RAM::GetRaw() const
{
	return Memory;
}

void nes::RAM::StoreRomData(const RomFile& romFile)
{
	std::uint8_t numRomBanks = romFile.GetNumberOfRomBanks();

	// Retrieve the entire ROM as a byte array
	const std::vector<std::uint8_t>& romDataRef = romFile.GetRaw();

	// Always copy the first ROM bank to the memory array
	std::uint16_t firstBankStart = romFile.GetFirstRomBankByteIndex();
	std::uint16_t firstBankEnd = firstBankStart + RomFile::ROM_BANK_SIZE;
	std::copy(romDataRef.begin() + firstBankStart, romDataRef.begin() + firstBankEnd, Memory + FIRST_ROM_BANK_ADDRESS);

	if (numRomBanks == 1)
	{
		// If the game only uses one ROM bank, mirror the first ROM bank
		std::copy(romDataRef.begin() + firstBankStart, romDataRef.begin() + firstBankEnd, Memory + SECOND_ROM_BANK_ADDRESS);
	}
	else
	{
		// Copy the second ROM bank to the memory array
		std::uint16_t secondBankStart = romFile.GetSecondRomBankByteIndex();
		std::uint16_t secondBankEnd = secondBankStart + RomFile::ROM_BANK_SIZE;
		std::copy(romDataRef.begin() + secondBankStart, romDataRef.begin() + secondBankEnd, Memory + SECOND_ROM_BANK_ADDRESS);
	}
}
