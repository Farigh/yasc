/*
 * This file is part of the YASC project (https://github.com/Farigh/yasc)
 * Copyright (C) 2016  David GARCIN <david.garcin.pro[at]gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef _YASC_GETOPTS_H_
# define _YASC_GETOPTS_H_

# include "YascOption.h"

# include <list>
# include <memory>
# include <set>
# include <string>
# include <unordered_map>

namespace yasc {
namespace utils {

class YascGetopts
{
public:
    using PrintUsageCallback = std::function<void()>;
    using PrintErrorCallback = std::function<void(const std::string&)>;

    YascGetopts();
    ~YascGetopts() = default;

    void registerOption(const char shortOpt,
                        const std::string& longOpt,
                        YascOption::NoOptionCallback callback,
                        const std::string& desc,
                        const bool isMandatory = false);
    void registerArgBasedOption(const char shortOpt,
                                const std::string& longOpt,
                                YascOption::WithOptionCallback callback,
                                const std::string& desc,
                                const std::string& argName,
                                const bool isMandatory = false);

    void registerHelpOption();
    void registerPrintUsageCallback(PrintUsageCallback callback);
    void registerPrintErrorCallback(PrintErrorCallback callback);

    std::list<std::string> parseArgs(const int argc, const char* const* argv);

    void PrintUsage();
    void PrintErrorMessage(const std::string& errorMsg);

private:
    void defaultPrintUsageCallback();
    void defaultPrintErrorCallback(const std::string& errorMsg);
    void innerRegister(std::shared_ptr<YascOption>&& option);
    void checkMandatoryOptions(std::set<char> foundMandatoryOptions);

    PrintUsageCallback _printUsageCallback;
    PrintErrorCallback _printErrorCallback;
    std::string _binaryName;
    std::list<YascOption::Ptr> _options;
    std::unordered_map<std::string, YascOption::WkPtr> _optionsMap;
};

} // namespace utils
} // namespace yasc

#endif /* !_YASC_GETOPTS_H_ */
