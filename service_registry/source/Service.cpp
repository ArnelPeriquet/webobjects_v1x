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
#include "Service.h"
#include "Modeling.h"


Service::Service(std::string iName)
    : name(iName) {
}

Service & Service::AddParameter(std::string iName, Type & iType) {
    if (mParameters.find(iName) != mParameters.end())
        throw std::invalid_argument("attempt to add parameter that already exists, name=" + iName);

    mParameters[iName] = &iType;

    return *this;
}
