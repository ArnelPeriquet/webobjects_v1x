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
#include "Type.h"


BOOST_AUTO_TEST_CASE( type_equals_for_different_type_names_fails )
{
    Type myType1("myName1", "myPackage");
    Type myType2("myName2", "myPackage");

    BOOST_CHECK(!myType1.Equals(myType2));
}

BOOST_AUTO_TEST_CASE( type_equals_for_different_same_type_names_but_different_packages_fails )
{
    Type myType1("myName", "myPackage1");
    Type myType2("myName", "myPackage2");

    BOOST_CHECK(!myType1.Equals(myType2));
}

BOOST_AUTO_TEST_CASE( type_equals_for_different_different_type_names_and_different_packages_fails )
{
    Type myType1("myName1", "myPackage1");
    Type myType2("myName2", "myPackage2");

    BOOST_CHECK(myType1 != myType2);
}

BOOST_AUTO_TEST_CASE( type_equals_by_same_object_succeeds )
{
    Type myType("myName", "myPackage");

    BOOST_CHECK(myType == myType);
}

BOOST_AUTO_TEST_CASE( type_equals_by_same_name_and_package_succeeds )
{
    Type myType1("myName", "myPackage");
    Type myType2("myName", "myPackage");

    BOOST_CHECK(myType1 == myType2);
}
