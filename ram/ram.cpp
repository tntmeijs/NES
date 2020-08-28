#include "ram.hpp"

nes::RAM::RAM() :
	SIZE(2048),
	Memory(nullptr)
{}

void nes::RAM::Initialize()
{
	Memory = new std::uint8_t[SIZE];
}

void nes::RAM::Delete()
{
	if (Memory)
	{
		delete[] Memory;
		Memory = nullptr;
	}
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
