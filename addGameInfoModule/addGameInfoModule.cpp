/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include "addGameInfoModule.hpp"
#include "keynodes/keynodes.hpp"
#include "agents/addInfoPriceAgent.hpp"
#include "agents/infoMissSearchAgent.hpp"
#include "agents/addInfoAgeRatingAgent.hpp"
using namespace addGameInfoModule;

SC_IMPLEMENT_MODULE(AddGameInfoModule)

sc_result AddGameInfoModule::InitializeImpl()
{
  if (!addGameInfoModule::Keynodes::InitGlobal())
    return SC_RESULT_ERROR;

  	SC_AGENT_REGISTER(addInfoPriceAgent)
	SC_AGENT_REGISTER(AinfoMissSearchAgent)
	SC_AGENT_REGISTER(addInfoAgeRatingAgent)
  return SC_RESULT_OK;
}

sc_result AddGameInfoModule::ShutdownImpl()
{
  	SC_AGENT_UNREGISTER(addInfoPriceAgent)
	SC_AGENT_UNREGISTER(AinfoMissSearchAgent)
	SC_AGENT_UNREGISTER(addInfoAgeRatingAgent)
  return SC_RESULT_OK;
}
