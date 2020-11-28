#include "editor_logger.hpp"

#include <ctime>
#include <iomanip>
#include <sstream>

nes::EditorLogger& nes::EditorLogger::GetInstance()
{
	static EditorLogger instance;
	return instance;
}

void nes::EditorLogger::LogInformation(std::string_view message) const
{
	Log(message, InformationCallbacks);
}

void nes::EditorLogger::LogWarning(std::string_view message) const
{
	Log(message, WarningCallbacks);
}

void nes::EditorLogger::LogError(std::string_view message) const
{
	Log(message, ErrorCallbacks);
}

void nes::EditorLogger::LogCpu(std::string_view message) const
{
	Log(message, CpuCallbacks);
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

void nes::EditorLogger::AddCpuListener(const std::function<void(std::string_view)>& callback)
{
	CpuCallbacks.push_back(callback);
}

void nes::EditorLogger::AddAnyListener(const std::function<void(std::string_view)>& callback)
{
	AddInformationListener(callback);
	AddWarningListener(callback);
	AddErrorListener(callback);
	AddCpuListener(callback);
}

void nes::EditorLogger::Log(std::string_view message, const std::vector<std::function<void(std::string_view)>>& callbacks) const
{
	for (const auto& callback : callbacks)
	{
		if (callback)
		{
			callback(AddTimestampToMessage(message));
		}
	}
}

std::string nes::EditorLogger::AddTimestampToMessage(std::string_view message) const
{
	auto now = std::time(0);
	auto* tm = std::localtime(&now);

	std::stringstream stream;
	stream << '[';
	stream << tm->tm_hour << ':' << tm->tm_min << ':' << std::setw(2) << std::setfill('0') << tm->tm_sec;
	stream << ']';
	stream << '\t';
	stream << message;

	return stream.str();
}
