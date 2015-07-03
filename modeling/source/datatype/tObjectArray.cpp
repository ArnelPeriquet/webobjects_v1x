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
#include "datatype/tObjectArray.h"
#include "Class.h"
#include "Object.h"


std::map<std::string, std::shared_ptr<tObjectArray>> tObjectArray::mObjectArrayTypes;


std::shared_ptr<Object> tObjectArray::Value(Class & iBaseType) {
    return std::make_shared<Object>(Instance(iBaseType)); //empty array
}

std::shared_ptr<Object> tObjectArray::Value(Class & iBaseType, std::shared_ptr<Object> iArray[], int length) {
    std::shared_ptr<Object> vObject = std::make_shared<Object>(Instance(iBaseType));
    vObject->AsObjectArray(iBaseType, length);

    for (int i=0; i<length; i++)
        vObject->AsObjectArray(iBaseType)[i] = iArray[i];

    return vObject;
}

tObjectArray & tObjectArray::Instance(Class & iBaseType) {
    if (mObjectArrayTypes.find(iBaseType.name) == mObjectArrayTypes.end())
        mObjectArrayTypes[iBaseType.name] = std::make_shared<tObjectArray>(iBaseType);

    return *mObjectArrayTypes[iBaseType.name]; 
}

tObjectArray::tObjectArray(Class & iBaseType) 
    : DataType("tObjectArray<" + iBaseType.name + ">"), mBaseType(iBaseType) {
}

bool tObjectArray::IsObjectArray() {
    return true;
}

