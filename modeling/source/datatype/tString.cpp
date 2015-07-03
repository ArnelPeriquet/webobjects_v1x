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
#include "datatype/tString.h"
#include "Object.h"


tString & tString::Instance() { 
    static tString _instance; 
    return _instance; 
}

tString::tString() 
    : DataType("tString") {
}

std::shared_ptr<Object> tString::Value(std::string iValue) {
    std::shared_ptr<Object> vObject = std::make_shared<Object>(Instance());
    vObject->AsString(iValue);

    return vObject;
}