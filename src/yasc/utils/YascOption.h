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
#ifndef _YASC_OPTION_H_
# define _YASC_OPTION_H_

# include <functional>
# include <memory>
# include <string>
# include <unordered_map>

namespace yasc {
namespace utils {

struct YascOption
{
public:
    using NoOptionCallback = std::function<void()>;
    using WithOptionCallback = std::function<void(const std::string&)>;
    using Ptr = std::shared_ptr<YascOption>;
    using WkPtr = std::weak_ptr<YascOption>;

    YascOption() = delete;
    YascOption(const char shortOpt,
               const std::string& longOpt,
               YascOption::NoOptionCallback callback,
               const std::string& desc,
               const bool isMandatory = false);

    YascOption(const char shortOpt,
               const std::string& longOpt,
               YascOption::WithOptionCallback callback,
               const std::string& desc,
               const std::string& argName,
               const bool isMandatory = false);

private:
    YascOption(const char shortOpt,
               const std::string& longOpt,
               YascOption::NoOptionCallback noOptionCallback,
               YascOption::WithOptionCallback withOptionCallback,
               const std::string& desc,
               const std::string& argName,
               const bool isMandatory);

public:
    const char ShortOption;
    const std::string LongOption;
    const YascOption::NoOptionCallback OptionlessCallback;
    const YascOption::WithOptionCallback OptionCallback;
    const std::string Description;
    const std::string ArgumentName;
    const bool IsMandatory;
    const bool NeedsArgument;
};

} // namespace utils
} // namespace yasc

#endif /* !_YASC_OPTION_H_ */
