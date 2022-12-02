/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include <sc-agents-common/utils/GenerationUtils.hpp>
#include <sc-agents-common/utils/AgentUtils.hpp>
#include <sc-agents-common/utils/IteratorUtils.hpp>
#include "addInfoPriceAgent.hpp"
#include <sc-memory/sc_link.hpp>
#include <sc-memory/sc_wait.hpp>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
using namespace utils;

namespace addGameInfoModule
{

SC_AGENT_IMPLEMENTATION(addInfoPriceAgent)
{
  if (!edgeAddr.IsValid())
    return SC_RESULT_ERROR;
  ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);
  ScAddr game = IteratorUtils::getFirstFromSet(ms_context.get(), questionNode);
  if (!game.IsValid())
    return SC_RESULT_ERROR_INVALID_PARAMS;
  ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);
  
  
  return SC_RESULT_OK;
}
}
