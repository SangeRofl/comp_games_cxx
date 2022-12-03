/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#pragma once

#include <sc-memory/sc_object.hpp>
#include <sc-memory/sc_addr.hpp>

#include "keynodes.generated.hpp"

namespace addGameInfoModule
{

class Keynodes : public ScObject
{
  SC_CLASS()
  SC_GENERATED_BODY()

public:
	SC_PROPERTY(Keynode("question_add_game_info"), ForceCreate)
  static ScAddr question_add_game_info;
  	
	SC_PROPERTY(Keynode("nrel_rating"), ForceCreate)
  static ScAddr nrel_rating;
  	
  	SC_PROPERTY(Keynode("lang_ru"), ForceCreate)
  static ScAddr lang_ru;
  	
  	SC_PROPERTY(Keynode("nrel_review"), ForceCreate)
  static ScAddr nrel_review;
  	
  	SC_PROPERTY(Keynode("nrel_platform"), ForceCreate)
  static ScAddr nrel_platform;
  
	SC_PROPERTY(Keynode("nrel_distributor"), ForceCreate)
  static ScAddr nrel_distributor;
  
  	SC_PROPERTY(Keynode("nrel_price"), ForceCreate)
  static ScAddr nrel_price;
  
  	SC_PROPERTY(Keynode("nrel_supported_language"), ForceCreate)
  static ScAddr nrel_supported_language;
  
	SC_PROPERTY(Keynode("nrel_minimal_system_requirements"), ForceCreate)
  static ScAddr nrel_minimal_system_requirements;
  
  
	SC_PROPERTY(Keynode("nrel_age_rating"), ForceCreate)
  static ScAddr nrel_age_rating;
  
  	SC_PROPERTY(Keynode("question_add_info_age_rating"), ForceCreate)
  static ScAddr question_add_info_age_rating;
  
  	SC_PROPERTY(Keynode("nrel_source_of_information"), ForceCreate)
  static ScAddr nrel_source_of_information;
  
  	SC_PROPERTY(Keynode("binary_string"), ForceCreate)
  static ScAddr binary_string;
  	
  	SC_PROPERTY(Keynode("nrel_main_idtf"), ForceCreate)
  static ScAddr nrel_main_idtf;
  	
  	SC_PROPERTY(Keynode("sc_node_not_relation"), ForceCreate)
  static ScAddr sc_node_not_relation;
  
    SC_PROPERTY(Keynode("question_add_info_price"), ForceCreate)
  static ScAddr question_add_info_price;
};

} // namespace exampleModule
