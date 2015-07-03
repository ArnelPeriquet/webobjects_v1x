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
#include <vector>
#include "Type.h"


class MODELING_API Class: public Type {
public:        
    Class(std::string iName, std::string iNameSpace = "default");

    virtual bool IsBuiltIn();    

    virtual void AddSuperClass(Class & iSuperClass);
    virtual std::vector<std::string> GetAttributeNames();    
    virtual bool HasAttribute(std::string iName);
    virtual Type & GetAttributeType(std::string iName);
    virtual Class & AddAttribute(std::string iName, Type & iType);

private:
    std::vector<Class *> mSupers;
    std::map<std::string, Type *> mAttributes;
};
