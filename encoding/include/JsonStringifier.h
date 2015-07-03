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

class Object;
class Type;
class Class;
class ClassModel;


class JsonStringifier {
public:
    JsonStringifier(ClassModel & iClassModel);
    std::string Stringify(Object & iObject, Class & iClass, bool iAllowMissingAttributes = true);

private:
    void Indent(std::stringstream & ss);
    void StringifyObject(std::stringstream & ss, Object & iObject, Class & iClass, bool iAllowMissingAttributes);
    void StringifyArray(std::stringstream & ss, Object & iObject, Type & iType);
    void StringifyObjectArray(std::stringstream & ss, Object & iObject, Type & iType, bool iAllowMissingAttributes);
    void StringifyPrimitive(std::stringstream & ss, Object & iObject, Type & iType);

    ClassModel & mClassModel;
    int mIndentation;
};