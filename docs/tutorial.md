# Tutorial

### Abstract Goals

- Provide a beginner with all they need to know
- Guided lessons
- Show them how rather than "what"

### Concrete Objectives

- Show how to download, build, and use this library
- Introduce the Matrix class and show how to use it


# RNG

Libejovo uses the xoroshiro prng for its non-cryptographic purposes, and a default
generator can be directly accessed in the `ejovo::rng` namespace as `ejovo::rng::default`. Otherwise, functions like `runif` and `rnorm` will use
`ejovo::rng::default` in the background.