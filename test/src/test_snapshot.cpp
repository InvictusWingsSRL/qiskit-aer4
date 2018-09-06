#define CATCH_CONFIG_MAIN
#include <map>
#include <catch.hpp>

#include <base/controller.hpp>
#include <base/engine.hpp>
#include <simulators/qubitvector/qubitvector.hpp>
#include <simulators/qubitvector/qv_state.hpp>

#include "utils.hpp"

namespace AER{
namespace Test{

TEST_CASE( "Simulators Snapshot", "[snaphot]" ) {
    std::map<std::string, json_t> qobj_snapshots;
    qobj_snapshots["state"] =
        AER::Test::Utilities::load_qobj("../../test/data/qobj_snapshot_state.json");
    qobj_snapshots["probs"] =
        AER::Test::Utilities::load_qobj("../../test/data/qobj_snapshot_probs.json");
    qobj_snapshots["pauli"] =
        AER::Test::Utilities::load_qobj("../../test/data/qobj_snapshot_pauli.json");
    qobj_snapshots["matrix"] =
        AER::Test::Utilities::load_qobj("../../test/data/qobj_snapshot_matrix.json");

    using State = AER::QubitVector::State;
    AER::Base::Controller sim{};

    SECTION( "State simulator snapshot" ) {
        auto expected_result = R"({
                "final":[[[0.7071067811865476,0.0],[0.0,0.0],[0.0,0.0],[0.7071067811865475,0.0]]],
                "initial":[[[1.0,0.0],[0.0,0.0],[0.0,0.0],[0.0,0.0]]],
                "middle":[[[0.7071067811865476,0.0],[0.7071067811865475,0.0],[0.0,0.0],[0.0,0.0]]]
            })"_json;
        auto result = sim.execute<QV::QubitVector, State>(qobj_snapshots["state"]);
        result = result["result"][0]["data"]["snapshots"]["state"];
        REQUIRE(result == expected_result);
    }
    SECTION( "Probs simulator snapshot" ) {
        REQUIRE(false);
    }
    SECTION( "Pauli simulator snaphsot" ) {
        REQUIRE(false);
    }
    SECTION( "Unitary simulator snapshot" ) {
        REQUIRE(false);
    }
}

//------------------------------------------------------------------------------
} // end namespace Test
//------------------------------------------------------------------------------
} // end namespace AER
//------------------------------------------------------------------------------
