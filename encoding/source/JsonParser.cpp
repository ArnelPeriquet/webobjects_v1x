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
#include "JsonParser.h"
#include "Class.h"
#include "Object.h"
#include "Type.h"
#include "ClassModel.h"
#include "tObject.h"
#include "datatype/DataTypes.h"


namespace {
    template <typename T>
    std::vector<T> as_vector(ptree & pt, ptree::key_type const & key)
    {
        std::vector<T> r;

        BOOST_FOREACH(ptree::value_type & vChild, pt.get_child(key)) {
            r.push_back(vChild.second.get_value<T>());
        }

        return r;
    }

    std::vector<ptree *> as_vector(ptree & pt, ptree::key_type const & key)
    {
        std::vector<ptree *> r;

        BOOST_FOREACH(ptree::value_type & vChild, pt.get_child(key)) {
            r.push_back(&vChild.second);
        }

        return r;
    }
}

JsonParser::JsonParser(ClassModel & iClassModel) 
    : mClassModel(iClassModel) {
}

std::shared_ptr<Object> JsonParser::Parse(std::string iJsonString, Class & iClass, bool iAllowMissingAttributes) {
    try {
        ptree vPropTree;
        read_json(std::stringstream(iJsonString), vPropTree);
        return CreateObject(iClass, vPropTree, iAllowMissingAttributes);
    } catch (std::exception & ex) {
        throw std::runtime_error(std::string(ex.what()) + ", json=" + iJsonString);
    }
}

std::shared_ptr<Object> JsonParser::CreateObject(Class & iClass, ptree & iPropTree, bool iAllowMissingAttributes) {
    std::shared_ptr<Object> vObject = std::make_shared<Object>(iClass);
    CreateAttributes(iClass, vObject, iPropTree, iAllowMissingAttributes);
    return vObject;
}

void JsonParser::CreateAttributes(Class & iClass, std::shared_ptr<Object> iObject, boost::property_tree::ptree & iPropTree, bool iAllowMissingAttributes) {
    std::vector<std::string> vAttribNames = iClass.GetAttributeNames();

    for (std::vector<std::string>::iterator vAttribName = vAttribNames.begin(); vAttribName != vAttribNames.end(); ++vAttribName) {                
        boost::optional<boost::property_tree::ptree&> vChild = iPropTree.get_child_optional(*vAttribName);

        if (!iAllowMissingAttributes && !vChild)
            throw std::runtime_error("missing attribute, name=" + *vAttribName);

        if (vChild) {
            std::shared_ptr<Object> vAttribValue;
            Type & vAttribType = iClass.GetAttributeType(*vAttribName);

            if (vAttribType.IsBuiltIn()) {
                if (vAttribType.IsArray())
                    vAttribValue = CreateArray(*vAttribName, vAttribType, iPropTree);
                else if (vAttribType.IsObjectArray())
                    vAttribValue = CreateObjectArray(*vAttribName, vAttribType, iPropTree, iAllowMissingAttributes);
                else
                    vAttribValue = CreatePrimitive(*vAttribName, vAttribType, iPropTree);
            } else {
                Class * vAttribClass = dynamic_cast<Class *>(&vAttribType);

                if (vAttribClass)
                    vAttribValue = CreateObject(*vAttribClass, iPropTree.get_child(*vAttribName), iAllowMissingAttributes);
                else
                    throw std::runtime_error("attempt to convert a non-class to a class, type=" + vAttribType.name);
            }

            iObject->Set(*vAttribName,  vAttribValue);
        }
    }
}

std::shared_ptr<Object> JsonParser::CreateArray(std::string iName, Type & iType, boost::property_tree::ptree & iPropTree) {
    if (iType == tArray<tCharacter>::Instance()) {
        std::vector<char> vVect = as_vector<char>(iPropTree, iName);

        if (vVect.size() == 0)
            return tArray<tCharacter>::Value(); // empty array
        else
            return tArray<tCharacter>::Value(&(vVect[0]), vVect.size());
    }

    if (iType == tArray<tInteger>::Instance()) {
        std::vector<int> vVect = as_vector<int>(iPropTree, iName);

        if (vVect.size() == 0)
            return tArray<tInteger>::Value(); // empty array
        else
            return tArray<tInteger>::Value(&(vVect[0]), vVect.size());
    }

    if (iType == tArray<tString>::Instance()) {
        std::vector<std::string> vVect = as_vector<std::string>(iPropTree, iName);

        if (vVect.size() == 0)
            return tArray<tString>::Value(); // empty array
        else
            return tArray<tString>::Value(&(vVect[0]), vVect.size());
    }

    if (iType == tArray<tBoolean>::Instance()) {
        std::shared_ptr<Object> vReturnVal;

        std::vector<bool> vVect = as_vector<bool>(iPropTree, iName);

        if (vVect.size() == 0) {
            return tArray<tBoolean>::Value(); // empty array
        } else {
            bool * vBools = new bool[vVect.size()];

            try {
                for (size_t i=0; i<vVect.size(); i++)
                    vBools[i] = vVect[i];

                vReturnVal = tArray<tBoolean>::Value(vBools, vVect.size());
            } catch (std::exception & ex) {
                delete[] vBools;
                throw ex;
            }

            delete[] vBools;

            return vReturnVal;
        }
    }

    throw std::runtime_error("unsupported tArray, name=" + iName + ", type=" + iType.name);
}

std::shared_ptr<Object> JsonParser::CreateObjectArray(std::string iName, Type & iType, boost::property_tree::ptree & iPropTree, bool iAllowMissingAttributes) {
    if (iType.name.find("tObjectArray") != std::string::npos) {
        std::shared_ptr<Object> vReturnVal;

        int vEndindex = iType.name.find(">");
        std::string vBaseClassName = iType.name.substr(13, vEndindex-13); 
        Class & vBaseClass = mClassModel.GetClass(vBaseClassName);

        std::vector<ptree *> vVect = as_vector(iPropTree, iName);

        if (vVect.size() == 0) {
            return tObjectArray::Value(vBaseClass); // empty array
        } else {
            std::shared_ptr<Object> * vObjects = new std::shared_ptr<Object>[vVect.size()];

            try {
                for (size_t i=0; i<vVect.size(); i++)
                    vObjects[i] = CreateObject(vBaseClass, *vVect[i], iAllowMissingAttributes);

                vReturnVal = tObjectArray::Value(vBaseClass, vObjects, vVect.size());
            } catch (std::exception & ex) {
                delete[] vObjects;
                throw ex;
            }

            delete[] vObjects;

            return vReturnVal;
        }
    }

    throw std::runtime_error("internal error: expecting tObjectArray, name=" + iName + ", type=" + iType.name);
}

std::shared_ptr<Object> JsonParser::CreatePrimitive(std::string iName, Type & iType, boost::property_tree::ptree & iPropTree) {
    if (iType == tCharacter::Instance())
        return tCharacter::Value(iPropTree.get<char>(iName));

    if (iType == tInteger::Instance())
        return tInteger::Value(iPropTree.get<int>(iName));

    if (iType == tString::Instance())
        return tString::Value(iPropTree.get<std::string>(iName));

    if (iType == tBoolean::Instance())
        return tBoolean::Value(iPropTree.get<bool>(iName));

    if (iType == tNull::Instance())
        return tNull::Value();

    throw std::runtime_error("unsupported primitive type, name=" + iName + ", type=" + iType.name);
}
