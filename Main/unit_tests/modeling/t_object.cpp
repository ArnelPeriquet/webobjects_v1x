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
#include "Object.h"
#include "Class.h"
#include "ModelExceptions.h"
#include "datatype/DataTypes.h"


BOOST_AUTO_TEST_CASE( object_set_as_string_fails )
{
    Object vMyObject(tInteger::Instance());
    BOOST_CHECK_THROW(vMyObject.AsString("a string value"), TypeMismatchException);
}

BOOST_AUTO_TEST_CASE( object_set_as_character_fails )
{
    Object vMyObject(tInteger::Instance());
    BOOST_CHECK_THROW(vMyObject.AsCharacter('b'), TypeMismatchException);
}

BOOST_AUTO_TEST_CASE( object_set_as_integer_fails )
{
    Object vMyObject(tString::Instance());
    BOOST_CHECK_THROW(vMyObject.AsInteger(-98), TypeMismatchException);
}

BOOST_AUTO_TEST_CASE( object_set_as_boolean_fails )
{
    Object vMyObject(tString::Instance());
    BOOST_CHECK_THROW(vMyObject.AsBoolean(false), TypeMismatchException);
}

BOOST_AUTO_TEST_CASE( object_get_as_string_fails )
{
    Object vMyObject(tCharacter::Instance());
    vMyObject.AsCharacter('b');
    BOOST_CHECK_THROW(vMyObject.AsString(), TypeMismatchException);
}

BOOST_AUTO_TEST_CASE( object_get_as_character_fails )
{
    Object vMyObject(tString::Instance());
    vMyObject.AsString("a string value");
    BOOST_CHECK_THROW(vMyObject.AsCharacter(), TypeMismatchException);
}

BOOST_AUTO_TEST_CASE( object_get_as_integer_fails )
{
    Object vMyObject(tString::Instance());
    vMyObject.AsString("a string value");
    BOOST_CHECK_THROW(vMyObject.AsInteger(), TypeMismatchException);
}

BOOST_AUTO_TEST_CASE( object_get_as_boolean_fails )
{
    Object vMyObject(tString::Instance());
    vMyObject.AsString("a string value");
    BOOST_CHECK_THROW(vMyObject.AsBoolean(), TypeMismatchException);
}

BOOST_AUTO_TEST_CASE( object_set_as_string )
{
    Object vMyObject(tString::Instance());
    BOOST_CHECK_EQUAL(vMyObject.AsString("a string value"), "a string value");
}

BOOST_AUTO_TEST_CASE( object_set_as_character )
{
    Object vMyObject(tCharacter::Instance());
    BOOST_CHECK_EQUAL(vMyObject.AsCharacter('b'), 'b');
}

BOOST_AUTO_TEST_CASE( object_set_as_integer )
{
    Object vMyObject(tInteger::Instance());
    BOOST_CHECK_EQUAL(vMyObject.AsInteger(-98), -98);
}

BOOST_AUTO_TEST_CASE( object_set_as_boolean )
{
    Object vMyObject(tBoolean::Instance());
    BOOST_CHECK_EQUAL(vMyObject.AsBoolean(false), false);
}

BOOST_AUTO_TEST_CASE( object_get_as_string )
{
    Object vMyObject(tString::Instance());
    vMyObject.AsString("a string value");
    BOOST_CHECK_EQUAL(vMyObject.AsString(), "a string value");
}

BOOST_AUTO_TEST_CASE( object_get_as_character )
{
    Object vMyObject(tCharacter::Instance());
    vMyObject.AsCharacter('b');
    BOOST_CHECK_EQUAL(vMyObject.AsCharacter(), 'b');
}

BOOST_AUTO_TEST_CASE( object_get_as_integer )
{
    Object vMyObject(tInteger::Instance());
    vMyObject.AsInteger(-98);
    BOOST_CHECK_EQUAL(vMyObject.AsInteger(), -98);
}

BOOST_AUTO_TEST_CASE( object_get_as_boolean )
{
    Object vMyObject(tBoolean::Instance());
    vMyObject.AsBoolean(false);
    BOOST_CHECK_EQUAL(vMyObject.AsBoolean(), false);
}

BOOST_AUTO_TEST_CASE( object_set_attribute_value_on_primitive_type_fails )
{
    BOOST_CHECK_THROW(tString::Value("15")->Set("attr1", tInteger::Value(15)), ObjectIsNotAClassException);
}

BOOST_AUTO_TEST_CASE( object_set_attribute_value_on_unknown_attribute_fails )
{
    Class vMyClass("MyClass");
    Object vMyObject(vMyClass);
    BOOST_CHECK_THROW(vMyObject.Set("attr1", tInteger::Value(15)), UnknownAttributeException);
}

BOOST_AUTO_TEST_CASE( object_set_attribute_value_with_mismatched_type_fails )
{
    Class vMyClass("MyClass");
    vMyClass.AddAttribute("attr1", tInteger::Instance());
    Object vMyObject(vMyClass);

    BOOST_CHECK_THROW(vMyObject.Set("attr1", tString::Value("15")), TypeMismatchException);
}

BOOST_AUTO_TEST_CASE( object_set_any_attribute_value_including_primitives_to_null_succeeds )
{
    Class vMyClass("MyClass");
    vMyClass.AddAttribute("attr1", tInteger::Instance());
    Object vMyObject(vMyClass);

    BOOST_CHECK_NO_THROW(vMyObject.Set("attr1", tNull::Value()));
}

BOOST_AUTO_TEST_CASE( object_set_attribute_value )
{
    Class vMyClass("MyClass");
    vMyClass.AddAttribute("attr1", tInteger::Instance());
    Object vMyObject(vMyClass);

    BOOST_CHECK_EQUAL(vMyObject.Set("attr1", tInteger::Value(15))->AsInteger(), 15);
}

BOOST_AUTO_TEST_CASE( object_get_attribute_value_from_primitive_type_fails )
{
    BOOST_CHECK_THROW(tString::Value("test")->Get("attr1"), ObjectIsNotAClassException);
}

BOOST_AUTO_TEST_CASE( object_get_attribute_value_for_unknown_attribute_fails )
{
    Class vMyClass("MyClass");
    Object vMyObject(vMyClass);
    BOOST_CHECK_THROW(vMyObject.Get("attr1"), UnknownAttributeException);
}

BOOST_AUTO_TEST_CASE( object_get_attribute_value )
{
    Class vMyClass("MyClass");
    vMyClass.AddAttribute("attr1", tInteger::Instance());
    Object vMyObject(vMyClass);

    vMyObject.Set("attr1", tInteger::Value(15));

    BOOST_CHECK_EQUAL(vMyObject.Get("attr1")->AsInteger(), 15);
}

BOOST_AUTO_TEST_CASE( object_string_is_compared_by_contents )
{
    BOOST_CHECK(tString::Value("test1")->Equals(tString::Value("test1")));
}

BOOST_AUTO_TEST_CASE( object_integer_is_compared_by_contents )
{
    BOOST_CHECK(tInteger::Value(-99)->Equals(tInteger::Value(-99)));
}

BOOST_AUTO_TEST_CASE( object_character_is_compared_by_contents )
{
    BOOST_CHECK(tCharacter::Value('a')->Equals(tCharacter::Value('a')));
}

BOOST_AUTO_TEST_CASE( object_boolean_is_compared_by_contents )
{
    BOOST_CHECK(tBoolean::Value(false)->Equals(tBoolean::Value(false)));
}

BOOST_AUTO_TEST_CASE( object_null_equals_null )
{
    BOOST_CHECK(tNull::Value()->Equals(tNull::Value()));
}

BOOST_AUTO_TEST_CASE( object_attribute_value_of_any_type_can_be_null )
{
    Class vMyClass("MyClass");
    vMyClass.AddAttribute("attr1", tInteger::Instance());
    Object vMyObject(vMyClass);

    vMyObject.Set("attr1", tNull::Value());

    BOOST_CHECK(vMyObject.Get("attr1")->Equals(tNull::Value()));
}