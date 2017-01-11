/// \file ProgramRegisterRead.cxx
/// \brief Utility that reads a register from a RORC
///
/// \author Pascal Boeschoten (pascal.boeschoten@cern.ch)

#include "CommandLineUtilities/Program.h"
#include <iostream>
#include "RORC/ChannelFactory.h"

namespace {
using namespace AliceO2::Rorc::CommandLineUtilities;

class ProgramRegisterRead: public Program
{
  public:

    virtual Description getDescription()
    {
      return {"Read Register", "Read a single register", "./rorc-reg-read --serial=12345 --channel=0 --address=0x8"};
    }

    virtual void addOptions(boost::program_options::options_description& options)
    {
      Options::addOptionRegisterAddress(options);
      Options::addOptionChannel(options);
      Options::addOptionCardId(options);
    }

    virtual void run(const boost::program_options::variables_map& map)
    {
      auto cardId = Options::getOptionCardId(map);
      int address = Options::getOptionRegisterAddress(map);
      int channelNumber = Options::getOptionChannel(map);
      auto params = AliceO2::Rorc::Parameters::makeParameters(cardId, channelNumber);
      auto channel = AliceO2::Rorc::ChannelFactory().getSlave(params);

      // Registers are indexed by 32 bits (4 bytes)
      uint32_t value = channel->readRegister(address / 4);
      if (isVerbose()) {
        std::cout << Common::makeRegisterString(address, value);
      } else {
        std::cout << "0x" << std::hex << value << '\n';
      }
    }
};
} // Anonymous namespace

int main(int argc, char** argv)
{
  return ProgramRegisterRead().execute(argc, argv);
}