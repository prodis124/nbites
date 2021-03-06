#include <Python.h>
#include <boost/python.hpp>
#include <boost/python/object.hpp>
#include <boost/python/module.hpp>
#include <boost/python/args.hpp>
#include <boost/shared_ptr.hpp>
using namespace std;
using namespace boost::python;
using namespace boost;

// #include "MCL.h"
// #include "LocEKF.h"
#include "LocSystem.h"
#include "BallEKF.h"

static shared_ptr<LocSystem> loc_reference;
static shared_ptr<BallEKF> ballEKF_reference;

/**
 * Class to hold the localization data needed in Python
 *
 */
class PyLoc {
private:
    shared_ptr<LocSystem> loc;
    shared_ptr<BallEKF> ballEKF;
public:
    PyLoc() {
        loc = loc_reference;
        ballEKF = ballEKF_reference;
    }

    void reset() {
        loc->reset();
        ballEKF->reset();
    }
    void resetBall() {
        ballEKF->reset();
    }
    void blueGoalieReset() {
        loc->blueGoalieReset();
        ballEKF->reset();
    }
    void redGoalieReset() {
        loc->redGoalieReset();
        ballEKF->reset();
    }

	void resetLocTo(float x, float y, float h){
		loc->resetLocTo(x, y, h * TO_RAD);
		ballEKF->reset();
	}

    /* Getters */
    // We use degreees in python, and radians in C++
    // Self localization
    const float getXEst() const { return loc->getXEst(); }
    const float getYEst() const { return loc->getYEst(); }
    const float getHEst() const { return loc->getHEstDeg(); }
    const float getRadHEst() const { return loc->getHEst(); }
    // Self Uncertainty
    const float getXUncert() const { return loc->getXUncert(); }
    const float getYUncert() const { return loc->getYUncert(); }
    const float getHUncert() const { return loc->getHUncertDeg(); }
    const float getRadHUncert() const { return loc->getHUncert(); }

    // Ball localization
    // Global Coordinates
    const float getBallXEst() const { return ballEKF->getXEst(); }
    const float getBallYEst() const { return ballEKF->getYEst(); }
    const float getXVelocityEst() const { return ballEKF->getXVelocityEst(); }
    const float getYVelocityEst() const { return ballEKF->getYVelocityEst(); }

    // Ball Uncertainty
    // Global Coordinates
    const float getBallXUncert() const { return ballEKF->getXUncert(); }
    const float getBallYUncert() const { return ballEKF->getYUncert(); }
    const float getXVelocityUncert() const {
        return ballEKF->getXVelocityUncert();
    }
    const float getYVelocityUncert() const {
        return ballEKF->getYVelocityUncert();
    }

    // Odometry
    const float getOdoF() const { return loc->getLastOdo().deltaF; }
    const float getOdoL() const { return loc->getLastOdo().deltaL; }
    const float getOdoR() const { return loc->getLastOdo().deltaR; }

};

BOOST_PYTHON_MODULE(_localization)
{
    class_<PyLoc>("Loc")
        .add_property("x", &PyLoc::getXEst)
        .add_property("y", &PyLoc::getYEst)
        .add_property("h", &PyLoc::getHEst)
        .add_property("radH", &PyLoc::getRadHEst)
        .add_property("ballX", &PyLoc::getBallXEst)
        .add_property("ballY", &PyLoc::getBallYEst)
        .add_property("ballVelX", &PyLoc::getXVelocityEst)
        .add_property("ballVelY", &PyLoc::getYVelocityEst)
        // Uncertainty
        .add_property("xUncert", &PyLoc::getXUncert)
        .add_property("yUncert", &PyLoc::getYUncert)
        .add_property("hUncert", &PyLoc::getHUncert)
        .add_property("radHUncert", &PyLoc::getRadHUncert)
        .add_property("ballXUncert", &PyLoc::getBallXUncert)
        .add_property("ballYUncert", &PyLoc::getBallYUncert)
        .add_property("ballVelXUncert", &PyLoc::getXVelocityUncert)
        .add_property("ballVelYUncert", &PyLoc::getYVelocityUncert)
        // Odometry
        .add_property("lastOdoF", &PyLoc::getOdoF)
        .add_property("lastOdoL", &PyLoc::getOdoL)
        .add_property("lastOdoR", &PyLoc::getOdoR)
        // functional
        .def("reset", &PyLoc::reset, "reset the localization system")
        .def("resetBall", &PyLoc::resetBall)
        .def("blueGoalieReset", &PyLoc::blueGoalieReset,
             "reset the localization system")
        .def("redGoalieReset", &PyLoc::redGoalieReset,
             "reset the localization system")
		.def("resetLocTo", &PyLoc::resetLocTo,
			 "reset the localiation system to a specific location")
        ;
}

void c_init_localization() {
    if (!Py_IsInitialized())
        Py_Initialize();
    try {
        init_localization();
    } catch (error_already_set) {
        PyErr_Print();
    }
}

void set_loc_reference(shared_ptr<LocSystem> _loc)
{
    loc_reference = _loc;
}

void set_ballEKF_reference(shared_ptr<BallEKF> _ballEKF)
{
    ballEKF_reference = _ballEKF;
}
