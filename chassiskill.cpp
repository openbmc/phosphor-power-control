#include "utility.hpp"

#include <nlohmann/json.hpp>
#include <phosphor-logging/log.hpp>

#include <fstream>

using json = nlohmann::json;
using namespace utility;

constexpr auto gpioDefsFile = "/etc/default/obmc/gpio/gpio_defs.json";

int main(void)
{
    std::ifstream gpioDefsStream(gpioDefsFile);

    if (!gpioDefsStream.is_open())
    {
        lg2::error("Error opening gpio definitions: {PATH}", "PATH",
                   gpioDefsFile);
        return 1;
    }

    auto data = json::parse(gpioDefsStream, nullptr, false);

    if (data.is_discarded())
    {
        lg2::error("Error parsing gpio definitions: {PATH}", "PATH",
                   gpioDefsFile);
        return 1;
    }

    // To determine what pins are needed to deassert, look in the
    // gpioDefsFile for the defined "power_up_outs" under
    // gpio_configs->power_config. Then match the name up with
    // its definition in "gpio_definitions" to determine the pin id's.
    auto gpios = data["gpio_configs"]["power_config"]["power_up_outs"];

    if (gpios.size() <= 0)
    {
        lg2::error("Could not find power_up_outs defs: {PATH}", "PATH",
                   gpioDefsFile);
        return 1;
    }

    auto defs = data["gpio_definitions"];

    for (const auto& gpio : gpios)
    {
        auto gpioEntry =
            std::find_if(defs.begin(), defs.end(), [&gpio](const auto& g) {
                return g["name"] == gpio["name"];
            });

        if (gpioEntry != defs.end())
        {
            std::string pin = (*gpioEntry)["pin"];
            bool activeLow = gpio["polarity"];

            if (!gpioSetValue(pin, !activeLow, false))
            {
                lg2::error("chassiskill::gpioSetValue() failed: {PIN}", "PIN",
                           pin);
                return 1;
            }
            else
            {
                lg2::info("chassiskill::operation complete: {PIN}", "PIN", pin);
            }
        }
    }

    return 0;
}
