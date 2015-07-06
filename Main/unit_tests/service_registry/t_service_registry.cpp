/*
 * (C) Copyright 2015  Arnel I Periquet.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 */

#include <stdafx.h>
#include <boost/test/unit_test.hpp>
#include "../TestServiceWithNoParams.h"


BOOST_AUTO_TEST_CASE (service_registry_register_service)
{
    ServiceRegistry registry;
    Test::TestServiceWithNoParams service;
    Service & retValue = registry.Register(service);

    BOOST_CHECK_EQUAL(&retValue, &service);
}

BOOST_AUTO_TEST_CASE (service_registry_register_same_service_twice_fails)
{
    ServiceRegistry registry;
    Test::TestServiceWithNoParams service;
    registry.Register(service);

    BOOST_CHECK_THROW(registry.Register(service), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE (service_registry_lookup_service_by_name)
{
    ServiceRegistry registry;
    Test::TestServiceWithNoParams service;
    registry.Register(service);

    BOOST_CHECK_NO_THROW(registry.Lookup("TestService"));
}

BOOST_AUTO_TEST_CASE (service_registry_lookup_unregistered_service_by_name_fails)
{
    ServiceRegistry registry;

    BOOST_CHECK_THROW(registry.Lookup("TestService"), std::invalid_argument);
}
