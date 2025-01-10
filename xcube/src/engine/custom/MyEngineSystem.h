#ifndef __MY_ENGINE_H__
#define __MY_ENGINE_H__

#include "../EngineCommon.h"
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <filesystem> // include filesystem ͷ�ļ�
#include <vector>     // vector ���洢�ļ�·��
#include <functional> // std::function 



namespace fs = std::filesystem;  // need C++17 �ļ�ϵͳ��

class MyEngineSystem {
public:
    // ö�٣���־���� Enum log level
    enum LogLevel { INFO, WARNING, ERROR, CRITICAL, EASTER_EGG};

    MyEngineSystem();  // ���캯��
    ~MyEngineSystem(); // ��������

    //��ͬ�������־��¼ different levels of logging
    void LogInfo(const std::string& message);
    void LogWarning(const std::string& message);
    void LogError(const std::string& message);
    void ActivateEasterEgg();// Egg

    void LogCritical(const std::string& message); // �쳣����

    bool logMovement = false; // log player movement

    // ������־������
    void SetLogLevel(LogLevel level);
    LogLevel GetLogLevel() const;

private:
    // ��ǰ�����־����
    LogLevel currentLogLevel;

    // ��ȡ��ǰʱ���
    std::string GetTimeStampForLog(); 

    // Get current time ��ȡ��ǰ��ʱ��
    std::string GetCurrentTime();

    // ˽�з�������¼��־
    void Log(const std::string& message, LogLevel level);

    //��־��תlog rotate
    void RotateLogs();

    std::ofstream logFile; // ��־�ļ�
};

// �ṩһ��ȫ�ֵ���־�ӿ�
extern MyEngineSystem g_Logger;

#endif // __MY_ENGINE_H__
