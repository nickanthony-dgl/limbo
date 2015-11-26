#ifndef LIMBO_STAT_SAMPLES_HPP
#define LIMBO_STAT_SAMPLES_HPP

#include <limbo/stat/stat_base.hpp>

namespace limbo {
    namespace stat {
        template <typename Params>
        struct Samples : public StatBase<Params> {
            template <typename BO, typename AggregatorFunction>
            void operator()(const BO& bo, const AggregatorFunction&, bool blacklisted)
            {
                if (!bo.stats_enabled() || bo.samples().empty())
                    return;

                this->_create_log_file(bo, "samples.dat");

                if (bo.iteration() == 0) {
                    for (size_t i = 0; i < bo.samples().size() -1; i++)
                        (*this->_log_file) << "-1 " << bo.samples()[i].transpose() << std::endl;
                }

                if (!blacklisted)
                    (*this->_log_file) << bo.iteration() << " " << bo.samples().back().transpose() << std::endl;
            }
        };
    }
}

#endif
