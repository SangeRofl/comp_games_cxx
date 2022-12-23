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
#include "addInfoAgeRatingAgent.hpp"
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

SC_AGENT_IMPLEMENTATION(addInfoAgeRatingAgent)
{

  
  if (!edgeAddr.IsValid())
    return SC_RESULT_ERROR;
    
  ScAddr questionNode = ms_context->GetEdgeTarget(edgeAddr);//получаем адрес игры
  ScAddr game = IteratorUtils::getFirstFromSet(ms_context.get(), questionNode);
  if (!game.IsValid())
    return SC_RESULT_ERROR_INVALID_PARAMS;
  ScAddr answer = ms_context->CreateNode(ScType::NodeConstStruct);//создаем узел ответа
  system("echo 1");
  ScIterator5Ptr it5_1 = IteratorUtils::getIterator5(ms_context.get(), game, Keynodes::nrel_source_of_information, true);//итератор5 для поиска источника информации
  while(it5_1->Next())
  {
  	system("echo 2");
  	ScAddr url = it5_1->Get(2);//получаем адрес источника информации (url)
  	ScIterator3Ptr it3_1 = ms_context->Iterator3(ScType::Unknown, ScType::EdgeAccessConstPosPerm, url);//итератор3 для поиска названия источника
  	ScLink lnk(*ms_context, url);//получаем sc-ссылку, в которой записан адрес сайта
     	std::string const val = lnk.Get<std::string>();//получаем строку адреса сайта из sc-ссылки
  	while(it3_1->Next())
  	{
  		system("echo 3");
  		ScAddr add1 = it3_1->Get(0);//получаем адрес узла источника
  		ScIterator5Ptr it5_2=ms_context->Iterator5(add1, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_main_idtf);//создаем итератор для получаения идентификатора узла источника
  		while(it5_2->Next())
  		{	
  			system("echo 4");
  			ScAddr sheaf = it5_2->Get(2);//получаем узел идентификатора источника
		  	ScLink link(*ms_context, sheaf);//получаем sc-ссылку, в которой записано название источника
		  	std::string const value = link.Get<std::string>();//получаем строку названия источника из sc-ссылки
		  	std::string ageRating_str;
		   	if(value == "gog")//проверяем подохдит ли источник для агента
		   	{
		   		system("echo 5");
		  		system(("python3 ../problem-solver/cxx/addGameInfoModule/agents/py_utils/gog.py -agent=ageRating -site="+val).c_str());//запускаем пайтон скрипт для парсинга сайта
		  		std::ifstream in("../problem-solver/cxx/addGameInfoModule/agents/py_utils/data/age_rating.txt");//считываем полученные данные из файла
  				if (in.is_open())
  				{
  				system("echo 6");
    				getline(in, ageRating_str);
  				}
  				in.close();			
		   	}
		   	else
		   		continue;
  			ScAddr ageRating = ms_context->CreateNode(ScType::NodeConst);//создаем узел для обозначеня возрастного рейтинга
  			CommonUtils::setMainIdtf(ms_context.get(), ageRating, ageRating_str, {Keynodes::lang_ru});//присваиваем ему идентификатор, в котором будет записана информация, полученная от парсинга
  			system("echo 7");
		  	ScAddr ageRatingText_edge = ms_context->CreateEdge(ScType::EdgeDCommonConst, game, ageRating);//создаем дугу между игрой и узлом с возрастным рейтингом
		  	system("echo 8");
		   	ScAddr ageRatingText_edgeAccess=ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, Keynodes::nrel_age_rating, ageRatingText_edge);//соединяем неролевое отношение возрастного рейтинга и созданную нами конструкцию игры и полученного возрастного рейтинга
		   	system("echo 9");
		   	//добавляем созданные конструкции в ответ агента
		   	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, game);
		   	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, ageRating);
		   	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, Keynodes::nrel_age_rating);
		   	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, ageRatingText_edge);
		   	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, ageRatingText_edgeAccess);
		   	break;
		}
  	}
  }
  AgentUtils::finishAgentWork(ms_context.get(), questionNode, answer);//завершаем работу агента
  return SC_RESULT_OK;
}
}
