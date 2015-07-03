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
#include "datatype/DataType.h"

class Class;
class Object;
class tObjectArray;

class MODELING_API tObjectArray: public DataType {
public:
    static std::shared_ptr<Object> Value(Class & iBaseType); // empty array
    static std::shared_ptr<Object> Value(Class & iBaseType, std::shared_ptr<Object> iArray[], int length);

    static tObjectArray & Instance(Class & iBaseType);

    tObjectArray(Class & iBaseType);
    
    bool IsObjectArray();

private:
    static std::map<std::string, std::shared_ptr<tObjectArray>> mObjectArrayTypes;    

    Class & mBaseType;
};
