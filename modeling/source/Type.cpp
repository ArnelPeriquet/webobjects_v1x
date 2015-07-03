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
#include "Type.h"


std::string Type::GetFullyQualifiedName(std::string iName, std::string iNameSpace) { 
    return iNameSpace + "." + iName; 
}

Type::Type(std::string iName, std::string iNameSpace)
    : name(iName), nameSpace(iNameSpace) {
}

bool Type::operator ==(const Type & iType) {
    return Equals(iType);
}

bool Type::operator !=(const Type & iType) {
    return !Equals(iType);
}

bool Type::Equals(const Type & iType) {
    return (name + nameSpace) == iType.name + iType.nameSpace;
}

bool Type::IsBuiltIn() {
    return false;
}

bool Type::IsArray() {
    return false;
}

bool Type::IsObjectArray() {
    return false;
}

std::string Type::GetFullyQualifiedName() { 
    return GetFullyQualifiedName(name, nameSpace);
}
