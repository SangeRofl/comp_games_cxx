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
#include "agents/addGameRatingAgent.hpp"
#include "agents/addGameMarketplaceAgent.hpp"
#include "agents/addGamePlatformsAgent.hpp"
#include "agents/addInfoReviewAgent.hpp"
#include "agents/addInfoSupportedLanguageAgent.hpp"
#include "agents/addInfoSystemRequirementsAgent.hpp"
using namespace addGameInfoModule;

SC_IMPLEMENT_MODULE(AddGameInfoModule)

sc_result AddGameInfoModule::InitializeImpl()
{
  if (!addGameInfoModule::Keynodes::InitGlobal())
    return SC_RESULT_ERROR;

  	SC_AGENT_REGISTER(addInfoPriceAgent)
	SC_AGENT_REGISTER(AinfoMissSearchAgent)
	SC_AGENT_REGISTER(addInfoAgeRatingAgent)
	SC_AGENT_REGISTER(addGameRatingAgent)
	SC_AGENT_REGISTER(addGameMarketplaceAgent)
	SC_AGENT_REGISTER(addGamePlatformsAgent)
	SC_AGENT_REGISTER(addInfoReviewAgent)
	SC_AGENT_REGISTER(addInfoSystemRequirementsAgent)
	SC_AGENT_REGISTER(addInfoSupportedLanguageAgent)
  return SC_RESULT_OK;
}

sc_result AddGameInfoModule::ShutdownImpl()
{
  	SC_AGENT_UNREGISTER(addInfoPriceAgent)
	SC_AGENT_UNREGISTER(AinfoMissSearchAgent)
	SC_AGENT_UNREGISTER(addInfoAgeRatingAgent)
	SC_AGENT_UNREGISTER(addGameRatingAgent)
	SC_AGENT_UNREGISTER(addGameMarketplaceAgent)
	SC_AGENT_UNREGISTER(addGamePlatformsAgent)
	SC_AGENT_UNREGISTER(addInfoReviewAgent)
	SC_AGENT_UNREGISTER(addInfoSystemRequirementsAgent)
	SC_AGENT_UNREGISTER(addInfoSupportedLanguageAgent)
  return SC_RESULT_OK;
}
