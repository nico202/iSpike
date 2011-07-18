#ifndef JOINTINPUTCHANNEL_HPP_
#define JOINTINPUTCHANNEL_HPP_

//iSpike includes
#include <iSpike/Channel/InputChannel/InputChannel.hpp>
#include <iSpike/Reader/YarpAngleReader.hpp>
#include <iSpike/Property.hpp>
#include <iSpike/Channel/InputChannel/InputChannelDescription.hpp>
#include <iSpike/NeuronSim/IzhikevichNeuronSim.hpp>
#include "iSpike/iSpikeThread.hpp"

//Other includes
#include <string>
#include <vector>
#include <map>
using namespace std;

namespace ispike {

	/** Converts a joint angle input into a spike pattern */
	class JointInputChannel : public InputChannel {

		private:
			//==========================  VARIABLES  ==========================
			std::vector< std::vector<int> > buffer;
			AngleReader* reader;
			int degreeOfFreedom;
			double currentAngle;
			double sd;
			double minAngle;
			double maxAngle;

			/*! Izhikevich neuron simulator */
			IzhikevichNeuronSim* izhikevichNeuronSim;

			/*! Parameters for Izhikevich neurons */
			double parameterA;
			double parameterB;
			double parameterC;
			double parameterD;

			double currentFactor;
			double constantCurrent;


			//==============================  METHODS  =========================
			void updateProperties(map<string, Property>& properties, bool updateReadOnly);


		public:
			JointInputChannel();
			~JointInputChannel();
			double getCurrentAngle(){ return currentAngle; }
			std::vector< std::vector<int> >& getFiring() { return buffer; }
			void initialize(AngleReader* reader, map<string, Property> properties);
			void setProperties(map<string, Property>& properties);
			void step();

	};
}

#endif /* JOINTINPUTCHANNEL_HPP_ */
