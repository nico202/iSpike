#ifndef INPUTCHANNEL_H_
#define INPUTCHANNEL_H_

#include <iSpike/Channel/Channel.hpp>
#include <iSpike/Description.hpp>
#include <iSpike/Reader/AngleReader.hpp>
#include <iSpike/PropertyHolder.hpp>

#include <vector>
#include <string>

namespace ispike {

	/**
	 * This class represents a directed Channel from a signal source (eg vision)
	 * to a spike output, so spikes can be read from this channel
	 */
	class InputChannel : public Channel {
		public:
			virtual ~InputChannel(){}
			Description getChannelDescription() { return channelDescription; }

			/*! Returns the latest spikes generated by the channel */
			virtual const std::vector<unsigned>& getFiring() = 0;

			/*! Initializes the channel with a reader and set of properties 
			 *
			 * The Channel assumes ownership of the Reader object.
			 */
			virtual void initialize(Reader* reader, map<std::string, Property>& properties) = 0;

		protected:
			Description channelDescription;
	};

}

#endif /* INPUTCHANNEL_H_ */
