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
#include "datatype/tCharacter.h"
#include "Object.h"


tCharacter & tCharacter::Instance() { 
    static tCharacter _instance; 
    return _instance; 
}

tCharacter::tCharacter()
    : DataType("tCharacter") {
}

std::shared_ptr<Object> tCharacter::Value(char iValue) {
    std::shared_ptr<Object> vObject = std::make_shared<Object>(Instance());
    vObject->AsCharacter(iValue);

    return vObject;
}