﻿//---------------------------------------------------------------------
// <copyright file="e2e_test_case.h" company="Microsoft">
//      Copyright (C) Microsoft Corporation. All rights reserved. See License.txt in the project root for license information.
// </copyright>
//---------------------------------------------------------------------

#pragma once
#include "odata/client/odata_client.h"
#include "odata_wcf_service.h"

namespace tests { namespace e2e { namespace odata {

using namespace ::odata::client;
using namespace ::utility;
using namespace odata_wcf_service;

class e2e_raw_client
{
public:
	odata_client client;

    e2e_raw_client() : client(_XPLATSTR("http://odatae2etest.azurewebsites.net/cpptest/DefaultService")) {
		//Reset data source first.
		client.send_data_to_server(_XPLATSTR("ResetDataSource")).get();
	}
};


class e2e_test_case
{
public:
	std::shared_ptr<InMemoryEntities> service_context;

    e2e_test_case() {
		service_context = ::odata::make_shared<InMemoryEntities>(_XPLATSTR("http://odatae2etest.azurewebsites.net/cpptest/DefaultService"));

		//Reset data source first.
		service_context->ResetDataSource().get();
	}
};
}}}