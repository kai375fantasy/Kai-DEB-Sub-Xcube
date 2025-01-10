#include "MyEngineSystem.h"
#include <iomanip>  // for std::put_time
#include <sstream>  // for std::ostringstream
#include <chrono>   // for std::chrono::system_clock
#include <ctime>    // for std::localtime
#include <filesystem> // for handling files and directories
#include <iostream>




namespace fs = std::filesystem;  // ʹ�� C++17 �ļ�ϵͳ��

// ����ȫ�ֵ� MyEngineSystem ʵ��
MyEngineSystem g_Logger;

// ���������־�ļ�����
const size_t MAX_LOG_FILES = 5;

// ��ȡ��ǰʱ�������ʽ��Ϊ yyyy-mm-dd_hh-mm-ss
std::string MyEngineSystem::GetTimeStampForLog() {
    auto now = std::chrono::system_clock::now();
    std::time_t timeNow = std::chrono::system_clock::to_time_t(now);
    std::tm* tmNow = std::localtime(&timeNow);
    std::ostringstream oss;
    oss << std::put_time(tmNow, "%Y-%m-%d_%H-%M-%S");  // ��ʽ��Ϊ "yyyy-mm-dd_hh-mm-ss"
    return oss.str();
}

// ��鲢ִ����־��ת���������µ� 5 ����־�ļ�
void MyEngineSystem::RotateLogs() {
    const std::string logDir = "logs";

    // �����־�ļ��в����ڣ������ļ���
    if (!fs::exists(logDir)) {
        fs::create_directory(logDir);
    }

    // ��ȡ������־�ļ�����ʱ������
    std::vector<fs::path> logFiles;
    for (const auto& entry : fs::directory_iterator(logDir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            logFiles.push_back(entry.path());
        }
    }

    // ���ļ��޸�ʱ�����򣨴���ɵ����£�
    std::sort(logFiles.begin(), logFiles.end(),
        [](const fs::path& a, const fs::path& b) {
            return fs::last_write_time(a) < fs::last_write_time(b);
        });

    // �����־�ļ������������ƣ�ɾ����ɵ��ļ�
    while (logFiles.size() > MAX_LOG_FILES - 1) { // ����һ��λ�ø����ļ�
        try {
            std::cout << "Removing old log file: " << logFiles.front() << std::endl;
            fs::remove(logFiles.front()); // ɾ����ɵ���־�ļ�
            logFiles.erase(logFiles.begin()); // ���б����Ƴ�
        }
        catch (const std::exception& e) {
            std::cerr << "Failed to remove old log file: " << logFiles.front() << " - " << e.what() << std::endl;
            break;
        }
    }
}


// ���캯��������־�ļ�
MyEngineSystem::MyEngineSystem() {
    static bool isInitialized = false; // ��̬��������¼�Ƿ��Ѿ���ʼ��

    if (isInitialized) {
        std::cout << "MyEngineSystem Constructor Called Again (Skipped)" << std::endl;
        return; // ����Ѿ���ʼ����ֱ�ӷ���
    }

    isInitialized = true; // ����Ϊ�ѳ�ʼ��

    std::cout << "MyEngineSystem Constructor Called" << std::endl;

    RotateLogs(); // ������־��תϵͳ

    std::string logFileName = "logs/MyEngineLog_" + GetTimeStampForLog() + ".txt";

    logFile.open(logFileName, std::ios::out);
    if (!logFile) {
        std::cerr << "Failed to open log file: " << logFileName << std::endl;
    }
    else {
        logFile << "Log file created successfully: " << logFileName << std::endl;
        std::cout << "Log file created: " << logFileName << std::endl;
    }
}

// �����������ر���־�ļ�
MyEngineSystem::~MyEngineSystem() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

std::string MyEngineSystem::GetCurrentTime() {
    auto now = std::chrono::system_clock::now();  // ��ȡ��ǰʱ�� Get current time
    std::time_t timeNow = std::chrono::system_clock::to_time_t(now);  // ת��Ϊʱ��� Convert to timestamp

    std::tm* tmNow = std::localtime(&timeNow);  // ��ȡ��ǰ����ʱ�� Get current local time
    std::ostringstream oss;
    oss << std::put_time(tmNow, "%Y-%m-%d %H:%M:%S");  // ��ʽ��ʱ��Formatting time
    return oss.str();
}

// ������־���˼���
void MyEngineSystem::SetLogLevel(LogLevel level) {
    currentLogLevel = level;
    LogInfo("Log level set to " + std::to_string(level)); // ��¼�������
}

// ��ȡ��ǰ��־���˼���
MyEngineSystem::LogLevel MyEngineSystem::GetLogLevel() const {
    return currentLogLevel;
}


// ˽�з�������¼��־
void MyEngineSystem::Log(const std::string& message, LogLevel level) {
    // ������־�������־������ڵ�ǰ���ã���ֱ�ӷ���
    if (level < currentLogLevel) {
        return; // ������־
    }
    
    std::string levelStr;
    switch (level) {
    case INFO: levelStr = "[INFO]"; break;
    case WARNING: levelStr = "[WARNING]"; break;
    case ERROR: levelStr = "[ERROR]"; break;
    case EASTER_EGG: levelStr = "[EASTER_EGG]"; break;
    }

    std::string timeStr = GetCurrentTime();  // ��ȡʱ���
    std::string logMessage = timeStr + " " + levelStr + " " + message;  // ��ʱ�������־��Ϣƴ��

    std::cout << logMessage << std::endl;  // ���������̨
    if (logFile.is_open()) {
        logFile << logMessage << std::endl;  // д����־�ļ�
    }
}

// ���з�������¼��ͬ�������־
void MyEngineSystem::LogInfo(const std::string& message) {
    Log(message, INFO);
}

void MyEngineSystem::LogWarning(const std::string& message) {
    Log(message, WARNING);
}

void MyEngineSystem::LogError(const std::string& message) {
    Log(message, ERROR);
}

// �����ڲʵ�
void MyEngineSystem::ActivateEasterEgg() {
    Log("Kai-Qian-CI517-2024", EASTER_EGG);
}

// ������������¼ CRITICAL �������־
void MyEngineSystem::LogCritical(const std::string& message) {
    Log(message, CRITICAL);
}

