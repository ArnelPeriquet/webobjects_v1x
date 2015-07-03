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

class Class;
class Object;
class Type;
class ClassModel;


class JsonParser {
public:
    JsonParser(ClassModel & iClassModel);

    std::shared_ptr<Object> Parse(std::string iJsonString, Class & iClass, bool iAllowMissingAttributes = true);

private:
    std::shared_ptr<Object> CreateObject(Class & iClass, boost::property_tree::ptree & iPropTree, bool iAllowMissingAttributes);
    void CreateAttributes(Class & iClass, std::shared_ptr<Object> iObject, boost::property_tree::ptree & iPropTree, bool iAllowMissingAttributes);
    std::shared_ptr<Object> CreateArray(std::string iName, Type & iType, boost::property_tree::ptree & iPropTree);
    std::shared_ptr<Object> CreateObjectArray(std::string iName, Type & iType, boost::property_tree::ptree & iPropTree, bool iAllowMissingAttributes);
    std::shared_ptr<Object> CreatePrimitive(std::string iName, Type & iType, boost::property_tree::ptree & iPropTree);

    ClassModel & mClassModel;
};
