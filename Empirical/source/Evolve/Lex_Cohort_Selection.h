#ifndef EMP_EVO_COHORT_SELECT_H
#define EMP_EVO_COHORT_SELECT_H

#include <map>
#include <functional>
#include <utility>
#include <algorithm>
#include <vector> 

#include "../base/array.h"
#include "../base/assert.h"
#include "../base/vector.h"
#include "../base/macros.h"
#include "../meta/reflection.h"
#include "../tools/IndexMap.h"
#include "../tools/Random.h"
#include "../tools/vector_utils.h"

namespace emp 
{
  template<typename ORG> class World;

  /// ==SingleHostSelection== Selection picks a single individual to from a group of qualified applicants
  /// through a single fitness function
  /// world -> World we are evolving
  /// qulifieres -> id's of 
  /// fit_fun -> fitness function we are using to evaluate
  /// return -> a vector of ID's that have the highest fitness

  template<typename ORG>
  emp::vector<size_t> SingleSelection(World<ORG> & world, const emp::vector<size_t> & qualifiers
                                                          , const std::function<double(ORG&)> & fit_fun)
  {
    std::map<double, emp::vector<size_t>> scores;
    
    for(size_t id : qualifiers)
    {
      auto & org = world.GetOrg(id);
      double score = fit_fun(org);
      auto it = scores.find(score);

      //if found insert into existing vector
      if(it != scores.end())
      {
        scores[score].push_back(id);
      }
      //else add new vector to the map with score
      else
      {
        emp::vector<size_t> temp;
        temp.push_back(id);
        scores.insert(std::pair<double, emp::vector<size_t>>(score, temp));
      }
    }
    return scores.rbegin()->second;
  }

  /// ==CohortHostSelect== Selection picks a set of the most fit individuals from a certian
  /// cohort. It will use a lexicase selection method where we will keep looking 
  /// through all the fitness functions until we have a single winner. In the case
  /// that there is no single winner, we will randomly select one of the remaining
  /// at random
  /// world -> World we are evolving
  /// cohorts -> vector of cohorts
  /// fit_funs -> vector of fitness functions we are checking
  /// cohort_size -> size of an individual cohort
  /// cohort_total -> total number of cohorts
  template<typename ORG>
  void CohortSelect(World<ORG> & world, const emp::vector<emp::vector<size_t>> & cohorts, 
                                    emp::vector<std::function<double(ORG&)>> fit_funs,
                                    const size_t & cohort_size, const size_t & cohort_total, 
                                    emp::Ptr<emp::Random> rng, size_t MAX_SIZE) 
  {
    emp::vector<size_t> winners; size_t c = 0;
    emp::Shuffle(*rng, fit_funs);
    
    for(emp::vector<size_t> cohort: cohorts)
    {
      size_t win_cnt = 0; 
      emp::vector<std::function<double(ORG&)>> cfit_funs;

      //Create a partition of fitness functions for a specific cohort
      for(size_t i = 0; i < cohort_size; ++i)
      {
        cfit_funs.push_back(fit_funs[(c * cohort_total) + i]);
      }
  
      while(win_cnt != cohort_size)
      {
        size_t fun_ptr = 0; 
        emp::vector<size_t> qualifiers = SingleSelection(world, cohort, cfit_funs[fun_ptr]);
        ++fun_ptr;

        while(qualifiers.size() > 1 && fun_ptr != cfit_funs.size())
        {
          qualifiers = SingleSelection(world, qualifiers, cfit_funs[fun_ptr]);
          ++fun_ptr;
        }

        //If number of qualified ID's is just 1
        if(qualifiers.size() == 1)
        {
          winners.push_back(qualifiers[0]);
        }
        //Qualified ID's > 1 and fun_ptr == fit_funs.size
        else
        {
          auto choices = emp::Choose(*rng, qualifiers.size(), 1);
          winners.push_back(qualifiers[choices[0]]);
        }
        ++win_cnt;
        emp::Shuffle(*rng, cfit_funs);
      }
      ++c;
    }

    if(winners.size() != (cohort_size * cohort_total))
    {
      std::cout << "Cohort_Selection winners vector not correct size!" << std::endl;
      exit(-1);
    }

    for(size_t id : winners)
    {
      world.DoBirth(world.GetGenomeAt(id), id, 1);
    }
  }
}

#endif