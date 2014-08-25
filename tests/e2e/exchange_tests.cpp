/***
* ==++==
*
* Copyright (c) Microsoft Corporation. All rights reserved. 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* ==--==
* =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
*
* enum_tests.cpp
*
*
*
* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
****/

#include "e2e_tests.h"
#include "exchange_service.h"

namespace tests { namespace e2e { namespace odata {

using namespace exchange_service;

class exchange_test_case
{
public:
	std::shared_ptr<EntityContainer> service_context;

    exchange_test_case() {
		service_context = std::make_shared<EntityContainer>(U("http://odatae2etest.azurewebsites.net/cpptemp/DefaultService/"));
	}
};

SUITE(exchange_tests)
{

TEST_FIXTURE(exchange_test_case, query_users)
{
	//auto users = service_context->create_users_query()->execute_query().get();

	//VERIFY_IS_TRUE(users.size() > 0);
}


}

}}}