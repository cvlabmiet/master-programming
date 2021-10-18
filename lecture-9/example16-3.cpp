#include <iostream>
#include <type_traits>

#include <boost/msm/front/euml/euml.hpp>
#include <boost/msm/front/euml/state_grammar.hpp>
#include <boost/msm/back/state_machine.hpp>

using namespace boost::msm::front::euml;

BOOST_MSM_EUML_DECLARE_ATTRIBUTE(int, switched_on)

BOOST_MSM_EUML_STATE((), Off)
BOOST_MSM_EUML_STATE((), On)

BOOST_MSM_EUML_EVENT(press)

BOOST_MSM_EUML_ACTION(WriteMessage)
{
    template<class Evt, class Fsm, class SourceState, class TargetState>
    void operator()(const Evt&, Fsm&, const SourceState&, const TargetState&)
    {
        if constexpr (std::is_same_v<SourceState, decltype(Off)>)
            std::cout << "Switched on\n";
        else
            std::cout << "Switched off\n";
    }
};

BOOST_MSM_EUML_TRANSITION_TABLE((
    Off + press [fsm_(switched_on) < Int_<2>()] / (++fsm_(switched_on), WriteMessage()) == On,
    On + press / WriteMessage() == Off
), light_transition_table)

BOOST_MSM_EUML_DECLARE_STATE_MACHINE((
    light_transition_table, init_ << Off, no_action, no_action, attributes_ << switched_on
), light_state_machine)

int main()
{
    boost::msm::back::state_machine<light_state_machine> light;
    std::cout << "Current state: " << *(light.current_state()) << "\n";
    light.process_event(press);
    std::cout << "Current state: " << *(light.current_state()) << "\n";
    light.process_event(press);
    std::cout << "Current state: " << *(light.current_state()) << "\n";
    light.process_event(press);
    std::cout << "Current state: " << *(light.current_state()) << "\n";
    light.process_event(press);
    std::cout << "Current state: " << *(light.current_state()) << "\n";
    light.process_event(press);
    std::cout << "Current state: " << *(light.current_state()) << "\n";
}
