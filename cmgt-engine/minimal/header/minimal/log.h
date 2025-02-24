#ifndef LOG_H
#define LOG_H
#pragma once
#include <filesystem>
#include <iostream>
#include <vector>
#include <mutex>
#include <string>
#include <fstream>
#include <chrono>
#include "types.h"
#include "paths.h"
namespace cmgt {
    namespace fs = std::filesystem;
    class Log {
    private:
        inline static std::ofstream _stream;
        inline static std::vector<std::string> _buffer;
        inline static std::mutex _log_lock;
        inline static std::mutex _buffer_lock;
        static std::string currentDateTime(){
            std::time_t timestamp = std::time(nullptr);
            std::string ascitime = std::asctime(std::localtime(&timestamp));
            ascitime.pop_back();
            return ascitime;
        } 

        static void write_buffer(const std::string& msg){
            _buffer.push_back(msg);
            if(_buffer.size() == 20)
                flush_buffer();
        }

        public:
        Log() = delete;
        ~Log() = delete;
        inline static bool test_complete = false;
        static void init(){
            std::string filename = CMGT_LOG_PATH;
            fs::path logDir = filename;
            if (!fs::exists(logDir)) {
                fs::create_directories(logDir);
            }

            filename += "runtime_logs.cmgt";
            _stream.open(filename, std::ios::out | std::ios::trunc);
            if (!_stream.is_open()) {
                std::cerr << "Failed to open log file: " << filename << std::endl;
            }
            _buffer.reserve(20);
            std::string log = "<----------(NEW SESION BEGINS HERE)---------->";
            _buffer.push_back(log);
            std::cout << log << std::endl;
            flush_buffer();
        }

        static void close(){
            std::string log = "<----------(SESION ENDED BY USER)---------->";
            _buffer.push_back(log);
            std::cout << log << std::endl;
            flush_buffer();

            _stream.close();
        }

        static std::string error(const std::string& error){
            std::lock_guard<std::mutex> lock(_log_lock);
            std::string log = " [ " + currentDateTime() + " ]  [ " + "ERROR" + " ]: " + error;
            write_buffer(log);
            std::cout << log << std::endl;

            return log;
        }

        static std::string warning(const std::string& warnign){
            std::lock_guard<std::mutex> lock(_log_lock);
            std::string log = " [ " + currentDateTime() + " ]  [ " + "WARRNING" + " ]: " + warnign;
            write_buffer(log);
            std::cout << log << std::endl;

            return log;
        }

        static std::string msg(const std::string& msg){
            std::lock_guard<std::mutex> lock(_log_lock);
            std::string log = " [ " + currentDateTime() + " ]  [ " + "MESSAGE" + " ]: " + msg;
            write_buffer(log);
            std::cout << log << std::endl;

            return log;
        }
        
        static std::string debug(const std::string& debug_msg){
            std::lock_guard<std::mutex> lock(_log_lock);
            std::string log = " [ " + currentDateTime() + " ]  [ " + "DEBUG" + " ]: " + debug_msg;
            write_buffer(log);
            #ifndef NDEBUG
            std::cout << log << std::endl;
            #endif

            return log;
        }

        static std::string error_critical(const std::string& msg){
                std::lock_guard<std::mutex> lock(_log_lock);
                std::string log = " [ " + currentDateTime() + " ]  [ " + "CRITICAL ERROR" + " ]: " + msg;
                _buffer.push_back(log);
                std::cout << log << std::endl;
                
                log = "<----------(SESION ENDED ABRUPTLY)---------->";
                _buffer.push_back(log);
                std::cout << log << std::endl;
            flush_buffer();

            _stream.close();
            return msg;
        }

        static void flush_buffer(){
            std::lock_guard<std::mutex> lock(_buffer_lock);
            for(const std::string& log : _buffer)
                _stream << log << std::endl;
            
            _stream.flush();

            _buffer.clear();
        }
    };
}
#endif //LOG_H