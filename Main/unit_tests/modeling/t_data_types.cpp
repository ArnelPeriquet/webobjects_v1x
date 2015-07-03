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
#include "boost/test/unit_test.hpp"
#include "Object.h"
#include "tObject.h"
#include "datatype/DataTypes.h"


BOOST_AUTO_TEST_CASE( tinteger_create_object )
{
    BOOST_CHECK_EQUAL(tInteger::Value(15)->AsInteger(), 15);
}

BOOST_AUTO_TEST_CASE( tstring_create_object )
{
    BOOST_CHECK_EQUAL(tString::Value("hello")->AsString(), "hello");
}

BOOST_AUTO_TEST_CASE( tchar_create_object )
{
    BOOST_CHECK_EQUAL(tCharacter::Value('a')->AsCharacter(), 'a');
}

BOOST_AUTO_TEST_CASE( tnull_create_object )
{
    BOOST_CHECK(tNull::Value()->type.Equals(tNull::Instance()));
}

BOOST_AUTO_TEST_CASE( tboolean_create_object )
{
    BOOST_CHECK_EQUAL(tBoolean::Value(false)->AsBoolean(), false);
}

BOOST_AUTO_TEST_CASE( tarray_array_of_ints_equals_array_of_ints )
{
    BOOST_CHECK(ARRAY_OF(tInteger).Equals(ARRAY_OF(tInteger)));
}

BOOST_AUTO_TEST_CASE( tarray_array_of_strings_does_not_equals_array_of_ints )
{
    BOOST_CHECK(!ARRAY_OF(tString).Equals(ARRAY_OF(tInteger)));
    std::cout << std::endl;
}

BOOST_AUTO_TEST_CASE( tarray_create_array_of_character_objects )
{
    char vCharacters[] = { 'a', 'b', 'c' };
    std::shared_ptr<Object> vArray = tArray<tCharacter>::Value(vCharacters, 3);
    BOOST_CHECK_EQUAL(vArray->AsArray<tCharacter>()[0]->AsCharacter(), 'a');
    BOOST_CHECK_EQUAL(vArray->AsArray<tCharacter>()[1]->AsCharacter(), 'b');
    BOOST_CHECK_EQUAL(vArray->AsArray<tCharacter>()[2]->AsCharacter(), 'c');
}

BOOST_AUTO_TEST_CASE( tarray_create_array_of_integer_objects )
{
    int vIntegers[] = { 1, 2, 3 };
    std::shared_ptr<Object> vArray = tArray<tInteger>::Value(vIntegers, 3);
    BOOST_CHECK_EQUAL(vArray->AsArray<tInteger>()[0]->AsInteger(), 1);
    BOOST_CHECK_EQUAL(vArray->AsArray<tInteger>()[1]->AsInteger(), 2);
    BOOST_CHECK_EQUAL(vArray->AsArray<tInteger>()[2]->AsInteger(), 3);
}

BOOST_AUTO_TEST_CASE( tarray_create_array_of_string_objects )
{
    std::string vStrings[] = { "test1", "test2", "test3" };
    std::shared_ptr<Object> vArray = tArray<tString>::Value(vStrings, 3);
    BOOST_CHECK_EQUAL(vArray->AsArray<tString>()[0]->AsString(), "test1");
    BOOST_CHECK_EQUAL(vArray->AsArray<tString>()[1]->AsString(), "test2");
    BOOST_CHECK_EQUAL(vArray->AsArray<tString>()[2]->AsString(), "test3");
}

BOOST_AUTO_TEST_CASE( tarray_create_array_of_boolean_objects )
{
    bool vBooleans[] = { true, false, true };
    std::shared_ptr<Object> vArray = tArray<tBoolean>::Value(vBooleans, 3);
    BOOST_CHECK_EQUAL(vArray->AsArray<tBoolean>()[0]->AsBoolean(), true);
    BOOST_CHECK_EQUAL(vArray->AsArray<tBoolean>()[1]->AsBoolean(), false);
    BOOST_CHECK_EQUAL(vArray->AsArray<tBoolean>()[2]->AsBoolean(), true);
}

// BOOST_AUTO_TEST_CASE( tarray_create_array_of_objects )
// {
//     std::shared_ptr<Object> vObjects[3] = { tInteger::Value(1), tString::Value("hey"), tCharacter::Value('c') };
//     std::shared_ptr<Object> vArray = tArray<tObject>::Value(vObjects, 3);
//     BOOST_CHECK_EQUAL(vArray->AsArray<tObject>()[0]->AsInteger(), 1);
//     BOOST_CHECK_EQUAL(vArray->AsArray<tObject>()[1]->AsString(), "hey");
//     BOOST_CHECK_EQUAL(vArray->AsArray<tObject>()[2]->AsCharacter(), 'c');
// }

