#pragma once

#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>

#include "csv.hpp"

using namespace csv;

class Parsing
{
public:
    Parsing() = default;
    auto run(const std::string csv_string, std::vector<std::string> &colNames) -> CSVReader
    {
        CSVReader rows = parse(csv_string);

        colNames = rows.get_col_names();

        // for (auto &r : rows)
        // {
        //     for (auto &i : colNames)
        //         std::cout << r[i] << std::endl;
        // }
        return rows;
    }
    virtual ~Parsing() = default;
};