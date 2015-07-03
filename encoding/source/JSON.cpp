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
#include "JSON.h"
#include "Class.h"
#include "Object.h"
#include "ClassModel.h"
#include "JsonParser.h"
#include "JsonStringifier.h"
#include "JssnParser.h"
#include "JsonStr.h"


JSON::JSON(ClassModel & iClassModel) 
    : mClassModel(iClassModel) {
}

void JSON::ParseSchema(JsonStr iAdapter) {
    ParseSchema(iAdapter());
}

void JSON::ParseSchema(std::string iJssnString) {
    JssnParser parser(mClassModel);
    return parser.Parse(iJssnString);
}

std::shared_ptr<Object> JSON::Parse(std::string iJsonString, Class & iClass, bool iAllowMissingAttributes) {
    JsonParser parser(mClassModel);
    return parser.Parse(iJsonString, iClass, iAllowMissingAttributes);
}

std::string JSON::Stringify(Object& iObject, Class & iClass, bool iAllowMissingAttributes) {
    JsonStringifier stringifier(mClassModel);
    return stringifier.Stringify(iObject, iClass, iAllowMissingAttributes);
}
