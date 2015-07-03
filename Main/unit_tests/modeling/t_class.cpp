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
#include "Class.h"
#include "datatype/DataTypes.h"


BOOST_AUTO_TEST_CASE( class_add_primitive_attributes )
{    
    Class vMyClass("MyClass");
    BOOST_CHECK(vMyClass.AddAttribute("name", tString::Instance()).GetAttributeType("name") == tString::Instance());
    BOOST_CHECK(vMyClass.AddAttribute("age", tInteger::Instance()).GetAttributeType("age") == tInteger::Instance());
    BOOST_CHECK(vMyClass.AddAttribute("size", tCharacter::Instance()).GetAttributeType("size") == tCharacter::Instance());
}

BOOST_AUTO_TEST_CASE( class_add_object_attribute )
{    
    Class vMyClass("MyClass");
    Class vAttrClass("MyClassB");
    BOOST_CHECK(vMyClass.AddAttribute("my_attr", vAttrClass).GetAttributeType("my_attr") == vAttrClass);
}

BOOST_AUTO_TEST_CASE( class_adding_same_attribute_twice_fails )
{    
    Class vMyClass("MyClass");
    vMyClass.AddAttribute("my_attr", tString::Instance());
    BOOST_CHECK_THROW(vMyClass.AddAttribute("my_attr", tString::Instance()), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE( class_has_attribute_fails )
{
    Class vMyClass("MyClass");
    BOOST_CHECK(!vMyClass.HasAttribute("my_attr"));
}

BOOST_AUTO_TEST_CASE( class_has_attribute_succeeds )
{
    Class vMyClass("MyClass");
    vMyClass.AddAttribute("my_attr", tString::Instance());
    BOOST_CHECK(vMyClass.HasAttribute("my_attr"));
}

BOOST_AUTO_TEST_CASE( class_get_attribute_type_for_missing_attribute_fails )
{
    Class vMyClass("MyClass");
    BOOST_CHECK_THROW(vMyClass.GetAttributeType("my_attr"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE( class_get_attribute_type_succeeds )
{
    Class vMyClass("MyClass");
    vMyClass.AddAttribute("my_attr", tString::Instance());
    BOOST_CHECK_EQUAL(vMyClass.GetAttributeType("my_attr").name, tString::Instance().name);
}

BOOST_AUTO_TEST_CASE( class_get_attribute_names ) 
{
    Class vMyClass("MyClass");
    vMyClass.AddAttribute("my_attr1", tString::Instance());
    vMyClass.AddAttribute("my_attr2", tInteger::Instance());
    
    std::vector<std::string> vNames = vMyClass.GetAttributeNames();
    std::vector<std::string>::iterator vIt = vNames.begin();
    BOOST_CHECK_EQUAL(*vIt, "my_attr1");
    ++vIt;
    BOOST_CHECK_EQUAL(*vIt, "my_attr2");
}