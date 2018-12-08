#ifndef HP_CONFIG_H
#define HP_CONFIG_H

#include "config/config.h"
constexpr double MUT = 0.009;

EMP_BUILD_CONFIG( HPConfig,
  GROUP(HARDWARE_GROUP, "Hardware settings"),
  VALUE(INPUT1,       size_t,     0, "Position that the UID will be in hw trait vector"),
  VALUE(INPUT2,      size_t,  1, "Position that the Vote will be in hw trait vector"),
  VALUE(INPUT3,      size_t,  2, "Position that the Coordinate X will be in hw trait vector"),
  VALUE(RESULT,      size_t,  3, "Position that the Coordinate Y will be in hw trait vector"),
  GROUP(MUTATION_GROUP, "Mutation settings"),
  VALUE(MAX_SIZE_G, size_t, 50, "Maximum Length of Genome"), 
  VALUE(ARG_SUB__PER_ARG, double, MUT, "% For argument substitution "),
  VALUE(INST_MUT_RATE, double, MUT, "% For instruction substitution "),
  VALUE(ARG_MUT_RATE, double, MUT, "% For instruction insertion "),
  VALUE(DEL_MUT_RATE, double, MUT, "% For instruction deletion "), 
  VALUE(INS_MUT_RATE, double, MUT, "% For instruction deletion "),
  GROUP(EXPERIMENT_GROUP, "Experiment settings"),
  VALUE(POP_SIZE,  size_t, 1000, "Population size."),
  VALUE(NUM_GENS,  size_t, 10000, "Number of generations per experiments."),
  VALUE(RNG_SEED,  size_t,    10, "Random number seed."),
  VALUE(SNAP_SHOT,  size_t,   50, "Time that we will take a snapshot of population"),
  VALUE(NUM_ITER, size_t,     100, "Number of iterations per trial."),
  VALUE(EXP, size_t, 0, "0->Median Experiment, 1->NumberIO Experiment, 2->SumOfSquares Experiment"),
  VALUE(SELECTION, size_t, 0, "0->CLS, 1->Tournament"),
  VALUE(COHORT, size_t, 5, "Positions in {50, 100, 200, 250, 500, 1000}"),
  VALUE(DIR, std::string, "", "Directory where we are sending the data too.")
)

#endif
