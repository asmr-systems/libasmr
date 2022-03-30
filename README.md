# libASMR
Embedded C++ Library/Framework

# structure
it resembles the structure of arduino cores and libraries so that each new mcu only needs to implement its own core and all libraries will not be hardware dependent.
also, it would be nice to conform to the arduino api so that in the future people can hack on it using arduino stuff maybe.
no reason not to besides hubris ;)
`/arch/` contains directories for each architecture that implements the asmr api and provides libraries.
`/arch/<architecture>/` contains all the code for a specific `<architecture>` (e.g. `samd`, `)
`/arch/<architecture>/variants/` similar to how the Arduino core variants work: just provide ways to remap pins/registers etc between different mcu variants
`/arch/<architecture>/libraries/` contains all additional libraries that an architecture has available. these are optional to implement, but must satisfy the apis for the libraries they implement.
`/arch/<architecture>/core/` contains all the core files for implementing the api
`/api/` contains the core api. this is kind of a subset of the arduino core api at this point probably. maybe eventually it can become an actualy arduino core implementation? idk.
`/libraries/` this will contain all libraries that are available. they will have `library.properties` files (like in arduino libraries) which specify which architectures that are required. all libraries should be written to only depend on platform independent code.
