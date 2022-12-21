/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include <sc-agents-common/utils/GenerationUtils.hpp>
#include <sc-agents-common/utils/AgentUtils.hpp>
#include <sc-agents-common/utils/IteratorUtils.hpp>
#include <sc-agents-common/utils/CommonUtils.hpp>
#include <sc-agents-common/keynodes/coreKeynodes.hpp>
#include "addGameRatingAgent.hpp"
#include "sc-core/sc_helper.h"
#include <sc-memory/sc_link.hpp>
#include <sc-memory/sc_wait.hpp>
#include <sc-memory/sc_stream.hpp>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace utils;

namespace addGameInfoModule {

    SC_AGENT_IMPLEMENTATION(addGameRatingAgent)
        {
            if (!edgeAddr.IsValid())
                return SC_RESULT_ERROR;
            ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);
            ScAddr game = IteratorUtils::getFirstFromSet(ms_context.get(), questionNode);
            if (!game.IsValid())
                return SC_RESULT_ERROR_INVALID_PARAMS;
            ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);
            system("echo 1");
            std::string const gameName = CommonUtils::getMainIdtf(ms_context.get(), game, {Keynodes::lang_en});
            //system(("echo " + gameName).c_str());
            if (gameName != "") {
                system("echo 2");
                system(("python3 ../problem-solver/cxx/addGameInfoModule/agents/py_utils/wikipedia.py -agent=gameRating -game=\"" + gameName+"\"").c_str());
                std::ifstream in("../problem-solver/cxx/addGameInfoModule/agents/py_utils/data/game_rating.txt");
                std::string gameRating;
                if (in.is_open()) {
                    system("echo 3");
                    while (!in.eof()) {
                        getline(in, gameRating);
                        if (gameRating == "")
                            break;
                        ScAddr gameRatingNode = ms_context->CreateNode(ScType::NodeConst);
                        CommonUtils::setMainIdtf(ms_context.get(), gameRatingNode, gameRating, {Keynodes::lang_ru});
                        system("echo 4");
                        ScAddr gameRatingTextEdge = ms_context->CreateEdge(ScType::EdgeDCommonConst, game, gameRatingNode);
                        system("echo 5");
                        ScAddr ageRatingTextEdgeAccess = ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm,
                                                                                Keynodes::nrel_rating,
                                                                                gameRatingTextEdge);
                        system("echo 6");
                        ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, gameRatingNode);
                        ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, gameRatingTextEdge);
                        ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, ageRatingTextEdgeAccess);
                    }
                    system("echo 7");
            	    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, game);
            	    ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, Keynodes::nrel_rating);
                }
                in.close();
            }
            
            
            AgentUtils::finishAgentWork(ms_context.get(), questionNode, answer);
            return SC_RESULT_OK;
        }
}
