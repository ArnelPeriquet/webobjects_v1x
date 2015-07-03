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
#include "datatype/tNull.h"
#include "Object.h"


tNull & tNull::Instance() { 
    static tNull _instance; 
    return _instance; 
}

tNull::tNull() 
    : DataType("tNull") {
}

std::shared_ptr<Object> tNull::Value() {
    return std::make_shared<Object>(Instance());
}