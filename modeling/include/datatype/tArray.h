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


class Type;
class Object;


template <typename T>
class MODELING_API tArray: public DataType {
public:
    static tArray<T> & Instance(); 

    virtual bool IsArray();

    static std::shared_ptr<Object> Value(); // empty array
    static std::shared_ptr<Object> Value(char iArray[], int length);
    static std::shared_ptr<Object> Value(int iArray[], int length);
    static std::shared_ptr<Object> Value(std::string iArray[], int length);
    static std::shared_ptr<Object> Value(bool iArray[], int length);

private:
    tArray(Type & iBaseType);

    Type & mBaseType;
};
