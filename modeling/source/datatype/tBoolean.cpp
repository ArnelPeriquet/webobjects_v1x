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
#include "datatype/tBoolean.h"
#include "Object.h"


tBoolean & tBoolean::Instance() { 
    static tBoolean _instance; 
    return _instance; 
}

tBoolean::tBoolean() 
    : DataType("tBoolean") {
}

std::shared_ptr<Object> tBoolean::Value(bool iValue) {
    std::shared_ptr<Object> vObject = std::make_shared<Object>(Instance());
    vObject->AsBoolean(iValue);

    return vObject;
}