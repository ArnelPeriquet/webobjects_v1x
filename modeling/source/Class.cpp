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
#include "Class.h"
#include "tObject.h"


Class::Class(std::string iName, std::string iNameSpace)
    : Type(iName, iNameSpace) {
        AddSuperClass(tObject::Instance());
}

bool Class::IsBuiltIn() { 
    return false; 
}

void Class::AddSuperClass(Class & iSuperClass) {
    mSupers.push_back(&iSuperClass);
}

std::vector<std::string> Class::GetAttributeNames() {
    std::vector<std::string> vNames;

    for (std::map<std::string, Type*>::iterator it=mAttributes.begin(); it != mAttributes.end(); ++it)
        vNames.push_back(it->first);   

    return vNames;
}

bool Class::HasAttribute(std::string iName) {
    return mAttributes.find(iName) != mAttributes.end(); 
}

Type & Class::GetAttributeType(std::string iName) {
    if (mAttributes.find(iName) == mAttributes.end())
        throw std::invalid_argument("attempt to get attribute type for unknown attribute");

    return *mAttributes[iName];
}

Class & Class::AddAttribute(std::string iName, Type & iType) {
    if (mAttributes.find(iName) != mAttributes.end())
        throw std::invalid_argument("attempt to add attribute that already exists");

    mAttributes[iName] = &iType;

    return *this;
}
