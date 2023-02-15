/// world generation probabilities (out of 100,000) (using the rand_ht() function)

// this is the probability of a rock cluster starting in any particular location
#define gwp_rock_cluster_start 1000
// this is the probability of the rock cluster branching off initially
#define gwp_rock_cluster_spread 50000
// this is how much rock_cluster_branch is scaled every iteration
#define gwp_rock_cluster_decay 0.9f

// probabilities for lake generation
#define gwp_lake_start 65
#define gwp_lake_spread 50000
#define gwp_lake_decay 0.93f

void gen_world();
