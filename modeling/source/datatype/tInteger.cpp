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
#include "datatype/tInteger.h"
#include "Object.h"


tInteger & tInteger::Instance() { 
    static tInteger _instance; 
    return _instance; 
}

tInteger::tInteger() 
    : DataType("tInteger") {
}

std::shared_ptr<Object> tInteger::Value(int iValue) {
    std::shared_ptr<Object> vObject = std::make_shared<Object>(Instance());
    vObject->AsInteger(iValue);

    return vObject;
}