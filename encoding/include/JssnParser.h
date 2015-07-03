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

#include <boost/property_tree/ptree.hpp>

class ClassModel;
class Class;
class Type;


// JavaScript Schema Notation (Jazzin')
class JssnParser {
public:
    JssnParser(ClassModel & iClassModel);
    void Parse(std::string iJssnString);

private:
    void ParseClass(std::string iClassName, boost::property_tree::ptree & iPropTree);
    Type & CreateType(std::string iTypeName);

    ClassModel & mClassModel;
};