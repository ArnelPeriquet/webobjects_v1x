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


class ObjectIsNotAClassException: public std::exception {
public:
    ObjectIsNotAClassException(std::string iMsg)
        : std::exception(iMsg.c_str()) {}
};

class UnknownAttributeException: public std::exception {
public:
    UnknownAttributeException(std::string iMsg)
        : std::exception(iMsg.c_str()) {}
};

class TypeMismatchException: public std::exception {
public:
    TypeMismatchException(std::string iMsg)
        : std::exception(iMsg.c_str()) {}
};