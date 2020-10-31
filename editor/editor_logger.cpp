#include "editor_logger.hpp"

#include <ctime>
#include <sstream>

nes::EditorLogger& nes::EditorLogger::GetInstance()
{
	static EditorLogger instance;
	return instance;
}

void nes::EditorLogger::LogInformation(std::string_view message) const
{
	for (const auto& callback : InformationCallbacks)
	{
		if (callback)
		{
			callback(AddTimestampToMessage(message));
		}
	}
}

void nes::EditorLogger::LogWarning(std::string_view message) const
{
	for (const auto& callback : WarningCallbacks)
	{
		if (callback)
		{
			callback(AddTimestampToMessage(message));
		}
	}
}

void nes::EditorLogger::LogError(std::string_view message) const
{
	for (const auto& callback : ErrorCallbacks)
	{
		if (callback)
		{
			callback(AddTimestampToMessage(message));
		}
	}
}

void nes::EditorLogger::AddInformationListener(const std::function<void(std::string_view)>& callback)
{
	InformationCallbacks.push_back(callback);
}

void nes::EditorLogger::AddWarningListener(const std::function<void(std::string_view)>& callback)
{
	WarningCallbacks.push_back(callback);
}

void nes::EditorLogger::AddErrorListener(const std::function<void(std::string_view)>& callback)
{
	ErrorCallbacks.push_back(callback);
}

std::string nes::EditorLogger::AddTimestampToMessage(std::string_view message) const
{
	auto now = std::time(0);
	auto* tm = std::localtime(&now);

	std::stringstream stream;
	stream << '[';
	stream << tm->tm_hour << ':' << tm->tm_min << ':' << tm->tm_sec;	// HH:MM:SS
	stream << ']';
	stream << '\t';
	stream << message;

	return stream.str();
}
