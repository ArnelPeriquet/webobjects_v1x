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
#include "ClassModel.h"
#include "Class.h"


// stored by fully qualified name rather than by ID to ensure types have unique names
Class & ClassModel::CreateClass(std::string iName, std::string iNameSpace) {
    std::shared_ptr<Class> vType = std::make_shared<Class>(iName, iNameSpace);
    std::string vFullyQualifiedName = vType->GetFullyQualifiedName();

    if (mClasses.find(vFullyQualifiedName) != mClasses.end())
        throw std::runtime_error("type model attempted to create a class whose name already exists, type=" + 
                                    vType->GetFullyQualifiedName());

    mClasses[vFullyQualifiedName] = vType;

    return *mClasses[vFullyQualifiedName];
}

bool ClassModel::HasClass(std::string iName, std::string iNameSpace) {
    std::string vFullyQualifiedName = Class::GetFullyQualifiedName(iName, iNameSpace);

    return mClasses.find(vFullyQualifiedName) != mClasses.end();
}

Class & ClassModel::GetClass(std::string iName, std::string iNameSpace) {
    std::string vFullyQualifiedName = Class::GetFullyQualifiedName(iName, iNameSpace);

    if (mClasses.find(vFullyQualifiedName) == mClasses.end())
        throw std::runtime_error("class does not exist, name=" + vFullyQualifiedName);

    return *mClasses[vFullyQualifiedName];
}