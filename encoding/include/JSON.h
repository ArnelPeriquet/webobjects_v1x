/*
 * (C) Copyright 2015  Arnel I Periquet.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 */

#pragma once

#include "JsonStr.h" // by convenience so user does not have to include this seperately

class Class;
class Object;
class ClassModel;
class JsonStr;

//
// This class is a facade and is the only thing exported from this library.
//
// - This library requires modeling.dll which itself has no library dependencies at all (for usage, nor for building).
// - No external 3rd party libraries are needed to use this library. (However, you'll need boost ptree header, to build the source code.)
//
//
class ENCODING_API JSON {
public:
    JSON(ClassModel & iClassModel);

    void ParseSchema(JsonStr iAdapter);
    void ParseSchema(std::string iJssnString); // JSSN (Jazzin') JavaScript Schema Notation
    //std::string StringifySchema();

    std::shared_ptr<Object> Parse(std::string iJsonString, Class & iClass, bool iAllowMissingAttributes = true);
    std::string Stringify(Object& iObject, Class & iClass, bool iAllowMissingAttributes = true);

private:
    ClassModel & mClassModel;
};