## Implementation of an algorithm to solve the multi-depot vehicle routing problem.

### Run:
First you need to compile the code:

```bash
$ make
```
Then you can run:

```bash
$ ./main <infile> <it> <pop size> <mut ratio> <n_populations> <it-mig> <it-in-mig> <migration mode> [<seed>]
```
There are several parameters to run, below they are listed in the order in which they should be placed.

\<infile>        : File with instance parameters
  
\<it>            : How many iterations the method should run
  
\<pop size>      : How many individuals there arein each population
  
\<mut ratio>     : Mutation Ratio [0.000 - 1.000]
  
\<n_populations> : Number of populations for the same route

\<it-mig>        : How many iterations between migrations

\<it-in-mig>     : How many iterations to a individual migrate

\<migration mode>: 0 to perform maximum number of migrations per cicle, otherwise 1 migration per clicle
  
 
[\<seed>]        : The seed to start random numbers in the method, this parameter is optional


The input instances can be found in  instances directory. They was taken from
(https://github.com/fboliveira/MDVRP-Instances) project.  But you can also build your own instances.
