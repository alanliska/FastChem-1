/*
* This file is part of the FastChem code (https://github.com/exoclime/fastchem).
* Copyright (C) 2022 Daniel Kitzmann, Joachim Stock
*
* FastChem is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* FastChem is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You find a copy of the GNU General Public License in the main
* FastChem directory under <license.md>. If not, see
* <http://www.gnu.org/licenses/>.
*/

#ifndef _condensed_phase_h
#define _condensed_phase_h

#include <string>
#include <vector>

#include "../elements/elements.h"
#include "../options.h"
#include "../species_struct.h"
#include "solver.h"


namespace fastchem {


template <class double_type>
class CondensedPhase {
  public:
    CondensedPhase(
      FastChemOptions<double_type>& options_,
      ElementData<double_type>& element_data_);
    CondensedPhase(
      const CondensedPhase &obj,
      FastChemOptions<double_type>& options_,
      ElementData<double_type>& element_data_);

    std::vector< Condensate<double_type> > condensates;

    void selectActiveCondensates(
      std::vector<Condensate<double_type>*>& condensates_act,
      std::vector<Element<double_type>*>& elements_cond);
    
    size_t nb_condensates = 0;
    size_t nb_elements = 0;

    bool is_initialised = false;

    bool calculate(
      const double temperature, const double density, unsigned int& nb_iterations);
  private:
    FastChemOptions<double_type>& options;
    ElementData<double_type>& element_data;
    std::vector<Element<double_type>>& elements;

    CondPhaseSolver<double_type> solver;

    void init();

    bool readCondensateData(const std::string& species_data_file);
    void addCondensate(
      const std::string name,
      const std::string symbol,
      const std::vector<std::string> species_elements,
      const std::vector<int> stoichiometric_coeff,
      const double_type density,
      const std::string phase, 
      const std::vector<double>& phase_temp_limits,
      const std::vector<double>& fit_temp_limits,
      const std::vector<double_type> fit_coeff);
};



}

#endif