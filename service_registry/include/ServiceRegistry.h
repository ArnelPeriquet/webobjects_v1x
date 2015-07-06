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


class Service;


class SERVICE_REGISTRY_API ServiceRegistry {
public:
    Service & Register(Service & iService, std::string iPath = "/");
    Service & Lookup(std::string iServiceName, std::string iPath = "/");

protected:
    std::map<std::string, Service *> mRegistry;
};