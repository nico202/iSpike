#ifndef YARPANGLEWRITER_HPP_
#define YARPANGLEWRITER_HPP_

//iSpike includes
#include <iSpike/Writer/AngleWriter.hpp>
#include <iSpike/YarpConnection.hpp>

//Other includes
#include <string>
#include <map>

namespace ispike {

	/** Writes angles to YARP */
	class YarpAngleWriter : public AngleWriter {
		public:
			YarpAngleWriter(string nameserverIP, unsigned nameserverPort);
			virtual ~YarpAngleWriter();
			void initialize(map<string,Property>& properties);
			void setAngle(double newAngle);
			void setDegreeOfFreedom(int dof);
			void setProperties(map<string,Property>& properties);
			void start();

		private:
			//===========================  VARIABLES  =========================
			/** Class handling connection to YARP */
			YarpConnection* yarpConnection;

			/*! Controls whether the angle should be output */
			bool angleChanged;

			/** The port to use */
			string portName;

			/** Amount to sleep in between writing commands */
			unsigned sleepDuration_ms;


			//===========================  METHODS  ===========================
			void updateProperties(map<string, Property>& properties);
			void workerFunction();
	};

}

#endif /* YARPANGLEWRITER_HPP_ */
