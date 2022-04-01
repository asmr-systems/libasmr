#include "fs.h"


asmr::FileSystem::FileSystem(Disk::Id) {

}

asmr::FileSystem::Status asmr::FileSystem::init() {
    if (f_mount(&fs, "0:", 1) == FR_OK) {
        return Status::Ok;
    }

    return Status::NotReady;
}

// asmr::FileSystem::Status asmr::FileSystem::mount() {

//     return Status::Ok;
// }

asmr::FileSystem::Status asmr::FileSystem::open(const char* path) {
    return Status::Ok;
}

asmr::FileSystem::Status asmr::FileSystem::list(const char* dir) {
    return Status::Ok;
}
