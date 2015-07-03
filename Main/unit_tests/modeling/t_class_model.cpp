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
#include "ClassModel.h"
#include "Class.h"


BOOST_AUTO_TEST_CASE( class_model_create_type ) 
{
    ClassModel vClassModel;
    BOOST_CHECK_NO_THROW(vClassModel.CreateClass("Employee"));
}

BOOST_AUTO_TEST_CASE( class_model_adding_same_type_name_twice_fails )
{    
    ClassModel vClassModel;
    vClassModel.CreateClass("Employee");
    BOOST_CHECK_THROW(vClassModel.CreateClass("Employee"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE( class_model_get_missing_type_fails )
{
    ClassModel vClassModel;
    BOOST_CHECK_THROW(vClassModel.GetClass("Employee"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE( class_model_get_added_type_exists )
{
    ClassModel vClassModel;    
    Class & vMyClass = vClassModel.CreateClass("Employee"); // use default namespace to add

    BOOST_CHECK(vClassModel.HasClass("Employee")); // use default namespace to retrieve
    BOOST_CHECK_NO_THROW(vClassModel.HasClass(vMyClass.name, vMyClass.nameSpace));
}

BOOST_AUTO_TEST_CASE( class_model_get_added_type_succeeds )
{
    ClassModel vClassModel;    
    Class & vMyClass = vClassModel.CreateClass("Employee"); // use default namespace to add

    BOOST_CHECK_NO_THROW(vClassModel.GetClass("Employee")); // use default namespace to retrieve
    BOOST_CHECK_NO_THROW(vClassModel.GetClass(vMyClass.name, vMyClass.nameSpace));
}