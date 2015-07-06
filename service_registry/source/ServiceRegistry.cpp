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
#include "ServiceRegistry.h"
#include "Service.h"


Service & ServiceRegistry::Register(Service & iService, std::string iPath) {
    std::string vUniqueName = iPath + iService.name;

    if (mRegistry.find(vUniqueName) != mRegistry.end())
        throw std::invalid_argument(std::string("attempt to add duplicate service to registry, uniqueName=") + vUniqueName);

    mRegistry[vUniqueName] = &iService;

    return *mRegistry[vUniqueName];
}

Service & ServiceRegistry::Lookup(std::string iServiceName, std::string iPath) { 
    std::string vUniqueName = iPath + iServiceName;

    if (mRegistry.find(vUniqueName) == mRegistry.end())
        throw std::invalid_argument(std::string("unable to locate service in registry, uniqueName=") + vUniqueName);

    return *mRegistry[vUniqueName];
}
