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
#include "addGameMarketplaceAgent.hpp"
#include "sc-core/sc_helper.h"
#include <sc-memory/sc_link.hpp>
#include <sc-memory/sc_wait.hpp>
#include <sc-memory/sc_stream.hpp>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
using namespace utils;

namespace addGameInfoModule
{

    SC_AGENT_IMPLEMENTATION(addGameMarketplaceAgent)
        {
            if (!edgeAddr.IsValid())
                return SC_RESULT_ERROR;
            ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);//получаем адрес игры
            ScAddr game = IteratorUtils::getFirstFromSet(ms_context.get(), questionNode);
            if (!game.IsValid())
                return SC_RESULT_ERROR_INVALID_PARAMS;
            ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);
            system("echo 1");
            ScIterator5Ptr it5_1 = IteratorUtils::getIterator5(ms_context.get(), game, Keynodes::nrel_source_of_information, true);//итератор5 для поиска источника информации
            while(it5_1->Next())
            {
                system("echo 2");
                ScAddr url = it5_1->Get(2);//получаем адрес источника информации (url)
                ScIterator3Ptr it3_1 = ms_context->Iterator3(ScType::Unknown, ScType::EdgeAccessConstPosPerm, url);//итератор3 для поиска названия источника
                ScLink lnk(*ms_context, url);
                std::string const val = lnk.Get<std::string>();
                while(it3_1->Next())
                {
                    system("echo 3");
                    ScAddr add1 = it3_1->Get(0);//получаем адрес названия источника
                    ScIterator5Ptr it5_2=ms_context->Iterator5(add1, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_main_idtf);
                    while(it5_2->Next())
                    {
                        system("echo 4");
                        ScAddr sheaf = it5_2->Get(2);
                        ScLink link(*ms_context, sheaf);
                        std::string const value = link.Get<std::string>();
                        std::string const gameMarketplace_str = value;
                        ScAddr gameMarketplace = ms_context->CreateNode(ScType::NodeConst);
                        CommonUtils::setMainIdtf(ms_context.get(), gameMarketplace, gameMarketplace_str, {Keynodes::lang_ru});
                        system("echo 7");
                        ScAddr gameMarketplaceText_edge = ms_context->CreateEdge(ScType::EdgeDCommonConst, game, gameMarketplace);
                        system("echo 8");
                        ScAddr gameMarketplaceText_edgeAccess=ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, Keynodes::nrel_distributor, gameMarketplaceText_edge);
                        system("echo 9");
                        ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, game);
                        ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, gameMarketplace);
                        ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, Keynodes::nrel_distributor);
                        ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, gameMarketplaceText_edge);
                        ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, gameMarketplaceText_edgeAccess);
                        break;
                    }
                }
            }
            AgentUtils::finishAgentWork(ms_context.get(), questionNode, answer);
            return SC_RESULT_OK;
        }
}
