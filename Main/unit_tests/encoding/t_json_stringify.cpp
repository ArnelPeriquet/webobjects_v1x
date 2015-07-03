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
#include "Class.h"
#include "Object.h"
#include "ClassModel.h"
#include "datatype/DataTypes.h"


BOOST_AUTO_TEST_CASE( json_stringify_char ) {
    ClassModel vClassModel;
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("myValue", tCharacter::Instance());    

    std::shared_ptr<Object> vMyObject = std::make_shared<Object>(vMyClass);
    vMyObject->Set("myValue", tCharacter::Value('a'));

    JSON json(vClassModel);
    std::cout << json.Stringify(*vMyObject, vMyClass) << std::endl;
}

BOOST_AUTO_TEST_CASE( json_stringify_int ) {
    ClassModel vClassModel;
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("myValue", tInteger::Instance());

    std::shared_ptr<Object> vMyObject = std::make_shared<Object>(vMyClass);
    vMyObject->Set("myValue", tInteger::Value(3));

    JSON json(vClassModel);
    std::cout << json.Stringify(*vMyObject, vMyClass) << std::endl;
}

BOOST_AUTO_TEST_CASE( json_stringify_string ) {
    ClassModel vClassModel;
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("myValue", tString::Instance());
    
    std::shared_ptr<Object> vMyObject = std::make_shared<Object>(vMyClass);
    vMyObject->Set("myValue", tString::Value("hello"));

    JSON json(vClassModel);
    std::cout << json.Stringify(*vMyObject, vMyClass) << std::endl;
}

BOOST_AUTO_TEST_CASE( json_stringify_bool ) {
    ClassModel vClassModel;
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("myValue", tBoolean::Instance());
  
    std::shared_ptr<Object> vMyObject = std::make_shared<Object>(vMyClass);
    vMyObject->Set("myValue", tBoolean::Value(true));

    JSON json(vClassModel);
    std::cout << json.Stringify(*vMyObject, vMyClass) << std::endl;
}

BOOST_AUTO_TEST_CASE( json_stringify_null ) {
    ClassModel vClassModel;
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("myValue", tNull::Instance());
    
    std::shared_ptr<Object> vMyObject = std::make_shared<Object>(vMyClass);
    vMyObject->Set("myValue", tNull::Value());

    JSON json(vClassModel);
    std::cout << json.Stringify(*vMyObject, vMyClass) << std::endl;
}

BOOST_AUTO_TEST_CASE( json_stringify_array_of_chars ) {
    ClassModel vClassModel;
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("myArray", tArray<tCharacter>::Instance());
    
    std::shared_ptr<Object> vMyObject = std::make_shared<Object>(vMyClass);
    char vArray[] = { 'a', 'b', 'c' };
    vMyObject->Set("myArray", tArray<tCharacter>::Value(vArray, 3));

    JSON json(vClassModel);
    std::cout << json.Stringify(*vMyObject, vMyClass) << std::endl;
}

BOOST_AUTO_TEST_CASE( json_stringify_array_of_ints ) {
    ClassModel vClassModel;    
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("myArray", tArray<tInteger>::Instance());
    
    std::shared_ptr<Object> vMyObject = std::make_shared<Object>(vMyClass);
    int vArray[] = { 7, 1, 9 };
    vMyObject->Set("myArray", tArray<tInteger>::Value(vArray, 3));

    JSON json(vClassModel);
    std::cout << json.Stringify(*vMyObject, vMyClass) << std::endl;
}

BOOST_AUTO_TEST_CASE( json_stringify_array_of_strings ) {
    ClassModel vClassModel;
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("myArray", tArray<tString>::Instance());
    
    std::shared_ptr<Object> vMyObject = std::make_shared<Object>(vMyClass);
    std::string vArray[] = { "this", "is", "cool" };
    vMyObject->Set("myArray", tArray<tString>::Value(vArray, 3));

    JSON json(vClassModel);
    std::cout << json.Stringify(*vMyObject, vMyClass) << std::endl;
}

BOOST_AUTO_TEST_CASE( json_stringify_array_of_booleans ) {
    ClassModel vClassModel;
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("myArray", tArray<tBoolean>::Instance());
    
    std::shared_ptr<Object> vMyObject = std::make_shared<Object>(vMyClass);
    bool vArray[] = { false, true, false };
    vMyObject->Set("myArray", tArray<tBoolean>::Value(vArray, 3));

    JSON json(vClassModel);
    std::cout << json.Stringify(*vMyObject, vMyClass) << std::endl;
}

BOOST_AUTO_TEST_CASE( json_stringify_object_attribute_with_array_of_bool_attribute ) {
    ClassModel vClassModel;
    Class & vMyClass2 = vClassModel.CreateClass("MyClass2").AddAttribute("myArray", tArray<tBoolean>::Instance());
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("embeddedObject", vMyClass2);

    std::shared_ptr<Object> vMyObject = std::make_shared<Object>(vMyClass);
    std::shared_ptr<Object> vMyInnerObject = vMyObject->Set("embeddedObject", std::make_shared<Object>(vMyClass2));
    bool vArray[] = { false, true, false };
    vMyInnerObject->Set("myArray", tArray<tBoolean>::Value(vArray, 3));

    JSON json(vClassModel);
    std::cout << json.Stringify(*vMyObject, vMyClass) << std::endl;
}

BOOST_AUTO_TEST_CASE( json_stringify_object_attribute_with_array_of_object_attribute ) {
    ClassModel vClassModel;
    Class & vMyClass3 = vClassModel.CreateClass("MyClass3");
    Class & vMyClass2 = vClassModel.CreateClass("MyClass2").AddAttribute("myArray", tObjectArray::Instance(vMyClass3));
    Class & vMyClass = vClassModel.CreateClass("MyClass").AddAttribute("embeddedObject", vMyClass2);

    std::shared_ptr<Object> vMyObject = std::make_shared<Object>(vMyClass);
    std::shared_ptr<Object> vMyInnerObject = vMyObject->Set("embeddedObject", std::make_shared<Object>(vMyClass2));

    vMyInnerObject->Set("myArray", std::make_shared<Object>(tObjectArray::Instance(vMyClass3)))->AsObjectArray(vMyClass3, 3); // allocate the array
    std::shared_ptr<Object> * vObjectArray = vMyInnerObject->Get("myArray")->AsObjectArray(vMyClass3);
    vObjectArray[0] = std::make_shared<Object>(vMyClass3);
    vObjectArray[1] = std::make_shared<Object>(vMyClass3);
    vObjectArray[2] = std::make_shared<Object>(vMyClass3);

    JSON json(vClassModel);
    std::cout << json.Stringify(*vMyObject, vMyClass) << std::endl;
}

