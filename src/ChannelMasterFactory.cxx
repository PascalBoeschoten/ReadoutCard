///
/// \file ChannelMasterFactory.cxx
/// \author Pascal Boeschoten
///

#include "RORC/ChannelMasterFactory.h"
#include <dirent.h>
#include <boost/range/iterator_range.hpp>
#include <boost/interprocess/sync/file_lock.hpp>
#include <boost/format.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#ifdef ALICEO2_RORC_PDA_ENABLED
#include <pda.h>
#include "ChannelMaster.h"
#include "ChannelPaths.h"
#endif
#include "RorcException.h"

namespace b = boost;
namespace bip = boost::interprocess;
namespace bfs = boost::filesystem;

namespace AliceO2 {
namespace Rorc {

ChannelMasterFactory::ChannelMasterFactory()
{
}

ChannelMasterFactory::~ChannelMasterFactory()
{
}

void makeParentDirectories(const bfs::path& path)
{
  system(b::str(b::format("mkdir -p %s") % path.parent_path()).c_str());
}

// Similar to the "touch" Linux command
void touchFile(const bfs::path& path)
{
  std::ofstream ofs(path.c_str(), std::ios::app);
}

std::shared_ptr<ChannelMasterInterface> ChannelMasterFactory::getChannel(int serialNumber, int channelNumber,
    const ChannelParameters& params)
{
#ifdef ALICEO2_RORC_PDA_ENABLED
//  if (serialNumber == DUMMY_SERIAL_NUMBER) {
//    return std::make_shared<ChannelMasterDummy>();
//  } else {

  makeParentDirectories(ChannelPaths::pages(serialNumber, channelNumber));
  makeParentDirectories(ChannelPaths::state(serialNumber, channelNumber));
  makeParentDirectories(ChannelPaths::fifo(serialNumber, channelNumber));
  makeParentDirectories(ChannelPaths::lock(serialNumber, channelNumber));
  touchFile(ChannelPaths::lock(serialNumber, channelNumber));

  return std::make_shared<ChannelMaster>(serialNumber, channelNumber, params);
//  }
#else
#pragma message("PDA not enabled, Alice02::Rorc::ChannelMasterFactory::getCardFromSerialNumber() will always return dummy implementation")
  return std::make_shared<CardDummy>();
#endif
}

} // namespace Rorc
} // namespace AliceO2