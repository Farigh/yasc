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
#include "YascGetopts.h"

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace yasc {
namespace utils {

YascGetopts::YascGetopts()
    // Register default print usage callback
    : _printUsageCallback([&](){ defaultPrintUsageCallback();}),
      _printErrorCallback([&](const std::string& errorMsg){ defaultPrintErrorCallback(errorMsg);})
{
}

/**
 * @brief Inner register function in charge of registering new options
 *
 * @param option The option to register
 *
 * @see registerOption
 * @see registerArgBasedOption
 */
void YascGetopts::innerRegister(YascOption::Ptr&& option)
{
    _options.push_back(std::forward<YascOption::Ptr>(option));

    YascOption::WkPtr wkOption = _options.back();

    // Register short option (starts with -)
    _optionsMap.insert({ "-" + std::string(1, wkOption.lock()->ShortOption), wkOption });

    // Register long option (starts with --)
    _optionsMap.insert({ "--" + wkOption.lock()->LongOption, wkOption });
}

/**
 * @brief Registers an option which takes no argument
 *
 * @param shortOpt The short option character
 * @param longOpt The long option string
 * @param callback The callback to call if option is passed to the program
 * @param desc The option description (will be displayed by the default usage callback)
 * @param isMandatory If set to true, @see parseArgs call will call std::exit(1) if the option is not
                      provided to the program
 * @return returns any remaining arguments added after args
 *         Any arguments after the -- option will be considered as such
 */
void YascGetopts::registerOption(const char shortOpt,
                                 const std::string& longOpt,
                                 YascOption::NoOptionCallback callback,
                                 const std::string& desc,
                                 const bool isMandatory)
{
    innerRegister(std::make_shared<YascOption>(shortOpt, longOpt, callback, desc, isMandatory));
}

/**
 * @brief Registers an option which takes an argument
 *
 * @param shortOpt The short option character
 * @param longOpt The long option string
 * @param callback The callback to call if option is passed to the program
 * @param desc The option description (will be displayed by the default usage callback)
 * @param argName The callback argument name (will be displayed by the default usage callback)
 * @param isMandatory If set to true, @see parseArgs call will call std::exit(1) if the option is not
                      provided to the program
 * @return returns any remaining arguments added after args
 *         Any arguments after the -- option will be considered as such
 */
void YascGetopts::registerArgBasedOption(const char shortOpt,
                                         const std::string& longOpt,
                                         YascOption::WithOptionCallback callback,
                                         const std::string& desc,
                                         const std::string& argName,
                                         const bool isMandatory)
{
    innerRegister(std::make_shared<YascOption>(shortOpt, longOpt, callback, desc, argName, isMandatory));
}

/**
 * @brief Prints the usage
 */
void YascGetopts::PrintUsage()
{
    _printUsageCallback();
}

/**
 * @brief Format and prints the given error message using the registered error callback
 */
void YascGetopts::PrintErrorMessage(const std::string& errorMsg)
{
    _printErrorCallback(errorMsg);
}

/**
 * @brief Registers the default help (-h,--help) option
 */
void YascGetopts::registerHelpOption()
{
    registerOption('h',
                   "help",
                   [&]()
                   {
                       PrintUsage();

                       // Help option stops the execution
                       std::exit(0);
                   },
                   "Display this help message");
}

/**
 * @brief Default Usage printing callback
 */
void YascGetopts::defaultPrintErrorCallback(const std::string& errorMsg)
{
    std::cerr << errorMsg << std::endl;
    if (_optionsMap.find("--help") != _optionsMap.end())
    {
        std::cerr << "Try '" << _binaryName << " --help' for more information." << std::endl;
    }
}

/**
 * @brief Default Usage printing callback
 */
void YascGetopts::defaultPrintUsageCallback()
{
    using OptionsValueType = typename decltype(_options)::value_type;

    std::cout << "Usage: " << _binaryName << " [Options]..." << std::endl
              << std::endl
              << "Options:" << std::endl;

    // Sort options alphabetically first
    _options.sort([](const OptionsValueType& first, const OptionsValueType& second)
                  {
                      // Compare based on short option
                      return first->ShortOption < second->ShortOption;
                  });

    // Print all available options
    for (const OptionsValueType& option : _options)
    {
        std::string isMandatoryStr = "";
        if (option->IsMandatory)
        {
            isMandatoryStr = "[Mandatory] ";
        }

        std::string longOptArgs = "";
        if (option->NeedsArgument)
        {
            longOptArgs = " <" + option->ArgumentName + " >";
        }

        std::cout << "    -" << option->ShortOption << ", --"
                  << option->LongOption << longOptArgs << std::endl
                  << "            " << isMandatoryStr << option->Description << std::endl;
    }
}

/**
 * @brief Parses given arguments
 *
 * Warning: Options must be registered before calling this function
 *
 * @param argc The argument count
 * @param argv The argument list (argv[0] must be the current binary name)
 * @return returns any remaining arguments added after args
 *         Any arguments after the -- option will be considered as such
 *
 * @see registerOption
 * @see registerArgBasedOption
 */
std::list<std::string> YascGetopts::parseArgs(const int argc, const char* const* argv)
{
    std::list<std::string> remainingArgs;
    _binaryName = std::string(argv[0]);

    std::set<char> foundMandatoryOptions;
    bool wasEndOfArgsEncountered = false;

    for (int i = 1; i < argc; i++)
    {
        const std::string currentOption(argv[i]);
        typename decltype(_optionsMap)::const_iterator it = _optionsMap.find(currentOption);

        // Look for non options args and add them to remainingArgs
        // Add all remaining args past -- special options
        if (wasEndOfArgsEncountered || (currentOption.substr(0, 1) != "-"))
        {
            remainingArgs.push_back(currentOption);
            continue;
        }

        // Special arg --
        if (currentOption == "--")
        {
            wasEndOfArgsEncountered = true;
            continue;
        }

        if (it != _optionsMap.end())
        {
            YascOption::Ptr opt = it->second.lock();
            if (opt->IsMandatory)
            {
                foundMandatoryOptions.insert(opt->ShortOption);
            }

            if (opt->NeedsArgument)
            {
                // TODO: handle = synthax on long opts
                if (++i < argc)
                {
                    const std::string currentOptionArg(argv[i]);
                    opt->OptionCallback(currentOptionArg);
                }
                else
                {
                    PrintErrorMessage("Error: option '" + currentOption + "' requires an argument");
                    std::exit(1);
                }
            }
            else
            {
                opt->OptionlessCallback();
            }
        }
        else
        {
            PrintErrorMessage("Error: unknown option '" + currentOption + "'");
            std::exit(1);
        }
    }

    checkMandatoryOptions(foundMandatoryOptions);

    return remainingArgs;
}

/**
 * @brief Checks that each and every mandatory options were provided
 *
 * Calls std::exit(1) if any mandatory option is not provided to the program
 */
void YascGetopts::checkMandatoryOptions(std::set<char> foundMandatoryOptions)
{
    bool isAnyOptionMissing = false;
    std::ostringstream errorMsgFormater;
    for (const typename decltype(_options)::value_type& option : _options)
    {
        if (option->IsMandatory && (foundMandatoryOptions.find(option->ShortOption) == foundMandatoryOptions.end()))
        {
            errorMsgFormater << "Error: Missing mandatory option: '-" << option->ShortOption << "|--" << option->LongOption << "'" << std::endl;
            isAnyOptionMissing = true;
        }
    }

    if (isAnyOptionMissing)
    {
        PrintErrorMessage(errorMsgFormater.str());
        std::exit(1);
    }
}

} // namespace utils
} // namespace yasc
