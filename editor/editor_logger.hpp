#ifndef NES_EDITOR_LOGGER_HPP
#define NES_EDITOR_LOGGER_HPP

#include <functional>
#include <string>
#include <string_view>
#include <vector>

namespace nes
{
    /**
     * Singleton logging class that allows other classes to log to the editor
     */
    class EditorLogger final
    {
    public:
        /**
         * Singleton pattern
         * @return  Editor logger instance
         */
        static EditorLogger& GetInstance();

    public:
		EditorLogger(const EditorLogger&) = delete;
		EditorLogger(EditorLogger&&) = delete;
		EditorLogger& operator=(const EditorLogger&) = delete;
		EditorLogger&& operator=(EditorLogger&&) = delete;

        /**
         * Log to the information channel
         * @param   message     Message to log
         */
        void LogInformation(std::string_view message) const;

        /**
         * Log to the warning channel
         * @param   message     Message to log
         */
        void LogWarning(std::string_view message) const;

        /**
         * Log to the error channel
         * @param   message     Message to log
         */
        void LogError(std::string_view message) const;

        /**
         * Log to the cpu channel
         * @param   message     Message to log
         */
        void LogCpu(std::string_view message) const;

        /**
         * Register a callback to the information channel
         * @param   callback    Callback to register
         */
        void AddInformationListener(const std::function<void(std::string_view)>& callback);

        /**
         * Register a callback to the warning channel
         * @param   callback    Callback to register
         */
        void AddWarningListener(const std::function<void(std::string_view)>& callback);

        /**
         * Register a callback to the error channel
         * @param   callback    Callback to register
         */
        void AddErrorListener(const std::function<void(std::string_view)>& callback);

        /**
         * Register a callback to the error channel
         * @param   callback    Callback to register
         */
        void AddCpuListener(const std::function<void(std::string_view)>& callback);

        /**
         * Register a callback to every channel available
         * @param   callback    Callback to register
         */
        void AddAnyListener(const std::function<void(std::string_view)>& callback);

    private:
        EditorLogger() = default;
		~EditorLogger() noexcept = default;

    private:
        /**
         * Helper function to log messages to a channel
         * @param   message     Message to log
         * @param   callbacks   Callbacks to call with the message
         */
        void Log(std::string_view message, const std::vector<std::function<void(std::string_view)>>& callbacks) const;

        /**
         * Helper function to construct a message with a timestamp
         * @param   message     Message to add the timestamp to
         * @return  Message with a timestamp added in front of it
         */
        std::string AddTimestampToMessage(std::string_view message) const;

    private:
		std::vector<std::function<void(std::string_view)>> InformationCallbacks;
		std::vector<std::function<void(std::string_view)>> WarningCallbacks;
		std::vector<std::function<void(std::string_view)>> ErrorCallbacks;
		std::vector<std::function<void(std::string_view)>> CpuCallbacks;
    };
}

#endif //! NES_EDITOR_LOGGER_HPP
