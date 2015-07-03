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
#include "tObject.h"


tObject & tObject::Instance() {
    static tObject _instance; 
    return _instance; 
}

tObject::tObject()
    : Class("tObject") {
}

bool tObject::IsBuiltIn() {
    return true;
}

void tObject::AddSuperClass(Class & iSuperClass) {
    throw std::runtime_error("attempt to add superclass to tObject, name=" + iSuperClass.name);
}
