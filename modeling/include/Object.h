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

#include <map>
#include "ModelExceptions.h"

class Type;
class Class;

// This is an artificial class that is neither part of the MOF (M2) nor the user model (M1).
// It merely exists because, by implementing meta-models, MOF Classes become C++ Classes and User Model Classes become
// C++ objects. So, then, what do User Model objects become? You can't instantiate a C++ object, i.e. C++ does not
// support dynamically created Class objects.
//
class MODELING_API Object {
public:
    Object(Type & iType);
    Object(Type & iType, std::string iObjectID);
    ~Object();

    std::string GetID();

    bool Equals(std::shared_ptr<Object> iObject);

    bool HasValue(std::string iName);
    std::shared_ptr<Object> Set(std::string iName, std::shared_ptr<Object> iValue);
    std::shared_ptr<Object> Get(std::string iName);
 
    std::string AsString(std::string iValue);
    char AsCharacter(char iValue);
    int AsInteger(int iValue);  
    bool AsBoolean(bool iValue);
    
    std::shared_ptr<Object> * AsObjectArray(Class & iBaseType, int iLength);

    template <typename T>
    std::shared_ptr<Object> * AsArray(int iLength) {
        if (!type.Equals(tArray<T>::Instance()))
            throw TypeMismatchException("mismatched type while trying to set value as " + type.name + ", expected type=" + tArray<T>::Instance().name);

        if (iLength <= 0) {
            std::ostringstream oss;
            oss << iLength;
            throw std::invalid_argument(std::string("requested array length of ") + oss.str() + " is not valid");
        }

        DeleteArrayValue();
        mArrayValue = new std::shared_ptr<Object>[iLength];
        mArrayLength = iLength;

        return mArrayValue;
    }

    std::string AsString();
    char AsCharacter();
    int AsInteger();
    bool AsBoolean();        
        
    int GetObjectArrayLength();
    std::shared_ptr<Object> * AsObjectArray(Class & iBaseType);

    int GetArrayLength();
    template <typename T>
    std::shared_ptr<Object> * AsArray() {
        if (!type.Equals(tArray<T>::Instance()))
            throw TypeMismatchException("mismatched type while trying to get value as " + type.name + ", expected type=" + tArray<T>::Instance().name);

        if (mArrayLength <= 0)
            return nullptr;

        return mArrayValue;
    }

    Type & type;

private:
    void DeleteArrayValue();
    void DeleteObjectArrayValue();

    std::string mID;

    std::map<std::string, std::shared_ptr<Object>>  mAttributeValues;
    std::string                                     mStringValue;
    char                                            mCharacterValue;
    int                                             mIntegerValue;
    bool                                            mBooleanValue;
    std::shared_ptr<Object> *                       mArrayValue;
    int                                             mArrayLength;
    std::shared_ptr<Object> *                       mObjectArrayValue;
    int                                             mObjectArrayLength;
    Class *                                         mObjectArrayBaseType;
};
