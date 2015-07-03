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
#include "datatype/tCharacter.h"
#include "datatype/tInteger.h"
#include "datatype/tString.h"
#include "datatype/tNull.h"
#include "datatype/tBoolean.h"
#include "datatype/tArray.h"
#include "datatype/tObjectArray.h"


#define CHARACTER_TYPE                 tCharacter::Instance()
#define INTEGER_TYPE                   tInteger::Instance()
#define STRING_TYPE                    tString::Instance()
#define NULL_TYPE                      tNull::Instance()
#define BOOLEAN_TYPE                   tBoolean::Instance()
#define ARRAY_OF(TYPE)                 tArray<TYPE>::Instance()
#define OBJECT_ARRAY                   tObjectArray::Instance()
