#ifndef ASMR_LIB_DISKS_H
#define ASMR_LIB_DISKS_H

#include <cstdint>
#include <map>
#include <vector>
#include <memory>


namespace asmr {

    class Disk {
    public:
        using Id = uint8_t;
        // TODO impl interface

        enum class Status {
            Ok       = 0,
            RWError  = 1,
            ReadOnly = 2,
            NotReady = 3,
            BadParam = 4,
            NoDisk   = 5,
        };

        virtual ~Disk() {}

        virtual Status init() = 0;
        virtual Status status() = 0;
        virtual Status read(uint8_t* buffer, uint64_t sector, unsigned int n) = 0;
        virtual Status write(const uint8_t* buffer, uint64_t sector, unsigned int n) = 0;
    };

    class Disks {
        static constexpr int N = 3;
    public:
        static void add(Disk::Id i, std::shared_ptr<Disk> d) {
            if (i < N) {
                auto& disks = Instance();
                disks.id_to_disk[i] = d;
            }
        };

        static std::shared_ptr<Disk> get(Disk::Id i) {
            if (i < N) {
                auto& disks = Instance();
                return disks.id_to_disk[i];
            }
            return nullptr;
        };
    protected:
        Disks() {}
        std::shared_ptr<Disk> id_to_disk[N];
        static Disks& Instance() {
            static Disks disks;
            return disks;
        };
    };

}

#endif
