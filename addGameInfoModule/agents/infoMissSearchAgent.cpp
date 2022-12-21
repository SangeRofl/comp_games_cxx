/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include <sc-agents-common/utils/GenerationUtils.hpp>
#include <sc-agents-common/utils/AgentUtils.hpp>
#include <sc-agents-common/utils/IteratorUtils.hpp>
#include "infoMissSearchAgent.hpp"
#include <sc-memory/sc_link.hpp>
#include <sc-memory/sc_wait.hpp>
#include <sc-memory/kpm/sc_agent.hpp>
#include<iostream>
#include<fstream>
#include<string>
#include <unistd.h>
using namespace std;
using namespace utils;

namespace addGameInfoModule
{

SC_AGENT_IMPLEMENTATION(AinfoMissSearchAgent)
{
  if (!edgeAddr.IsValid())
    return SC_RESULT_ERROR;
  ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);
  ScAddr game = IteratorUtils::getFirstFromSet(ms_context.get(), questionNode);
  if (!game.IsValid())
    return SC_RESULT_ERROR_INVALID_PARAMS;
  ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);
  
  ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, game);
  
  ScIterator5Ptr age_rating_it5 = ms_context->Iterator5(game, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_age_rating);;
  if(!age_rating_it5->Next())
  {	
  	system("echo 10");
  	//ScAddr questionNode = ScAgentAction::CreateCommand(*ms_context, Keynodes::nrel_age_rating, {game});
  	//system("echo 11");
  	//ScAgentAction::InitiateCommandWait(*ms_context, questionNode, 10000);
  	ScAddr ageRating_questionNode = AgentUtils::createQuestionNode(ms_context.get());
  	AgentUtils::assignParamsToQuestionNode(ms_context.get(),  ageRating_questionNode, {game});
  	//system("echo 11");
  	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, Keynodes::question_add_info_age_rating, ageRating_questionNode);
	//system("echo 12");
	//ScIterator5Ptr age_rating_it5_1 = ms_context->Iterator5(game, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_age_rating);;
	//{
	//	system("echo 15");
	//	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, age_rating_it5_1->Get(1));
	//	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, age_rating_it5_1->Get(2));
	//	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, age_rating_it5_1->Get(3));
	//	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, age_rating_it5_1->Get(4));
	//}
  }
  
  //RATING
  ScIterator5Ptr game_rating_it5 = ms_context->Iterator5(game, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_rating);;
  if(!game_rating_it5->Next())
  {
      ScAddr gameRating_questionNode = AgentUtils::createQuestionNode(ms_context.get());
      AgentUtils::assignParamsToQuestionNode(ms_context.get(),  gameRating_questionNode, {game});

      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, Keynodes::question_add_game_rating, gameRating_questionNode);
  }
  //MARKETPLACE
  ScIterator5Ptr game_marketplace_it5 = ms_context->Iterator5(game, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_distributor);;
  if(!game_marketplace_it5->Next())
  {
      ScAddr gameMarketplace_questionNode = AgentUtils::createQuestionNode(ms_context.get());
      AgentUtils::assignParamsToQuestionNode(ms_context.get(),  gameMarketplace_questionNode, {game});

      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, Keynodes::question_add_game_marketplace, gameMarketplace_questionNode);
  }
  //PLATFROM
  ScIterator5Ptr game_paltform_it5 = ms_context->Iterator5(game, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_platform);;
  if(!game_paltform_it5->Next())
  {
      ScAddr gamePlatform_questionNode = AgentUtils::createQuestionNode(ms_context.get());
      AgentUtils::assignParamsToQuestionNode(ms_context.get(),  gamePlatform_questionNode, {game});

      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, Keynodes::question_add_info_game_platforms, gamePlatform_questionNode);
  }
  //REVIEW
  ScIterator5Ptr game_review_it5 = ms_context->Iterator5(game, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_review);;
  if(!game_review_it5->Next())
  {
      ScAddr gameReview_questionNode = AgentUtils::createQuestionNode(ms_context.get());
      AgentUtils::assignParamsToQuestionNode(ms_context.get(),  gameReview_questionNode, {game});

      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, Keynodes::question_add_info_review, gameReview_questionNode);
  }
  //LANGUAGE
  ScIterator5Ptr game_language_it5 = ms_context->Iterator5(game, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_supported_language);;
  if(!game_language_it5->Next())
  {
      ScAddr gameLanguage_questionNode = AgentUtils::createQuestionNode(ms_context.get());
      AgentUtils::assignParamsToQuestionNode(ms_context.get(),  gameLanguage_questionNode, {game});

      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, Keynodes::question_add_info_supported_language, gameLanguage_questionNode);
  }
  //SYSTEM REQUIREMENTS
  ScIterator5Ptr game_requirements_it5 = ms_context->Iterator5(game, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_minimal_system_requirements);;
  if(!game_requirements_it5->Next())
  {
      ScAddr gameRequirements_questionNode = AgentUtils::createQuestionNode(ms_context.get());
      AgentUtils::assignParamsToQuestionNode(ms_context.get(),  gameRequirements_questionNode, {game});

      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, Keynodes::question_add_info_system_requirements, gameRequirements_questionNode);
  }
  //PRICE
  ScIterator5Ptr game_price_it5 = ms_context->Iterator5(game, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_price);;
  if(!game_price_it5->Next())
  {
      ScAddr gamePrice_questionNode = AgentUtils::createQuestionNode(ms_context.get());
      AgentUtils::assignParamsToQuestionNode(ms_context.get(),  gamePrice_questionNode, {game});

      ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, Keynodes::question_add_info_price, gamePrice_questionNode);
  }
  //ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);
  //ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, param, Keynodes::price_5);
  //ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, Keynodes::nrel_subdividing);
  //system("python ./main.py");
  //std::ifstream in("./price.txt");
  //std::string s;
  //if (in.is_open())
  //{
    //getline(in, s);
    //system(((std::string("echo ")+ s)).c_str());
  //}
  //in.close();
//   ScIterator5Ptr iterator5 = ms_context->Iterator5(param, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_main_idtf);
//   system("echo 1");
//   while (iterator5->Next())
//   {
//     ScAddr sheaf = iterator5->Get(2);
//     ScLink link(*ms_context, sheaf);
//     std::string const value = link.Get<std::string>();
//     system("echo 2");
//     system(((std::string("echo ")+ value)).c_str());
//   }
// system("echo 3");
  AgentUtils::finishAgentWork(ms_context.get(), questionNode, answer);
  return SC_RESULT_OK;
}
}
