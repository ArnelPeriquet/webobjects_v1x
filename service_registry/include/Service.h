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


class Type;
class Object;


class SERVICE_REGISTRY_API Service {
public:
    Service(std::string iName);

    Service & AddParameter(std::string iName, Type & iType);

    virtual std::shared_ptr<Object> Invoke(std::vector<std::shared_ptr<Object>> iArgs) = 0;

    std::string name;

private:
    std::map<std::string, Type *> mParameters;
};
