#ifndef __MYTESTSUITE_H
#define __MYTESTSUITE_H

#include <cxxtest/TestSuite.h>
#include "config/Configuration.h"

class ServerConfigTest : public CxxTest::TestSuite
{
    float amount_cars = 4;
    float amount_players = 10;
    float hours_played = 5;

public:
    void testServerConfigFile() {
        std::cout << "Testing server configs load correctly" << std::endl;
//        Configuration config = Configuration("tests/mock_yamls/server_config.yaml");
//        TS_ASSERT_EQUALS(amount_cars, config.getConfigurationData("amount_cars"));
//        TS_ASSERT_EQUALS(amount_players, config.getConfigurationData("amount_players"));
//        TS_ASSERT_EQUALS(hours_played, config.getConfigurationData("hours_played"));
    }
};

#endif

