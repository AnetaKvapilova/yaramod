/**
 * @file src/types/modules/cuckoo_module.cpp
 * @brief Implementation of CuckooModule.
 * @copyright (c) 2017 Avast Software, licensed under the MIT license
 */

#include "yaramod/types/expression.h"
#include "yaramod/types/modules/cuckoo_module.h"
#include "yaramod/types/symbol.h"

namespace yaramod {

/**
 * Constructor.
 */
CuckooModule::CuckooModule() : Module("cuckoo")
{
}

/**
 * Initializes module structure.
 *
 * @return @c true if success, otherwise @c false.
 */
bool CuckooModule::initialize()
{
	using Type = Expression::Type;

	auto cuckooStruct = std::make_shared<StructureSymbol>("cuckoo");
	auto networkStruct = std::make_shared<StructureSymbol>("network");
	networkStruct->addAttribute(std::make_shared<FunctionSymbol>("dns_lookup", Type::Int, Type::Regexp));
	networkStruct->addAttribute(std::make_shared<FunctionSymbol>("http_get", Type::Int, Type::Regexp));
	networkStruct->addAttribute(std::make_shared<FunctionSymbol>("http_post", Type::Int, Type::Regexp));
	networkStruct->addAttribute(std::make_shared<FunctionSymbol>("http_request", Type::Int, Type::Regexp));
	networkStruct->addAttribute(std::make_shared<FunctionSymbol>("tcp_request", Type::Int, Type::Regexp));
	networkStruct->addAttribute(std::make_shared<FunctionSymbol>("tcp_request", Type::Int, Type::Regexp, Type::Int));
	networkStruct->addAttribute(std::make_shared<FunctionSymbol>("http_request_body", Type::Int, Type::Regexp));
	networkStruct->addAttribute(std::make_shared<FunctionSymbol>("http_request_body", Type::Int, Type::Regexp, Type::Regexp));
	networkStruct->addAttribute(std::make_shared<FunctionSymbol>("http_response_body", Type::Int, Type::Regexp));
	networkStruct->addAttribute(std::make_shared<FunctionSymbol>("http_response_body", Type::Int, Type::Regexp, Type::Regexp));
	networkStruct->addAttribute(std::make_shared<FunctionSymbol>("connection_ip", Type::Int, Type::Regexp));
	networkStruct->addAttribute(std::make_shared<FunctionSymbol>("connection_country", Type::Int, Type::Regexp));
	networkStruct->addAttribute(std::make_shared<FunctionSymbol>("irc_command", Type::Int, Type::Regexp, Type::Regexp));
	cuckooStruct->addAttribute(networkStruct);

	auto registryStruct = std::make_shared<StructureSymbol>("registry");
	registryStruct->addAttribute(std::make_shared<FunctionSymbol>("key_access", Type::Int, Type::Regexp));
	registryStruct->addAttribute(std::make_shared<FunctionSymbol>("key_read", Type::Int, Type::Regexp));
	registryStruct->addAttribute(std::make_shared<FunctionSymbol>("key_write", Type::Int, Type::Regexp));
	registryStruct->addAttribute(std::make_shared<FunctionSymbol>("key_delete", Type::Int, Type::Regexp));
	registryStruct->addAttribute(std::make_shared<FunctionSymbol>("key_value_access", Type::Int, Type::Regexp, Type::Regexp));
	cuckooStruct->addAttribute(registryStruct);

	auto filesystemStruct = std::make_shared<StructureSymbol>("filesystem");
	filesystemStruct->addAttribute(std::make_shared<FunctionSymbol>("file_access", Type::Int, Type::Regexp));
	filesystemStruct->addAttribute(std::make_shared<FunctionSymbol>("file_read", Type::Int, Type::Regexp));
	filesystemStruct->addAttribute(std::make_shared<FunctionSymbol>("file_write", Type::Int, Type::Regexp));
	filesystemStruct->addAttribute(std::make_shared<FunctionSymbol>("file_delete", Type::Int, Type::Regexp));
	filesystemStruct->addAttribute(std::make_shared<FunctionSymbol>("pipe", Type::Int, Type::Regexp));
	filesystemStruct->addAttribute(std::make_shared<FunctionSymbol>("mailslot", Type::Int, Type::Regexp));
	cuckooStruct->addAttribute(filesystemStruct);

	auto syncStruct = std::make_shared<StructureSymbol>("sync");
	syncStruct->addAttribute(std::make_shared<FunctionSymbol>("mutex", Type::Int, Type::Regexp));
	syncStruct->addAttribute(std::make_shared<FunctionSymbol>("event", Type::Int, Type::Regexp));
	syncStruct->addAttribute(std::make_shared<FunctionSymbol>("semaphore", Type::Int, Type::Regexp));
	syncStruct->addAttribute(std::make_shared<FunctionSymbol>("atom", Type::Int, Type::Regexp));
	syncStruct->addAttribute(std::make_shared<FunctionSymbol>("section", Type::Int, Type::Regexp));
	syncStruct->addAttribute(std::make_shared<FunctionSymbol>("job", Type::Int, Type::Regexp));
	syncStruct->addAttribute(std::make_shared<FunctionSymbol>("timer", Type::Int, Type::Regexp));
	cuckooStruct->addAttribute(syncStruct);

	auto processStruct = std::make_shared<StructureSymbol>("process");
	processStruct->addAttribute(std::make_shared<FunctionSymbol>("executed_command", Type::Int, Type::Regexp));
	processStruct->addAttribute(std::make_shared<FunctionSymbol>("created_service", Type::Int, Type::Regexp));
	processStruct->addAttribute(std::make_shared<FunctionSymbol>("started_service", Type::Int, Type::Regexp));
	processStruct->addAttribute(std::make_shared<FunctionSymbol>("resolved_api", Type::Int, Type::Regexp));
	processStruct->addAttribute(std::make_shared<FunctionSymbol>("load_path", Type::Int, Type::Regexp));
	processStruct->addAttribute(std::make_shared<FunctionSymbol>("load_sha256", Type::Int, Type::String));
	processStruct->addAttribute(std::make_shared<FunctionSymbol>("api_call", Type::Int, Type::Regexp));
	processStruct->addAttribute(std::make_shared<FunctionSymbol>("modified_clipboard", Type::Int, Type::Regexp));
	cuckooStruct->addAttribute(processStruct);

	auto signatureStruct = std::make_shared<StructureSymbol>("signature");
	signatureStruct->addAttribute(std::make_shared<FunctionSymbol>("name", Type::Int, Type::Regexp));
	signatureStruct->addAttribute(std::make_shared<FunctionSymbol>("hits", Type::Int, Type::Regexp));
	signatureStruct->addAttribute(std::make_shared<FunctionSymbol>("hits", Type::Int, Type::Regexp, Type::Regexp));
	signatureStruct->addAttribute(std::make_shared<FunctionSymbol>("hits", Type::Int, Type::String));
	signatureStruct->addAttribute(std::make_shared<FunctionSymbol>("hits", Type::Int, Type::String, Type::Regexp));
	cuckooStruct->addAttribute(signatureStruct);

	auto summaryStruct = std::make_shared<StructureSymbol>("summary");
	summaryStruct->addAttribute(std::make_shared<FunctionSymbol>("ml_score", Type::Float, Type::String));
	cuckooStruct->addAttribute(summaryStruct);

	_structure = cuckooStruct;
	return true;
}

}
