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
class Class;

class MODELING_API ClassModel {
public:
    Class & CreateClass(std::string iName, std::string iNameSpace = "default");
    bool HasClass(std::string iName, std::string iNameSpace = "default");
    Class & GetClass(std::string iName, std::string iNameSpace = "default");

private:
    std::map<std::string, std::shared_ptr<Class>> mClasses;
};
