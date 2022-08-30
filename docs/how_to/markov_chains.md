# How-to: Simulating a Markov Chain

For some mathematical background, check out [TODO] this exposition

# Objective

In this guide we are going to simulate a discrete-time Markov Chain with finite
state space `X` and transition matrix `T`

Before we begin, we make note that the elements in `X` will be indexed by 1, ..., n, and that an appropriate transition matrix `T` has been instantiated.

# Markov Chain

To begin this guide, we will use a transition matrix that arises from the classic _gambler's ruin_ problem, which can be constructud using the `MarkovChain::gambler()` function.