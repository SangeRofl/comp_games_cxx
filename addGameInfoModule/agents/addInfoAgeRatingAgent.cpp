/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include <sc-agents-common/utils/GenerationUtils.hpp>
#include <sc-agents-common/utils/AgentUtils.hpp>
#include <sc-agents-common/utils/IteratorUtils.hpp>
#include "addInfoAgeRatingAgent.hpp"
#include <sc-memory/sc_link.hpp>
#include <sc-memory/sc_wait.hpp>
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
    
  ScAddr game = ms_context->GetEdgeTarget(edgeAddr);//получаем адрес игры
  
  if (!game.IsValid())
    return SC_RESULT_ERROR_INVALID_PARAMS;
  
  ScIterator5Ptr it5_1 = IteratorUtils::getIterator5(ms_context.get(), game, Keynodes::nrel_source_of_information, true);//итератор5 для поиска источника информации
  while(it5_1->Next())
  {
  	ScAddr url = it5_1->Get(2);//получаем адрес источника информации (url)
  	ScIterator3Ptr it3_1 = ms_context->Iterator3(ScType::Unknown, ScType::EdgeAccessConstPosPerm, url);//итератор3 для поиска названия источника
  		ScLink lnk(*ms_context, url);
     std::string const val = lnk.Get<std::string>();
  	while(it3_1->Next())
  	{
  		ScAddr add1 = it3_1->Get(0);//получаем адрес названия источника
  		ScIterator5Ptr it5_2=ms_context->Iterator5(add1, ScType::EdgeDCommonConst, ScType::Unknown, ScType::EdgeAccessConstPosPerm, Keynodes::nrel_main_idtf);
  		while(it5_2->Next())
  		{	
  			ScAddr sheaf = it5_2->Get(2);
		  	ScLink link(*ms_context, sheaf);
		  	std::string const value = link.Get<std::string>();
		  	std::string ageRating_str;
		   	if(value == "gog")
		   	{
		  		ScLink url_link(*ms_context, url);
		  		std::string const text_url = link.Get<std::string>();
		  		system(("python3 ../problem-solver/cxx/addGameInfoModule/agents/py_utils/gog.py -agent=ageRating -site="+val).c_str());
		  		std::ifstream in("../problem-solver/cxx/addGameInfoModule/agents/py_utils/data/age_rating.txt");
  				if (in.is_open())
  				{
    				getline(in, ageRating_str);
  				}
  				in.close();			
		   	}
		   	else
		   		continue;
		   	ScAddr ageRating = ms_context->CreateNode(ScType::NodeConst);
		   	ScAddr ageRating_edge = ms_context->CreateEdge(ScType::EdgeDCommonConst, game, ageRating);
		   	ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, Keynodes::nrel_age_rating, ageRating_edge);
		   	ScLink ageRating_link(*ms_context, ageRating);
		   	ageRating_link.Set<std::string>(ageRating_str);
		   	ms_context->CreateEdge(ScType::EdgeAccessConstPosTemp, Keynodes::binary_string, ageRating);
		   	//ScAddr ageRating_value = ms_context->CreateNode(ScType::NodeConst);
		   	//ScLink ageRating_link(*ms_context, ageRating_value);
		  	//ageRating_link.Set<std::string>(ageRating_str);
		  	//ScAddr ageRatingText_edge = ms_context->CreateEdge(ScType::EdgeDCommonConst, ageRating, ageRating);
		   	//ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, Keynodes::nrel_main_idtf, ageRatingText_edge);
		   	break;
			}
  	}
  }
  ms_context->EraseElement(edgeAddr);
  return SC_RESULT_OK;
}
}
