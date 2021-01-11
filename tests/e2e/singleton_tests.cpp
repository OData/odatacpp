﻿//---------------------------------------------------------------------
// <copyright file="singleton_tests.cpp" company="Microsoft">
//      Copyright (C) Microsoft Corporation. All rights reserved. See License.txt in the project root for license information.
// </copyright>
//---------------------------------------------------------------------

#include "e2e_tests.h"
#include "odata_wcf_service.h"

namespace tests { namespace e2e { namespace odata {

using namespace odata_wcf_service;

SUITE(singleton_tests_raw_client)
{

TEST_FIXTURE(e2e_raw_client, query_singleton)
{
	auto query_result = client.get_data_from_server(_XPLATSTR("Company")).get();
	VERIFY_ARE_EQUAL(query_result.size(), 1);
	VERIFY_ARE_EQUAL(edm_type_kind_t::Entity, query_result[0]->get_value_type()->get_type_kind());
}

}

SUITE(singleton_tests)
{

TEST_FIXTURE(e2e_test_case, query_update_singleton)
{
	auto vip = service_context->create_vipcustomer_query()->execute_query().get();
	VERIFY_ARE_EQUAL(1, vip->get_personid());
	VERIFY_ARE_EQUAL(_XPLATSTR("London"), vip->get_city());

	vip->set_city(_XPLATSTR("Shanghai"));
	::utility::seconds time(123);
	vip->set_timebetweenlasttwoorders(time);
	auto status_code = service_context->update_object(vip).get();
	VERIFY_ARE_EQUAL(204, status_code);

	auto new_vip = service_context->create_vipcustomer_query()->execute_query().get();
	VERIFY_ARE_EQUAL(_XPLATSTR("Shanghai"), new_vip->get_city());
}


TEST_FIXTURE(e2e_test_case, derived_type_singleton)
{
	auto boss = service_context->create_boss_query()->execute_query().get();
	auto boss_customer = std::dynamic_pointer_cast<Customer>(boss);
	VERIFY_ARE_EQUAL(2, boss_customer->get_personid());
	VERIFY_ARE_EQUAL(_XPLATSTR("Sydney"), boss_customer->get_city());

	boss_customer->set_city(_XPLATSTR("Shanghai"));
	::utility::seconds time(123);
	boss_customer->set_timebetweenlasttwoorders(time);
	auto status_code = service_context->update_object(boss_customer).get();
	VERIFY_ARE_EQUAL(204, status_code);

	auto check_result = service_context->create_boss_query()->execute_query().get();
	auto new_boss = std::dynamic_pointer_cast<Customer>(check_result);
	VERIFY_ARE_EQUAL(_XPLATSTR("Shanghai"), new_boss->get_city());
}

TEST_FIXTURE(e2e_test_case, singleton_with_navigation_properties)
{
	auto company = service_context->create_company_query()->execute_query().get();
	company->load_employees().get();

	auto employees = company->get_employees();
	VERIFY_ARE_EQUAL(2, employees.size());
	VERIFY_ARE_EQUAL(_XPLATSTR("http://odatae2etest.azurewebsites.net/cpptest/DefaultService/Employees(PersonID=3)"), employees[0]->get_edit_link());
	VERIFY_ARE_EQUAL(_XPLATSTR("Jacob"), employees[0]->get_firstname());

	company->load_vipcustomer().get();
	auto vip = company->get_vipcustomer();
	VERIFY_ARE_EQUAL(_XPLATSTR("http://odatae2etest.azurewebsites.net/cpptest/DefaultService/VipCustomer"), vip->get_edit_link());
	VERIFY_ARE_EQUAL(_XPLATSTR("Bob"), vip->get_firstname());
}

TEST_FIXTURE(e2e_test_case, singleton_with_query_options)
{
	auto company = service_context->create_company_query()
		->expand(odata_query_path::creat_query_path(_XPLATSTR("Employees"))->filter(_XPLATSTR("PersonID eq 3")))->expand(_XPLATSTR("VipCustomer"))
		->execute_query().get();

	auto employees = company->get_employees();
	VERIFY_ARE_EQUAL(1, employees.size());
	VERIFY_ARE_EQUAL(_XPLATSTR("http://odatae2etest.azurewebsites.net/cpptest/DefaultService/Employees(PersonID=3)"), employees[0]->get_edit_link());
	VERIFY_ARE_EQUAL(_XPLATSTR("Jacob"), employees[0]->get_firstname());

	auto vip = company->get_vipcustomer();
	VERIFY_ARE_EQUAL(_XPLATSTR("http://odatae2etest.azurewebsites.net/cpptest/DefaultService/VipCustomer"), vip->get_edit_link());
	VERIFY_ARE_EQUAL(_XPLATSTR("Bob"), vip->get_firstname());
}

}

}}}
