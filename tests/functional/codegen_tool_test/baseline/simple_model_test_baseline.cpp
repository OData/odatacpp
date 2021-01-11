﻿//---------------------------------------------------------------------
// <copyright file="simple_model_test_baseline.cpp" company="Microsoft">
//      Copyright (C) Microsoft Corporation. All rights reserved. See License.txt in the project root for license information.
// </copyright>
//---------------------------------------------------------------------

#include "simple_model_test.h"

namespace Simple
{

BEGIN_ENTITY_CONSTRUCTOR(TestType, type_base)
    ON_PROPERTY_IN_ENTITY_CONSTRUCTOR(keyprop, 0)
END_ENTITY_CONSTRUCTOR(TestType, type_base)

BEGIN_ENTITY_DESTRUCTOR(TestType)
END_ENTITY_DESTRUCTOR(TestType)

IMPLEMENT_PRIMITIVE_PROPERTY_IN_ENTITY_MAPPING(TestType, keyprop, KeyProp, int32_t);
IMPLEMENT_PRIMITIVE_PROPERTY_IN_ENTITY_MAPPING(TestType, valueprop, ValueProp, ::odata::string_t);

IMPLEMENT_EDM_INFO(TestType, Simple, TestType)

BEGIN_PROPERTY_IN_ENTITY_MAPPING(TestType)
    ON_PROPERTY_IN_ENTITY_MAPPING(TestType, keyprop)
    ON_PROPERTY_IN_ENTITY_MAPPING(TestType, valueprop)
END_PROPERTY_IN_ENTITY_MAPPING(TestType)

BEGIN_SERIALIZE_PROPERTY_IN_ENTITY_MAPPING(TestType)
    ON_SERIALIZE_PROPERTY_IN_ENTITY_MAPPING(TestType, keyprop)
    ON_SERIALIZE_PROPERTY_IN_ENTITY_MAPPING(TestType, valueprop)
END_SERIALIZE_PROPERTY_IN_ENTITY_MAPPING(TestType)


IMPLEMENT_EMPTY_DERIVED_TYPE_CREATOR_MAP(TestType)
}
