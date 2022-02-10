#pragma once

#include "customtypes/Injectable.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

#include "GlobalNamespace/QuestAppInit.hpp"
#include "GlobalNamespace/MainSettingsMenuViewControllersInstaller.hpp"
#include "GlobalNamespace/StandardGameplayInstaller.hpp"
#include "GlobalNamespace/MissionGameplayInstaller.hpp"
#include "GlobalNamespace/MultiplayerLocalPlayerInstaller.hpp"
#include "GlobalNamespace/TutorialInstaller.hpp"
#include "GlobalNamespace/MultiplayerCoreInstaller.hpp"
#include "GlobalNamespace/GameCoreSceneSetup.hpp"
#include "GlobalNamespace/MultiplayerConnectedPlayerInstaller.hpp"

namespace z::zenject {
    /// @brief Beat Saber specific locations, which points to a place install Zenject bindings.
    enum class Location {
        /// @brief Represents no binding.
        None = 0,

        /// @brief Installs your bindings in the app context. Anything installed here will be available in every container.
        App = 1,

        /// @brief Installs your bindings onto the menu.
        Menu = 2,

        /// @brief Installs your bindings onto the standard gameplay (Solo or Party) player
        StandardPlayer = 4,

        /// @brief Installs your bindings onto the campaign player.
        CampaignPlayer = 8,

        /// @brief Installs your bindings onto the local multiplayer player.
        Multi = 16,

        /// @brief Installs your bindings onto any player location (Standard, Campaign, or Multiplayer)
        Player = StandardPlayer | CampaignPlayer | Multi,

        /// @brief Installs your bindings onto the tutorial.
        Tutorial = 32,

        /// @brief Installs your bindings onto GameCore.
        /// @brief Anything specific to the game level will be installed here.
        ///        It does not necessarily guarantee that anything player specific (audio managers, saber stuff, note spawning stuff)
        ///        will be included. Some things you would expect to be in here would be the currently played map (difficulty beatmap).
        GameCore = 64,

        /// @brief Installs your bindings onto the Multiplayer Core.
        MultiplayerCore = 128,

        /// @brief Installs your bindings onto all Players related to singleplayer (Standard, Campaign, or Tutorial).
        SinglePlayer = StandardPlayer | CampaignPlayer | Tutorial,

        /// @brief Installs your bindings onto every connected player in multiplayer.
        ConnectedPlayer = 256
    };

    inline Location operator|(Location a, Location b)
    {return static_cast<Location>(static_cast<int>(a) | static_cast<int>(b));}

    inline Location operator&(Location a, Location b)
    {return static_cast<Location>(static_cast<int>(a) & static_cast<int>(b));}

    inline bool HasFlag(Location location, Location flag) {
        return (location & flag) == flag;
    }

    static std::unordered_set<Il2CppClass*> getInstallerForLocation(Location location) {
        using namespace GlobalNamespace;

        std::unordered_set < Il2CppClass * > installerTypes;

        if (HasFlag(location, Location::App))
            installerTypes.emplace(classof(QuestAppInit * ));
        if (HasFlag(location, Location::Menu))
            installerTypes.emplace(classof(MainSettingsMenuViewControllersInstaller * ));
        if (HasFlag(location, Location::StandardPlayer))
            installerTypes.emplace(classof(StandardGameplayInstaller * ));
        if (HasFlag(location, Location::CampaignPlayer))
            installerTypes.emplace(classof(MissionGameplayInstaller * ));
        if (HasFlag(location, Location::Multi))
            installerTypes.emplace(classof(MultiplayerLocalPlayerInstaller * ));
        if (HasFlag(location, Location::Tutorial))
            installerTypes.emplace(classof(TutorialInstaller * ));
        if (HasFlag(location, Location::GameCore))
            installerTypes.emplace(classof(GameCoreSceneSetup * ));
        if (HasFlag(location, Location::MultiplayerCore))
            installerTypes.emplace(classof(MultiplayerCoreInstaller * ));
        if (HasFlag(location, Location::ConnectedPlayer))
            installerTypes.emplace(classof(MultiplayerConnectedPlayerInstaller * ));

        return installerTypes;
    }
}
