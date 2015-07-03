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
#include "datatype/tArray.h"
#include "datatype/DataTypes.h"
#include "Object.h"
#include "tObject.h"


// various supported instantiations
template class tArray<tCharacter>;
template class tArray<tInteger>;
template class tArray<tString>;
template class tArray<tBoolean>;
template class tArray<tNull>;


template <typename T>
tArray<T> & tArray<T>::Instance() { 
    static tArray<T> _instance(T::Instance());    
    return _instance; 
}

template <typename T>
tArray<T>::tArray(Type & iBaseType) 
    : DataType(std::string("tArray") + "<" + iBaseType.name + ">"), mBaseType(iBaseType) {
}

template <typename T>
bool tArray<T>::IsArray() {
    return true;
}

template <typename T>
std::shared_ptr<Object> tArray<T>::Value() {
    return std::make_shared<Object>(Instance()); //empty array
}

template <typename T>
std::shared_ptr<Object> tArray<T>::Value(char iArray[], int length) {
    std::shared_ptr<Object> vObject = std::make_shared<Object>(Instance());
    vObject->AsArray<T>(length);

    for (int i=0; i<length; i++)
        vObject->AsArray<T>()[i] = tCharacter::Value(iArray[i]);

    return vObject;
}

template <typename T>
std::shared_ptr<Object> tArray<T>::Value(int iArray[], int length) {
    std::shared_ptr<Object> vObject = std::make_shared<Object>(Instance());
    vObject->AsArray<T>(length);

    for (int i=0; i<length; i++)
        vObject->AsArray<T>()[i] = tInteger::Value(iArray[i]);

    return vObject;
}

template <typename T>
std::shared_ptr<Object> tArray<T>::Value(std::string iArray[], int length) {
    std::shared_ptr<Object> vObject = std::make_shared<Object>(Instance());
    vObject->AsArray<T>(length);

    for (int i=0; i<length; i++)
        vObject->AsArray<T>()[i] = tString::Value(iArray[i]);

    return vObject;
}

template <typename T>
std::shared_ptr<Object> tArray<T>::Value(bool iArray[], int length) {
    std::shared_ptr<Object> vObject = std::make_shared<Object>(Instance());
    vObject->AsArray<T>(length);

    for (int i=0; i<length; i++)
        vObject->AsArray<T>()[i] = tBoolean::Value(iArray[i]);

    return vObject;
}
