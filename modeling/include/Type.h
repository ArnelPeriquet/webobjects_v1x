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


class MODELING_API Type {
public:
    static std::string GetFullyQualifiedName(std::string iName, std::string iNameSpace);  

    Type(std::string iName, std::string iNameSpace = "default");

    bool operator ==(const Type & iType);
    bool operator !=(const Type & iType);

    virtual bool Equals(const Type & iType);
    virtual bool IsBuiltIn();
    virtual bool IsArray();
    virtual bool IsObjectArray();

    std::string GetFullyQualifiedName();

    std::string name;
    std::string nameSpace;
};

