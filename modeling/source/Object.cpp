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
#include "Object.h"
#include "Type.h"
#include "Class.h"
#include "IDGenerator.h"
#include "datatype/DataTypes.h"


Object::Object(Type & iType)
    : type(iType), mArrayValue(nullptr), mArrayLength(0), mObjectArrayValue(nullptr), mObjectArrayLength(0) {
        mID = Modeling::IDGenerator::GenerateObjectID();
}

Object::Object(Type & iType, std::string iObjectID)
    : type(iType), mID(iObjectID), mArrayValue(nullptr), mArrayLength(0), mObjectArrayValue(nullptr), mObjectArrayLength(0) {
}

Object::~Object() {
    DeleteArrayValue();
    DeleteObjectArrayValue();
}

void Object::DeleteObjectArrayValue() {
    if (mObjectArrayValue) {
        delete[] mObjectArrayValue;
        mObjectArrayValue = nullptr;
        mObjectArrayLength = 0;
    }
}

void Object::DeleteArrayValue() {
    if (mArrayValue) {
        delete[] mArrayValue;
        mArrayValue = nullptr;
        mArrayLength = 0;
    }
}

std::string Object::GetID() { 
    return mID;
}

bool Object::Equals(std::shared_ptr<Object> iObject) {    
    if (!iObject->type.Equals(tNull::Instance()) &&  // type tNull is compatible with all other types
        !type.Equals(iObject->type))
        throw TypeMismatchException("mismatched type while trying to set attribute value, type=" + type.name);

    if (type.IsBuiltIn()) {
        if (type.Equals(tString::Instance()))
            return mStringValue == iObject->AsString();
        if (type.Equals(tCharacter::Instance()))
            return mCharacterValue == iObject->AsCharacter();
        if (type.Equals(tInteger::Instance()))
            return mIntegerValue == iObject->AsInteger();
        if (type.Equals(tBoolean::Instance()))
            return mBooleanValue == iObject->AsBoolean();
        if (type.Equals(tNull::Instance()))
            return iObject->type.Equals(tNull::Instance());

        throw std::exception(std::string("unknown type encountered, type=" + type.name).c_str());
    } else {
        return GetID() == iObject->GetID();
    }
}

std::shared_ptr<Object> Object::Set(std::string iName, std::shared_ptr<Object> iValue) {   
    if (type.IsBuiltIn())
        throw ObjectIsNotAClassException("attempt to set attribute value on type that is not a class, type=" + type.name);

    Class & vClass = dynamic_cast<Class &>(type);

    if (!vClass.HasAttribute(iName)) 
        throw UnknownAttributeException("unknown attribute name=" + iName);

    if (!iValue->type.Equals(tNull::Instance()) &&  // type tNull is compatible with all other types
        !vClass.GetAttributeType(iName).Equals(iValue->type))
        throw TypeMismatchException("mismatched type while trying to set attribute value, type=" + type.name);

    mAttributeValues[iName] = iValue;

    return mAttributeValues[iName];
}

bool Object::HasValue(std::string iName) {
    return mAttributeValues.find(iName) != mAttributeValues.end();
}

std::shared_ptr<Object> Object::Get(std::string iName) {
    if (type.IsBuiltIn())
        throw ObjectIsNotAClassException("attempt to get attribute value from type that is not a class, type=" + type.name);

    Class & vClass = dynamic_cast<Class &>(type);

    if (!vClass.HasAttribute(iName)) 
        throw UnknownAttributeException("unknown attribute name=" + iName);

    return mAttributeValues[iName];
}

std::string Object::AsString(std::string iValue) {
    if (!type.Equals(tString::Instance()))
        throw TypeMismatchException("mismatched type while trying to set value as tString, type=" + type.name);

    mStringValue = iValue;

    return mStringValue;
}

char Object::AsCharacter(char iValue) {
    if (!type.Equals(tCharacter::Instance()))
        throw TypeMismatchException("mismatched type while trying to set value as tCharacter, type=" + type.name);

    mCharacterValue = iValue;

    return mCharacterValue;
}

int Object::AsInteger(int iValue) {
    if (!type.Equals(tInteger::Instance()))
        throw TypeMismatchException("mismatched type while trying to set value as tInteger, type=" + type.name);

    mIntegerValue = iValue;

    return mIntegerValue;
}

bool Object::AsBoolean(bool iValue) {
    if (!type.Equals(tBoolean::Instance()))
        throw TypeMismatchException("mismatched type while trying to set value as tBoolean, type=" + type.name);

    mBooleanValue = iValue;

    return mBooleanValue;
}

std::shared_ptr<Object> * Object::AsObjectArray(Class & iBaseType, int iLength) {
    if (!type.Equals(tObjectArray::Instance(iBaseType)))
        throw TypeMismatchException("mismatched type while trying to set value as " + tObjectArray::Instance(iBaseType).name + ", type=" + type.name);

    if (iLength <= 0) {
        std::ostringstream oss;
        oss << iLength;
        throw std::invalid_argument(std::string("requested array length of ") + oss.str() + " is not valid");
    }

    DeleteObjectArrayValue();
    mObjectArrayValue = new std::shared_ptr<Object>[iLength];
    mObjectArrayLength = iLength;
    mObjectArrayBaseType = &iBaseType;

    return mObjectArrayValue;
}

std::string Object::AsString() {
    if (!type.Equals(tString::Instance()))
        throw TypeMismatchException("mismatched type while trying to get value as tString, type=" + type.name);

    return mStringValue;
}

char Object::AsCharacter() {
    if (!type.Equals(tCharacter::Instance()))
        throw TypeMismatchException("mismatched type while trying to get value as tCharacter, type=" + type.name);

    return mCharacterValue;
}

int Object::AsInteger() {
    if (!type.Equals(tInteger::Instance()))
        throw TypeMismatchException("mismatched type while trying to get value as tInteger, type=" + type.name);

    return mIntegerValue;
}

bool Object::AsBoolean() {
    if (!type.Equals(tBoolean::Instance()))
        throw TypeMismatchException("mismatched type while trying to get value as tBoolean, type=" + type.name);

    return mBooleanValue;
}

int Object::GetArrayLength() {
    return mArrayLength;
}

int Object::GetObjectArrayLength() {
    return mObjectArrayLength;
}

std::shared_ptr<Object> * Object::AsObjectArray(Class & iBaseType) {
    if (!type.Equals(tObjectArray::Instance(iBaseType)))
        throw TypeMismatchException("mismatched type while trying to get value as " + tObjectArray::Instance(iBaseType).name + ", type=" + type.name);

    if (mObjectArrayLength <= 0)
        return nullptr;

    return mObjectArrayValue;
}
