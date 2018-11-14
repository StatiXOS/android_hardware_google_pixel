#ifndef HARDWARE_GOOGLE_PIXEL_POWERSTATS_GENERICSTATERESIDENCYDATAPROVIDER_H
#define HARDWARE_GOOGLE_PIXEL_POWERSTATS_GENERICSTATERESIDENCYDATAPROVIDER_H

#include <pixelpowerstats/PowerStats.h>

namespace android {
namespace hardware {
namespace google {
namespace pixel {
namespace powerstats {

class StateResidencyConfig {
  public:
    std::string name;
    std::string header;

    bool entryCountSupported;
    std::string entryCountPrefix;
    std::function<uint64_t(uint64_t)> entryCountTransform;

    bool totalTimeSupported;
    std::string totalTimePrefix;
    std::function<uint64_t(uint64_t)> totalTimeTransform;

    bool lastEntrySupported;
    std::string lastEntryPrefix;
    std::function<uint64_t(uint64_t)> lastEntryTransform;
};

class PowerEntityConfig {
  public:
    PowerEntityConfig(std::vector<StateResidencyConfig> stateResidencyConfigs);
    PowerEntityConfig(std::string header, std::vector<StateResidencyConfig> stateResidencyConfigs);
    std::string mHeader;
    std::vector<std::pair<uint32_t, StateResidencyConfig>> mStateResidencyConfigs;
};

class GenericStateResidencyDataProvider : public IStateResidencyDataProvider {
  public:
    GenericStateResidencyDataProvider(std::string path) : mPath(std::move(path)){};
    ~GenericStateResidencyDataProvider() = default;
    void addEntity(uint32_t id, PowerEntityConfig config);
    bool getResults(std::map<uint32_t, PowerEntityStateResidencyResult> &results) override;
    std::vector<PowerEntityStateSpace> getStateSpaces() override;

  private:
    std::string mPath;
    std::vector<std::pair<uint32_t, PowerEntityConfig>> mPowerEntityConfigs;
};

}  // namespace powerstats
}  // namespace pixel
}  // namespace google
}  // namespace hardware
}  // namespace android

#endif  // HARDWARE_GOOGLE_PIXEL_POWERSTATS_GENERICSTATERESIDENCYDATAPROVIDER_H