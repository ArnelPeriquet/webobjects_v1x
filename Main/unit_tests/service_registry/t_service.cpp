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
#include "ServiceRegistry.h"
#include "Modeling.h"
#include "..\TestServiceWithNoParams.h"
#include "..\TestServiceWithParams.h"
#include "..\TestServiceWithObjectParams.h"


BOOST_AUTO_TEST_CASE( service_invoke_no_params )
{
    Test::TestServiceWithNoParams service;
    std::vector<std::shared_ptr<Object>> params;

    BOOST_CHECK_EQUAL(service.Invoke(params)->AsInteger(), TestServiceWithNoParams_EXPECTED_RETURN_VALUE);
}

BOOST_AUTO_TEST_CASE( service_invoke_with_params )
{
    Test::TestServiceWithParams service;
    std::vector<std::shared_ptr<Object>> params;

    std::shared_ptr<Object> param1 = std::make_shared<Object>(tInteger::Instance());
    param1->AsInteger(15);
    std::shared_ptr<Object> param2 = std::make_shared<Object>(tString::Instance());
    param2->AsString("hello");

    params.push_back(param1);
    params.push_back(param2);

    BOOST_CHECK_EQUAL(service.Invoke(params)->AsString(), TestServiceWithParams_EXPECTED_RETURN_VALUE);
}

BOOST_AUTO_TEST_CASE( service_invoke_with_object_params )
{
    Test::TestServiceWithObjectParams service;
    std::vector<std::shared_ptr<Object>> params;

    Class class1("MyClass1");
    class1.AddAttribute("attr1", tInteger::Instance());
    Class class2("MyClass2");
    class2.AddAttribute("attr1", tString::Instance());

    std::shared_ptr<Object> param1 = std::make_shared<Object>(class1);
    param1->Set("attr1", tInteger::Value(15));
    
    std::shared_ptr<Object> param2 = std::make_shared<Object>(class2);
    param2->Set("attr1", tString::Value("hello"));

    params.push_back(param1);
    params.push_back(param2);

    BOOST_CHECK_EQUAL(service.Invoke(params)->AsString(), TestServiceWithObjectParams_EXPECTED_RETURN_VALUE);
}