#include "engine/state/GameActionInteractor.hpp"

// Static create method for native initialization
std::shared_ptr< engine::GameInteractor > engine::GameInteractor::Create() {
    return std::make_shared< engine::state::GameActionInteractor_t >();
}

engine::state::GameActionInteractor_t::GameActionInteractor_t() {

}

std::string engine::state::GameActionInteractor_t::Test() {
    return "Testing from C++!";
}