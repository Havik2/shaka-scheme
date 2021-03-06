//
// Created by Brandon Wong on 3/26/18.
//

#ifndef SHAKA_SCHEME_GC_HPP
#define SHAKA_SCHEME_GC_HPP

#include "shaka_scheme/system/gc/GCList.hpp"
#include "shaka_scheme/system/gc/GCData.hpp"
#include "shaka_scheme/system/base/Data.hpp"

namespace shaka {

    namespace gc {

    /**
         * @brief Implements the factory method of the GC, which allows the
         * construction of GCData and automatically adds those GCData to the
         * GCList
         */
        class GC {
        public:

            GC();
            ~GC();
            GC(const GC& other) = delete;
            GC(GC&& other);

            GCData *create_data(const Data& data);
            int get_size();
            void sweep();

        private:
            GCList list;
        };
    }
}
#endif //SHAKA_SCHEME_GC_HPP
