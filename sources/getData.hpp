#pragma once

#include <curl/curl.h>
#include <string>
#include <iostream>

static std::string readBuffer;

class CovidInfo
{
private:
    CURL *curl_handle;
    int sizeRead;
private:
    auto getDate(int m, int d, int y) -> std::string;
    static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
    {
        ((std::string *)stream)->append((char *)ptr, size * nmemb);
        return size * nmemb;
    }

public:
    CovidInfo()
    {
        curl_global_init(CURL_GLOBAL_ALL);
        curl_handle = curl_easy_init();
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &readBuffer);
    };
    ~CovidInfo() {
        curl_easy_cleanup(curl_handle);
        curl_global_cleanup();
    };
    auto download(const std::string url) -> bool;
    auto download_daily_report(int month, int day, int year) -> bool;
    auto download_today_report(void) -> bool;
    auto getSizeRead() const -> int { return sizeRead; };
};
