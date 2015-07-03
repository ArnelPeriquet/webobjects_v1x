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
#include "JSON.h"
#include "Object.h"
#include "Class.h"
#include "ClassModel.h"
#include "datatype/DataTypes.h"


BOOST_AUTO_TEST_CASE( json_parse_invalid_json_fails )
{    
    ClassModel vClassModel;
    Class & vMyClass = vClassModel.CreateClass("MyClass");
    
    JSON json(vClassModel);
    BOOST_CHECK_THROW(json.Parse("invalid json", vMyClass), std::runtime_error);
}

BOOST_AUTO_TEST_CASE( json_parse_ignores_unknown_attributes )
{
    std::string vJsonWithUnknownAttributes(
        "{"
        "   \"unknown1\"       : \"111\","
        "   \"unknown2\"       : \"stuff\""
        "}");

    ClassModel vClassModel;
    Class & vMyClass = vClassModel.CreateClass("MyClass");

    JSON json(vClassModel);
    BOOST_CHECK_NO_THROW(json.Parse(vJsonWithUnknownAttributes, vMyClass));
}

BOOST_AUTO_TEST_CASE( json_parse_character_attribute )
{
    std::string vJsonWithCharacterAttribute(
        "{"
        "   \"myValue\"           : \"a\""
        "}");

    ClassModel vClassModel;
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("myValue", tCharacter::Instance());

    JSON json(vClassModel);
    std::shared_ptr<Object> vMyObject = json.Parse(vJsonWithCharacterAttribute, vMyClass);
    BOOST_CHECK_EQUAL(vMyObject->Get("myValue")->AsCharacter(), 'a');
}

BOOST_AUTO_TEST_CASE( json_parse_integer_attribute )
{
    std::string vJsonWithIntegerAttribute(
        "{"
        "   \"myValue\"           : -99"
        "}");

    ClassModel vClassModel;
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("myValue", tInteger::Instance());

    JSON json(vClassModel);
    std::shared_ptr<Object> vMyObject = json.Parse(vJsonWithIntegerAttribute, vMyClass);
    BOOST_CHECK_EQUAL(vMyObject->Get("myValue")->AsInteger(), -99);
}

BOOST_AUTO_TEST_CASE( json_parse_string_attribute )
{
    std::string vJsonWithStringAttribute(
        "{"
        "   \"myValue\"           : \"mystr\""
        "}");

    ClassModel vClassModel;
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("myValue", tString::Instance());

    JSON json(vClassModel);
    std::shared_ptr<Object> vMyObject = json.Parse(vJsonWithStringAttribute, vMyClass);
    BOOST_CHECK_EQUAL(vMyObject->Get("myValue")->AsString(), "mystr");
}

BOOST_AUTO_TEST_CASE( json_parse_boolean_attribute )
{
    std::string vJsonWithBooleanAttribute(
        "{"
        "   \"myValue\"           : false"
        "}");

    ClassModel vClassModel;
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("myValue", tBoolean::Instance());

    JSON json(vClassModel);
    std::shared_ptr<Object> vMyObject = json.Parse(vJsonWithBooleanAttribute, vMyClass);
    BOOST_CHECK_EQUAL(vMyObject->Get("myValue")->AsBoolean(), false);
}

BOOST_AUTO_TEST_CASE( json_parse_null_attribute )
{
    std::string vJsonWithNullAttribute(
        "{"
        "   \"myValue\"       : null"
        "}");

    ClassModel vClassModel;
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("myValue", tNull::Instance());

    JSON json(vClassModel);
    std::shared_ptr<Object> vMyObject = json.Parse(vJsonWithNullAttribute, vMyClass);
    BOOST_CHECK(vMyObject->Get("myValue")->Equals(tNull::Value()));
}

BOOST_AUTO_TEST_CASE( json_parse_multiple_primitive_attributes )
{
    std::string vTestJsonObject(
        "{"
        "   \"myInt\"        : -99,"
        "   \"myStr\"        : \"test\","
        "   \"myChar\"       : \"a\","
        "   \"myBool\"       : true,"
        "   \"myNull\"       : null"
        "}");

    ClassModel vClassModel;
    Class & vMyClass = vClassModel.CreateClass("MyClass")
                                  .AddAttribute("myInt", tInteger::Instance())
                                  .AddAttribute("myStr", tString::Instance())
                                  .AddAttribute("myChar", tCharacter::Instance())
                                  .AddAttribute("myBool", tBoolean::Instance())
                                  .AddAttribute("myNull", tNull::Instance());

    JSON json(vClassModel);
    std::shared_ptr<Object> vMyObject = json.Parse(vTestJsonObject, vMyClass);
    BOOST_CHECK(vMyObject->Get("myInt")->AsInteger() == -99);
    BOOST_CHECK(vMyObject->Get("myStr")->AsString() == "test");
    BOOST_CHECK(vMyObject->Get("myChar")->AsCharacter() == 'a');
    BOOST_CHECK(vMyObject->Get("myBool")->AsBoolean() == true);
    BOOST_CHECK(vMyObject->Get("myNull")->Equals(tNull::Value()));
}

BOOST_AUTO_TEST_CASE( json_parse_object_attribute )
{
    std::string vJsonWithObjectAttribute(
        "{"
        "   \"myValue\"       : \"MyClass2\""
        "}");

    ClassModel vClassModel;
    Class & vMyClass2 = vClassModel.CreateClass("MyClass2");
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("myValue", vMyClass2);

    JSON json(vClassModel);
    std::shared_ptr<Object> vMyObject = json.Parse(vJsonWithObjectAttribute, vMyClass);
    BOOST_CHECK(vMyObject->Get("myValue")->type == vMyClass2);
}

BOOST_AUTO_TEST_CASE( json_parse_empty_array_attribute )
{
    std::string vJsonWithEmptyArrayAttribute(
        "{"
        "   \"myArray\"       : []"
        "}");

    ClassModel vClassModel;
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("myArray", tArray<tInteger>::Instance());

    JSON json(vClassModel);
    std::shared_ptr<Object> vMyObject = json.Parse(vJsonWithEmptyArrayAttribute, vMyClass);
    BOOST_CHECK(vMyObject->Get("myArray")->type.Equals(tArray<tInteger>::Instance()));
}

BOOST_AUTO_TEST_CASE( json_parse_char_array_attribute )
{
    std::string vJsonWithCharacterArrayAttribute(
        "{"
        "   \"myArray\"       : [\"d\",\"a\",\"z\"]"
        "}");

    ClassModel vClassModel;
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("myArray", tArray<tCharacter>::Instance());

    JSON json(vClassModel);
    std::shared_ptr<Object> vMyObject = json.Parse(vJsonWithCharacterArrayAttribute, vMyClass);
    std::shared_ptr<Object> * vArray = vMyObject->Get("myArray")->AsArray<tCharacter>();
    BOOST_CHECK_EQUAL('d', vArray[0]->AsCharacter());
    BOOST_CHECK_EQUAL('a', vArray[1]->AsCharacter());
    BOOST_CHECK_EQUAL('z', vArray[2]->AsCharacter());    
}

BOOST_AUTO_TEST_CASE( json_parse_int_array_attribute )
{
    std::string vJsonWithIntegerArrayAttribute(
        "{"
        "   \"myArray\"       : [7,1,9]"
        "}");

    ClassModel vClassModel;
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("myArray", tArray<tInteger>::Instance());

    JSON json(vClassModel);
    std::shared_ptr<Object> vMyObject = json.Parse(vJsonWithIntegerArrayAttribute, vMyClass);
    std::shared_ptr<Object> * vArray = vMyObject->Get("myArray")->AsArray<tInteger>();
    BOOST_CHECK_EQUAL(7, vArray[0]->AsInteger());
    BOOST_CHECK_EQUAL(1, vArray[1]->AsInteger());
    BOOST_CHECK_EQUAL(9, vArray[2]->AsInteger()); 
}

BOOST_AUTO_TEST_CASE( json_parse_string_array_attribute )
{
    std::string vJsonWithStringArrayAttribute(
        "{"
        "   \"myArray\"       : [\"this\",\"is\",\"cool\"]"
        "}");

    ClassModel vClassModel;
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("myArray", tArray<tString>::Instance());

    JSON json(vClassModel);
    std::shared_ptr<Object> vMyObject = json.Parse(vJsonWithStringArrayAttribute, vMyClass);
    std::shared_ptr<Object> * vArray = vMyObject->Get("myArray")->AsArray<tString>();
    BOOST_CHECK_EQUAL("this", vArray[0]->AsString());
    BOOST_CHECK_EQUAL("is", vArray[1]->AsString());
    BOOST_CHECK_EQUAL("cool", vArray[2]->AsString());
}

BOOST_AUTO_TEST_CASE( json_parse_boolean_array_attribute )
{
    std::string vJsonWithBooleanArrayAttribute(
        "{"
        "   \"myArray\"       : [true,false,false]"
        "}");

    ClassModel vClassModel;
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("myArray", tArray<tBoolean>::Instance());

    JSON json(vClassModel);
    std::shared_ptr<Object> vMyObject = json.Parse(vJsonWithBooleanArrayAttribute, vMyClass);
    std::shared_ptr<Object> * vArray = vMyObject->Get("myArray")->AsArray<tBoolean>();
    BOOST_CHECK_EQUAL(true, vArray[0]->AsBoolean());
    BOOST_CHECK_EQUAL(false, vArray[1]->AsBoolean());
    BOOST_CHECK_EQUAL(false, vArray[2]->AsBoolean());
}

BOOST_AUTO_TEST_CASE( json_parse_object_array_attribute )
{
    std::string vTestJsonObject(
        "{"
        "   \"myArray\"       : [{}, {}]"
        "}");

    ClassModel vClassModel;
    Class & vMyClass2 = vClassModel.CreateClass("MyClass2");
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("myArray", tObjectArray::Instance(vMyClass2));

    JSON json(vClassModel);

    // don't do this one liner or your attribute object will get deallocated cause it's not referenced
    //std::shared_ptr<Object> * vArray = json.Parse(vTestJsonObject, *vMyClass)->Get("myArray")->AsObjectArray();

    // save the attribute object in a variable instead so it stays around
    std::shared_ptr<Object> vMyObject = json.Parse(vTestJsonObject, vMyClass)->Get("myArray");
    std::shared_ptr<Object> * vArray = vMyObject->AsObjectArray(vMyClass2);

    BOOST_CHECK_EQUAL("MyClass2", vArray[0]->type.name);
    BOOST_CHECK_EQUAL("MyClass2", vArray[1]->type.name);
}

BOOST_AUTO_TEST_CASE( json_parse_object_with_embedded_object )
{
    std::string vTestJsonObject(
        "{"
        "   \"embeddedObject\": { \"myArray\" : [{}, {}] }"
        "}");

    ClassModel vClassModel;
    Class & vMyClass3 = vClassModel.CreateClass("MyClass3");
    Class & vMyClass2 = vClassModel.CreateClass("MyClass2").AddAttribute("myArray", tObjectArray::Instance(vMyClass3));
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("embeddedObject", vMyClass2);
    
    JSON json(vClassModel);    
    std::shared_ptr<Object> vMyEmbeddedObject = json.Parse(vTestJsonObject, vMyClass)->Get("embeddedObject");
    std::shared_ptr<Object> * vArray = vMyEmbeddedObject->Get("myArray")->AsObjectArray(vMyClass3);
    BOOST_CHECK_EQUAL("MyClass3", vArray[0]->type.name);
    BOOST_CHECK_EQUAL("MyClass3", vArray[1]->type.name);
}

BOOST_AUTO_TEST_CASE( json_parse_object_with_embedded_object_with_missing_attribute_fails )
{
    std::string vTestJsonObject(
        "{"
        "   \"embeddedObject\": {}"
        "}");

    ClassModel vClassModel;
    Class & vMyClass3 = vClassModel.CreateClass("MyClass3");
    Class & vMyClass2 = vClassModel.CreateClass("MyClass2").AddAttribute("myArray", tObjectArray::Instance(vMyClass3));
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("embeddedObject", vMyClass2);

    JSON json(vClassModel);    
    BOOST_CHECK_THROW(json.Parse(vTestJsonObject, vMyClass, false), std::runtime_error);
}

