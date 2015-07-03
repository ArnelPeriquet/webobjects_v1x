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

#include "datatype/DataType.h"


class Object;


class MODELING_API tString: public DataType {
public:
    static tString & Instance(); 
    static std::shared_ptr<Object> Value(std::string iValue);
private:
    tString();
};
