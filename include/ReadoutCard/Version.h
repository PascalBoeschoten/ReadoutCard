/// \file    RORC/include/ReadoutCard/Version.h
/// \brief   Report the version for this package.
///
/// \author  Barthelemy von Haller, CERN

#ifndef ALICEO2_READOUTCARD_VERSION_H
#define ALICEO2_READOUTCARD_VERSION_H

#include <string>
#include <sstream>

namespace AliceO2 {
namespace roc {
namespace Core {
/// The current major version.
#define RORC_VERSION_MAJOR 0

/// The current minor version.
#define RORC_VERSION_MINOR 1

/// The current patch level.
#define RORC_VERSION_PATCH 0

/// The current VCS revision.
#define RORC_VCS_REVISION "454f08b5d91df7204251e821b7349b5f355862c9"

/// True if the current version is newer than the given one.
#define RORC_VERSION_GT(MAJOR, MINOR, PATCH) \
  ((RORC_VERSION_MAJOR > MAJOR) ||           \
   (RORC_VERSION_MAJOR ==                    \
    MAJOR&&(RORC_VERSION_MINOR > MINOR || (RORC_VERSION_MINOR == MINOR&& RORC_VERSION_PATCH > PATCH))))

/// True if the current version is equal or newer to the given.
#define RORC_VERSION_GE(MAJOR, MINOR, PATCH) \
  ((RORC_VERSION_MAJOR > MAJOR) ||           \
   (RORC_VERSION_MAJOR ==                    \
    MAJOR&&(RORC_VERSION_MINOR > MINOR || (RORC_VERSION_MINOR == MINOR&& RORC_VERSION_PATCH >= PATCH))))

/// True if the current version is older than the given one.
#define RORC_VERSION_LT(MAJOR, MINOR, PATCH) \
  ((RORC_VERSION_MAJOR < MAJOR) ||           \
   (RORC_VERSION_MAJOR ==                    \
    MAJOR&&(RORC_VERSION_MINOR < MINOR || (RORC_VERSION_MINOR == MINOR&& RORC_VERSION_PATCH < PATCH))))

/// True if the current version is older or equal to the given.
#define RORC_VERSION_LE(MAJOR, MINOR, PATCH) \
  ((RORC_VERSION_MAJOR < MAJOR) ||           \
   (RORC_VERSION_MAJOR ==                    \
    MAJOR&&(RORC_VERSION_MINOR < MINOR || (RORC_VERSION_MINOR == MINOR&& RORC_VERSION_PATCH <= PATCH))))

/// Information about the current Monitoring version.
class Version {
  public:
    /// @return the current major version of Monitoring.
    static int getMajor()
    {
    return RORC_VERSION_MAJOR;
    }

    /// @return the current minor version of Monitoring.
    static int getMinor()
    {
    return RORC_VERSION_MINOR;
    }

    /// @return the current patch level of Monitoring.
    static int getPatch()
    {
    return RORC_VERSION_PATCH;
    }

    /// @return the current Monitoring version (MM.mm.pp).
    static std::string getString()
    {
    std::ostringstream version;
    version << RORC_VERSION_MAJOR << '.' << RORC_VERSION_MINOR << '.' << RORC_VERSION_PATCH;
    return version.str();
    }

    /// @return the VCS revision.
    static std::string getRevision()
    {
    return RORC_VCS_REVISION;
    }

    /// @return the current Monitoring version plus the VCS revision (MM.mm.pp.rev).
    static std::string getRevString()
    {
    std::ostringstream version;
    version << getString() << '.' << RORC_VCS_REVISION;
    return version.str();
    }
};

} // namespace Core
} // namespace ReadoutCard
} // namespace AliceO2

#endif // ALICEO2_READOUTCARD_VERSION_H
