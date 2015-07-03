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
#include "JssnParser.h"
#include "ClassModel.h"
#include "Class.h"
#include "Type.h"
#include "datatype/DataTypes.h"


JssnParser::JssnParser(ClassModel & iClassModel) 
    : mClassModel(iClassModel) {
}

void JssnParser::Parse(std::string iJssnString) {
    try {        
        ptree vPropTree;
        read_json(std::stringstream(iJssnString), vPropTree);

        BOOST_FOREACH(ptree::value_type & vChild, vPropTree) {
            ParseClass(vChild.first, vChild.second);
        }
    } catch (std::exception & ex) {
        throw std::runtime_error(std::string(ex.what()) + ", jssn=" + iJssnString);
    }
}

void JssnParser::ParseClass(std::string iClassName, boost::property_tree::ptree & iPropTree) {
    if (mClassModel.HasClass("iClassName"))
        throw std::runtime_error(std::string("attempt to define duplicate class, name=") + iClassName);

    Class & vClass = mClassModel.CreateClass(iClassName);

    BOOST_FOREACH(ptree::value_type & vChild, iPropTree) {
        Type & vType = CreateType(iPropTree.get<std::string>(vChild.first));
        vClass.AddAttribute(vChild.first, vType);
    }
}

Type & JssnParser::CreateType(std::string iTypeName) {
    if (iTypeName == tCharacter::Instance().name)
        return tCharacter::Instance();

    if (iTypeName == tInteger::Instance().name)
        return tInteger::Instance();

    if (iTypeName == tString::Instance().name)
        return tString::Instance();

    if (iTypeName == tBoolean::Instance().name)
        return tBoolean::Instance();

    if (iTypeName == tNull::Instance().name)
        return tNull::Instance();

    if (iTypeName == tArray<tCharacter>::Instance().name)
        return tArray<tCharacter>::Instance();

    if (iTypeName == tArray<tInteger>::Instance().name)
        return tArray<tInteger>::Instance();

    if (iTypeName == tArray<tString>::Instance().name)
        return tArray<tString>::Instance();

    if (iTypeName == tArray<tBoolean>::Instance().name)
        return tArray<tBoolean>::Instance();

    if (iTypeName == tArray<tNull>::Instance().name)
        return tArray<tNull>::Instance();

    if (iTypeName.find("tObjectArray") != std::string::npos) {
        int vEndindex = iTypeName.find(">");
        std::string vBaseClassName = iTypeName.substr(13, vEndindex-13); 
        Class & vBaseClass = mClassModel.GetClass(vBaseClassName);
        return tObjectArray::Instance(vBaseClass);
    }

    return mClassModel.GetClass(iTypeName);
}