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
#include "Class.h"
#include "ClassModel.h"
#include "JSON.h"
#include "datatype/DataTypes.h"

namespace {
    std::string vSimpleClassStr = "[" 
                                        "{"
                                            "\"_name\"      : \"Query\","
                                        "},"
                                        "{"
                                            "\"_name\"      : \"Request\","
                                            "\"char_val\"   : \"tCharacter\","
                                            "\"str_val\"    : \"tString\","
                                            "\"int_val\"    : \"tInteger\","
                                            "\"bool_val\"   : \"tBoolean\","
                                            "\"null_val\"   : \"tNull\","
                                            "\"obj_val\"    : \"Query\""
                                        "}"
                                  "]";
}

/*
BOOST_AUTO_TEST_CASE( jssn_parse_class_name )
{  
    JSON jssn;
    std::shared_ptr<ClassModel> vClassModel = jssn.Parse(vSimpleClassStr);
    BOOST_CHECK(vClassModel->HasClass("Request"));
}
*/
/*

BOOST_AUTO_TEST_CASE( jssn_parse_class_attribute_supports_character )
{
    JSSN jssn;
    std::shared_ptr<ClassModel> vClassModel = jssn.Parse(vSimpleClassStr);
    std::shared_ptr<Class> vRequest = vClassModel->GetClass("Request");
    BOOST_CHECK(vRequest->GetAttributeType("char_val") == tCharacter::Instance());
}

BOOST_AUTO_TEST_CASE( jssn_parse_class_attribute_supports_string )
{
    JSSN jssn;
    std::shared_ptr<ClassModel> vClassModel = jssn.Parse(vSimpleClassStr);
    std::shared_ptr<Class> vRequest = vClassModel->GetClass("Request");
    BOOST_CHECK(vRequest->GetAttributeType("str_val") == tString::Instance());
}

BOOST_AUTO_TEST_CASE( jssn_parse_class_attribute_supports_integer )
{
    JSSN jssn;
    std::shared_ptr<ClassModel> vClassModel = jssn.Parse(vSimpleClassStr);
    std::shared_ptr<Class> vRequest = vClassModel->GetClass("Request");
    BOOST_CHECK(vRequest->GetAttributeType("int_val") == tInteger::Instance());
}

BOOST_AUTO_TEST_CASE( jssn_parse_class_attribute_supports_boolean )
{
    JSSN jssn;
    std::shared_ptr<ClassModel> vClassModel = jssn.Parse(vSimpleClassStr);
    std::shared_ptr<Class> vRequest = vClassModel->GetClass("Request");
    BOOST_CHECK(vRequest->GetAttributeType("bool_val") == tBoolean::Instance());
}

BOOST_AUTO_TEST_CASE( jssn_parse_class_attribute_supports_null )
{
    JSSN jssn;
    std::shared_ptr<ClassModel> vClassModel = jssn.Parse(vSimpleClassStr);
    std::shared_ptr<Class> vRequest = vClassModel->GetClass("Request");
    BOOST_CHECK(vRequest->GetAttributeType("null_val") == tNull::Instance());
}

BOOST_AUTO_TEST_CASE( jssn_parse_class_attribute_supports_object )
{
    JSSN jssn;
    std::shared_ptr<ClassModel> vClassModel = jssn.Parse(vSimpleClassStr);
    std::shared_ptr<Class> vRequest = vClassModel->GetClass("Request");
    std::shared_ptr<Class> vQuery = vClassModel->GetClass("Query");
    BOOST_CHECK(vRequest->GetAttributeType("obj_val") == *vQuery);
}
*/
