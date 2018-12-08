#ifndef HP_EXPERIMENT_H
#define HP_EXPERIMENT_H

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#include "hp_config.h"
#include "../../Empirical/source/tools/Random.h"
#include "../../Empirical/source/tools/random_utils.h"
#include "../../Empirical/source/hardware/AvidaGP.h"
#include "../../Empirical/source/hardware/AvidaCPU_InstLib.h"
#include "../../Empirical/source/Evolve/World.h"
#include "../../Empirical/source/Evolve/Lex_Cohort_Selection.h" //Include my selection function.

/* CONSTEXPR FOR HARDWARE */

//Number of bits in the tag per hardware
constexpr size_t TAG_WIDTH = 16;

//Error we are allowing!
constexpr double EPSILLON = .000001;

//Experiments
constexpr size_t MEDIAN = 0;
constexpr size_t NUMBERIO = 1;
constexpr size_t SUMOFSQU = 2;
constexpr size_t CLS = 0;
constexpr size_t TOURN = 1;

//Training set directories
std::string TRAIN_MED = "Train/median.csv";
std::string TRAIN_IO = "Train/number-io.csv";
std::string TRAIN_SOS = "Train/sum-of-squares.csv";

//Testing set directories
std::string TEST_MED = "Test/median.csv";
std::string TEST_IO = "Test/number-io.csv";
std::string TEST_SOS = "Test/sum-of-squares.csv";
std::string EXP_STR;

/* NEW TYPE DECLARATIONS FOR HARDWARE*/

//type of hardware we are using
using hardware_t = emp::AvidaGP;
//Genome of the avidian
using program_t = hardware_t::Genome;
//Instruction object for hardware
using inst_t = hardware_t::Instruction;
//Instruction library for hardware
using inst_lib_t = emp::AvidaGP::inst_lib_t;


/* NEW TYPE DECLARATIONS FOR SIMPLICITY*/

using coor_t = std::pair<size_t, size_t>;


class Experiment
{
  struct Agent;

  //World of Agents
  using world_t = emp::World<Agent>;  
  //Fitness funs
  using fun_t = std::function<double(Agent&)>;

  struct Agent
  {
    //Agents score
    emp::vector<double> mScore;
    double mTotal = -999;
    bool mChanged = false;
    program_t mGenome;

    Agent(const program_t & p) : mGenome(p) {;}
    program_t & GetGenome() {return mGenome;}

    void SetGenome(const program_t & p) {mGenome = p;}

    double GetScore(size_t i )
    {
      return mScore[i];
    }

    double SumScore()
    {      
      mTotal = 0;
      for(auto i : mScore)
        mTotal += i;

      if(!mChanged)
      {
        std::cout << "mTotal unchaged in agent" << std::endl;
      }

      return mTotal;
    }

    void Resize(size_t n)
    {
      mChanged = true;
      mScore.resize(n);
    }

    void InsertScore(size_t i, double s)
    {
      if(!mChanged)
      {
        std::cout << "Cannot insert score!" << std::endl;
        exit(-1);
      }
      mScore[i] = s;
    }

    double GetTotal()
    {
      if(!mChanged)
      {
        std::cout << "Cannot insert score!" << std::endl;
        exit(-1);
      }
      return mTotal;
    }
  };

  struct Case
  {
    double a = -999.0;
    double b = -999.0;
    double c = -999.0;
    double ans = -999.0;
  };

  public:
    Experiment(const HPConfig & config) :
    ARG_SUB__PER_ARG(config.ARG_SUB__PER_ARG()), INST_MUT_RATE(config.INST_MUT_RATE()), 
    ARG_MUT_RATE(config.ARG_MUT_RATE()), DEL_MUT_RATE(config.DEL_MUT_RATE()), INS_MUT_RATE(config.INS_MUT_RATE()),
    MAX_SIZE_G(config.MAX_SIZE_G()),POP_SIZE(config.POP_SIZE()), NUM_GENS(config.NUM_GENS()), 
    RNG_SEED(config.RNG_SEED()), SNAP_SHOT(config.SNAP_SHOT()), NUM_ITER(config.NUM_ITER()), EXP(config.EXP()),
    SELECTION(config.SELECTION()), COHORT(config.COHORT()), CHAMP_SIZE(config.MAX_SIZE_G()), DIR(config.DIR())
    {
      mRng = emp::NewPtr<emp::Random>(RNG_SEED);
      mWorld = emp::NewPtr<world_t>(*mRng, "World");
      SetInput1(config.INPUT1()); SetInput2(config.INPUT2());
      SetInput3(config.INPUT3()); SetResult(config.RESULT());

      for(size_t i = 0; i < POP_SIZE; ++i)
        mPopIndex.push_back(i);

      if(EXP == MEDIAN)
      {
        LoadMedData(TRAIN_MED, TEST_MED);
        EXP_STR = "Median-";
      }

      if(EXP == NUMBERIO)
      {
        LoadIOData(TRAIN_IO, TEST_IO);
        EXP_STR = "NumIO-";
      }

      if(EXP == SUMOFSQU)
      {
        LoadSOSData(TRAIN_SOS, TEST_SOS);  
        EXP_STR = "SOS-";
      }

      Set_Fit();
    }

    ~Experiment()
    {
      mWorld.Delete();
      mRng.Delete();
    }

    /* FUNCTIONS DEDICATED TO THE EXPERIMENT */

    //Run the experiment
    void Run();

    //Load the training and testing csv for Median data
    void LoadMedData(std::string train, std::string test);

    //Load the training and testing csv for Median data
    void LoadSOSData(std::string train, std::string test);

    //Load the training and testing csv for Median data
    void LoadIOData(std::string train, std::string test);
    
    //Confiugre all the neccesary things
    void Config_All();

    //Evalute each agent for 
    emp::vector<Agent> Evaluation_step(std::ofstream & csv);

    //Selection
    void Selection_step(size_t size, size_t grp);

    //Update
    void Update_step();

    //Set up the fitness functions
    void Set_Fit();

    //Partition up the world!
    void Partition(size_t num, size_t grp);

    //Run a single organism on Median problem
    void Single_Run(Agent & a);

    //Final test for the agents able to solve all training casses
    size_t Final_Test(emp::vector<Agent> pop, std::ofstream & champs, size_t gen);


    /* FUNCTIONS DEDICATED TO THE CONFIGURATIONS and INSTRUCTIONS*/

    //Will make the instruction library
    void Config_Inst();

    //Will set the vote of the hardware
    static void Inst_SetAns(hardware_t & hw, const inst_t & inst);
    //Will set the vote of the hardware
    static void Inst_GetA(hardware_t & hw, const inst_t & inst);
    //Will set the vote of the hardware
    static void Inst_GetB(hardware_t & hw, const inst_t & inst);
    //Will set the vote of the hardware
    static void Inst_GetC(hardware_t & hw, const inst_t & inst);

    //Will configure the mutator
    void Config_Mut();
    //Will create the hardware and add it to the world
    void Config_HW();
    //Will configure the world
    void Config_World();
    //Will load a genome full of NOPs!
    program_t Genome_NOP();

    /* FUNCTIONS DEDICATED TO MODULARIZE CODE!*/
    
    //Data Loader for hardware!
    void LoadCase(hardware_t & hw, Case & c);

    /* FUNCTIONS DEDICATED TO SETTERS */
    static void SetInput1(size_t x) {INPUT1 = x;}
    static void SetInput2(size_t x) {INPUT2 = x;}
    static void SetInput3(size_t x) {INPUT3 = x;}
    static void SetResult(size_t x) {RESULT = x;}

  private:

    /* HARDWARE SPECIFIC PARAMATERS - CONFIG*/

    //Position of UID within hw trait vector
    static size_t INPUT1;
    //Position of VOTE within hw trait vector
    static size_t INPUT2;
    //Position of X coordinate within hw trait vector
    static size_t INPUT3;
    //Position of Y coordinate within hw trait vector
    static size_t RESULT;

    /* MUTATION SPECIFIC PARAMATERS - CONFIG */
    double ARG_SUB__PER_ARG;
    double INST_MUT_RATE;
    double ARG_MUT_RATE;
    double DEL_MUT_RATE;
    double INS_MUT_RATE;
    size_t MAX_SIZE_G;


    /* EXPERIMENT SPECIFIC PARAMATERS - CONFIG */

    //Size of the population we are evaluating.
    size_t POP_SIZE;
    //Number of genearations evaluating during experiments
    size_t NUM_GENS;
    //Random Number Seed Number
    size_t RNG_SEED;
    //Snapshot index
    size_t SNAP_SHOT;
    //All the iterations
    size_t NUM_ITER;
    //Experiment we are doing
    size_t EXP;
    //Selection method we are using
    size_t SELECTION; 

    //Instruction Library for hardware
    inst_lib_t inst_lib;
    //Pointer for random generator
    emp::Ptr<emp::Random> mRng;
    //World to hold organisms
    emp::Ptr<world_t> mWorld;
    //Container for Training Cases
    emp::vector<Case> mTraining;
    //Container for Testing Cases
    emp::vector<Case> mTesting;
    //Container for all the fitness functions
    emp::vector<fun_t> mTrainFuns;
    //Directory of NOP genome
    std::string GENOME_NOP = "NOP.txt";
    //Vector of cohort sizes
    emp::vector<size_t> mCohortSize = {50, 100, 200, 250, 500, 1000};
    //Vector of cohort groups
    emp::vector<size_t> mCohortGroup = {20, 10, 5, 4, 2, 1};
    //Indexs for the world orgs
    emp::vector<size_t> mPopIndex;
    //Partitioned up population
    emp::vector<emp::vector<size_t>> mPopPar;
    //Index of best org 
    size_t BEST_ORG;
    //Cohort we are evaluating 
    size_t COHORT;
    //Current Agent genome size Champion!
    size_t CHAMP_SIZE;
    //Directory We are writing too!
    std::string DIR;
};

size_t Experiment::INPUT1 = 0;
size_t Experiment::INPUT2 = 0;
size_t Experiment::INPUT3 = 0;
size_t Experiment::RESULT = 0;

/* FUNCTIONS DEDICATED TO THE EXPERIMENT */

//Run the experiment
void Experiment::Run()
{
  Experiment::Config_All();
  size_t size = mCohortSize[COHORT]; size_t grp = mCohortGroup[COHORT];
  //Variables to store values for the csv!
  std::ofstream csv; 
  std::string filename = DIR + EXP_STR + std::to_string(grp) + "-" + std::to_string(size) + ".csv";
  std::cout << filename << std::endl;
  csv.open(filename);
  csv << "POP_BEST" << "," << "POP_AVG" << "," << "QUALS_CNT" << "," << "SOL_CNT" << std::endl;

  //Store the chanpion genomes!
  std::ofstream champs;
  std::string fn = DIR + "champion.txt";
  std::cout << fn << std::endl;
  champs.open(fn);
  
  //Go through the entire simulation!
  for(size_t gen = 0; gen < NUM_GENS; ++gen)
  {
    //Reshuffle the cohorts everytime!
    Experiment::Partition(size, grp); 
    std::cout << EXP_STR << "Gen-" << size << "-" << grp << ": " << gen << std::endl;

    //Evaluation step along with finding number of solutions
    emp::vector<Agent> best_orgs = Experiment::Evaluation_step(csv); 
    size_t solutions = 0;
    if(best_orgs.size() > 0)
    {
      solutions = Experiment::Final_Test(best_orgs, champs, gen);
    }
    csv << solutions << std::endl;
    std::cout << "Number of solutions: " << solutions << std::endl;

    if((gen%SNAP_SHOT) == 0)
    {
      hardware_t avi;
      avi.SetGenome(mWorld->GetOrg(BEST_ORG).GetGenome());
      avi.PrintGenome();
    }
    Experiment::Selection_step(size, grp);
    Experiment::Update_step();
    std::cout << std::endl;
  }
  champs.close();
  csv.close();
}

//Set the fitness functions
void Experiment::Set_Fit()
{
  mTrainFuns.resize(mTraining.size());

  for(size_t i = 0; i < mTraining.size(); ++i)
  {
    mTrainFuns[i] = [i](Agent & agent)
    {
      return agent.GetScore(i);
    };
  }  
  if(mTrainFuns.size() != POP_SIZE)
  {
    auto temp = mTrainFuns;
    size_t mod = mTrainFuns.size();
    size_t cnt = 0;
    while(mTrainFuns.size() != POP_SIZE)
    {
      mTrainFuns.push_back(temp[cnt % mod]);
      ++cnt;
    }
  }
}

//Evalute each agent against training cases
emp::vector<Experiment::Agent> Experiment::Evaluation_step(std::ofstream & csv)
{
  emp::vector<Experiment::Agent> testing;
  size_t quals_cnt = 0;
  //Have every agent go againt the training cases
  for(size_t i = 0; i < mWorld->GetSize() ; ++i)
  {
    Agent & a = mWorld->GetOrg(i);
    Experiment::Single_Run(a);
  }

  //Calculate the average success on training casses for all orgs
  double avg = 0.0; double best_score = 0.0;
  for(size_t i = 0; i < mWorld->GetSize(); ++i)
  {
    Agent & a = mWorld->GetOrg(i);
    double score = a.SumScore();

    if(best_score < score)
    {
      best_score = score;
      BEST_ORG = i;
    }

    if(score == (double) mTraining.size())
    {
      testing.push_back(a);
      ++quals_cnt;
    }

    avg += score;
  }
  double size = mWorld->GetSize();
  avg = avg / size;
  std::cout << "PopBestScore: " << best_score << " PopAvgScore: " << avg << " Qualifier Cnt: " << quals_cnt << " Min Champ Genome Size: " << CHAMP_SIZE << std::endl;
  csv << best_score << "," << avg << "," << quals_cnt << ",";
  return testing;
}

//Run a single organism
void Experiment::Single_Run(Agent & a)
{
  //Resize Agent vector for score storage
  a.Resize(mTraining.size());

  //Run all training cases on the org
  for(size_t j = 0; j < mTraining.size(); ++j)
  {
    //initialize org and insert genome
    hardware_t hw(a.GetGenome());
    Case c = mTraining[j];
    //Set up case paramaters in the hardware.
    Experiment::LoadCase(hw, c);

    //Hardware runs executes its genome
    hw.Process(NUM_ITER);
    //We store it guess
    double guess = hw.GetTrait(RESULT);

    //If the case is Number IO then we need to score with respect to epsillon
    if(EXP == NUMBERIO)
    {
      double diff = std::fabs(guess - c.ans);
      //Guess it to far off our threshold
      if(diff > EPSILLON)
      {
        a.InsertScore(j,0);
      }
      else
      {
        double score = 1 - (diff / EPSILLON);
        a.InsertScore(j,score);
      }
    }
    //Every other case requires an exact match to the output.
    else
    {
      if(guess == c.ans)
      {
        a.InsertScore(j, 1);
      }
      else
      {
        a.InsertScore(j, 0);
      }
    }
  }
}

//Final test for the agents able to solve all training casses
size_t Experiment::Final_Test(emp::vector<Agent> pop, std::ofstream & champs, size_t gen)
{
  emp::vector<Agent> winners;
  for(auto org : pop)
  {
    double cnt = 0;
    for(auto c : mTesting)
    {
      //Load genome into hardware!
      hardware_t hw(org.GetGenome());
      //Load cases!
      Experiment::LoadCase(hw, c);
      //Hardware runs executes its genome
      hw.Process(NUM_ITER);
      //We store it guess
      double guess = hw.GetTrait(RESULT);

      //If the case is Number IO then we need to score with respect to epsillon
      if(EXP == NUMBERIO)
      {
        double diff = std::fabs(guess - c.ans);
        //Guess it to far off our threshold
        if(diff <= EPSILLON)
        {
          double score = 1 - (diff / EPSILLON);
          cnt+=score;
        }
      }
      //Every other case requires an exact match to the output.
      else if  (guess == c.ans)
      {
        cnt += 1.0;
      }
    }

    if(cnt == ((double) mTesting.size()))
    {
      winners.push_back(org);
    }
  }

  //This is to find all the organisms that are worthy of being named champions
  std::sort(winners.begin(), winners.end(), [](Agent & a, Agent & b) 
  {
    return a.GetGenome().sequence.size() < b.GetGenome().sequence.size();
  });

  if(winners.size() > 0)
  {
    size_t curr = winners[0].GetGenome().sequence.size();
    if(curr < CHAMP_SIZE)
    {
      CHAMP_SIZE = curr;
      champs << "Gen: " << gen << std::endl;
      hardware_t org(winners[0].GetGenome());
      org.PrintGenome(champs);
      champs << std::endl;
    }
  }

  return winners.size();
}
 
//Selection
void Experiment::Selection_step(size_t size, size_t grp)
{
  if(SELECTION == CLS)
  {
    emp::CohortSelect(*mWorld, mPopPar, mTrainFuns, size, grp, mRng, MAX_SIZE_G);
  }

  if(SELECTION == TOURN)
  {
    emp::TournamentSelect(*mWorld, mWorld->GetSize(), 1);
  }
}

//Update
void Experiment::Update_step()
{
  mWorld->Update();
  mWorld->DoMutations();
}

//Partition up the orgs and functions!
void Experiment::Partition(size_t num, size_t grp)
{
  emp::Shuffle(*mRng, mPopIndex);
  mPopPar.clear();

  //Set up each partition
  for(size_t i = 0; i < grp; ++i)
  {
    emp::vector<size_t> cohort;
    //Add orgs/funs to each cohort
    for(size_t j = 0; j < num; ++j)
    {
      size_t index = (i*num) + j;
      cohort.push_back(mPopIndex[index]);
    }
    mPopPar.push_back(cohort);
  }

  if(mPopPar.size() != grp)
  {
    std::cout << "Number of org partitions does not match grp" << std::endl;
    exit(-1);
  }
  for(auto v : mPopPar)
  {
    if(v.size() != num)
    {
      std::cout << "Number of orgs in partition incorrect" << std::endl;
      exit(-1);
    }
  }
}

//Load the training and testing csv for Median data
void Experiment::LoadMedData(std::string train, std::string test)
{
  std::ifstream f; std::string line;
  f.open(train);

  //Go through every row in the csv
  //Skip the first line
  std::getline(f,line);
  while(std::getline(f, line))
  {
    std::string cell; emp::vector<double> row;
    std::istringstream lines(line);

    //Go through every cell
    while(std::getline(lines, cell, ','))
      row.push_back(std::stod(cell));

    //Store the row values into our data vector
    Case c;
    c.a = row[0]; c.b = row[1];
    c.c = row[2]; c.ans = row[3];
    mTraining.push_back(c);
  }

  std::ifstream f1; std::string l;
  f1.open(test); 
  std::getline(f1, l);

  //Go through every row after the first one
  while(std::getline(f1, l))
  {
    std::string cell; emp::vector<double> row;
    std::istringstream lines(l);

    //Go through every cell in the row
    while(std::getline(lines, cell, ','))
      row.push_back(std::stod(cell));

    //Store the row values into our data vector
    Case c;
    c.a = row[0]; c.b = row[1];
    c.c = row[2]; c.ans = row[3];
    mTesting.push_back(c);
  }
}

//Load the training and testing csv for Sum of Squares data
void Experiment::LoadSOSData(std::string train, std::string test)
{
  std::ifstream f; std::string line;
  f.open(train);

  //Go through every row in the csv
  //Skip the first line
  std::getline(f,line);
  while(std::getline(f, line))
  {
    std::string cell; emp::vector<double> row;
    std::istringstream lines(line);

    //Go through every cell
    while(std::getline(lines, cell, ','))
      row.push_back(std::stod(cell));

    //Store the row values into our data vector
    Case c;
    c.a = row[0]; c.ans = row[1];
    mTraining.push_back(c);
  }

  std::ifstream f1; std::string l;
  f1.open(test); 
  std::getline(f1, l);

  //Go through every row after the first one
  while(std::getline(f1, l))
  {
    std::string cell; emp::vector<double> row;
    std::istringstream lines(l);

    //Go through every cell in the row
    while(std::getline(lines, cell, ','))
      row.push_back(std::stod(cell));

    //Store the row values into our data vector
    Case c;
    c.a = row[0]; c.ans = row[1];
    mTesting.push_back(c);
  }
}

//Load the training and testing csv for Number IO data
void Experiment::LoadIOData(std::string train, std::string test)
{
  std::ifstream f; std::string line;
  f.open(train);

  //Go through every row in the csv
  //Skip the first line
  std::getline(f,line);
  while(std::getline(f, line))
  {
    std::string cell; emp::vector<double> row;
    std::istringstream lines(line);

    //Go through every cell
    while(std::getline(lines, cell, ','))
      row.push_back(std::stod(cell));

    //Store the row values into our data vector
    Case c;
    c.a = row[0]; c.b = row[1]; c.ans = row[2];
    mTraining.push_back(c);
  }

  std::ifstream f1; std::string l;
  f1.open(test); 
  std::getline(f1, l);

  //Go through every row after the first one
  while(std::getline(f1, l))
  {
    std::string cell; emp::vector<double> row;
    std::istringstream lines(l);

    //Go through every cell in the row
    while(std::getline(lines, cell, ','))
      row.push_back(std::stod(cell));

    //Store the row values into our data vector
    Case c;
    c.a = row[0]; c.b = row[1]; c.ans = row[2];
    mTesting.push_back(c);
  }
}


/* FUNCTIONS DEDICATED TO THE CONFIGURATIONS and INSTRUCTIONS */

//Will get the vote of a hardware
void Experiment::Inst_GetA(hardware_t & hw, const inst_t & inst)
{
  double A = (double) hw.GetTrait(INPUT1);
  hw.regs[inst.args[0]] = A;
}

//Will get the vote of a hardware
void Experiment::Inst_GetB(hardware_t & hw, const inst_t & inst)
{
  double B = (double) hw.GetTrait(INPUT2);
  hw.regs[inst.args[0]] = B;
}

//Will get the vote of a hardware
void Experiment::Inst_GetC(hardware_t & hw, const inst_t & inst)
{
  double C = (double) hw.GetTrait(INPUT3);
  hw.regs[inst.args[0]] = C;
}

//Will set the result of the hardware
void Experiment::Inst_SetAns(hardware_t & hw, const inst_t & inst)
{
  double pred = hw.regs[inst.args[0]];
  hw.SetTrait(RESULT, pred);
}

//Confiugre all the neccesary things
void Experiment::Config_All()
{
  Experiment::Config_Inst();
  Experiment::Config_World();
  Experiment::Config_HW();
}

//Will make the instruction library
void Experiment::Config_Inst()
{
  //Load all default instruction!
  inst_lib = emp::AvidaGP::inst_lib_t::DefaultInstLib();

  if(EXP == MEDIAN)
  {
    inst_lib.AddInst("GetA", Inst_GetA, 1, "INPUT1 => Local Memory Arg1");
    inst_lib.AddInst("GetB", Inst_GetB, 1, "INPUT2 => Local Memory Arg1");
    inst_lib.AddInst("GetC", Inst_GetC, 1, "INPUT3 => Local Memory Arg1");
    inst_lib.AddInst("SetAns", Inst_SetAns, 1, "Local Memory Arg1 => Hw.Trait[RESULT]");
  }
  else if (EXP == NUMBERIO)
  {
    inst_lib.AddInst("GetA", Inst_GetA, 1, "INPUT1 => Local Memory Arg1");
    inst_lib.AddInst("GetB", Inst_GetB, 1, "INPUT2 => Local Memory Arg1");
    inst_lib.AddInst("SetAns", Inst_SetAns, 1, "Local Memory Arg1 => Hw.Trait[RESULT]");
  }
  else if (EXP == SUMOFSQU)
  {
    inst_lib.AddInst("GetA", Inst_GetA, 1, "INPUT1 => Local Memory Arg1");
    inst_lib.AddInst("SetAns", Inst_SetAns, 1, "Local Memory Arg1 => Hw.Trait[RESULT]");
  }  
}

//Will create the hardware
void Experiment::Config_HW()
{
  //Initialize the instruction set
  for(size_t i = 0; i < POP_SIZE; ++i)
  {
    program_t p(inst_lib);
    Agent a(p);
    hardware_t org(a.GetGenome());

    for(size_t i = 0; i < MAX_SIZE_G; ++i)
    {
      auto inst = org.GetRandomInst(*mRng);
      org.PushInst(inst);
    }
    a.SetGenome(org.GetGenome());
    mWorld->Inject(a.GetGenome(), 1);
  }
}

//Will configure the world
void Experiment::Config_World()
{
  mWorld->Reset();
  mWorld->SetPopStruct_Mixed(true);
  mWorld->SetFitFun([](Agent & agent) {return agent.GetTotal();});
  mWorld->SetMutFun([this](Agent & agent, emp::Random & r)
  {
    int count = 0;
    hardware_t org(inst_lib);
    org.SetGenome(agent.GetGenome());
    for (size_t i = 0; i < org.GetSize(); ++i) 
    {
      if (r.P(INST_MUT_RATE)) 
      {
          org.RandomizeInst(i, r);
          count++;
      }
      for (size_t j = 0; j < emp::AvidaGP::base_t::INST_ARGS; j++) 
      {
          if (r.P(ARG_MUT_RATE)) 
          {
              org.genome.sequence[i].args[j] = r.GetUInt(org.CPU_SIZE);        
              count++;
          }
      }
      if (r.P(INS_MUT_RATE)) 
      {
          if (org.GetSize() < MAX_SIZE_G) 
          {
              org.genome.sequence.insert(org.genome.sequence.begin() + (int)i, emp::AvidaGP::genome_t::sequence_t::value_type());
              org.RandomizeInst(i, r);
              count++;
          }
      }
      if (r.P(DEL_MUT_RATE)) 
      {
          if (org.GetSize() > 1) 
          {
              org.genome.sequence.erase(org.genome.sequence.begin() + (int)i);
              count++;
          }
      }
  }
  agent.SetGenome(org.GetGenome());
  return count;
  });
}

/*Helper Functions!*/

//Load data into agent depending on the case!
void Experiment::LoadCase(hardware_t & hw, Case & c)
{
  //For median experiment we need to load all the data a,b,c
  if(EXP == MEDIAN)
  {
    hw.SetTrait(INPUT1, c.a);
    hw.SetTrait(INPUT2, c.b); 
    hw.SetTrait(INPUT3, c.c);
  }
  //For sum of squares we only need a
  else if (EXP == SUMOFSQU)
  {
    hw.SetTrait(INPUT1, c.a);
  }
  //For Number IO we only need a,b
  else if (EXP == NUMBERIO)
  {
    hw.SetTrait(INPUT1, c.a);
    hw.SetTrait(INPUT2, c.b);
  }
  else
  {
    std::cout << "EXPERIMENT VALUE NOT SET" << std::endl;
    exit(-1);
  }
  hw.SetTrait(RESULT, -9999);
}

#endif