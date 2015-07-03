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
#include "JsonStringifier.h"
#include "Object.h"
#include "Type.h"
#include "Class.h"
#include "ClassModel.h"
#include "datatype/DataTypes.h"


JsonStringifier::JsonStringifier(ClassModel & iClassModel) 
    : mClassModel(iClassModel), mIndentation(0) {
}

void JsonStringifier::Indent(std::stringstream & ss) {
    for (int i=0; i<mIndentation*3; i++)
        ss << " ";
}

std::string JsonStringifier::Stringify(Object & iObject, Class & iClass, bool iAllowMissingAttributes) {   
    std::stringstream ss;
    StringifyObject(ss, iObject, iClass, iAllowMissingAttributes);
    return ss.str();
}

void JsonStringifier::StringifyObject(std::stringstream & ss, Object & iObject, Class & iClass, bool iAllowMissingAttributes) {   
    std::vector<std::string> vAttribNames = iClass.GetAttributeNames();    

    ss << "{\n";
    mIndentation++;
    mIndentation++;    

    for (std::vector<std::string>::iterator vAttribName = vAttribNames.begin(); vAttribName != vAttribNames.end(); ++vAttribName) {              
        if (!iAllowMissingAttributes && !iObject.HasValue(*vAttribName))
            throw std::runtime_error("object is missing value, name=" + *vAttribName);

        if (iObject.HasValue(*vAttribName)) {
            std::shared_ptr<Object> vAttribValue = iObject.Get(*vAttribName);
            Type & vAttribType = iClass.GetAttributeType(*vAttribName); 
            
            mIndentation--;
            Indent(ss);

            ss << *vAttribName << " :\n";

            mIndentation++;
            Indent(ss);         

            if (vAttribType.IsBuiltIn()) {
                if (vAttribType.IsArray())                 
                    StringifyArray(ss, *vAttribValue, vAttribType);
                else if (vAttribType.IsObjectArray())
                    StringifyObjectArray(ss, *vAttribValue, vAttribType, iAllowMissingAttributes);
                else
                    StringifyPrimitive(ss, *vAttribValue, vAttribType);
            } else {
                Class * vAttribClass = dynamic_cast<Class *>(&vAttribType);

                if (vAttribClass)
                    StringifyObject(ss, *vAttribValue, *vAttribClass, iAllowMissingAttributes);
                else
                    throw std::runtime_error("attempt to convert a non-class to a class, type=" + vAttribType.name);
            }                        
        }  

        ss << ",";

        if (vAttribName+1 != vAttribNames.end())
            ss << "\n";
    }

    // remove trailing comma
    ss.seekp(-1, ss.cur);
    ss << "\n";
    
    mIndentation--;
    mIndentation--;
    Indent(ss);
    ss << "}";
}

void JsonStringifier::StringifyArray(std::stringstream & ss, Object & iObject, Type & iType) {
    int vLength = iObject.GetArrayLength();

    ss << "[\n";
    mIndentation++;
    Indent(ss);

    if (iType == tArray<tCharacter>::Instance()) {
        std::shared_ptr<Object> * vArray = iObject.AsArray<tCharacter>();

        for (int i=0; i<vLength; i++) {
            ss << "\"" << vArray[i]->AsCharacter() << "\"";

            if (i != vLength-1) {
                ss << ",\n";
                Indent(ss);
            }
        }
    }

    if (iType == tArray<tInteger>::Instance()) {
        std::shared_ptr<Object> * vArray = iObject.AsArray<tInteger>();

        for (int i=0; i<vLength; i++) {
            ss << vArray[i]->AsInteger();

            if (i != vLength-1) {
                ss << ",\n";
                Indent(ss);
            }
        }
    }

    if (iType == tArray<tString>::Instance()) {
        std::shared_ptr<Object> * vArray = iObject.AsArray<tString>();

        for (int i=0; i<vLength; i++) {
            ss << "\"" << vArray[i]->AsString() << "\"";

            if (i != vLength-1) {
                ss << ",\n";
                Indent(ss);
            }
        }
    }

    if (iType == tArray<tBoolean>::Instance()) {
        std::shared_ptr<Object> * vArray = iObject.AsArray<tBoolean>();

        for (int i=0; i<vLength; i++) {
            ss << (vArray[i]->AsBoolean() ? "true" : "false");

            if (i != vLength-1) {
                ss << ",\n";
                Indent(ss);
            }
        }
    }    

    ss << "\n";
    mIndentation--;
    Indent(ss);
    ss << "]";
}

void JsonStringifier::StringifyObjectArray(std::stringstream & ss, Object & iObject, Type & iType, bool iAllowMissingAttributes) {
    int vLength = iObject.GetObjectArrayLength();

    ss << "[\n";
    mIndentation++;
    Indent(ss);

    if (iType.name.find("tObjectArray") != std::string::npos) {
        int vEndindex = iType.name.find(">");
        std::string vBaseClassName = iType.name.substr(13, vEndindex-13);
        Class & vBaseClass = mClassModel.GetClass(vBaseClassName);

        std::shared_ptr<Object> * vArray = iObject.AsObjectArray(vBaseClass);

        for (int i=0; i<vLength; i++) {
            StringifyObject(ss, *vArray[i], vBaseClass, iAllowMissingAttributes);

            if (i != vLength-1) {
                ss << ",\n";
                Indent(ss);
            }
        }
    } else {
        throw std::runtime_error("internal error: expecting tObjectArray, type=" + iType.name);
    }

    ss << "\n";
    mIndentation--;
    Indent(ss);
    ss << "]";
}


void JsonStringifier::StringifyPrimitive(std::stringstream & ss, Object & iObject, Type & iType) {
    if (iType == tCharacter::Instance())
        ss << "\"" << iObject.AsCharacter() << "\"";

    if (iType == tInteger::Instance())
        ss << iObject.AsInteger();

    if (iType == tString::Instance())
        ss << "\"" << iObject.AsString() << "\"";

    if (iType == tBoolean::Instance())
        ss << (iObject.AsBoolean() ? "true" : "false");

    if (iType == tNull::Instance())
        ss << "null";
}