#include "getData.hpp"
#include "Parsing.hpp"
#include <ctime>
#include <iostream>

auto CovidInfo::download(const std::string url) -> bool
{
    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
    curl_easy_perform(curl_handle);
}
auto CovidInfo::download_daily_report(int month, int day, int year) -> bool
{
    std::string date = getDate(day, month, year);
    std::string url = "https://raw.githubusercontent.com/CSSEGISandData/COVID-19/master/csse_covid_19_data/csse_covid_19_daily_reports/" + date;
    std::cout << url << std::endl;
    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
    curl_easy_perform(curl_handle);
}
auto CovidInfo::download_today_report() -> bool
{
    std::time_t t = std::time(nullptr);
    std::tm *calendar = std::localtime(&t);

    calendar->tm_mday-=1;
    std::mktime(calendar);

    std::string date = getDate(calendar->tm_mday, calendar->tm_mon+1, calendar->tm_year + 1900);
    std::string url = "https://raw.githubusercontent.com/CSSEGISandData/COVID-19/master/csse_covid_19_data/csse_covid_19_daily_reports/" + date;
    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
    curl_easy_perform(curl_handle);
}

auto CovidInfo::getDate(int month, int day, int year) -> std::string
{
    std::string d = std::to_string(day);
    std::string m = std::to_string(month);

    if (d.size() < 2)
        d = "0" + d;
    if (m.size() < 2)
        m = "0" + m;
    std::string date = d + "-" + m + "-" + std::to_string(year) + ".csv";
    return date;
}


// 2 000 000   inf
// 50          